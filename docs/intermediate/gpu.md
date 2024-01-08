# Uso da GPU

O NPAD dispõe de duas partições para uso da GPU: A gpu-4-a100 com 4 GPUS e a gpu-8-v100 com 8 GPUS. Consulte a página de [Hardware](http://npad.ufrn.br/hardware.php) para mais informações sobre estas GPUS.

Para requisitar uma ou mais gpus para um job, utilize a diretiva ```gpus-per-node```.

Um exemplo de script de job para usar duas GPUs da partição gpu-8-v100:

```bash
#!/bin/bash
#SBATCH --partition=gpu-8-v100 
#SBATCH --gpus-per-node=2   # Número GPUs por nó
#SBATCH --time=3:00

./meuprograma # use nvidia-smi para teste
```

Exemplo de script para um job com múltiplos threads usando a partição gpu-4-a100

```bash
#!/bin/bash
#SBATCH --partition=gpu-4-a100 
#SBATCH --gpus-per-node=1  # Número GPUs por nó
#SBATCH --cpus-per-task=6        
#SBATCH --time=0-03:00
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./meuprograma
```

## Uso do Pytorch

O Pytorch para uso em GPUS está instalado no ambiente conda gpu. Você pode ativá-lo com
```bash
$ conda activate gpu
```

É importante saber que o Pytorch usa somente uma GPU por default. Para usar múltiplas GPU veja a discussão na seção seguinte que também serve para o software TensorFlow.

## Treinamento da rede neural usando múltiplas GPUs

Há duas maneiras básicas (que podem ser combinadas) de realizar um treinamento da rede neural com múltiplas GPUs: paralelismo de dados e paralelismo de modelo.

No paralelismo de dados o modelo da rede neural é replicado em cada GPU e cada réplica processa um diferente "batch" de dados. Em seguida, os resultados são reunidos. Pytorch dispõe de classes que facilitam a implementação deste método. Veja mais em:

- [Data Parallelism](https://pytorch.org/tutorials/beginner/blitz/data_parallel_tutorial.html)

- [Multi-GPU Examples](https://pytorch.org/tutorials/beginner/former_torchies/parallelism_tutorial.html)

- [Getting started with distributed data parallel](https://pytorch.org/tutorials/intermediate/ddp_tutorial.html#getting-started-with-distributed-data-parallel)

No paralelismo de modelo diferentes partes de um mesmo modelo de rede neurais são executadas em diferentes GPUS, mas processando o mesmo "batch" de dados. Veja mais em:

- [Model Parallel](https://pytorch.org/tutorials/intermediate/model_parallel_tutorial.html)

