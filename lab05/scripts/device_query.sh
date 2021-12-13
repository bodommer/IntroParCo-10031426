#!/bin/bash

#SBATCH --job-name=hello-cuda
#SBATCH --output=hello-cuda-%j.out
#SBATCH --error=hello-cuda-%j.err

#SBATCH --partition training
#SBATCH --gres=gpu
#SBATCH --nodes 1
#SBATCH --time=00:10:00

#SBATCH --ntasks=1

module load cuda-11.2.1
module load gcc-6.5.0
#hostname

#echo "Size; Block; Time (microseconds)" > sum-time.out

#nvcc ../src/sum.cu -o ../src/output/sum -lm

#for i in  18 20
#do
#	for j in 128 256 512 1024
#	do
		srun -N 1 ../src/output/deviceQuery >> device-query.out
#	done
#done
