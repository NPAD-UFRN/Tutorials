# Tutorial Introdução ao Supercomputador - Parte 1 (Linux)

- [Tutorial Introdução ao Supercomputador - Parte 1 (Linux)](#tutorial-introdução-ao-supercomputador---parte-1-linux)
  - [Criação de conta no Supercomputador](#criação-de-conta-no-supercomputador)
  - [Geração de chave SSH pública](#geração-de-chave-ssh-pública)
  - [Acessando o supercomputador](#acessando-o-supercomputador)
    - [Dica: Crie uma configuração para ssh](#dica-crie-uma-configuração-para-ssh)
  - [Copiando arquivos para o supercomputador](#copiando-arquivos-para-o-supercomputador)
    - [scp](#scp)
      - [Copiar Um arquivo DO SEU COMPUTADOR para o supercomputador usando scp](#copiar-um-arquivo-do-seu-computador-para-o-supercomputador-usando-scp)
      - [Copiar Um arquivo DO SUPERCOMPUTADOR para o seu computador usando scp](#copiar-um-arquivo-do-supercomputador-para-o-seu-computador-usando-scp)
    - [rsync](#rsync)
      - [Copiar Um arquivo DO SEU COMPUTADOR para o supercomputador usando rsync](#copiar-um-arquivo-do-seu-computador-para-o-supercomputador-usando-rsync)
      - [Copiar Um arquivo DO SUPERCOMPUTADOR para o seu computador usando rsync](#copiar-um-arquivo-do-supercomputador-para-o-seu-computador-usando-rsync)
    - [Acesso pelo Gnome files do Linux](#acesso-pelo-gnome-files-do-linux)
      - [Clique em Other Locations](#clique-em-other-locations)
      - [Digite o endereço do super pc](#digite-o-endereço-do-super-pc)
        - [Dica: Adicione nos favoritos](#dica-adicione-nos-favoritos)
  - [Informações extras sobre os comandos utilizados](#informações-extras-sobre-os-comandos-utilizados)

Neste tutorial iremos aprender a gerar a chave SSH, a acessar o supercomputador e a transferir arquivos para o supercomputador. Caso tenha alguma dúvida durante o tutorial, sinta-se à vontade para entrar em contato conosco através do e-mail atendimento\<at>npad.ufrn.b (substituindo \<at> por @).

## Criação de conta no Supercomputador

Para utilizar o supercomputador é necessário criar uma conta na nossa [Página de Cadastro](http://npad.ufrn.br/primeirospassos.php). Para realizar o cadastro, verifique qual o seu enquadramento na nossa Política de Acesso para saber qual o Tipo de Usuário da sua conta. Na Página de Primeiros Passos você obterá informações sobre o primeiro acesso. Depois de fazer o cadastro no site do NPAD, você receberá um e-mail confirmando sua inscrição. Após receber o e-mail, você poderá acessar o supercomputador do computador que gerou o par de chaves ssh observando as orientações presentes neste tutorial. Para realizar o cadastro, será necessário criar uma chave ssh.

## Geração de chave SSH pública

A chave ssh é um protocolo de autenticação que permite ao usuário trocar informações de maneira rápida e segura. Após criada a chave ssh pública, o usuário deverá realizar o cadastro e informar a chave gerada.

Para gerar sua chave ssh pública, abra seu terminal Linux e digite o comando a seguir:

```bash
ssh-keygen -t rsa
```

Irá ser realizado uma sequência de perguntas, apenas pressione enter em todas elas.

Para visualizar sua chave pública, abra seu terminal Linux e digite o comando a seguir:

```bash
cat ~/.ssh/id_rsa.pub
```

Se você pretende acessar o supercomputador a partir de mais de um computador, você precisará gerar novas chaves RSA para cada máquina diferente que você pretende utilizar e, então, deverá associá-las à sua conta do supercomputador, através da nossa Página de Adição de Chave. Posteriormente, você será informado via email e, confirmando que foi você mesmo que fez a solicitação, basta você clicar no link indicado para validar a nova chave. Repita esse procedimento cada nova chave a ser cadastrada.

## Acessando o supercomputador

O acesso ao supercomputador pode se dar de duas formas. A primeira via terminal do Linux e a segunda via interface gráfica.

Para acessar o supercomputador no Linux digite em seu terminal o comando a seguir:

```bash
ssh -p4422 nomeDoUsuario@sc.npad.imd.ufrn.br
```

substituindo o termo **nomeDoUsuario** pelo nome de usuário criado. Caso tenha feito tudo corretamente será apresentada a tela inicial do supercomputador:

```bash
Last login: Wed Apr 12 10:43:17 2023 from 201.17.86.147
╭──────────────────────────────────────── NPAD ────────────────────────────────────────╮
│  Núcleo de Processamento de Alto Desempenho - Universidade Federal do Rio Grande do  │
│                                        Norte                                         │
│                                                                                      │
│ ────────────────────────────────────── ALERTA ────────────────────────────────────── │
│                                                                                      │
│ O uso deste sistema é restrito apenas a usuários autorizados. Você deve possuir      │
│ permissões explícitas para acessar ou configurar este servidor. Todas as atividades  │
│ realizadas neste dispositivo estão sujeitas a monitoramento e gravação e poderão ser │
│ devidamente reportadas em caso de uso ilegal. Obrigado.                              │
│                                                                                      │
│ ─────────────────────────────────────── FAQ ──────────────────────────────────────── │
│                                                                                      │
│ Dúvidas? Veja nosso FAQ em http://npad.ufrn.br/faq.php                               │
│                                                                                      │
│ ─────────────────────────────────────── USO ──────────────────────────────────────── │
│                                                                                      │
│                            Uso atual dos nós do sistema                              │
│                  ┏━━━━━━━━━━━┳━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━━━━━━┓                   │
│                  ┃ Partição  ┃ Idle ┃ Mixed ┃ Alloc ┃ Maint/Down ┃                   │
│                  ┡━━━━━━━━━━━╇━━━━━━╇━━━━━━━╇━━━━━━━╇━━━━━━━━━━━━┩                   │
│                  │ cluster   │ 10   │ 9     │ 31    │ 1          │                   │
│                  │ service   │ 3    │ 0     │ 1     │ 0          │                   │
│                  │ test      │ 13   │ 9     │ 32    │ 1          │                   │
│                  │ intel-512 │ 0    │ 0     │ 6     │ 0          │                   │
│                  │ intel-256 │ 3    │ 3     │ 0     │ 1          │                   │
│                  │ gpu       │ 2    │ 0     │ 0     │ 0          │                   │
│                  └───────────┴──────┴───────┴───────┴────────────┘                   │
│                                                                                      │
│ ────────────────────────────────────── QUOTA ─────────────────────────────────────── │
│                                                                                      │
│                     Você utilizou 81.5 % de sua quota de disco.                      │
│ ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╺━━━━━━━━━━━━━━━ │
│                                                                                      │
│ ───────────────────────────────────── NOTÍCIAS ───────────────────────────────────── │
│                                                                                      │
|                                      ...........                                     |
╰──────────────────────────────────────────────────────────────────────────────────────╯

[nomeDoUsuario@service0 ~]$
```

### Dica: Crie uma configuração para ssh

Se você criar ou adicionar a seguinte configuração no arquivo **~/.ssh/config**:

```bash
Host super-pc
  HostName sc2.npad.ufrn.br
  Port 4422
  User nomeDoUsuario
```

trocando o **nomeDoUsuario** pelo nome do sue usuário, você poderá acessar o supercomputador usando o comando:

```bash
ssh super-pc
```

## Copiando arquivos para o supercomputador

Para copiar arquivos para o supercomputador, você pode utilizar os programas **scp**, **rsync** ou acessar os arquivos remotamente pelo aplicativo de interface gráfica **gnome-files**.

### scp

#### Copiar Um arquivo DO SEU COMPUTADOR para o supercomputador usando scp

Para copiar o arquivo **meuArquivo** DO SEU COMPUTADOR para o super computador usando o programa **scp**. Abra um terminal Linux, use o seguinte comando:

```bash
# caso tenha configurado o ~/.ssh/config 
scp -r meuArquivo super-pc:~/
# caso não tenha configurado 
scp -r -P4422 meuArquivo nomeDoUsuario@sc2.npad.ufrn.br:~/
```

*LEMBRE-SE* de substituir o **nomeDoUsuario** para o seu usuário. Perceba que o arquivo a ser copiado está na pasta home do supercomputador.

#### Copiar Um arquivo DO SUPERCOMPUTADOR para o seu computador usando scp

Para copiar o arquivo: **meuArquivo** DO SUPERCOMPUTADOR para o seu computador na pasta **Downloads** usando o programa **scp**. Abra um terminal Linux, use o seguinte comando:

```bash
# caso tenha configurado o ~/.ssh/config 
scp -r super-pc:~/meuArquivo  ~/Downloads
# caso não tenha configurado 
scp -r -P4422  nomeDoUsuario@sc2.npad.ufrn.br:~/meuArquivo  ~/Downloads
```

*LEMBRE-SE* de substituir o **nomeDoUsuario** para o seu usuário. Perceba que o arquivo a ser copiado está na pasta home do supercomputador.

### rsync

Outra aplicação que permite copiar arquivos é o **rsync**. Em alguns sistemas eles
não vem instalado por padrão, certifique-se de que ele esteja instalado.

#### Copiar Um arquivo DO SEU COMPUTADOR para o supercomputador usando rsync

Para copiar o arquivo **meuArquivo** DO SEU COMPUTADOR para o super computador usando o programa **rsync**. Abra um terminal Linux, use o seguite comando:

```bash
# caso tenha configurado o ~/.ssh/config 
rsync  -aP  ~/Downloads/meuArquivo super-pc:~/
# caso não tenha configurado 
rsync  -aP  ~/Downloads/meuArquivo --rsh='ssh -p4422' -aP nomeDoUsuario@sc2.npad.ufrn.br:~/
```

*LEMBRE-SE* de substituir o **nomeDoUsuario** para o seu usuário. Perceba que o arquivo: **meuArquivo** a será copiado na pasta home do supercomputador. Perceba que  o arquivo **meuArquivo** está localizado na pasta Downloads.

#### Copiar Um arquivo DO SUPERCOMPUTADOR para o seu computador usando rsync

Para copiar o arquivo: **meuArquivo** DO SUPERCOMPUTADOR para o seu computador na pasta **Downloads** usando o programa **rsync**. Abra um terminal Linux, use o seguinte comando:

```bash
# caso tenha configurado o ~/.ssh/config 
rsync super-pc:~/meuArquivo  ~/Downloads
# caso não tenha configurado 
rsync --rsh='ssh -p4422' -aP nomeDoUsuario@sc2.npad.ufrn.br:~/meuArquivo  ~/Downloads
```

*LEMBRE-SE* de substituir o **nomeDoUsuario** para o seu usuário. Perceba que o arquivo a ser copiado está na pasta home do supercomputado

### Acesso pelo Gnome files do Linux

**Gnome** é a interface padrão do **Ubuntu**. Que é distribuição padrão
para desenvolvimento do Instituto Metrópole Digital (IMD). Portanto iremos mostrar como conectar o gestor de arquivos padrão do Gnome, chamado **Gnome files** com os seus arquivos no supercomputador.

![Imagem do Gnome files](/assets/superpc_linux_introduction/files.png)

#### Clique em Other Locations

Abra o gestor de arquivos Gnome files e clique em **Other Locations** como
apontado na imagem

![Clique em other Locations](/assets/superpc_linux_introduction/files_click_on_other_locations.png)

#### Digite o endereço do super pc

No canto inferior direito, digite o endereço do supercomputador. No caso o endereço varia de acordo com o seu nome de usuário:

```bash
ssh://nomeDoUsuario@sc2.npad.ufrn.br:4422
```

No entanto caso você tenha configurado o arquivo **~/.ssh/config**
o endereço pode ser escrito da seguinte forma:

```bash
ssh://super-pc
```

![Clique em other Locations](/assets/superpc_linux_introduction/enter_server_addresss.png)

##### Dica: Adicione nos favoritos

Para não precisar ficar refazendo este tutorial, você pode salvar o
o endereço do supercomputador nos favoritos, clicando com botão direito do mouse e depois em **add to Bookmarks**

![adicione nos favoritos](/assets/superpc_linux_introduction/add_bookmarks.png)

## Informações extras sobre os comandos utilizados

Sobre os comandos utilizados **rsync** e **scp**, você pode saber mais informações
sobre eles em suas respectivas referências:

- **scp**: [linux.die.net/man/1/scp](https://linux.die.net/man/1/scp)
- **rsync**: [linux.die.net/man/1/rsync](https://linux.die.net/man/1/rsync)
