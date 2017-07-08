#!/bin/bash
#SBATCH --job-name=MPI_hello  
#SBATCH --output=saida%j.out
#SBATCH --error=erro%j.err
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=2
#SBATCH --cpus-per-task=1
#SBATCH --time=0-0:5

srun mpi_hello