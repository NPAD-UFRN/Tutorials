# Tutorial Introdução ao Supercomputador - Parte 1 (Linux)

Neste tutorial iremos aprender a gerar a chave SSH, a acessar o supercomputador e a transferir arquivos para supercomputador. Caso tenha alguma dúvida durante o tutorial, sinta-se à vontade para entrar em contato conosco através do e-mail atendimento\<at>npad.ufrn.b (substituindo \<at> por @).

## Criação de conta no Supercomputador

Para utilizar o supercomputador é necessário criar uma conta na nossa [Página de Cadastro](http://npad.ufrn.br/primeirospassos.php). Para realizar o cadastro, verifique qual o seu enquadramento na nossa Política de Acesso para saber qual o Tipo de Usuário da sua conta. Na Página de Primeiros Passos você obterá informações sobre o primeiro acesso. Depois de fazer o cadastro no site do NPAD, você receberá um e-mail confirmando sua inscrição. Após receber o e-mail, você poderá acessar o supercomputador do computador que gerou o par de chaves ssh observando as orientações presentes nesse tutorial. Para realizar o cadastro, será necessário criar uma chave ssh.

## Geração de chave SSH pública

A chave ssh é um protocolo de autenticação que permite o usuário trocar informações de maneira rápida e segura. Após criada a chave ssh pública, o usuário deverá realizar o cadastro e informar a chave gerada.

Para gerar sua chave ssh pública, abra seu terminal Linux e digite o comando a seguir:

```bash
ssh-keygen -t rsa
```

Irá ser realizado uma seguência de perguntas, apenas precione enter em todos elas.

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

substituindo o termo **nomeDoUsuario** pelo nome de usuário criado. Caso tenha feito tudo corretamente será apresentaa a tela inicial do supercomputador:

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

### Dica

Se você criar ou adicionar a seguinte configuração no arquivo **~/.ssh/config**:

```bash
Host super-pc
  HostName sc2.npad.ufrn.br
  Port 4422
  User nomeDoUsuario
```

trocando o **nomeDoUsuario** pelo nome do sue usuário, você poderá acessar o super compudor
usando o comando:

```bash
ssh super-pc
```

## Copiando arquivos para o supercomputador

Para copiar arquivos para o supercomputador, você pode utilizar os programas **scp**, **rsync** ou acessar os arquivos remotamente pelo aplicativo de interface gráfica **gnome-files**.

### scp

#### Copiar Um arquivo DO SEU COMPUTADOR para o super computador usando scp

Para copiar o arquivo **meuArquivo** DO SEU COMPUTADOR para o super computador usando o programa **scp**. Abra um terminal Linux, use o seguite comando:

```bash
# caso tenha configurado o ~/.ssh/config 
scp -r meuArquivo super-pc:~/
# caso não tenha configurado 
scp -r -P4422 meuArquivo nomeDoUsuario@sc2.npad.ufrn.br:~/
```

#### Copiar Um arquivo DO SUPER COMPUTADOR para o seu computador usando scp

Para copiar o arquivo: **meuArquivo** DO SUPER COMPUTADOR para o seu computador na pasta **Downloads** usando o programa **scp**. Abra um terminal Linux, use o seguite comando:

```bash
# caso tenha configurado o ~/.ssh/config 
scp -r super-pc:~/meuArquivo  ~/Downloads
# caso não tenha configurado 
scp -r -P4422  scavalcanti@sc2.npad.ufrn.br:~/meuArquivo  ~/Downloads
```

*LEMBRE-SE* de substituir o **nomeDoUsuario** para o seu usuário.

### rsync

Outra aplicação que permite copiar arquivos é o **rsync**

