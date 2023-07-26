# Comandos do supercomputador

O [Slurm](https://slurm.schedmd.com/) é o gerenciador de recursos usado no
supercomputador. Ele que auxilia o usuário na utilização do supercomputador,
disponibilizando ferramentas e comandos que ajudam na submissão, execução e
gerenciamento de jobs. Aqui então vamos listar alguns desses comandos, muito
úteis para o usuário saber o que se passa com seu job recém-submetido.

## Comandos

| Comando             | Descrição                                                                          |
| ------------------- | ---------------------------------------------------------------------------------- |
| [sinfo](#sinfo)     | Visualize as informações das partições e nós do supercomputador.                   |
| [sprio](#sprio)     | Visualize as informações dos fatores que compõem a prioridade na fila de cada job. |
| [squeue](#squeue)   | Visualize as informações gerais dos Job's que estão na fila ou executando.         |
| [sbatch](#sbatch)   | Submeta um Job para o supercomputador.                                             |
| [scancel](#scancel) | Cancele um Job que está na fila ou em execução.                                    |

### sinfo

sinfo exibe as informações das partições e nós do supercomputador.

#### Exemplo: sinfo

```bash
scavalcanti@headnode0 ~]$ sinfo
PARTITION AVAIL  TIMELIMIT  NODES  STATE NODELIST
cluster*     up 20-00:00:0      1  down* r1i2n14
cluster*     up 20-00:00:0     18  alloc r1i0n[1-2,4-7,11-12,14-16],r1i1n[7,9,15],r1i2n[1-2,11],r1i3n1
cluster*     up 20-00:00:0     13    mix r1i0n[0,3,9],r1i1n[4-6,10,14],r1i2n[3-4,10,13],r1i3n2
cluster*     up 20-00:00:0     19   idle r1i0n[10,17],r1i1n[0-3,11-13,16],r1i2n[0,5-7,9,12,15-16],r1i3n0
service      up 20-00:00:0      3    mix service[1,3-4]
service      up 20-00:00:0      1  alloc service2
test         up      30:00      1  down* r1i2n14
test         up      30:00     19  alloc r1i0n[1-2,4-7,11-12,14-16],r1i1n[7,9,15],r1i2n[1-2,11],r1i3n1,service2
test         up      30:00     16    mix r1i0n[0,3,9],r1i1n[4-6,10,14],r1i2n[3-4,10,13],r1i3n2,service[1,3-4]
test         up      30:00     19   idle r1i0n[10,17],r1i1n[0-3,11-13,16],r1i2n[0,5-7,9,12,15-16],r1i3n0
intel-512    up 20-00:00:0      6    mix r1i3n[11-16]
intel-256    up 20-00:00:0      6    mix r1i3n[3-6,9-10]
intel-256    up 20-00:00:0      1   idle r1i3n7
gpu          up 2-00:00:00      2   idle gpunode[0-1]
```

A lista abaixo mostra o que representa cada campo de saída do comando sinfo.

- **PARTITION**: Partições do supercomputador
  - **cluster**: Partição padrão indicada pelo asterisco, composta por 64 nós
    computacionais em lâmina.
    \
    r1i0n[0-7, 9-12, 14-17], r1i1n[0-7, 9-16], r1i2n[0-7, 9-16] e r1i3n[0-7,
    9-16]
  - **test**: Partição para testes rápidos, composta por 72 (todos) nós
    computacionais. Jobs rodados na partição teste tem o valor de prioridade
    aumentado em 15000.
    \
    r1i0n[0-7, 9-12, 14-17], r1i1n[0-7, 9-16], r1i2n[0-7, 9-16], r1i3n[0-7,
    9-16], service[1-4, 8-11]
  - **service**: Partição composta por 4 nós computacionais.
    \
    service[1-4]
  - **knl**: Partição composta por 2 nós computacionais com grande número de
    núcleos.
    \
    service[8,9]
  - **gpu**: Partição composta por 2 nós computacionais com 8 GPUs cada.
    \
    service[10,11]
  - **full**: Partição composta por todos os 72 nós computacionais.
    \
    r1i0n[0-7, 9-12, 14-17], r1i1n[0-7, 9-16], r1i2n[0-7, 9-16], r1i3n[0-7,
    9-16], service[1-4, 8-11]

  Mais detalhes sobre o hardware podem ser vistos em
  [Hardware](http://npad.ufrn.br/hardware.php)

- **AVAIL**: Disponibilidade de cada partição (_Available_)

- **TIMELIMIT**: Tempo limite de execução do job na partição correspondente.
  Todas as partições possuem o tempo limite de 20 dias para execução do job.
  Exceto a partição teste, cujo o tempo limite é de 30 minutos com ganho na
  prioridade para execução.\
  **Formato do timelimit no comando sinfo**: Dias **-** horas **:** minutos
  **:** segundos, exemplo: 20-13:22:21 significa 20 dias, 13 horas, 22 minutos e
  21 segundos

- **NODES**: Número de nós de cada partição

- **STATE**: Campo mais relevante dado como resposta do comando sinfo. Seu
  resultado pode ter significados diferentes, dependendo da saída fornecida,
  conforme é possível verificar abaixo.
  - **alloc**: Indica que um conjunto de nós está em uso

  - **idle**: Indica que um conjunto de nós está ocioso

  - **down/drain**: Indica que um conjunto de nós se encontra indisponível

  - **maint/resv**: Indica que um conjunto de nós está reservados

  - **mix**: Indica que um conjunto de nós está sendo compartilhados por mais de
    um job

- **NODELIST**: Representa as listas de nós correspondentes a cada par
  partição/estado

### sprio

Sprio é usado para exibir componentes da prioridade da fila de jobs. Quanto
maior for seu valor, maior será a sua prioridade. São mostradas somente as
informações dos jobs que ainda não estão em execução. Caso seja de seu interesse
entender como se dá o cálculo da prioridade da fila de jobs,
[clique aqui](http://npad.ufrn.br/uso.php#fila-jobs).

#### Exemplo: sprio

```bash
sprio -l
          JOBID PARTITION     USER   PRIORITY       SITE        AGE      ASSOC  FAIRSHARE    JOBSIZE  PARTITION        QOS        NICE
         164854 intel-512 dnpinhei      25031          0       1000          0         31          0          0      24000           0
         165887 intel-512 dnpinhei      25031          0       1000          0         31          0          0      24000           0
         167884 cluster   dnpinhei      25031          0       1000          0         31          0          0      24000           0
         168322 intel-512 bpesilva       1486          0       1000          0        487          0          0          0           0
         168323 intel-512 bpesilva       1486          0       1000          0        487          0          0          0           0
         168333 intel-512 bpesilva       1486          0       1000          0        487          0          0          0           0
         168917 intel-512 bpesilva       1226          0        740          0        487          0          0          0           0
         170024 cluster   jxdlneto       1028          0        510          0        518          0          0          0           0
         170025 cluster   jxdlneto       1028          0        510          0        518          0          0          0           0
         170026 cluster   jxdlneto       1027          0        510          0        518          0          0          0           0
         170027 cluster   jxdlneto       1027          0        509          0        518          0          0          0           0
         170028 cluster   jxdlneto       1027          0        509          0        518          0          0          0           0
         170030 cluster   jxdlneto       1026          0        509          0        518          0          0          0           0
         170031 cluster   jxdlneto       1024          0        506          0        518          0          0          0           0
         170032 cluster   jxdlneto       1024          0        506          0        518          0          0          0           0
         170033 cluster   jxdlneto       1023          0        506          0        518          0          0          0           0
         170034 cluster    crcosta       1840          0        506          0       1334          0          0          0           0
         170035 cluster    crcosta       1838          0        504          0       1334          0          0          0           0
         170036 cluster    crcosta       1838          0        504          0       1334          0          0          0           0
         170037 cluster   scavalca       2984          0        504          0       2480          0          0          0           0
         170514 cluster   thsrodri       2423          0        446          0       1978          0          0          0           0
         170515 cluster   thsrodri       2423          0        446          0       1978          0          0          0           0
         170516 cluster   thsrodri       2423          0        446          0       1978          0          0          0           0
         170517 cluster   thsrodri       2423          0        446          0       1978          0          0          0           0
```

A lista abaixo mostra o que representa cada campo de saída do comando sprio.

- **JOBID**: Identificador (ID) do job em espera

- **USER**: Usuário que submeteu o job

- **PRIORITY**: Representa a prioridade do job na fila. Quanto maior seu valor,
  maior sua prioridade

- **AGE**: É utilizado para o cálculo da prioridade. Se o job acabou de ser
  submetido, então o AGE vale 0; caso o mesmo esteja em espera há 24 horas,
  então o AGE tem valor 500; a partir de 48 horas, esse campo passa a
  valer 1000. Quaisquer valores intermediários representam frações de tempo,
  obedecendo o padrão supracitado.

- **FAIRSHARE** É utilizado para o cálculo da prioridade, juntamente com o valor
  do campo AGE. Representa uma espécie de peso, compensação, no caso do usuário
  consumir uma quantidade menor ou maior do que sua fatia esperada.

- **JOBSIZE**: Campo irrelevante: não é utilizado no cálculo da prioridade

- **PARTITION**: Somente terá um valor caso a fila utilizada seja a test

- **QOS**: Representa simplesmente um bônus na prioridade, caso o usuário seja o
  administrador

- **NICE**: Campo irrelevante: não é utilizado no cálculo da prioridade

### squeue

Squeue exibe as informações gerais dos Job's que estão na fila ou executando.
Este comando possuí variações como:\
**squeue --start**: Exibe, além da fila, o tempo esperado para execução dos
jobs.\
**watch squeue**: Atualiza a exibição da fila a cada 2 segundos.

#### Exemplo: squeue

```bash
squeue
             JOBID PARTITION     NAME     USER ST       TIME  NODES NODELIST(REASON)
            167884   cluster   tupi10 dnpinhei PD       0:00     21 (Resources)
            170642   cluster   MIN_06 rbdpasso PD       0:00      2 (Priority)
            170639   cluster   MIN_03 rbdpasso PD       0:00      2 (Priority)
            170640   cluster   MIN_04 rbdpasso PD       0:00      2 (Priority)
            170641   cluster   MIN_05 rbdpasso PD       0:00      2 (Priority)
            170643   cluster   MIN_07 rbdpasso PD       0:00      2 (Priority)
            170037   cluster PascalAn scavalca PD       0:00      1 (Priority)
            170518   cluster    cout1 thsrodri PD       0:00      1 (Priority)
            170519   cluster    cout1 thsrodri PD       0:00      1 (Priority)
            170517   cluster    cout1 thsrodri PD       0:00      1 (Priority)
            170516   cluster    cout1 thsrodri PD       0:00      1 (Priority)
            170515   cluster    cout1 thsrodri PD       0:00      1 (Priority)
            170514   cluster    cout1 thsrodri PD       0:00      1 (Priority)
            170034   cluster   SLP_20  crcosta PD       0:00      1 (Priority)
            170035   cluster   SLP_21  crcosta PD       0:00      1 (Priority)
            170036   cluster   SLP_22  crcosta PD       0:00      1 (Priority)
            170659   cluster   SLP_31  crcosta PD       0:00      1 (Priority)
            170660   cluster   SLP_32  crcosta PD       0:00      1 (Priority)
            170661   cluster   SLP_33  crcosta PD       0:00      1 (Priority)
            170662   cluster   SLP_41  crcosta PD       0:00      1 (Priority)
            170663   cluster   SLP_42  crcosta PD       0:00      1 (Priority)
            170664   cluster   SLP_43  crcosta PD       0:00      1 (Priority)
            170025   cluster dinam_hw jxdlneto PD       0:00      1 (Priority)
            170026   cluster dinam_iw jxdlneto PD       0:00      1 (Priority)
            170024   cluster dinam_hw jxdlneto PD       0:00      1 (Priority)
            170027   cluster dinam_iw jxdlneto PD       0:00      1 (Priority)
            170028   cluster dinam_iw jxdlneto PD       0:00      1 (Priority)
            170030   cluster PBEqe_ge jxdlneto PD       0:00      1 (Priority)
            170032   cluster PBEd35qe jxdlneto PD       0:00      1 (Priority)
            170033   cluster PBEd36qe jxdlneto PD       0:00      1 (Priority)
            170031   cluster PBEd2qe_ jxdlneto PD       0:00      1 (Priority)
            170657   cluster complex_ ldflacer PD       0:00      1 (Priority)
            170658   cluster   Citopt bpesilva PD       0:00      1 (Priority)
            168024   cluster fwi-deli cdssanta  R 2-02:21:08      4 r1i0n[14-16],r1i1n9
```

A lista abaixo mostra o que representa cada campo de saída do comando squeue.

- **JOBID**: Identificador (ID) do job

- **PARTITION**: Fila do supercomputador que está sendo utilizada

- **NAME**: Nome do job.

- **USER**: Usuário que está executando aquele job

- **ST**: O estado em que se encontra o job. Abaixo seguem os dois estados
  possíveis em que um job pode se encontrar.
  - **PD** (**Pending**): Significa que o job está pendente, devido a uma ou
    mais razões. Neste caso, mais detalhes são mostrados no campo
    NODELIST(REASON)
  - **R** (**Running**): Significa que o job está em execução normal

- **TIME**: O tempo total em que o job está em execução

- **NODES**: O número de nós em que o job está sendo executado

- **NODELIST(REASON)**: Se o job estiver em execução, esse campo lista os nomes
  dos nós em que o job está sendo executado. Se o job estiver pendente, este
  campo mostra o motivo pelo qual o trabalho está pendente. Neste caso, os
  motivos podem ser:

  - **Resources**: Significa que os recursos de computação necessários para
    aquele job não estão disponíveis no momento

  - **Priority**: Indica que o job está aguardando sua vez na fila,seguindo a
    fila de prioridades

  - **Dependency**: Indica que o job está aguardando a conclusão de outro
    trabalho antes de ser executado. Dependências são solicitadas quando um
    trabalho é submetido

  - **PartitionTimeLimit**: Significa que o job solicitou mais tempo de execução
    do que a fila permite

  - **AssocGrpCpuLimit**: Indica que o grupo do usuário está executando próximo
    ao seu número máximo de núcleos de CPU permitidos

  - **AssocGrpCPURunMinsLimit**: Indica que executar aquele job colocaria o
    grupo do usuário além do número máximo de minutos de CPU alocados para os
    jobs atualmente em execução.

  - **AssocGrpMemLimit**: O grupo do usuário alocou sua quantidade máxima de RAM

  - **JobArrayTaskLimit**: Indica que aquele job está envolvido em um vetor
    (grupo) de tarefas limitado a executar em um número definido de núcleos de
    CPU de uma vez

### sbatch

Sbatch envia um script para o supercomputador, esse script é passado através do
nome do arquivo que for especificado, o sbach irá ler o script a partir da
entrada padrão. (Você pode encontrar como criar um script na Parte 2 do tutorial
referente à introdução ao supercomputador).

#### Exemplo

```bash
squeue -u scavalcanti
             JOBID PARTITION     NAME     USER ST       TIME  NODES NODELIST(REASON)
sbatch run_pascalanalyzer.sh
Submitted batch job 170926
squeue -u scavalcanti
             JOBID PARTITION     NAME     USER ST       TIME  NODES NODELIST(REASON)
            170926   cluster PascalAn scavalca PD       0:00      1 (Priority)
```

no exemplo acima, foi utilizado o comando **squeue** como o parâmetro **-u**
para mostrar as informações gerais dos jobs do usuário scavalcanti, tanto os que
estão executando. quanto os que estão na fila. Sendo que não havia nenhum job a
ser mostrado. Posteriormente, o comando **sbatch** foi usado para submeter um
job. Novamente, o comando squeue foi usado, mostrando que o job foi devidamente
submetido e aguarda na fila para ser executado.

### scancel

Scancel é utilizado para cancelar um job depois que ele foi submetido, podendo
ele estar na fila de espera ou em execução. O job será interrompido de imediato,
então seja sempre cuidadoso ao usar esse comando, lembrando sempre que ao
executar outro job você estará no final da fila. Entretando, você não precisa se
preocupar que nenhum usuário terá acesso ao job de outro, sendo assim, não há
riscos de alguém cancelar job's que não são seus.

#### Exemplo: scancel

```bash
squeue -u scavalcanti
             JOBID PARTITION     NAME     USER ST       TIME  NODES NODELIST(REASON)
            170926   cluster PascalAn scavalca PD       0:00      1 (Priority)
scancel 170926
squeue -u scavalcanti
             JOBID PARTITION     NAME     USER ST       TIME  NODES NODELIST(REASON)
```

No exemplo acima, foi utilizado o comando **squeue** como o parâmetro **-u**
para mostrar as informações gerais dos jobs do usuário scavalcanti, tanto os que
estão executando. quanto os que estão na fila. Sendo mostrado um único job em
espera. Posteriormente, o comando scancel foi usado para cancelar o único job
existente. Novamente, o comando squeue foi usado, mostrando que o job foi
devidamente deletado.
