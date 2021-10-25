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

gcc ../src/thread_count.c -o ../src/thread_count.out -fopenmp

export OMP_NUM_THREADS=16

../src/thread_count.out >> thread_count.out
