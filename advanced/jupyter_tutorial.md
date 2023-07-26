# Usando o Jupyter no supercomputador

O Jupyter é uma aplicação web de código-fonte aberto que permite você criar e compartilhar documentos (chamados de notebooks) que contém código, equações, visualizações e texto.

Para usar o jupyter no supercomputador, deve-se criar um script semelhante ao mostrado abaixo:

```bash
#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=10      #Quantidade de núcleos
#SBATCH --time=1-00:00          #Tempo máximo do job no formato DIAS-HORAS:MINUTOS
#SBATCH --hint=compute_bound

# Execute conda activate forge
# antes de submeter este script de job

## Parametros iniciais
XDG_RUNTIME_DIR=""
ipnport=$(shuf -i8000-9999 -n1)
ipnip=$(hostname -i)

## Imprime na saída slurm-{jobid}.out
echo -e "
    Copy/Paste this in your local terminal to ssh tunnel with remote
    Copie e cole no terminal local da sua máquina o comando abaixo
    -----------------------------------------------------------------

    ssh -N -L $ipnport:$ipnip:$ipnport -p4422 $USER@sc2.npad.ufrn.br

    -----------------------------------------------------------------
    "

## start an ipcluster instance and launch jupyter server
## Inicia servidor Jupyter

jupyter-lab --no-browser --port=$ipnport --ip=$ipnip  
```

 No nosso exemplo, o script foi salvo com nome script_jupyter.sh.

Com o script criado, siga as seguintes etapas para acessar o jupyter no supercomputador. 

Primeiro, ative o conda forge no terminal do supercomputador. Digite:

```bash
$ conda activate forge
```

Envie o job para fila de execução com o comando sbatch:

```bash
$ sbatch script-jupyter.sh 

Submitted batch job JOBID 
```

JOBID é número do job. Agora, verifique se o seu job está rodando com o comando squeue:

```bash
$ squeue -lu $USER
```

 Caso o job de código JOBID esteja com estado R (RUNNING) na coluna STATE, o job já foi iniciado e podemos seguir em diante. 

Use o comando cat slurm-JOBID.out (substitua JOBID com o número do job).
```bash
$ cat slurm-JOBID.out
```

Aparecerá uma mensagem contendo duas informações que você deveria copiar. A primeira é a seguinte:

```bash
ssh -N -L PORTA:IP:PORTA -p4422 NOMEDOUSUARIO@sc2.npad.ufrn.br
```

Trata-se de um comando para ser executado no terminal de seu computador. Nesse comando, PORTA é um valor númerico, IP são valores numéricos separados por ponto e NOMEDOUSUARIO é o nome do seu usuário no supercomputador.
Copie e cole e execute ele no terminal do seu computador. O terminal ficará travado.

A segunda informação é a seguinte:  

```bash
http://127.0.0.1:PORTA/lab?token=TOKEN 
```

Copie e cole no seu navegador e o jupyter irá aparecer. 

Quando terminar de usar o jupyter, destrave o terminal do seu computador com Ctrl+C. E também cancele o job do supercomputador:

```bash
$ scancel JOBID 
```
