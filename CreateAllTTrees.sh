#!/bin/bash
#root -b -q -l 'GeneralAna_v6.C("C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh0_TPC1650_a/")'
for dir in /home/amarinei/Year0_PhD/TPC/Comissioning/TPC_Ana/LeCroyPMT_Ana/Swan_Data/Configuration_18/*/; do
    if [ -s $dir"binary_dat" ]; then
	name=${dir:91:-1}
	root -b -q -l 'GeneralAna_v6.C("'$name'/")'
    fi
done
