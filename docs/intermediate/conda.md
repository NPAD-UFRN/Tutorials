# Tutorial do Conda

[TOC]

### O que é conda?

É um gerenciador de pacotes e um sistema de gerenciamento de ambientes virtuais para várias linguagens como: Python, R, Ruby, Lua, Scala, Java, JavaScript, Go, C/ C++, FORTRAN. É também um software de código aberto e pode ser utilizado no Windows, Linux e MacOs. 

Atualmente, o conda é muito popular como gerenciador de pacotes do Python and R.  Originalmente, o conda foi desenvolvido para superar as dificuldades enfrentadas pelos cientistas de dados no gerenciamento de pacotes do Python (Wikipedia: Conda).

### Como usar os ambientes virtuais

No NPAD, existem diversos ambientes virtuais do conda com pacotes do Python pré-instalados a fim de atender os usuários.

Para visualizar os ambientes conda disponíveis no NPAD,  digite:

```bash
$ conda env list

# conda environments:
#
bioinformatics           /opt/npad/shared/conda/bioinformatics
biology                  /opt/npad/shared/conda/biology
forge                    /opt/npad/shared/conda/forge
forge2023                /opt/npad/shared/conda/forge2023
geral                    /opt/npad/shared/conda/geral
gpu                      /opt/npad/shared/conda/gpu
base                  *  /usr
```

A lista de ambientes mostrada pode ser diferente da lista acima por que os ambientes estão sempre sendo atualizados.

Para ativar, por exemplo, o ambiente virtual forge2023 da lista acima, digite:

```bash
$ conda activate forge2023
```

Uma vez ativado, o usuário já pode utilizar o python e os pacotes disponíveis naquele ambiente. A versão do python e dos pacotes variam de ambiente para ambiente.

Para visualizar os pacotes disponíveis, digite:

```bash
$ conda list
```

Para desativar um ambiente, digite:

```bash
$ conda deactivate 
```

### Submissão de jobs usando os ambientes virtuais

O ambiente virtual deve ser ativado antes da submissão do job ao supercomputador. Por exemplo, considere o seguinte script de job chamado de my-job.sh:

```bash
#!/bin/bash
#SBATCH --time=0-00:10
#SBATCH --nodes=1

python meuprograma.py 
```

Para submeter my-job.sh ao supercomputador usando o ambiente virtual forge2023, digite:

```bash
$ conda activate forge2023
$ sbatch my-job.sh
```

Caso seja necessário ativar o ambiente no próprio script de job,  você pode usar o seguinte exemplo: 

```bash
#!/bin/bash
#SBATCH --time=0-00:10
#SBATCH --nodes=1

eval "$(conda shell.bash hook)" # inclua esta linha antes executar o conda
conda activate forge2023
python meuprograma.py 
```

### Criação de ambientes virtuais

Se os ambientes disponíveis no sistema não forem satisfatórios para o usuário, ele mesmo pode criar seu próprio ambiente virtual.

Para criar um ambiente virtual básico digite:

```bash
$ conda create --name meu-amb python
```

A opção `--name` é usada para definir o nome do ambiente virtual. Neste exemplo, foi utilizado o nome meu-amb. Em seguida, pode-se especificar uma lista de pacotes a serem instalados . Por exemplo:

```bash
$ conda create --name meu-amb python numpy pandas matplotlib
```

Usando o sinal de igual "=", pode-se definir a versão do Python ou do pacote a ser instalado:

```bash
$ conda create --name meu-amb38 python=3.8 numpy=1.23.4 pandas
```

!!! Dica
    Apesar de poder adicionar pacotes ao ambiente após a sua criação, é recomendado instalar todos os pacotes ao mesmo tempo para evitar conflitos com dependência de pacotes. 

### Gerenciando os ambientes virtuais

Para gerenciar um ambiente virtual, primeiro ative ele. Por exemplo:

```bash
$ conda activate meu-ambz
```

Então, pode-se adicionar mais pacotes ao ambiente ativado. Por exemplo:

```bash
$ conda install pacote1 
```

O conda procura os pacotes para instalar nos repositórios padrão (default). Para instalar de pacote de outros repositórios, basta especificar o nome do repositório usando a opção `--channel`.  Por exemplo,

```bash
$ conda install pacote1 --channel=conda-forge
```
Para remover um pacote específico, use o comando `conda remove` seguido do nome do pacote a ser removido. Exemplo:

```bash
$ conda remove pacote 
```

Para remover um ambiente virtual, primeiro desative o ambiente e em seguida remova o ambiente como neste exemplo: 

```bash
$ conda deactivate 
$ conda remove --name meu-amb --all 
```

### Criando um ambiente a partir de um arquivo

Pode-se criar um ambiente a partir de um arquivo `environment.yml` contendo a relação de pacotes a serem instalados. Por exemplo

```bash
name: meu-amb
dependencies:
  - numpy
  - pandas
```

Então crie o ambiente de nome meu-amb, digitando:

```bash
conda env create -f environment.yml
```

Pode-se especificar também canais de repositórios e versões do pacote. Por exemplo

```bash
name: meu-amb
channels:
  - conda-forge
dependencies:
  - numpy=1.23.4
  - pandas
  - python=3.8 
  - matplotlib
```

### Acelerando a instalação de pacotes com Mamba

A instalação de pacotes pelo conda pode demorar bastante devido a resolução de dependências. Neste caso, você pode usar o Mamba para acelerar a instalação. O Mamba é um reimplementação do conda em linguagem C++ para tornar mais eficiente e rápido a instalação dos pacotes do conda.

O Mamba pode ser instalado como se fosse um pacote:

```bash
$ conda install mamba
```

Mamba utiliza uma linha de comando compatível com a do conda. Ou seja, usar  mamba é similar a usar conda. Exemplos:

Instalação de pacotes:

```bash
$ mamba install pacote1
```

Remoção de pacotes:

```bash
$ mamba remove pacote1
```

Lista de pacotes instalados:

```bash
$ mamba list
```

### Sobre o uso de pip e conda juntos

pip é o instalador de pacotes do Python. É possivel usar pip para instalar pacotes do Python em um ambiente virtual do conda. Geralmente, pip já está instalado quando for criado um ambiente virtual. Caso não esteja, é só instalar:

```bash
conda install pip
```

De acordo com o site do [conda](https://docs.conda.io/projects/conda/en/latest/user-guide/tasks/manage-environments.html#using-pip-in-an-environment), podem surgir problemas ao usar pip e conda juntos. Somente após o conda ter sido usado para instalar tantos pacotes quanto possível, o pip deve ser usado para instalar qualquer pacote restante. Se forem necessárias modificações no ambiente, é melhor criar um novo ambiente em vez de executar conda após pip.
