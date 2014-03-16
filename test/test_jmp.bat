pushd ..\gen
call update
popd
cl -I../ -I./ -DXBYAK_TEST jmp.cpp %OPT% /Od /Zi
jmp
