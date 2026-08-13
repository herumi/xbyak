#!/usr/bin/env python3
import sys

BEGIN = '@@@begin of avx_type_def.h'
END = '@@@end of avx_type_def.h'

def main():
	src = sys.argv[1] if len(sys.argv) > 1 else '../xbyak/xbyak.h'
	dst = sys.argv[2] if len(sys.argv) > 2 else 'avx_type_def.h'
	lines = []
	inside = False
	with open(src, 'r') as f:
		for line in f:
			line = line.rstrip('\n')
			if BEGIN in line:
				inside = True
			if inside:
				lines.append(line)
			if END in line:
				if not inside:
					print('ERR:%s appears before %s in %s' % (END, BEGIN, src))
					return 1
				inside = False
				break
	if not lines:
		print('ERR:%s is not found in %s' % (BEGIN, src))
		return 1
	if inside:
		print('ERR:%s is not found in %s' % (END, src))
		return 1
	# keep LF so that the file is identical to the one made by sed
	with open(dst, 'w', newline='\n') as f:
		f.write('\n'.join(lines) + '\n')
	return 0

if __name__ == '__main__':
	sys.exit(main())
