#!/bin/bash

#SBATCH --job-name analyze_num
#SBATCH --error Log/analyze_num-error.e%A_%a
#SBATCH --output Log/analyze_num-out.o%A_%a
#SBATCH --ntasks 1
#SBATCH --cpus-per-task 1
#SBATCH --partition public-cpu
#SBATCH --mem=12000
#SBATCH --time 0-02:00:00


ml GCC/11.2.0  OpenMPI/4.1.1 ROOT/6.24.06 CMake/3.22.1


srun analyze_num.sh "${SLURM_ARRAY_TASK_ID}" | tee Log/analyze_num-stdout.txt
