# Instalação de programas no supercomputador

No supercomputador, há diversos programas instalados para todos os usuários. Caso deseje instalar um novo software no supercomputador, você pode solicitar que a equipe do NPAD faça a instalação, através da nossa [Página de Solicitação de Software](http://npad.ufrn.br/solicitarNovoSoftware.php). Entretanto, esse pedido de software será analisado e apenas softwares a serem utilizados por diversos pesquisadores serão aprovados. Os software aprovados entrarão na fila de tarefas da equipe do NPAD e serão instalados assim que possível. Caso sua necessidade de instalação seja urgente ou o software que você deseja instalar não seja largamente utilizado por pesquisadores, você poderá instalar o programa desejado na sua pasta pessoal seguindo uma das duas formas de instalação.
Instalação manual ou através do gerenciador de pacotes

[TOC]

## Instalação manual (recomendado)

A instalação manual se resume em baixar, compilar o código fonte e instalar na pasta home. A instalação manual é a recomendada pois dessa forma você está livre para realizar as modificações que quiser, escolher a versão que quiser sem a necessidade de intervenção da equipe NPAD. No entanto, exige um conhecimento avançado sobre Linux que muitos clientes não possuem.

### Exemplo: instalação manual do programa htop

Baixando o **htop**. No meu caso estou na minha pasta home, ao executar o comando.

```bash
wget https://github.com/htop-dev/htop/archive/refs/tags/3.2.2.tar.gz
```

ao finalizar o download terei baixado o arquivo: **3.2.2.tar.gz** que representa o código do htop na sua versão **3.2.2**. Posso visualizar o arquivos com o comando **ls**.

```bash
# comando ls na minha pasta home
ls
3.2.2.tar.gz  etc  libvips  pascal-parsec  pkgs  scratch 
```

O arquivo está compactado no formato **.tar.gz**. Então vou descompactar
o arquivo.

```bash
tar -xf 3.2.2.tar.gz 
```

Listando o diretório novamente verei que agora tenho uma pasta chamada
**htop-3.2.2**.

```bash
ls
3.2.2.tar.gz  etc  htop-3.2.2  libvips  pascal-parsec  pkgs  scratch 
```

Entro do diretório do **htop-3.2.2** e inicio o processo de configuração e compilação do pacote seguindo a documentação do projeto <https://github.com/htop-dev/htop#compile-from-source>

```bash
cd  htop-3.2.2;
```

Segundo a documentação preciso executar 3 comandos **autogen\.sh**, .**/configure** e **make**. Sendo o último comando a  compilação. Segundo a documentação o comando **./configure**, aceita o parâmetro **--prefix** referente ao local de instalação do pacote. Como não se pode instalar nenhum programa globalmente no supercomputador, então deve-se passar um outro diretório. Segundo a [freedesktop.org](https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html) é recomendado instalar aplicações de usuário na pasta oculta: **~/.local** ou  **$HOME/.local**, caso não exista essa pasta, crie.

```bash
# configurando e compilando o htop
./autogen.sh && ./configure --prefix=$HOME/.local && make
# instalando o htop
make install
```

Agora posso executar htop da seguinte forma

```bash
~/.local/bin/htop
```

Como você instalou o htop na pasta padrão do **freedesktop**, então se você relogar ou executar o comando

```bash
source ~/.bashrc
```

irá perceber que o htop está disponível nas suas variáveis de ambiente ou seja, pode executar o htop da seguinte forma:

```bash
htop --version
htop 3.2.2
```

perceba que a versão que vem instalada por padrão é a **3.0.5**

```bash
/bin/htop --version
htop 3.0.5
```

## Instalando programas utilizando o yumdownloader

Ao acessar sua pasta no supercomputador, execute o seguinte comando para baixar o seu programa.

```bash
yumdownloader <nome do programa>
```

O yumdownloader irá procurar em diferentes repositórios  uma versão empacotada **.rpm** do programa que você pesquisou. Caso você encontre o pacote é possível instalar o programa na sua pasta home com os programas: `rpm2cpio` e `cpio`, através do seguinte comando:

```bash
rpm2cpio <nome do arquivo baixado>.rpm | cpio -idv 
```

Se tudo der certo o programa será instalado no caminho relativo: `./usr`.

### Exemplo: Instalação do htop através do yumdownloader

Procure o **htop** nos repositórios com `yumdownloader`

```bash
yumdownloader htop
```

Caso yumdownloader encontre o pacote ele irá baixá-lo para você

```bash
ls
etc  htop-3.2.1-1.el8.x86_64.rpm  libvips  pascal-parsec  pkgs  scratch 
```

no caso do htop ele encontrou uma versão mais antiga da aplicação a versão **3.2.1**. Para instalar o htop no diretório: `./usr`,  basta usar o comando:

```bash
rpm2cpio  htop-3.2.1-1.el8.x86_64.rpm | cpio -idv 
```

Perceba que ele criou uma pasta **usr** no local onde você está e instalar o htop nessa pasta

```bash
ls 
etc  htop-3.2.1-1.el8.x86_64.rpm  libvips  pascal-parsec  pkgs  scratch  usr
```

Como eu utilizei o comando `rpm2cpio`  na minha pasta home. Então posso posso executar htop da seguinte forma

```bash
~/usr/bin/htop
```
