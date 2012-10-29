@echo off
rm a.lst b.lst
echo nasm
nasm -l a.lst -f win64 test.asm
cat a.lst
echo yasm
yasm -l b.lst -f win64 test.asm
cat b.lst
