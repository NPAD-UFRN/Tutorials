# Tutorial do scp

**scp** é um aplicação  que copia arquivos entre dois computadores pela internet
através do **ssh**. É possível utilizar o scp tanto no Linux quando no Windows.

## Copiar um arquivo DO SEU COMPUTADOR para o supercomputador usando scp

Para copiar o arquivo **meuArquivo** DO SEU COMPUTADOR para o super computador usando o programa **scp**. Abra um terminal Linux, use o seguinte comando:

```bash
# caso tenha configurado o ~/.ssh/config 
scp -r meuArquivo super-pc:~/
# caso não tenha configurado 
scp -r -P4422 meuArquivo nomeDoUsuario@sc2.npad.ufrn.br:~/
```

*LEMBRE-SE* de substituir o **nomeDoUsuario** para o seu usuário. Perceba que o arquivo a ser copiado está na pasta home do supercomputador.

## Copiar um arquivo DO SUPERCOMPUTADOR para o seu computador usando scp

Para copiar o arquivo: **meuArquivo** DO SUPERCOMPUTADOR para o seu computador na pasta **Downloads** usando o programa **scp**. Abra um terminal Linux, use o seguinte comando:

```bash
# caso tenha configurado o ~/.ssh/config 
scp -r super-pc:~/meuArquivo  ~/Downloads
# caso não tenha configurado 
scp -r -P4422  nomeDoUsuario@sc2.npad.ufrn.br:~/meuArquivo  ~/Downloads
```

*LEMBRE-SE* de substituir o **nomeDoUsuario** para o seu usuário. Perceba que o arquivo a ser copiado está na pasta home do supercomputador.

