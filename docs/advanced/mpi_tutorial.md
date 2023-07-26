# Tutorial de MPI

Nesse tutorial iremos aprender a conduzir a execução de aplicações utilizando o Intel MPI no supercomputador, uma das melhores implementações MPI da indústria, de maneira simples e prática.

O MPI é um padrão de troca de mensagens para uso em computação paralela, oferecendo uma infraestrutura para a criação de programas que utilizem recursos de CPU e memória de múltiplos computadores em um cluster ou nós em um supercomputador, além de permitir a passagem coordenada de mensagens entre processos.

Definindo um padrão industrial para a troca de mensagens, existem diversas implementações do MPI. Iremos utilizar o Intel MPI juntamente com o gerenciador de recursos SLURM de acordo com os passos a seguir:

1. Conexão ao supercomputador por SSH
2. Criação de um programa MPI
3. Compilação do programa MPI
4. Execução do programa no supercomputador

## Passo 1: Conexão ao supercomputador por SSH

Para se conectar ao supercomputador é necessário utilizar o SSH já disponível por padrão na maioria dos sistemas Unix como nas distribuições Linux e todas as versões do Mac OS X assim como disponível livremente na Internet como download para a plataforma Windows. O cliente SSH mais popular da plataforma Windows é o [Putty](../beginner/putty_tutorial.md)

Iremos nesse tutorial utilizar como padrão a plataforma Linux, mas sua execução no Windows segue os mesmos princípios.

Para se conectar no nó de login do supercomputador basta executar o seguinte comando:

```bash
$ ssh -p 4422 USUARIO@sc2.npad.ufrn.br
```

Troque **USUARIO** pelo seu nome de usuário já autorizado. Você deve visualizar uma tela com notícias sobre o supercomputador e a criação dos seus diretórios pessoais.

Nesse momento você já está conectado ao supercomputador no ambiente Linux da máquina em sua área pessoal de arquivos. Todos os comandos padrão da distribuição CentOS assim como alguns editores de texto como o 'Emacs' e 'Vi' estão disponíveis para que você possa manipular seus arquivos e pastas pessoais. Nesse momento você já está conectado ao supercomputador no ambiente Linux da máquina em sua área pessoal de arquivos. Todos os comandos padrão da distribuição CentOS assim como alguns editores de texto como o 'Emacs' e 'Vi' estão disponíveis para que você possa manipular seus arquivos e pastas pessoais.

## Passo 2: Criação de um programa MPI

O esqueleto de um programa MPI é estruturado da seguinte forma:

- Inclusão do cabeçalho mpi.h e dos demais cabeçalhos necessários ao programa
- Início do programa indicado pela linha de código "int main (int argc, char *argv[])"
- Código sequencial opcional, por exemplo: inicialização de variáveis
- Inicialização do código paralelo indicado pela linha de código "MPI_Init(&argc, &argv);"
- Leitura da quantidade de processos criados indicado pela linha de código "MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);"
- Leitura do rank do processo utilizado, indicado pela linha de código "MPI_Comm_rank(MPI_COMM_WORLD, &comm_sz);"
- Código paralelo
- Finalização do código paralelo indicado pela linha de código "MPI_Finalize();"
- Código sequencial opcional e finalização do programa

Um exemplo de programa MPI é ilustrado abaixo. Copie esse programa para um arquivo na sua pasta pessoal e salve com o nome "mpi_hello.c". A função desse programa é imprimir uma mensagem de forma paralela a partir de processos diferentes. Esses processos podem estar no mesmo nó, utilizando diferentes núcleos, ou podem estar em nós diferentes. Essa escolha é feita pelo usuário a partir dos parâmetros utilizados no script de submissão que será mostrado numa seção (ou passo) posterior.

```c
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main (int argc, char *argv[])
{
  int  rank, comm_sz, len;
  char hostname[MPI_MAX_PROCESSOR_NAME];
  
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Get_processor_name(hostname, &len);
  printf ("Hello from process %d on node %s!\n", rank, hostname);
  if (rank == 0)
    printf("From process %d: Number of MPI processes is %d\n", rank, comm_sz);

  MPI_Finalize();
}
```

## Passo 3: Compilação do programa MPI

De posse do arquivo `mpi_hello.c`, você pode compilar o mesmo com o comando “mpiicc” da seguinte forma:

```bash
$ mpiicc mpi_hello.c -o mpi_hello 
$ ls 
mpi_hello.c   mpi_hello
```

A compilação gerou com sucesso o arquivo binário “mpi_hello” que será executado em vários núcleos de processadores do supercomputador no próximo passo.

