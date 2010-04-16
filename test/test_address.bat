@echo off
if /i "%1"=="64" (
	set OPT2=-DXBYAK64
	set OPT3=win64
) else (
	set OPT2=
	set OPT3=win32
)

pushd ..\gen
call update
popd

if /i "%1"=="64" (
	call :sub 1
	call :sub 2
) else (
	call :sub 1
)
goto end

:sub
cl address.cpp %OPT% %OPT2%
address %1% > a.asm
nasm -f %OPT3% -l a.lst a.asm
awk "{print $3}" < a.lst > ok.lst
address %1% jit > nm.cpp
cl -I../ -DTEST_NM nm_frame.cpp %OPT% %OPT2%
nm_frame > x.lst
diff x.lst ok.lst
wc x.lst

:end
