pushd ..\gen
call update
popd
cl -I../ -DTEST_NM jmp.cpp %OPT%
jmp
