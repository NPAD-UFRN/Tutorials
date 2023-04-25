# Tutorial Introdução ao Supercomputador - Parte 3

Nesse tutorial iremos aprender a função de algumas opções que podem ser inseridas nos scripts enviados para o supercomputador. Caso surja alguma dúvida durante o tutorial, sinta-se à vontade para entrar em contato através do e-mail **atendimento\<at>npad.ufrn.br** (substituindo \<at> por **@**).

## Tópicos

- [Tutorial Introdução ao Supercomputador - Parte 3](#tutorial-introdução-ao-supercomputador---parte-3)
  - [Tópicos](#tópicos)
  - [Script para multithreading](#script-para-multithreading)
  - [Script para utilização de vários nós](#script-para-utilização-de-vários-nós)
    - [**Compartilhamento dos nós**](#compartilhamento-dos-nós)
  - [Escolha de QOS e Limite no uso do supercomputador](#escolha-de-qos-e-limite-no-uso-do-supercomputador)
    - [QOS 1](#qos-1)
    - [QOS 2](#qos-2)
    - [QOS 3](#qos-3)
  - [Receber e-mails sobre início e fim da execução](#receber-e-mails-sobre-início-e-fim-da-execução)
  - [Definir a quantidade de memória a ser utilizada](#definir-a-quantidade-de-memória-a-ser-utilizada)
  - [Carregando softwares disponíveis](#carregando-softwares-disponíveis)
  - [Utilizando a pasta /home](#utilizando-a-pasta-home)
  - [Utilizando a pasta /scratch/local](#utilizando-a-pasta-scratchlocal)
  - [Utilizando a pasta /scratch/global](#utilizando-a-pasta-scratchglobal)
  - [Backfill e escolha do tempo de execução](#backfill-e-escolha-do-tempo-de-execução)

## Script para multithreading

Por padrão, quando não é definido o número de núcleos a ser utilizado, o supercomputador executará o job em apenas **um** núcleo do nó. Para que seu programa execute em mais de um núcleo, é necessário definir no script da seguinte forma:

```bash
 #!/bin/bash
#SBATCH --job-name=multithreading_example
#SBATCH --time=0-0:5
#SBATCH --cpus-per-task=32
#SBATCH --hint=compute_bound
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./hello_threads 32 #32 threads
```

A opção **--hint=compute\_bound** muda a configuração para ser um thread por core.

## Script para utilização de vários nós

Por padrão, quando não é definido o número de nós a ser utilizado, o supercomputador executará o job em apenas **um** nó e em **um** núcleo desse nó. Para que seu programa execute em mais de um nó, é necessário definir no script da seguinte forma:

```bash
#!/bin/bash
#SBATCH --nodes=2 #número de nós
#SBATCH --ntasks=4 #número total de tarefas
#SBATCH --ntasks-per-node=2 #número de tarefas por nó

srun prog1 #programa a ser executado. #srun: executa jobs em paralelo
```

Onde **--nodes** indica a quantidade de nós a ser utilizada, podendo também ser definido com **-N**. Também se pode definir o número de tarefas por nó e a quantidade de cpus por tarefas, essas configurações estão relacionadas a paralelização com [MPI](/tutoriais/mpi.php). Para isso é necessário primeiramente definir o número de tarefas com a opção **--ntasks** ou **-n**. Com **--ntasks-per-node** é definido as tarefas por nó. Já **--cpus-per-task** define a quantidade de cpu por tarefas. Vale salientar que as duas últimas opções citadas não são dependentes. Com isso, pode ser que a nó que esteja utilizando seja compartilhado com outros jobs.

### **Compartilhamento dos nós**

Outro padrão do supercomputador é, ao submeter um job o nó não será reservado exclusivamente para aquele job, podendo ser alocado mais jobs dependendo da disponibilidade dos recursos naquele nó. Caso seu programa necessite de um nó por completo, utilize a opção **--exclusive**. Por exemplo, para um programa que será executado em paralelo, o desempenho do programa será melhor se o programa puder utilizar os recursos por completo.

Outro aspecto importante do compartilhamento de nós é a não especificação da utilizaçao dos recursos. Ou seja, se seu script não conter a quantidade de nós a ser utilizado nem o número de tarefas ou outra informaçao relacionada aos recursos, será reservado os recursos completos. No caso da não especificação do nó, será reservado um nó por completo. Se foi especificado **n** nós e não tinha no script quanto de cpu ou memória iria utilizar, esses n nós serão reservados para sua tarefa.

## Escolha de QOS e Limite no uso do supercomputador

O usuário poderá enviar múltiplos jobs para o supercomputador. Porém, para permitir que mais pesquisadores compartilhem esse recurso com menos tempo de espera foram impostos limites no uso do supercomputador a partir do QOS utilizado. Comando a ser acrescentado no script de execução:

```bash
#SBATCH --qos=qosN #Subistitua N pelo tipo de QOS desejado

```

### QOS 1

O QOS 1 é o QOS padrão, com ele o usuário poderá enviar múltiplos jobs para o supercomputador até que se atinja o limite de 512 jobs ou 512 núcleos físicos (16 nós completos), o que ocorrer primeiro. Ex.:

```bash
 #!/bin/bash
 #SBATCH --time=0-0:5

 ./prog1
```

### QOS 2

O QOS 2 é mais indicado para mais jobs que utilizam um nó inteiro ou jobs que utilizam alguns poucos nós. Com ele, o usuário poderá enviar múltiplos jobs para o supercomputador até que se atinja o limite de 32 jobs ou 1024 núcleos físicos (32 nós completos), o que ocorrer primeiro. Ex.:

```bash
 #!/bin/bash
 #SBATCH --time=0-0:5
 #SBATCH --cpus-per-task=32
 #SBATCH --hint=compute_bound
 #SBATCH --exclusive
 #SBATCH --qos=qos2

 ./prog1

```

### QOS 3

O QOS 3 é mais indicado para mais jobs que utilizam um nó inteiro. Com ele, o usuário poderá enviar um único job para usar quantos nós desejar no supercomputador. Ex.:

```bash
 #!/bin/bash
 #SBATCH --time=1-0:0
 #SBATCH --nodes=68
 #SBATCH --ntasks-per-node=32
 #SBATCH --cpus-per-task=1
 #SBATCH --exclusive
 #SBATCH --qos=qos3

 srun prog1
```

## Receber e-mails sobre início e fim da execução

Caso deseje receber notificações por e-mail sobre início e fim de execução, utiliza-se a opção **--mail-type** onde se pode definir que tipo de notificação deseja receber. Se for definido **ALL**, as notificações recebidas serão sobre BEGIN, END, FAIL, REQUEUE e STAGE\_OUT. Caso deseje apenas um evento específico utilize uma das opções, sendo as opções disponíveis: NONE, BEGIN, END, FAIL, REQUEUE, STAGE\_OUT, TIME\_LITMIT, TIME\_LIMIT\_90 (alcançou 90% do tempo limite), TIME\_LIMIT\_50 e ARRAY\_TASKS (enviar e-mail para cada array task).

Também é necessário definir o e-mail que irá receber as notificações com **--mail-user**.

```bash
#!/bin/bash
#SBATCH --mail-user=meuemail@mail.com
#SBATCH --mail-type=ALL

./prog1
```

## Definir a quantidade de memória a ser utilizada

O supercomputador está configurado para atribuir, no mínimo, 4GB de memória por núcleo. Caso queira modificar a quantidade de memória padrão, você pode utilizar a opção **--mem-per-cpu**, como demonstrado no exemplo a seguir:

```bash
#!/bin/bash
#SBATCH --mem-per-cpu=8000
#SBATCH --cpus-per-task=8

./prog1
```

O script do exemplo utiliza oito cpus e para cada cpu é reservado aproximadamente 8GB de memória. Sendo que a multiplicação entre a quantidade de memória por cpu e o número de cpus usada não pode ultrapassar de 128GB, pois esse é o limite de cada nó.

Também há a opção **--mem** que já especifica a quantidade de memória para o job por completo.

```bash
#!/bin/bash
#SBATCH --mem=64000
#SBATCH --cpus-per-task=8

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
#SBATCH --time=0-0:5

module load nome-do-software #nome do software que aparecerá após usar o comando module avail
nome-do-software prog1
```

## Utilizando a pasta /home

Ao logar no supercomputador, você estará na pasta home. Essa pasta possui uma comunicação via rede com o supercomputador e já está configurada para, ao submeter os scripts para o supercomputador, ler os arquivos de entrada necessários para executar o job dessa pasta, assim como arquivo log de saída que será salvo nesse mesmo local.

Ou seja, não é necessário utilizar comandos extras ao utilizar essa pasta. Apenas as configurações básicas do script, como o tempo estimado de execução do programa, quantidade de cpus, a fila em que deseja alocar o job e afins.

Uma vez com o script pronto, é só enviar o script com o comando **sbatch seuscript**.

```bash
[usuario@service0 ~]$ sbatch meu-script.sh
```

## Utilizando a pasta /scratch/local

A pasta /scratch/local fica localizada em um disco SSD em cada nó de computação, com capacidade de 110 GB para os nós r1i\*n\* (onde * são numerais) e 19 GB para os nós service. Como a pasta /scratch/local é local de cada nó de computação, não é possível ver o conteúdo dessas pastas locais a partir do nó de login. O nó de login também possui uma pasta /scratch/local, mas ela é diferente das demais. Logo, cada pasta /scratch/local em cada nó é diferente da pasta /scratch/local de outro nó, o que não ocorre com o home. Para utilizar a pasta /scratch/local nos jobs, é necessário que, antes de submeter os jobs, os arquivos de entrada esteja em alguma pasta compartilhada (ex: /home, /scratch/global), e que o script submetido copie alguns arquivos de entrada para a pasta /scratch/local, execute o programa desejado e mova a saída de volta para uma pasta compartilhada. O script abaixo mostra um exemplo de job que utiliza a pasta /scratch/local. Nos nós de computação, a varíável de ambiente **$SCRATCH** equivale a pasta /scratch/local/<seu-nome-de-usuário>

Exemplo de uso do /scratch/local:

```bash
#!/bin/bash

#SBATCH --time=0-0:5
#SBATCH --ntasks=1

INP="input1.in input2.in" #Especifica os arquivos de entrada.

WRKDIR=$SCRATCH/$SLURM_JOB_ID #Declara variável WRKDIR.
mkdir -p $WRKDIR #Verifica se existe um diretório, se não, cria o diretório.
cp $INP  $WRKDIR #copia os arquivos de entrada para a pasta /scratch/local/$USER
cd $WRKDIR #muda para a pasta /scratch/local/$USER/JOBID
./prog #execução normal do seu programa
mv $WRKDIR/ $SLURM_SUBMIT_DIR/#move os arquivos de saída para o diretório /home/$USER
```

## Utilizando a pasta /scratch/global

Na pasta /scratch/global há a comunicação via rede da mesma forma da pasta /home, mas utiliza uma banda maior, o que faz com que seja mais rápido mas não tão rápida quanto ao /scratch/local. Sendo, ainda, que essa pasta possui um sistema de leitura e escrita de arquivos em paralelo, chamado [Lustre](http://lustre.org).

Acessando a pasta /scratch/global destinada ao seu usuário:

```bash
[usuario@service0 ~]$ cd $SCRATCH_GLOBAL
```

O sistema já faz a leitura e escrita de forma paralela de acordo com a configuração, não precisando determinar através do script ou qualquer outro código a ser utilizado. A utilização fica sendo da mesma forma que na pasta /home. Como se pode ver no script exemplo:

```bash
#!/bin/bash

#SBATCH --time=0-0:5
#SBATCH --ntasks=1

mv param.in $SCRATCH_GLOBAL #move os arquivos com os parâmetros de entrada para a pasta /scratch/global
./prog #execução normal do seu programa
mv file.out /home/usuarioNPAD/ #move os arquivos de saída para o diretório /home/<seu-nome-de-usuário>
```

## Backfill e escolha do tempo de execução

O Supercomputador por padrão aloca os jobs de acordo com suas prioridades, ou seja, jobs com alta prioridade executam antes. Porém a opção backfill é utilizada para uma melhor utilização do sistema. Com isso é possível que jobs com prioridades menores sejam alocados e executados antes de jobs com alta prioridade. Isso acontece apenas no caso em que o tempo de início esperado do jobs de alta prioridade for maior que o tempo limite de execução do job de baixa prioridade.

O tempo de início esperado depende da finalização dos jobs em execução e o tempo limite de execução depende da opção **--time** no script do job. Logo, uma escolha razoável do tempo estimado de execução pode fazer com que o job comece a executar mais rápido. Ex.:

```bash
 #!/bin/bash
#SBATCH --time=0-0:5 #Formato padrão: dias-horas:minutos

```

Para executar programas em paralelo no supercomputador, leia os tutorias de [OpenMP](/advanced/openmp_tutorial.md) e [MPI](/advanced/mpi_tutorial.md).
