#!/bin/bash
foldername=$( sed "${1}q;d" filenames.txt )
echo $foldername
dir="/home/amarinei/Year1_PhD/TPC/Comissioning/TPC_Ana/LeCroyPMT_Ana/Swan_Data/Configuration_18/""$foldername"
echo $dir
    if [ -s $dir"/binary_dat" ]; then
	root -b -q -l 'GeneralAna_v6.C("'$foldername'/")'
    fi
