# Introdução ao supercomputador - Parte&nbsp;3

Nesse tutorial iremos aprender a função de algumas opções que podem ser inseridas nos scripts enviados para o supercomputador. Caso surja alguma dúvida durante o tutorial, sinta-se à vontade para entrar em contato através do e-mail **atendimento\<at>npad.ufrn.br** (substituindo \<at> por **@**).

[TOC]

## Script para multithreading

Por padrão, quando não é definido o número de núcleos a ser utilizado, o supercomputador executará o job em apenas um **um** núcleo do nó. Para que seu programa execute em mais de um núcleo, é necessário definir no script `#SBATCH --cpus-per-task`, da seguinte forma:

```bash
#!/bin/bash
#SBATCH --job-name=multithreading_example
#SBATCH --time=0-0:5
#SBATCH --partition=amd-512
#SBATCH --cpus-per-task=32
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./hello_threads 
```

A opção `#SBATCH --cpus-per-task=32` está definindo 32 cores ou núcleos para esse job. A variável de ambiente `SLURM_CPUS_PER_TASK` fornece a você o número de cores que seu job terá durante a execução do programa.

## Script para utilização de vários nós

Novamente, por padrão, **quando não é definido o número de nós a ser utilizado, o supercomputador executará o job em apenas um nó e em um núcleo desse nó**. Para que seu programa execute em mais de um nó, é necessário definir no script da seguinte forma:

```bash
#!/bin/bash
#SBATCH --partition=amd-512  # partição para a qual o job é enviado
#SBATCH --nodes=2 #número de nós
#SBATCH --ntasks-per-node=2 #número de tarefas por nó
#SBATCH --hint=compute_bound

#programa a ser executado.
#srun: executa jobs em paralelo
srun prog1 

#alternativa para casos em que srun não funciona:
mpirun prog1
```

Onde `#SBATCH --nodes` indica a quantidade de nós a ser utilizada, podendo também ser definido com `#SBATCH -N`. Também se pode definir o número de tarefas por nó e a quantidade de cpus por tarefas, essas configurações estão relacionadas a paralelização com [MPI](../advanced/mpi.md). Para isso é necessário primeiramente definir o número de tarefas com a opção `#SBATCH --ntasks` ou `#SBATCH -n`, que define o total de tarefas, ou `#SBATCH --ntasks-per-node` que define o número de tarefas por nó. 
A opção `#SBATCH --hint=compute_bound` muda a configuração para ser um thread por core e pode trazer benefícios de performance quando se usa apenas paralelismo de memória distribuída.

Cada tarefa é um processo, ou seja, um programa em execução. Então iniciar 10 tarefas em 2 nós significa iniciar 10 processos em paralelo em cada um dos nós, para um total de 20 processos. Se esses processos não usam MPI, ou alguma outra forma de comunicação entre si, há o risco de que eles apenas executem o mesmo trabalho 20 vezes.

O comando srun é quase sempre equivalente a mpirun: sua função é efetivamente iniciar as tarefas com os recursos que foram alocados. No entanto, em casos em que se usam versões de MPI incompatíveis com Slurm, o comando srun poderá ter efeitos diferentes de mpirun. Em caso de dúvidas, recomenda-se testar cada caso.

## Compartilhamento dos nós

Outro padrão do supercomputador é, ao submeter um job o nó **não** será reservado exclusivamente para aquele job, podendo ser alocado mais jobs dependendo da disponibilidade dos recursos naquele nó. Caso seu programa necessite de um nó por completo, utilize a opção `#SBATCH --exclusive`. Por exemplo, para um programa que será executado em paralelo, o desempenho do programa será melhor se o programa puder utilizar os recursos por completo.

## Preempção e tempo máximo de uso

Conforme nossa política de uso, há algumas distinções importantes entre usuários prioritários e não-prioritários (comuns).
Uma delas é que jobs de usuários comuns podem ser cancelados para liberar recursos para jobs de usuários prioritários.
Esse cancelamento chama-se **preempção**, e pode ocorrer se um job de um usuário comum executar por mais do que 6 horas 
em partições de GPU, ou 2 dias nas demais partições. A esse intervalo chamaremos de imunidade.

