set TARGETS=old.txt bf16.txt misc.txt convert.txt minmax.txt saturation.txt amx.txt apx.txt comp.txt
for %%f in (%TARGETS%) do (
  echo %%f
  call test_by_xed.bat dataset\%%f
)
