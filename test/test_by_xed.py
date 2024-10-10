import re
import math
import sys

class Reg:
  def __init__(self, s):
    self.name = s
  def __str__(self):
    return self.name

g_regTbl = '''
eax ecx edx ebx esp ebp esi edi
ax cx dx bx sp bp si di
al cl dl bl ah ch dh bh
k1 k2 k3 k4 k5 k6 k7
rax rcx rdx rbx rsp rbp rsi rdi r8 r9 r10 r11 r12 r13 r14 r15
r16 r17 r18 r19 r20 r21 r22 r23 r24 r25 r26 r27 r28 r29 r30 r31
r8d r9d r10d r11d r12d r13d r14d r15d
r16d r17d r18d r19d r20d r21d r22d r23d r24d r25d r26d r27d r28d r29d r30d r31d
r8w r9w r10w r11w r12w r13w r14w r15w
r16w r17w r18w r19w r20w r21w r22w r23w r24w r25w r26w r27w r28w r29w r30w r31w
r8b r9b r10b r11b r12b r13b r14b r15b
r16b r17b r18b r19b r20b r21b r22b r23b r24b r25b r26b r27b r28b r29b r30b r31b
spl bpl sil dil
xmm0 xmm1 xmm2 xmm3 xmm4 xmm5 xmm6 xmm7
xmm8 xmm9 xmm10 xmm11 xmm12 xmm13 xmm14 xmm15
xmm16 xmm17 xmm18 xmm19 xmm20 xmm21 xmm22 xmm23
xmm24 xmm25 xmm26 xmm27 xmm28 xmm29 xmm30 xmm31
ymm0 ymm1 ymm2 ymm3 ymm4 ymm5 ymm6 ymm7
ymm8 ymm9 ymm10 ymm11 ymm12 ymm13 ymm14 ymm15
ymm16 ymm17 ymm18 ymm19 ymm20 ymm21 ymm22 ymm23
ymm24 ymm25 ymm26 ymm27 ymm28 ymm29 ymm30 ymm31
zmm0 zmm1 zmm2 zmm3 zmm4 zmm5 zmm6 zmm7
zmm8 zmm9 zmm10 zmm11 zmm12 zmm13 zmm14 zmm15
zmm16 zmm17 zmm18 zmm19 zmm20 zmm21 zmm22 zmm23
zmm24 zmm25 zmm26 zmm27 zmm28 zmm29 zmm30 zmm31
'''.split()

# define global constants
for e in g_regTbl:
  globals()[e] = Reg(e)

g_replaceCharTbl = '{}();|,'
g_replaceChar = str.maketrans(g_replaceCharTbl, ' '*len(g_replaceCharTbl))
g_sizeTbl = ['byte', 'word', 'dword', 'qword', 'xword', 'yword', 'zword']
g_attrTbl = ['T_sae', 'T_rn_sae', 'T_rd_sae', 'T_ru_sae', 'T_rz_sae'] #, 'T_z']
g_attrXedTbl = ['sae', 'rne-sae', 'rd-sae', 'ru-sae', 'rz-sae']

class Attr:
  def __init__(self, s):
    self.name = s
  def __str__(self):
    return self.name

for e in g_attrTbl:
  globals()[e] = Attr(e)

class Memory:
  def __init__(self, size=0, base=None, index=None, scale=0, disp=0):
    self.size = size
    self.base = base
    self.index = index
    self.scale = scale
    self.disp = disp

  def __str__(self):
    s = 'ptr' if self.size == 0 else g_sizeTbl[int(math.log2(self.size))]
    s += ' ['
    needPlus = False
    if self.base:
      s += str(self.base)
      needPlus = True
    if self.index:
      if needPlus:
        s += '+'
      s += str(self.index)
      if self.scale > 1:
        s += f'*{self.scale}'
      needPlus = True
    if self.disp:
      if needPlus:
        s += '+'
      s += hex(self.disp)
    s += ']'
    return s


  def __eq__(self, rhs):
    return str(self) == str(rhs)

def parseMemory(s):
  sizeTbl = {
    'byte': 1, 'word': 2, 'dword': 4, 'qword': 8,
    'xword': 16, 'yword': 32, 'zword': 64
  }

  s = s.replace(' ', '').lower()

  # Parse size
  size = 0
  for i in range(len(g_sizeTbl)):
    w = g_sizeTbl[i]
    if s.startswith(w):
      size = 1<<i
      s = s[len(w):]

  # Remove 'ptr' if present
  if s.startswith('ptr'):
    s = s[3:]

  # Extract the content inside brackets
  r = re.match(r'\[(.*)\]', s)
  if not r:
    raise ValueError(f'bad format {s=}')

  # Parse components
  elems = re.findall(r'([a-z0-9]+)(?:\*([0-9]+))?|([+-])', r.group(1))

  base = index = None
  scale = 0
  disp = 0

  for i, e in enumerate(elems):
    if e[2]: # This is a '+' or '-' sign
      continue

    if e[0].isalpha():
      if base is None and (not e[1] or int(e[1]) == 1):
        base = e[0]
      elif index is None:
        index = e[0]
        scale = int(e[1]) if e[1] else 1
      else:
        raise ValueError(f'bad format2 {s=}')
    else:
      sign = -1 if i > 0 and elems[i-1][2] == '-' else 1
      b = 16 if e[0].startswith('0x') else 10
      disp += sign * int(e[0], b)

  return Memory(size, base, index, scale, disp)

