#!/bin/bash

#SBATCH --job-name=test
#SBATCH --output=test-%j.out
#SBATCH --error=test-%j.err

#SBATCH --partition training
#SBATCH --gres=gpu
#SBATCH --mem-per-cpu=4gb
#SBATCH --nodes 1
#SBATCH --time=00:02:00
#SBATCH --ntasks=1

gcc ../src/Scan_openmp.c -o ../src/make/Scan_openmp.out -fopenmp

for i in 256 512 1024 2048 4096 8192 16384 32768 65536 131072 
#for i in 65536
do
	for j in 2 4 8 16
	#for j in 8
	do
		export OMP_NUM_THREADS=$j
		../src/make/Scan_openmp.out $i >> ../experiments/scan_openmp_$j.out
		sleep 2
	done
done