Usuários comuns podem submeter jobs com duração de até 20 dias, mas ao submeter jobs com duração superior ao tempo de 
imunidade, devem estar cientes de que *o job corre o risco ser preemptado sem aviso prévio*. 
Caso o usuário comum decida correr esse risco, é aconselhável adotar técnicas de *checkpoint*, ou outras metodologias
que não resultem em perda completa do trabalho se ele for preemptado.

## Receber e-mails sobre início e fim da execução

Caso deseje receber notificações por e-mail sobre início e fim de execução, utiliza-se a opção **--mail-type** onde se pode definir que tipo de notificação deseja receber. Se for definido `ALL`, as notificações recebidas serão sobre `BEGIN`, `END`, `FAIL`, `REQUEUE` e `STAGE_OUT`. Caso deseje apenas um evento específico utilize uma das opções, sendo as opções disponíveis: `NONE`, `BEGIN`, `END`, `FAIL`, `REQUEUE`, `STAGE_OUT`, `TIME_LITMIT`, `TIME_LIMIT_90` (alcançou 90% do tempo limite), `TIME_LIMIT_50` e `ARRAY_TASKS` (enviar e-mail para cada array task).

Também é necessário definir o e-mail que irá receber as notificações com `#SBATCH --mail-user`.

```bash
#!/bin/bash
#SBATCH --partition=amd-512
#SBATCH --mail-user=meuemail@mail.com
#SBATCH --mail-type=ALL

./prog1
```

## Definir a quantidade de memória a ser utilizada

O supercomputador está configurado para atribuir, no mínimo, 2GB de memória por thread (cpu). Caso queira modificar a quantidade de memória padrão, você pode utilizar a opção `#SBATCH --mem-per-cpu`, como demonstrado no exemplo a seguir:

```bash
#!/bin/bash
#SBATCH --partition=amd-512
#SBATCH --mem-per-cpu=1000
#SBATCH --cpus-per-task=3

./prog1
```

O script do exemplo utiliza 3 cpus e para cada cpu é reservado aproximadamente 1GB de memória. Sendo que a multiplicação entre a quantidade de memória por cpu e o número de cpus usadas não pode ultrapassar o limite total do nó, que varia de acordo com a sua partição. Um nó pertencente a partição **intel-128** só pode utilizar ao total 4GB por core, ou 2GB por cpu. Um nó na partição **intel-256** e  **gpu**  pode usar até 8 GB e **intel-512** pode usar até 16GB.

A tabela a seguir lista os limites de memória por partição:

|   Partição |  Padrão          |  Máximo |
|------------|------------------|---------|
| amd-512    | 2000             | 4000    |
| intel-128  | 2000             | 4000    |
| intel-256  | 4000             | 8000    |
| intel-512  | 8000             | 16000   |
| gpu-8-v100 | 8000             | 8000    |
| gpu-4-a100 | 2000             | 2000    |

Também há a opção `#SBATCH --mem` que já especifica a quantidade de memória para o job por completo.

```bash
#!/bin/bash
#SBATCH --partition=amd-512
#SBATCH --mem=3000
#SBATCH --cpus-per-task=3

./prog1
```

## Carregando softwares disponíveis

A grande maioria dos softwares científicos instalados no supercomputador são executados por módulo e, portanto, será preciso carregar seus módulos. Para verificar quais módulos estão disponíveis no supercomputador, digite no terminal do Linux o comando a seguir:

```bash
module avail
```

Depois de verificar os módulos disponíveis, você poderá carregar aqueles dos quais você precisa utilizando um comando semelhante ao mostrado a seguir:

```bash
module load libraries/zlib/1.2.11-intel-16.0.1     # Substitua libraries/zlib/1.2.11-intel-16.0.1 pelo módulo desejado, inserindo seu caminho completo fornecido pelo comando module avail
```