class Nmemonic:
  def __init__(self, name, args=[], attrs=[]):
    self.name = name
    self.args = args
    self.attrs = attrs
  def __str__(self):
    s = f'{self.name}('
    for i in range(len(self.args)):
      if i > 0:
        s += ', '
      s += str(self.args[i])
    for e in self.attrs:
      s += f'|{e}'
    s += ');'
    return s

def parseNmemonic(s):
  s = s.translate(g_replaceChar)

  # reconstruct memory string
  v = []
  inMemory = False
  for e in s.split():
    if inMemory:
      v[-1] += e
      if ']' in e:
        inMemory = False
    else:
      v.append(e)
      if e in g_sizeTbl or e == 'ptr':
        v[-1] += ' ' # to avoid 'byteptr'
        inMemory = True

  name = v[0]
  args = []
  attrs = []
  for e in v[1:]:
    if e.startswith('0x'):
      args.append(int(e, 16))
    elif e[0] in '0123456789':
      args.append(int(e))
    elif e in g_attrTbl:
      attrs.append(Attr(e))
    elif e in g_attrXedTbl:
      attrs.append(Attr(g_attrTbl[g_attrXedTbl.index(e)]))
    elif e in g_regTbl:
      args.append(e)
    else:
      args.append(parseMemory(e))
  return Nmemonic(name, args, attrs)

def loadFile(name):
  with open(name) as f:
    r = []
    for line in f.read().split('\n'):
      if line:
        if line[0] == '#':
          continue
        r.append(line)
    return r

# remove top 5 information
# e.g. XDIS 0: AVX512    AVX512EVEX 62F1E91858CB             vaddpd ymm1{rne-sae}, ymm2, ymm3
def removeExtraInfo(s):
  v = s.split()
  return ' '.join(v[5:])

def run(cppText, xedText):
  cpp = loadFile(cppText)
  xed = loadFile(xedText)
  for i in range(len(cpp)):
    line1 = cpp[i]
    line2 = removeExtraInfo(xed[i])
    m1 = parseNmemonic(line1)
    m2 = parseNmemonic(line2)

    assertEqualStr(m1, m2, f'{i}')
  print('run ok')

def assertEqualStr(a, b, msg=None):
  if str(a) != str(b):
    raise Exception(f'assert fail {msg}:', str(a), str(b))

def MemoryTest():
  tbl = [
    (Memory(0, rax), 'ptr [rax]'),
    (Memory(4, rax), 'dword [rax]'),
    (Memory(8, rax, rcx), 'qword [rax+rcx]'),
    (Memory(8, rax, rcx, 4), 'qword [rax+rcx*4]'),
    (Memory(8, None, rcx, 4), 'qword [rcx*4]'),
    (Memory(8, rax, None, 0, 5), 'qword [rax+0x5]'),
    (Memory(8, None, None, 0, 255), 'qword [0xff]'),
  ]
  for (m, expected) in tbl:
    assertEqualStr(m, expected)

def parseMemoryTest():
  print('parseMemoryTest')
  tbl = [
    ('[]', Memory()),
    ('[rax]', Memory(0, rax)),
    ('ptr[rax]', Memory(0, rax)),
    ('dword[rbx]', Memory(4, rbx)),
    ('xword ptr[rcx]', Memory(16, rcx)),
    ('xword ptr[rdx*8]', Memory(16, None, rdx, 8)),
    ('[12345]', Memory(0, None, None, 0, 12345)),
    ('[0x12345]', Memory(0, None, None, 0, 0x12345)),
    ('yword [rax+rdx*4]', Memory(32, rax, rdx, 4)),
    ('zword [rax+rdx*4+123]', Memory(64, rax, rdx, 4, 123)),
  ]
  for (s, expected) in tbl:
    my = parseMemory(s)
    assertEqualStr(my, expected)

def parseNmemonicTest():
  print('parseNmemonicTest')
  tbl = [
    ('vaddpd(ymm1, ymm2, ymm3 |T_rn_sae);', Nmemonic('vaddpd', [ymm1, ymm2, ymm3], [T_rn_sae])),
    ('vaddpd ymm1{rne-sae}, ymm2, ymm3', Nmemonic('vaddpd', [ymm1, ymm2, ymm3], [T_rn_sae])),
    ('mov(rax, dword ptr [rcx + rdx * 8 ] );', Nmemonic('mov', [rax, Memory(4, rcx, rdx, 8)])),
    ('mov(rax, ptr [rcx + rdx * 8 ] );', Nmemonic('mov', [rax, Memory(0, rcx, rdx, 8)])),
    ('vcmppd(k1, ymm2, ymm3 |T_sae, 3);', Nmemonic('vcmppd', [k1, ymm2, ymm3, 3], [T_sae])),
    ('vcmppd k1{sae}, ymm2, ymm3, 0x3', Nmemonic('vcmppd', [k1, ymm2, ymm3, 3], [T_sae])),
  ]
  for (s, expected) in tbl:
    e = parseNmemonic(s)
    assertEqualStr(e, expected)

def test():
  print('test start')
  MemoryTest()
  parseMemoryTest()
  parseNmemonicTest()
  print('test end')

def main():
  if len(sys.argv) == 2 and sys.argv[1] == 'test':
    test()
  elif len(sys.argv) == 3:
    run(sys.argv[1], sys.argv[2])
  else:
    print(f'{__name__} <cpp-text> <xed-text> # compare cpp-text and xed-text generated by xed')
    print(f'{__name__} test # for test')

if __name__ == '__main__':
  main()
