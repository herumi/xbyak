@echo off
echo 32bit
rm a.lst
echo nasm
nasm -l a.lst -f win32 -DWIN32 test.asm
cat a.lst
echo yasm
yasm -l a.lst -f win32 -DWIN32 test.asm
cat a.lst
