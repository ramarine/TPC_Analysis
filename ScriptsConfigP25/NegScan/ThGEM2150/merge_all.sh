#!/bin/bash

#SBATCH --job-name merge_num
#SBATCH --error Log/merge_num-error.e%A_%a
#SBATCH --output Log/merge_num-out.o%A_%a
#SBATCH --ntasks 1
#SBATCH --cpus-per-task 1
#SBATCH --partition shared-cpu
#SBATCH --time 0-03:00:00
#SBATCH --mem=12000

module load GCC/11.2.0  OpenMPI/4.1.1 ROOT/6.24.06 CMake/3.22.1
srun merge_num.sh "${SLURM_ARRAY_TASK_ID}" | tee Log/merge_num-stdout.txt
