# Introdução ao Supercomputador - Parte 1 (Windows)

- [Introdução ao Supercomputador - Parte 1 (Windows)](#introdução-ao-supercomputador---parte-1-windows)
  - [Instalando o OpenSSH no Windows](#instalando-o-openssh-no-windows)
  - [Geração de chave SSH pública](#geração-de-chave-ssh-pública)
  - [Criação de conta no Supercomputador](#criação-de-conta-no-supercomputador)
  - [Acessando o supercomputador](#acessando-o-supercomputador)
    - [Dica: Crie uma configuração para ssh](#dica-crie-uma-configuração-para-ssh)
  - [Copiar Um arquivo DO SEU COMPUTADOR para o supercomputador usando scp](#copiar-um-arquivo-do-seu-computador-para-o-supercomputador-usando-scp)
  - [Copiar Um arquivo DO SUPERCOMPUTADOR para o seu computador usando scp](#copiar-um-arquivo-do-supercomputador-para-o-seu-computador-usando-scp)
  - [Informações extras sobre os comandos utilizados](#informações-extras-sobre-os-comandos-utilizados)

Neste tutorial iremos aprender a gerar a chave SSH, a acessar o supercomputador e a transferir arquivos para o supercomputador. Caso tenha alguma dúvida durante o tutorial, sinta-se à vontade para entrar em contato conosco através do e-mail atendimento\<at>npad.ufrn.b (substituindo \<at> por @).

## Instalando o OpenSSH no Windows

Na própria documentação oficial. A Microsoft oferece um tutorial de
como [instalar o OpenSSH](https://learn.microsoft.com/pt-br/windows-server/administration/openssh/openssh_install_firstuse). Ao Completar o tutorial
você deverá ser capaz de Abrir o **Windows PowerShell** e executar o comando **ssh**:

```PS
PS: C:\Users\tests> ssh
usage: ssh [-46AaCfGgKkMNnqsTtVvXxYy] [-B bind_interface]
           [-b bind_address] [-c cipher_spec] [-D [bind_address:]port]
           [-E log_file] [-e escape_char] [-F configfile] [-I pkcs11]
           [-i identity_file] [-J [user@]host[:port]] [-L address]
           [-l login_name] [-m mac_spec] [-O ctl_cmd] [-o option] [-p port]
           [-Q query_option] [-R address] [-S ctl_path] [-W host:port]
           [-w local_tun[:remote_tun]] destination [command [argument ...]]
```

## Geração de chave SSH pública

A chave ssh é um protocolo de autenticação que permite ao usuário trocar informações de maneira rápida e segura. Após criada a chave ssh pública, o usuário deverá realizar o cadastro e informar a chave gerada.

Para gerar sua chave ssh pública, abra Windows PowerShell e digite o comando a seguir:

```bash
ssh-keygen -t rsa
```

Irá ser realizado uma sequência de perguntas, apenas pressione enter em todas elas.

Para visualizar sua chave pública, abra o Windows PowerShell e digite o comando a seguir:

```PS
cat .\.ssh\id_rsa.pub
```

Se você pretende acessar o supercomputador a partir de mais de um computador, você precisará gerar novas chaves RSA para cada máquina diferente que você pretende utilizar e, então, deverá associá-las à sua conta do supercomputador, através da nossa Página de Adição de Chave. Posteriormente, você será informado via email e, confirmando que foi você mesmo que fez a solicitação, basta você clicar no link indicado para validar a nova chave. Repita esse procedimento cada nova chave a ser cadastrada.

## Criação de conta no Supercomputador

Para utilizar o supercomputador é necessário criar uma conta na nossa [Página de Cadastro](http://npad.ufrn.br/primeirospassos.php). Para realizar o cadastro, verifique qual o seu enquadramento na nossa Política de Acesso para saber qual o Tipo de Usuário da sua conta. Na Página de Primeiros Passos você obterá informações sobre o primeiro acesso. Depois de fazer o cadastro no site do NPAD, você receberá um e-mail confirmando sua inscrição. Após receber o e-mail, você poderá acessar o supercomputador do computador que gerou o par de chaves ssh observando as orientações presentes neste tutorial. Para realizar o cadastro, será necessário criar uma chave ssh.

## Acessando o supercomputador

O acesso ao supercomputador pode se dar através de programa por linha de comando chamado **ssh**. Para acessar o supercomputador no Windows abra o Windows PowerShell e digite em seu terminal o comando a seguir:

```ps
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

Para criar o arquivo utilize o comando: **New-Item**  e para editar o aquivo pode utilizar o **NotePad**.

```PS
New-Item ~/.ssh/config
```

O arquivo estará armazenado em **C:\Users\\NomeDoSeuUsuario\.ssh\config**. É interessante criar o arquivo atráves do comando, pois atráves da interface gráfica o arquivo pode ter o nome **config.txt** ao invés de **config**.

## Copiar Um arquivo DO SEU COMPUTADOR para o supercomputador usando scp

Para copiar o arquivo **meuArquivo** DO SEU COMPUTADOR para o super computador usando o programa **scp**. Abra o Windows PowerShell, use o seguinte comando:

```ps
# caso tenha configurado o ~/.ssh/config 
scp -r meuArquivo super-pc:~/
# caso não tenha configurado 
scp -r -P4422 meuArquivo nomeDoUsuario@sc2.npad.ufrn.br:~/
```

*LEMBRE-SE* de substituir o **nomeDoUsuario** para o seu usuário. Perceba que o arquivo a ser copiado está na pasta home do supercomputador.

## Copiar Um arquivo DO SUPERCOMPUTADOR para o seu computador usando scp

Para copiar o arquivo: **meuArquivo** DO SUPERCOMPUTADOR para o seu computador na pasta **Downloads** usando o programa **scp**. Abra o Windows PowerShell, use o seguinte comando:

```bash
# caso tenha configurado o ~/.ssh/config 
scp -r super-pc:~/meuArquivo  ~/Downloads
# caso não tenha configurado 
scp -r -P4422  nomeDoUsuario@sc2.npad.ufrn.br:~/meuArquivo  ~/Downloads
```

*LEMBRE-SE* de substituir o **nomeDoUsuario** para o seu usuário. Perceba que o arquivo a ser copiado está na pasta home do supercomputador.

## Informações extras sobre os comandos utilizados

- **scp**: [learn microsoft scp](https://learn.microsoft.com/pt-br/azure/virtual-machines/copy-files-to-vm-using-scp)

- **ssh**: [learn microsoft ssh](https://learn.microsoft.com/pt-br/windows-server/administration/openssh/openssh_install_firstuse?tabs=gui)
