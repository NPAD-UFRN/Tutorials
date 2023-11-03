# Tutorial de Job Array

[TOC]

## Para que serve um array de jobs?

O array de jobs ou de tarefas (tasks) permite rodar um mesmo job várias vezes com variações em cada rodada, por exemplo, na entrada de dados ou nas configurações.

Para fazer isso, usa-se a diretiva `--array`  no script de job. Por exemplo,

```bash
#SBATCH --array=1-10
```

Isto fará com que o mesmo script de job seja executado 10 vezes onde cada um dos 10 jobs é independente um do outro. 

Em geral, a diretiva `--array` é usada em conjunto com variável de ambiente `SLURM_ARRAY_TASK_ID` que fornece o indice do array de jobs, ou seja, o índice do job em execução. Este índice pode ser usado para selecionar dados de entrada, configurações, comandos etc.

## Exemplo

Suponha a situação onde um programa, digamos, `meuprograma`, deve ser executado para cada um dos dez arquivos de entrada: entrada1.txt,  entrada2.txt, entrada3.txt etc.  Ao invés de criar 10 scripts de jobs diferentes para cada arquivo, podemos usar um único script de array de jobs, como este:

```bash
#!/bin/bash 
#SBATCH --time=0-0:10
#SBATCH --array=1-10

./meuprograma entrada${SLURM_ARRAY_TASK_ID}.txt
```

A variável  `$SLURM_ARRAY_TASK_ID`  fornece o índice do array de jobs.  Ela é usada na última linha para selecionar o arquivo de entrada para o programa `meuprograma`. Digamos que o script tenha nome de `script_job_array.sh`. Então submetemos este script de arrays de jobs:

```bash
$ sbatch script_job_array.sh 
Submitted batch job 123456
```

E para visualizar como estão os Jobs na fila de execução, digite:

```bash
$ squeue -u $USER

             JOBID PARTITION     NAME     USER ST       TIME  NODES NODELIST(REASON)
          123456_1   cluster job_arra  usuario  R       0:51      1 r1i2n10
          123456_2   cluster job_arra  usuario  R       0:52      1 r1i2n10
          123456_3   cluster job_arra  usuario  R       0:41      1 r1i2n10
          123456_4   cluster job_arra  usuario  R       0:54      1 r1i2n10
          123456_5   cluster job_arra  usuario  R       0:51      1 r1i2n10
          123456_6   cluster job_arra  usuario  R       0:51      1 r1i2n10
          123456_7   cluster job_arra  usuario  R       0:55      1 r1i2n10
          123456_8   cluster job_arra  usuario  R       0:50      1 r1i2n10
          123456_9   cluster job_arra  usuario  R       0:52      1 r1i2n10
```

Nota-se que foi criado um job array de 10 jobs independentes e como um jobID diferenciado apenas pelo índice do array de jobs.  

!!! Nota
    As especificações no script do array de jobs tais como --nodes, --cpus-per-task, --mem, etc refere-se apenas a execução de um único job do array de jobs. Por isso, não precisamos alocar recursos para todos os jobs do array, mas somente para um único job e o slurm repetirá a mesma alocação para todas os outros.

## Deletando jobs

Para deletar um array de jobs inteiro, digite `scancel` seguido do job ID do array de jobs. Por exemplo

```bash
$ scancel 123456
```

E para deletar um job específico, use `scancel` seguido do job ID do job. Por exemplo:

```bash
$ scancel 123456_5
```

## Mais Exemplos

Nem sempre os arquivos de entrada estão numerados sequencialmente como no exemplo acima. Supondo que eles estão na pasta `/path/to/input`. Então pode-se usar o seguinte script:

```bash
#!/bin/bash 
#SBATCH --time=0-0:10
#SBATCH --array=1-5

INPUT_PATH=/path/to/input
$entrada=$(ls ${INPUT_PATH}/*.txt | sed -n ${SLURM_ARRAY_TASK_ID}p)
./meuprograma $entrada
```

Se ao invés de arquivos de entrada, o programa recebe um argumento de linha de comando. Então pode-se salvar os argumentos em um arquivo `lista.txt`

```bash
$ cat lista.txt
1 23 3.1 2 1.2
```

 e usar o seguinte script de array de jobs

