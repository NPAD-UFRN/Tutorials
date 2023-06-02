# Tutorial Introdução ao Supercomputador - Parte 3

Nesse tutorial iremos aprender a função de algumas opções que podem ser inseridas nos scripts enviados para o supercomputador. Caso surja alguma dúvida durante o tutorial, sinta-se à vontade para entrar em contato através do e-mail **atendimento\<at>npad.ufrn.br** (substituindo \<at> por **@**).

## Tópicos

- [Tutorial Introdução ao Supercomputador - Parte 3](#tutorial-introdução-ao-supercomputador---parte-3)
  - [Tópicos](#tópicos)
  - [Script para multithreading](#script-para-multithreading)
  - [Script para utilização de vários nós](#script-para-utilização-de-vários-nós)
    - [Compartilhamento dos nós](#compartilhamento-dos-nós)
  - [Escolha da qualidade de serviço e Limite no uso do supercomputador](#escolha-da-qualidade-de-serviço-e-limite-no-uso-do-supercomputador)
    - [QOS 1](#qos-1)
    - [QOS 2](#qos-2)
    - [preempt](#preempt)
  - [Receber e-mails sobre início e fim da execução](#receber-e-mails-sobre-início-e-fim-da-execução)
  - [Definir a quantidade de memória a ser utilizada](#definir-a-quantidade-de-memória-a-ser-utilizada)
  - [Carregando softwares disponíveis](#carregando-softwares-disponíveis)
  - [Utilizando a sua pasta home](#utilizando-a-sua-pasta-home)
  - [Utilizando o scratch local](#utilizando-o-scratch-local)
  - [Utilizando o scratch global](#utilizando-o-scratch-global)
  - [Backfill e escolha do tempo de execução](#backfill-e-escolha-do-tempo-de-execução)

## Script para multithreading

Por padrão, quando não é definido o número de núcleos a ser utilizado, o supercomputador executará o job em apenas um **um** núcleo do nó. Para que seu programa execute em mais de um núcleo, é necessário definir no script `#SBATCH --cpus-per-task`, da seguinte forma:

```bash
 #!/bin/bash
#SBATCH --job-name=multithreading_example
#SBATCH --time=0-0:5
#SBATCH --cpus-per-task=32
#SBATCH --hint=compute_bound
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./hello_threads 32 #32 threads
```

A opção `#SBATCH --hint=compute_bound` muda a configuração para ser um thread por core. A opção `#SBATCH --cpus-per-task=32` está definindo 32 cores ou núcleos para esse job. A variável de ambiente `SLURM_CPUS_PER_TASK` fornece a você o número de cores que seu job terá durante a execução do programa.

## Script para utilização de vários nós

Novamente, por padrão, **quando não é definido o número de nós a ser utilizado, o supercomputador executará o job em apenas um nó e em um núcleo desse nó**. Para que seu programa execute em mais de um nó, é necessário definir no script da seguinte forma:

```bash
#!/bin/bash
#SBATCH --nodes=2 #número de nós
#SBATCH --ntasks=4 #número total de tarefas
#SBATCH --ntasks-per-node=2 #número de tarefas por nó

srun prog1 #programa a ser executado. #srun: executa jobs em paralelo
```

Onde `#SBATCH --nodes` indica a quantidade de nós a ser utilizada, podendo também ser definido com `#SBATCH -N`. Também se pode definir o número de tarefas por nó e a quantidade de cpus por tarefas, essas configurações estão relacionadas a paralelização com [MPI](/advanced/mpi_tutorial.md). Para isso é necessário primeiramente definir o número de tarefas com a opção `#SBATCH --ntasks` ou `#SBATCH -n`. Com `#SBATCH --ntasks-per-node` é definido as tarefas por nó. Já `#SBATCH --cpus-per-task` define a quantidade de cpu por tarefas. Vale salientar que as duas últimas opções citadas não são dependentes. Com isso, pode ser que a nó que esteja utilizando seja compartilhado com outros jobs.

### Compartilhamento dos nós

Outro padrão do supercomputador é, ao submeter um job o nó **não** será reservado exclusivamente para aquele job, podendo ser alocado mais jobs dependendo da disponibilidade dos recursos naquele nó. Caso seu programa necessite de um nó por completo, utilize a opção `#SBATCH --exclusive`. Por exemplo, para um programa que será executado em paralelo, o desempenho do programa será melhor se o programa puder utilizar os recursos por completo.

## Escolha da qualidade de serviço e Limite no uso do supercomputador

O usuário poderá enviar múltiplos jobs para o supercomputador. Porém, para permitir que mais pesquisadores compartilhem esse recurso com menos tempo de espera foram impostos limites no uso do supercomputador a partir da **qualidade do serviço em inglês Quality of Service (QOS)** utilizado. Comando a ser acrescentado no script de execução:

```bash
#SBATCH --qos=qosN #Subistitua N pelo tipo de QOS desejado
```

### QOS 1

O QOS 1 é o QOS padrão, com ele o usuário poderá enviar até 100 jobs para o supercomputador, sendo somente 4 jobs em execução ou 256 núcleos físicos (4 nós completos) em utilização, o que ocorrer primeiro. O job tem limite de tempo de até **2 dias** Ex.:

```bash
 #!/bin/bash
 #SBATCH --time=0-0:5

 ./prog1
```

### QOS 2

O QOS 2 é mais indicado para mais jobs que utilizam um nó inteiro ou jobs que utilizam alguns poucos nós. Com ele, o usuário poderá colocar 100 jobs na fila, mas apenas **1 job** em execução  com até 256 núcleos físicos (4 nós completos) em utilização, o que ocorrer primeiro. Tendo o job o limite de tempo de até **7 dias** Ex.:

```bash
 #!/bin/bash
 #SBATCH --time=0-0:5
 #SBATCH --qos=qos2

 ./prog1
```

### preempt

Para trabalhos que necessitem rodar vários jobs simultaneamente , ou job que precisa de mais de até 20 dias para ser executado. Recomenda-se utilizar preempt, nele o usuário pode deixar rodando até 100 jobs simultâneos. No entanto, por falta de recurso o seus jobs poderão ser cancelados a qualquer momento. Ex:

```bash
 #!/bin/bash
 #SBATCH --time=0-0:5
 #SBATCH --qos=preempt

 ./prog1
```

## Receber e-mails sobre início e fim da execução

Caso deseje receber notificações por e-mail sobre início e fim de execução, utiliza-se a opção **--mail-type** onde se pode definir que tipo de notificação deseja receber. Se for definido `ALL`, as notificações recebidas serão sobre `BEGIN`, `END`, `FAIL`, `REQUEUE` e `STAGE_OUT`. Caso deseje apenas um evento específico utilize uma das opções, sendo as opções disponíveis: `NONE`, `BEGIN`, `END`, `FAIL`, `REQUEUE`, `STAGE_OUT`, `TIME_LITMIT`, `TIME_LIMIT_90` (alcançou 90% do tempo limite), `TIME_LIMIT_50` e `ARRAY_TASKS` (enviar e-mail para cada array task).

Também é necessário definir o e-mail que irá receber as notificações com `#SBATCH --mail-user`.

```bash
#!/bin/bash
#SBATCH --mail-user=meuemail@mail.com
#SBATCH --mail-type=ALL

./prog1
```

## Definir a quantidade de memória a ser utilizada

O supercomputador está configurado para atribuir, no mínimo, 4GB de memória por núcleo. Caso queira modificar a quantidade de memória padrão, você pode utilizar a opção `#SBATCH --mem-per-cpu`, como demonstrado no exemplo a seguir:

```bash
#!/bin/bash
#SBATCH --mem-per-cpu=1000
#SBATCH --cpus-per-task=3

./prog1
```

O script do exemplo utiliza 3 cpus e para cada cpu é reservado aproximadamente 1GB de memória. Sendo que a multiplicação entre a quantidade de memória por cpu e o número de cpus usada não pode ultrapassar de 4GB, pois esse é o limite de cada nó. O limite de cada nó varia de acordo com a sua partição. Um Nó pertencente a partição **cluster** ou **service**, só pode utilizar ao total 4GB. Um nó na partição **intel-256** e  **gpu**  pode usar até 8 GB e **intel-512** pode usar até 16GB. Lembrando que a partição **test** é **cluster** mais **service**.

Também há a opção `#SBATCH --mem` que já especifica a quantidade de memória para o job por completo.

```bash
#!/bin/bash
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
#SBATCH --time=0-0:5

module load nome-do-software #nome do software que aparecerá após usar o comando module avail
nome-do-software prog1
```

## Utilizando a sua pasta home

Ao logar no supercomputador, você estará na pasta home. Essa pasta possui uma comunicação via rede com o supercomputador e já está configurada para, ao submeter os scripts para o supercomputador, ler os arquivos de entrada necessários para executar o job dessa pasta, assim como arquivo log de saída que será salvo nesse mesmo local.

Ou seja, não é necessário utilizar comandos extras ao utilizar essa pasta. Apenas as configurações básicas do script, como o tempo estimado de execução do programa, quantidade de cpus, a fila em que deseja alocar o job e afins.

Uma vez com o script pronto, é só enviar o script com o comando `sbatch`.

```bash
[usuario@service0 ~]$ sbatch meu-script.sh
```


## Utilizando o scratch global

O NPAD utiliza o BeeGFS para scratch global, ou seja, armazenamento temporário de arquivos, compartilhado com todos os nós. Como usuário do sistema, tudo que você precisa fazer é copiar os arquivos relevantes pra pasta ~/scratch. Você pode inclusive submeter jobs de lá. Essa pasta na verdade é um symlink que aponta pra /scratch/global/usuario. Num job script, você também pode usar a variável de ambiente $SCRATCH_GLOBAL para pegar a localização dessa pasta. 

Acessando a pasta /scratch/global destinada ao seu usuário:

```bash
[usuario@service0 ~]$ cd ~/scratch
```

ou

```bash
[usuario@service0 ~]$ cd $SCRATCH_GLOBAL
```

Exemplo de utilização:

```bash
#!/bin/bash

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
#SBATCH --time=0-0:5 #Formato padrão: dias-horas:minutos
```

Para executar programas em paralelo no supercomputador, leia os tutorias de [OpenMP](/advanced/openmp_tutorial.md) e [MPI](/advanced/mpi_tutorial.md).
