@echo off
echo 64bit
set TARGETS=avx512.txt bf16.txt misc.txt convert.txt minmax.txt saturation.txt amx.txt apx.txt comp.txt avx512old.txt ace_1.txt
for %%f in (%TARGETS%) do (
  echo %%f
  call test_by_xed.bat dataset\%%f
)
echo 32bit
set TARGETS=avx512old-32.txt
for %%f in (%TARGETS%) do (
  echo %%f
  call test_by_xed.bat -32 dataset\%%f
)
