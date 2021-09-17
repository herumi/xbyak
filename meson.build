# SPDX-FileCopyrightText: 2021 Andrea Pappacoda
#
# SPDX-License-Identifier: BSD-3-Clause

project(
	'xbyak',
	'cpp',
	version: '6.00',
	license: 'BSD-3-Clause',
	default_options: 'b_ndebug=if-release'
)

install_subdir('xbyak', install_dir: get_option('includedir'))

xbyak_dep = declare_dependency(include_directories: include_directories('.'))

if meson.version().version_compare('>=0.54.0')
	meson.override_dependency('xbyak', xbyak_dep)
endif

import('pkgconfig').generate(
	name: 'xbyak',
	description: 'JIT assembler for x86(IA32), x64(AMD64, x86-64)',
	version: meson.project_version(),
	url: 'https://github.com/herumi/xbyak'
)