Para verificar quais módulos você tem atualmente carregados, utilize o comando a seguir:

```bash
module list
```

Para limpar todos os módulos que você tem atualmente carregados, utilize o comando a seguir:

```bash
module clear
```

Os módulos podem ser adicionados ao script criado usando o editor de textos disponível de sua preferência, caso queira editar via linha comando, pode utilizar o editor **Nano**, basta você efetuar o devido carregamento dos módulos necessários, através dos comandos supracitados. Tome o cuidado apenas de, no script, carregar os módulos antes de fazer a execução do programa propriamente dito.

```bash
#!/bin/bash
#SBATCH --partition=amd-512
#SBATCH --time=0-0:5

module load nome-do-software #nome do software que aparecerá após usar o comando module avail
nome-do-software prog1
```

## Utilizando a sua pasta home

Ao logar no supercomputador, você estará na pasta home. Essa pasta possui uma comunicação via rede com o supercomputador e já está configurada para, ao submeter os scripts para o supercomputador, ler os arquivos de entrada necessários para executar o job dessa pasta, assim como arquivo log de saída que será salvo nesse mesmo local.

Ou seja, não é necessário utilizar comandos extras ao utilizar essa pasta. Apenas as configurações básicas do script, como o tempo estimado de execução do programa, quantidade de cpus, a fila em que deseja alocar o job e afins.

Uma vez com o script pronto, é só enviar o script com o comando `sbatch`.

```bash
$ sbatch meu-script.sh
```


## Utilizando o scratch global

O NPAD utiliza o BeeGFS para scratch global, ou seja, armazenamento temporário de arquivos, compartilhado com todos os nós. Como usuário do sistema, tudo que você precisa fazer é copiar os arquivos relevantes pra pasta ~/scratch. Você pode inclusive submeter jobs de lá. Essa pasta na verdade é um symlink que aponta pra /scratch/global/usuario. Num job script, você também pode usar a variável de ambiente $SCRATCH_GLOBAL para pegar a localização dessa pasta. 

Acessando a pasta /scratch/global destinada ao seu usuário:

```bash
$ cd ~/scratch
```

ou

```bash
$ cd $SCRATCH_GLOBAL
```

Exemplo de utilização:

```bash
#!/bin/bash
#SBATCH --partition=amd-512
#SBATCH --time=0-0:5

#move os arquivos com os parâmetros de entrada para a pasta /scratch/global
mv entrada.in $SCRATCH_GLOBAL 
cd $SCRATCH_GLOBAL

#execução normal do seu programa
./prog 

#move os arquivos de saída para o diretório /home/usuario
mv saida.out /home/usuario/ 
```

O scratch global deve ser considerada como uma pasta temporária, e os arquivos lá podem ser excluídos se a equipe do NPAD determinar que eles não estão sendo usados há muito tempo. Portanto, não mantenha arquivos importantes nela. A boa prática é usar a scratch global para a geração de arquivos temporários e depois copiar os resultados importantes para fora dela.


## Backfill e escolha do tempo de execução

O Supercomputador por padrão aloca os jobs de acordo com suas prioridades, ou seja, jobs com alta prioridade executam antes. Porém a opção backfill é utilizada para uma melhor utilização do sistema. Com isso é possível que jobs com prioridades menores sejam alocados e executados antes de jobs com alta prioridade. Isso acontece apenas no caso em que o tempo de início esperado do jobs de alta prioridade for maior que o tempo limite de execução do job de baixa prioridade.

O tempo de início esperado depende da finalização dos jobs em execução e o tempo limite de execução depende da opção **--time** no script do job. Logo, uma escolha razoável do tempo estimado de execução pode fazer com que o job comece a executar mais rápido. Ex.:

```bash
#!/bin/bash
#SBATCH --partition=amd-512
#SBATCH --time=0-0:5 #Formato padrão: dias-horas:minutos
```

Para executar programas em paralelo no supercomputador, leia os tutorias de [OpenMP](../advanced/openmp.md) e [MPI](../advanced/mpi.md).
