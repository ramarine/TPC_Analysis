while read p; do
  root -b -q -l 'GeneralAna_v7.C("'$p'")'
done <filenames.txt
