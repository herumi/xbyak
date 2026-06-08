#!/bin/bash

: "${SDE:=sde64}"

UPDATE=0
if [ $# -eq 1 ]; then
UPDATE=1
fi

if [ $UPDATE == 1 ]; then
  echo "UPDATE"
fi

make -C ../ test_util64

cpus=(p4p mrm pnr nhm wsm snb ivb hsw bdw slt slm glm glp tnt skl cnl icl skx clx cpx icx tgl adl mtl rpl spr emr gnr dmr srf arl lnl ptl nvl cwf)

for cpu in ${cpus[@]} ; do
  echo $cpu
  if [ $UPDATE == 1 ]; then
    ${SDE} -$cpu -- ../test_util64 -cpuid > $cpu.txt
  else
    ${SDE} -$cpu -- ../test_util64 -cpuid > tmp.txt
    diff $cpu.txt tmp.txt
  fi
done

