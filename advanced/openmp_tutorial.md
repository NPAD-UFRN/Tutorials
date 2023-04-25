# Tutorial OpenMP

Veremos neste tutorial como executar um job contendo códigos escritos com OpenMP no supercomputador. OpenMP é um modelo de programação paralela para sistemas de memória compartilhada. Nesse modelo, o programa cria diversas threads que são coordenadas por um thread mestre. O programador define algumas seções do código como paralelas utilizando diretivas de preprocessamento específicas.

Os nós do supercomputador não compartilham memória. Por isso, não é possível executar em mais de um nó um job que utiliza somente OpenMP como ferramenta de programação parelela. Contudo, um programa escrito com OpenMP pode ser executado em múltiplos cores em um mesmo nó. Para que um job seja executado em vários nós, deve-se utilizar um modelo de programçáo paralela para sistemas de memória distribuída (e.g. MPI). Também é possível utilizar OpenMP e MPI em um mesmo código.

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

Em seguida, é necessário escrever um script para executar o programa.

```bash
#!/bin/bash 
#SBATCH --job-name=OMP_hello 
#SBATCH --time=0-0:5
#SBATCH --cpus-per-task=8
#SBATCH --hint=compute_bound
export OMP_NUM_THREADS=32

./hello_openmp
```

A descrição dos valores dos campos do script é informada abaixo:

job-name: Nome que aparecerá na fila de jobs
time: Tempo máximo para execução do job (neste exemplo = 5 min). Caso o job ainda não tenha terminado, após esse tempo ele será cancelado. Formato: dias-horas:minutos.

Note a configuração da variável de ambiente `OMP_NUM_THREADS` para 32. Isso controla quantas threads serão utilizadas nos jobs que usam OpenMP. Configurar essa variável para um número maior que 32 provavelmente não irá melhorar o desempenho do programa uma vez que cada nó do supercomputador possui 32 cores.

## Submissão de um job

Para enviar arquivos para o supercomputador recomenda-se utilizar o comando rsync.

```bash
aluno@ubuntu:~ $  rsync -azP -e "ssh -p 4422" ~/pastaLocal/{hello_openmp.c,run.slurm} seuUsuario@sc2.npad.ufrn.brr:~/pastaRemota
```

O acesso ao supercomputador pode ser feito através do protocolo SSH (Secure Shell).

```bash
aluno@ubuntu:~ $  ssh -p4422 nome_do_usuario@sc2.npad.ufrn.brr
```

Em seguida, acesse a pasta onde estão o código fonte em OpenMP e o script de execução.

```bash
[seuUsuario@service0 ~]$ cd pastaRemota/
```

Compile o código fonte com a flag de otimização "-O_" desejada. No exemplo abaixo, é utilizada a flag -O2 (a flag é habilitada pela letra "O" e não o número "0").

```bash
[seuUsuario@service0 ~]$ icc -O2 hello_openmp.c -o hello_openmp -openmp
```

### Flags de otimização

- **-O0** Desabilita todas as otimizações.

- **-O1** Habilita otimização para melhorar velocidade, entretanto desabilita  algumas otimizações que aumentam o tamanho do código e afetam a velocidade.

- **-O2** Habilita otimização para melhorar velocidade. Esse é o nível de otimização normalente recomendável e padrão para o icc. Vetorização é habilitada em O2 e níveis maiores.
- **-O3** Realiza otimizações O2 e habilita transformações de loop mais agressivos. Essas otimizações podem deixar o código mais lento em alguns casos quando comparados a O2. A opção O3 é recomendada para aplicações que têm loops que utilizam fortemente cálculos de ponto flutante e processam grandes conjuntos de dados.

Quanto maior o nível de otimização, mais liberdade o compilador terá para fazer suposições sobre o seu código, podendo produzir resultados indesejados.

Submeta o job.

```bash
[seuUsuario@service0 ~]$ sbatch run.slurm
```

O job entrará em uma fila para ser executado. Quando isso acontecer, será possível verificar as saídas que foram salvas nos arquivos configurados nas tags "--output" e "--error".

```bash
[seuUsuario@service0 ~]$ cat slurm.out

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
