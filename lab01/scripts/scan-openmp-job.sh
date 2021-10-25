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

gcc ../src/Scan_openmp_vec.c -o ../src/Scan_openmp_vec.out -ftree-vectorize -msse3 -mfpmath=sse -ftree-vectorizer-verbose=5 -fopt-info-vec-missed=output.miss -funroll-loops

gcc ../src/Scan_openmp.c -o ../src/Scan_openmp.out

for i in [ 256 512 1024 2048 4096 8192 16384 32768 65536 131072 ] 
do
	../src/Scan_openmp_vec.out $i >> scan_openmp_vec.out
	sleep 2
	../src/Scan_openmp.out $i >> scan_openmp.out
done
