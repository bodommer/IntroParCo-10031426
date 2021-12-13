#!/bin/bash

#SBATCH --job-name=test
#SBATCH --output=test-%j.out
#SBATCH --error=test-%j.err

#SBATCH --partition training
#SBATCH --gres=gpu
#SBATCH --mem-per-cpu=4gb
#SBATCH --nodes 1
#SBATCH --time=00:10:00
#SBATCH --ntasks=1

gcc ../src/own_reduction.c -o ../src/output/own_reduction.out -fopenmp -lm

for i in 256 512 1024 2048 4096 8192 16384 32768 65536 131072 
#for i in 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576 2098152 4194304 8388608 16777216 33554432
do
	for j in 2 4 8 16
	#for j in 8
	do
		export OMP_NUM_THREADS=$j
		../src/output/own_reduction.out $i >> ../experiments/own_reduction_$j.out
		sleep 2
	done
done