## Passo 4: Execução do programa no supercomputador

No supercomputador é utilizado o gerenciador de recursos SLURM para se executar tarefas em diversos processadores da máquina. Tradicionalmente usuários do MPI utilizam o comando “mpirun” ou “mpiexec”, mas no nosso ambiente iremos utilizar o SLURM com o comando “sbatch” que recebe um script bash contendo configurações específicas sobre os recursos desejados, assim como que programa será executado pela sua tarefa. Esse script é chamado oficialmente de “Job submission file”.

### Exemplo de script mais simples

Para executar 4 tarefas do programa “mpi_hello” devemos criar um script chamado, por exemplo, de “jobMPI.sh” com o conteúdo abaixo:

```bash
#!/bin/bash

srun --time=0-0:5 -n4 mpi_hello
```

Para enviar esse “job” para a fila de execução usamos o comando:

```bash
$ sbatch jobMPI.sh 

Submitted batch job 2230
```

Esse comando irá adicionar o “job” na fila de execução e retornar um id (nesse caso 2230) dessa nova tarefa adicionada. Para monitorar a tarefa você pode usar o comando `squeue` para visualizar todas as tarefas em andamento. Se desejar cancelar uma tarefa em execução utilize o comando `scancel JOB_ID`.

Ao finalizar sua execução o SLURM cria automaticamente um arquivo chamado “slurm-JOB_ID.out” com a saída padrão de sua tarefa redirecionada para esse arquivo. O nome do arquivo contém o ID do job enviado (JOB_ID) para facilitar sua relação com o mesmo. Isso é importante se seu programa gera uma saída padrão que contém um resultado útil da sua execução. Veja abaixo o resultado da execução do simples script que criamos e sua saída em arquivos:

```bash
$ sbatch jobMPI.sh 

Submitted batch job 2230

$ cat slurm-2230.out 

Hello from process 3 on node r1i2n16!

Hello from process 2 on node r1i2n16!

Hello from process 1 on node r1i2n16!

Hello from process 0 on node r1i2n16!

From process 0: Number of MPI processes is 4
```

Repare que todas as 4 tarefas foram executadas no mesmo nó (neste caso o r1i2n16), pois o SLURM só foi instruído para executar 4 tarefas e nada mais.

### Exemplo de script mais detalhado

Um exemplo de script que solicita que 4 tarefas do programa “mpi_hello” executem em 2 nós diferentes é mostrado abaixo:

```bash
#!/bin/bash
#SBATCH --job-name=MPI_hello  
#SBATCH --output=saida%j.out
#SBATCH --error=erro%j.err
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=2
#SBATCH --cpus-per-task=1
#SBATCH --time=0-0:5

srun mpi_hello
```

Repare que agora o script contém vários parâmetros que foram adicionados. A descrição desses parâmetros é informada abaixo:

- `job-name`: Nome que aparecerá na fila de jobs
- `output`: Arquivo de saída padrão do programa
- `error`: Arquivo de saída de erro do programa
- `nodes`: Quantidade de nós alocados para o programa
- `ntasks-per-node`: Número de processos em um mesmo nó (normalmente 1 para jobs OpenMP) - Útil para jobs MPI
- `cpus-per-task`: Número de núcleos de CPU alocados para um processo do programa
- `time`: Tempo máximo para execução do job (nesse exemplo = 5 min). Caso o job ainda não tenha terminado, após esse tempo ele será cancelado. Formato: dias-horas:minutos

Observa-se, então, que foram requisitados 2 (valor de --nodes) nós para os jobs e que em cada nó serão criados 2 (valor de --ntasks-per-node) processos. O comando “srun mpi_hello” agora não deve mais conter o número de tarefas que será executada, uma vez que isso já está definido anteriormente no script. Veja sua execução:

```bash
$ sbatch jobMPI.sh 

Submitted batch job 2236

[seuUsuario@service0 ~]$  cat slurm-2236.out 

Hello from process 3 on node r1i1n2!

Hello from process 2 on node r1i1n2!

Hello from process 1 on node r1i3n5!

Hello from process 0 on node r1i3n5!

From process 0: Number of MPI processes is 4
```

Repare que agora as 4 tarefas foram executadas em dois nós distintos (r1i1n2 e r1i3n5), exatamente da forma que instruímos.

Assim finalizamos nosso tutorial Intel MPI. Para mais informações sobre o Intel MPI e o SLURM acesse os links abaixo:

- <http://slurm.schedmd.com/>
- <https://software.intel.com/en-us/intel-mpi-library>