```bash
#!/bin/bash 
#SBATCH --time=0-0:10
#SBATCH --array=1-5

ARGS=($(<lista.txt))
ARG=${ARGS[${SLURM_ARRAY_TASK_ID}]}
./meuprograma -n $ARG
```

Se o programa recebe n argumentos, como neste exemplo:

```bash
./meuprograma --type 1 --name jupiter --factor 4.1
```

pode-se salvar os argumentos em um arquivo com n argumentos por linha. Neste caso com n=3 argumentos por linha, por exemplo

```bash
$ cat argumentos.txt 

1 jupiter 4.1 
3 saturno 4.5 
2 faraday 3.0 
```

E então usar:

```bash
#!/bin/bash 
#SBATCH --time=0-0:10
#SBATCH --array=1-5

IFS=$'\n' read -d '' -r -a ARGS < argumentos.txt
IFS=$' ' read -d '' -r -a ARG <<< ${ARGS[${SLURM_ARRAY_TASK_ID}]}
./meuprograma --type ${ARG[0]} --name ${ARG[1]} --factor ${ARG[2]}
```

## Acessando variáveis de ambiente

As linguagens de programação, em geral, possuem comandos para ler a variáveis de ambiente. Por exemplo, para ler variável  `SLURM_ARRAY_TASK_ID` 

Em Python:

```python
import os
task_id = os.getenv('SLURM_ARRAY_TASK_ID')
```

Em R:

```r
task_id <- Sys.getenv("SLURM_ARRAY_TASK_ID")
```

Em C:

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    char* task_id = getenv("SLURM_ARRAY_TASK_ID");
    printf("SLURM_ARRAY_TASK_ID: %s\n", task_id ? task_id : "null");
    return 0;
}
```

Em C++:

```cpp
#include <cstdlib>
#include <iostream>
using namespace std;

int main() {
    char* task_id = getenv("SLURM_ARRAY_TASK_ID");
    if (task_id != NULL) {
        cout << "SLURM_ARRAY_TASK_ID: " << task_id << endl;
    }
    return 0;
}
```

Em Fortran:

```fortran
program exemplo
character task_id*4
call get_environment_variable ('SLURM_ARRAY_TASK_ID', task_id)
write (*,*) 'task id = ', task_id
end
```

## Nome dos arquivos de saída e erro

Nos scripts de job array, usa-se os códigos `%A` e `%a` para indicar o job ID do array de jobs e o índice do job, respectivamente. Por exemplo 

```bash
#SBATCH --output=saida_%A_%a.out
#SBATCH --error=erros_%A_%a.error
```

Se o código `%a` for omitido, as saídas de todas os jobs do array serão escritas no mesmo arquivo.

## A diretiva --array

Pode-se especificar os índices de jobs usando a seguinte forma geral  `--array=x-y`. Por exemplo, para gerar índices entre 10 e 20, use

```bash
SBATCH --array=10-15
```

Neste caso será gerado 6 jobs com índices 10, 11, 12, 13, 14 e 15.

Para gerar índices com incrementos maiores que um use a forma `--array=x-y:passo` onde passo é o tamanho do incremento. Por exemplo

```bash
SBATCH --array=10-20:2
```

Neste caso será índices espaçados com incremento igual a dois: 10, 12, 14, 16, 18 e 20.

É também possível especificar individualmente os índices. Por exemplo

```bash
SBATCH --array=3,5,8,10
```

Um exemplo mais complexo seria:

```bash
SBATCH --array=3,5,11-13,22-26:2
```

O operador `%` é usado para limitar o números de jobs que são executados simultaneamente. Por exemplo:



```bash
SBATCH --array=1-10%3
```

Aqui serão submetidos 10 jobs, mas, no máximo três deles serão executados simultaneamente. Ao visualizarmos os jobs usando `squeue`, veremos que no máximo três em execução e o restante da fila de espera. Por exemplo,

```bash
$ squeue -u $USER
             JOBID PARTITION     NAME     USER ST       TIME  NODES NODELIST(REASON)
   123456_[4-10%3]   cluster job_arra usuario  PD       0:00      1 (JobArrayTaskLimit)
          123456_1   cluster job_arra usuario   R       0:20      1 r1i3n2
          123456_2   cluster job_arra usuario   R       0:20      1 r1i3n2
          123456_3   cluster job_arra usuario   R       0:20      1 r1i3n2
```


