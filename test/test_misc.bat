pushd ..\gen
call update
popd
cl -I../ -I./ -DXBYAK_TEST misc.cpp %OPT% /Od /Zi
misc
