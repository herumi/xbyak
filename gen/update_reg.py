#!/usr/bin/env python3
# Update the three derived register-definition sections in xbyak.h from the
# master section (the static constexpr one in #ifdef XBYAK_INLINE_VARIABLE).
# The four sections are delimited by "@regDefBegin" and "@regDefEnd" and
# appear in this order:
#   1. master        : static constexpr Type name{args}, ...;  (hand-written)
#   2. member decls  : const Type name, ...;                   (generated)
#   3. ctor init list: , name(args), ...                       (generated)
#   4. util namespace: static const XBYAK_CONSTEXPR Type name(args), ...;
import argparse
import os
import re

BEGIN = '@regDefBegin'
END = '@regDefEnd'

# xm0..zm31 are copies of xmm0..zmm31 in the master section, but references in
# the member-declaration and constructor sections, and absent in util.
ALIAS_RE = re.compile(r'^[xyz]m\d+$')
DECL_RE = re.compile(r'^\t?static constexpr (\w+) (.+?);(\s*//.*)?$')


def split_declarators(s):
    """'a{0}, b{1, true}' -> [('a', '0'), ('b', '1, true')]"""
    decls = []
    depth = 0
    token = ''
    for c in s + ',':
        if c == ',' and depth == 0:
            token = token.strip()
            m = re.match(r'^(\w+)\{(.*)\}$', token)
            if not m:
                raise SystemExit(f'cannot parse declarator: {token!r}')
            decls.append((m.group(1), m.group(2).strip()))
            token = ''
        else:
            if c == '{':
                depth += 1
            elif c == '}':
                depth -= 1
            token += c
    return decls


def parse_master(lines):
    """Return a list of items: ('pp', line), ('comment', line) or
    ('decl', type, [(name, args)...], trailing_comment, is_alias)."""
    items = []
    for line in lines:
        stripped = line.strip()
        if stripped.startswith('#'):
            items.append(('pp', stripped))
        elif stripped.startswith('//'):
            items.append(('comment', stripped))
        else:
            m = DECL_RE.match(line)
            if not m:
                raise SystemExit(f'cannot parse line: {line!r}')
            type_, body, comment = m.group(1), m.group(2), m.group(3)
            decls = split_declarators(body)
            is_alias = type_ in ('Xmm', 'Ymm', 'Zmm') and all(ALIAS_RE.match(name) for name, _ in decls)
            items.append(('decl', type_, decls, comment.strip() if comment else '', is_alias))
    return items


def gen_member_decl(items):
    out = []
    for item in items:
        if item[0] in ('pp', 'comment'):
            out.append(item[1] if item[0] == 'pp' else '\t' + item[1])
            continue
        _, type_, decls, comment, is_alias = item
        ref = '&' if is_alias else ''
        names = ', '.join(ref + name for name, _ in decls)
        tail = ' ' + comment if comment else ''
        out.append(f'\tconst {type_} {names};{tail}')
    return out


def gen_ctor_init(items):
    out = []
    for item in items:
        if item[0] == 'pp':
            out.append(item[1])
            continue
        if item[0] == 'comment':
            out.append('\t\t' + item[1])
            continue
        _, type_, decls, comment, is_alias = item
        if is_alias:
            # xm0 -> reference to xmm0
            inits = ', '.join(f'{name}({name[0]}m{name[1:]})' for name, _ in decls)
        else:
            inits = ', '.join(f'{name}({args})' for name, args in decls)
        out.append(f'\t\t, {inits}')
    return out


def gen_util(items):
    out = []
    for i, item in enumerate(items):
        if item[0] == 'pp':
            out.append(item[1])
            continue
        if item[0] == 'comment':
            # drop a comment which annotates an alias line (aliases are not in util)
            nexts = [x for x in items[i + 1:] if x[0] == 'decl']
            if nexts and nexts[0][4]:
                continue
            out.append(item[1])
            continue
        _, type_, decls, comment, is_alias = item
        if is_alias:
            continue
        # 'name' without parentheses if no argument (T_z() would declare a function)
        body = ', '.join(f'{name}({args})' if args else name for name, args in decls)
        tail = ' ' + comment if comment else ''
        out.append(f'static const XBYAK_CONSTEXPR {type_} {body};{tail}')
    return out


def find_sections(lines):
    """Return [(begin_idx, end_idx)] of lines between markers (exclusive)."""
    sections = []
    begin = -1
    for i, line in enumerate(lines):
        if BEGIN in line:
            if begin >= 0:
                raise SystemExit(f'nested {BEGIN} at line {i + 1}')
            begin = i
        elif END in line:
            if begin < 0:
                raise SystemExit(f'unmatched {END} at line {i + 1}')
            sections.append((begin + 1, i))
            begin = -1
    if begin >= 0:
        raise SystemExit(f'unclosed {BEGIN}')
    return sections


def main():
    parser = argparse.ArgumentParser(description='update register-definition sections in xbyak.h')
    parser.add_argument('file', nargs='?', default=os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'xbyak', 'xbyak.h'))
    parser.add_argument('-c', '--check', action='store_true', help="don't write, exit 1 if update is needed")
    args = parser.parse_args()

    with open(args.file) as f:
        lines = f.read().splitlines()
    sections = find_sections(lines)
    if len(sections) != 4:
        raise SystemExit(f'expected 4 {BEGIN}/{END} sections, found {len(sections)}')

    items = parse_master(lines[sections[0][0]:sections[0][1]])
    bodies = [gen_member_decl(items), gen_ctor_init(items), gen_util(items)]
    # replace from the last section to keep indices valid
    new_lines = lines[:]
    for (begin, end), body in reversed(list(zip(sections[1:], bodies))):
        new_lines[begin:end] = body

    if new_lines == lines:
        print(f'{args.file}: up to date')
        return
    if args.check:
        raise SystemExit(f'{args.file}: needs update (run gen/update_reg.py)')
    with open(args.file, 'w') as f:
        f.write('\n'.join(new_lines) + '\n')
    print(f'{args.file}: updated')


if __name__ == '__main__':
    main()
