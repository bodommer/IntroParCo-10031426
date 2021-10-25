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

srun -N 1 hostname

sse

gcc ../src/Array_malloc.c -o ../src/Array_malloc.out -ftree-vectorize -msse3 -mfpmath=sse -ftree-vectorizer-verbose=5 -fopt-info-vec-missed=output.miss -funroll-loops

gcc ../src/Array_malloc.c -o ../src/Array_no_vec.out

for i in [ 256 512 1024 2048 4096 8192 16384 32768 65536 131072 ] 
do
	../src/Array_malloc.out $i >> vec.out
	sleep 2
	../src/Array_no_vec.out $i >> no_vec.out
done
