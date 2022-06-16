#!/bin/bash

make -C ../ test_util64

cpus=(p4p mrm pnr nhm wsm snb ivb hsw bdw slt slm glm glp tnt skl cnl icl skx clx cpx icx knl knm tgl adl spr)
for cpu in ${cpus[@]} ; do
  echo $cpu
  ~/bin/sde -$cpu -- ../test_util64 -cpuid > $cpu.txt
done

