# Tutorial de OpenMP

Veremos neste tutorial como executar um job contendo códigos escritos com OpenMP no supercomputador. OpenMP é um modelo de programação paralela para sistemas de memória compartilhada. Nesse modelo, o programa cria diversas threads que são coordenadas por um thread mestre. O programador define algumas seções do código como paralelas utilizando diretivas de preprocessamento específicas.

Os nós do supercomputador não compartilham memória. Por isso, não é possível executar em mais de um nó um job que utiliza somente OpenMP como ferramenta de programação paralela. Contudo, um programa escrito com OpenMP pode ser executado em múltiplos cores em um mesmo nó. Para que um job seja executado em vários nós, deve-se utilizar um modelo de programação paralela para sistemas de memória distribuída (e.g. MPI). Também é possível utilizar OpenMP e MPI em um mesmo código.

## Exemplo: Hello World

```c
//Arquivo hello_openmp.c 
#include <omp.h> 
#include <stdio.h>
int main (int argc, char *argv[]) 
{ 
 int nthreads, thread_id; 
 #pragma omp parallel private(nthreads, thread_id) 
 { 
  thread_id = omp_get_thread_num();
  printf("Thread %d says: Hello World\n", thread_id); 
  if (thread_id == 0)
  { 
   nthreads = omp_get_num_threads();
   printf("Thread %d reports: the number of threads are %d\n", thread_id, nthreads); 
  } 
 } 
 return 0; 
}
```

Em seguida, é necessário escrever um script de job para executar o programa. Por exemplo:

```bash
#!/bin/bash 
#SBATCH --job-name=OMP_hello 
#SBATCH --time=0-0:5
#SBATCH --cpus-per-task=8 

./hello_openmp
```

A descrição dos valores das diretivas do script é informada abaixo:

- ``--job-name``: Nome que aparecerá na fila de jobs
- ``--time``: Tempo máximo para execução do job (neste exemplo = 5 min). Caso o job ainda não tenha terminado, após esse tempo ele será cancelado. Formato: dias-horas:minutos.
- ``--cpus-per-task``: Significa que foi solicitado oito processadores para o programa hello_openmp.  

O Slurm considera que cada core tem dois processadores. Na verdade, esses dois processadores são threads de hardware. Para fazer com que o Slurm considere cada core como sendo um só processador use a diretiva ``--hint=compute_bound``.

Em programas OpenMP, usa-se a variável de ambiente `OMP_NUM_THREADS` para especificar explicitamente o número de threads do programa. Você pode usar a variável de ambiente `SLURM_CPUS_PER_TASK` para definir `OMP_NUM_THREADS`. Por exemplo:

```bash
#!/bin/bash 
#SBATCH --job-name=OMP_hello 
#SBATCH --time=0-0:5
#SBATCH --cpus-per-task=8 
#SBATCH --hint=compute_bound

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./hello_openmp
```

Note que configurar `OMP_NUM_THREADS` para um número maior que `cpus-per-task` provavelmente não irá melhorar o desempenho do programa porque forçará as threads do programa a compartilhar os recursos do mesmo processador. Em geral, para melhor desempenho, deve-se alocar um processador para cada thread do programa.

## Submissão de um job

Edite o arquivo ``hello_openmp.c`` com seu editor favorito e [transfira para o supercomputador](../beginner/superpc_introduction_part_1.md#acessando-arquivos-do-supercomputador). Acesse o supercomputador e compile o programa:

```bash
gcc -g -Wall -fopenmp -o hello_openmp hello_openmp.c
```

Na mesma forma, crie o script de job ``script_job.sh``. Então submeta o job:

```bash
$ sbatch script_job.sh

Submitted batch job JOBID
```

JOBID é número do job. O job entrará em uma fila para ser executado. Quando isso acontecer, o saída do programa será gravada no arquivo slurm-JOBID.out. Então, é possível verificar a saída com o seguinte comando:

```bash
$ cat slurm-JOBID.out

  Thread 0 says: Hello Word!

  Thread 0 reports: the number of threads are 8

  Thread 7 says: Hello Word!

  Thread 4 says: Hello Word!

  Thread 6 says: Hello Word!

  Thread 1 says: Hello Word!

  Thread 3 says: Hello Word!

  Thread 5 says: Hello Word!

  Thread 2 says: Hello Word!
```
