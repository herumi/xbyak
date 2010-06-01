pushd ..\gen
call update
popd
cl -I../ -DXBYAK_TEST jmp.cpp %OPT%
jmp
