In order to run GeneralAna_v6 on all the directories you need to you need two files. 

filenames.txt > this contains the folders which for which you want to run GeneralAna_v6.C

READM_RunBatch_CreateAllTTrees.sh   > this call a script (analyze_num.sh) which in fact runs GeneralAna_v6.C over all the folders we. 

analyze_num -> this sets the argument which is fed into GeneralAna_v6.C('argunet')


//----------------------------//


In order to run a batch job on slurm you simply have to do this command:

sbatch --array=1-100%4 RunBatch_CreateAllTTrees.sh


//----------------------------//


Check the status: 

scontrol show Job=60407288

show jobid 60407288


// --------------------------//

To cancel jobs: scancel <jobid>

To cancel all jobs: scancel --user=amarinei --state=pending


