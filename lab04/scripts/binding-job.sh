#!/bin/bash

#SBATCH --job-name=test
#SBATCH --output=test-%j.out
#SBATCH --error=test-%j.err

#SBATCH --partition training
#SBATCH --gres=gpu
#SBATCH --mem-per-cpu=4gb
#SBATCH --nodes 1
#SBATCH --time=00:01:00
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=32

srun -N 1 hostname

gcc ../src/Thread_num.c -o ../src/make/Thread_num.out -fopenmp

export OMP_NUM_THREADS=32
#export OMP_PLACES=sockets
export OMP_PROC_BIND=false

../src/make/Thread_num.out > ../experiments/threads_id.out
