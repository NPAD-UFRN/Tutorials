# Tutorial do rsync

Outra aplicação que permite copiar arquivos é o **rsync**. Em alguns sistemas eles
não vem instalado por padrão, certifique-se de que ele esteja instalado.

## Copiar um arquivo DO SEU COMPUTADOR para o supercomputador usando rsync

Para copiar o arquivo **meuArquivo** DO SEU COMPUTADOR para o super computador usando o programa **rsync**. Abra um terminal Linux, use o seguinte comando:

```bash
# caso tenha configurado o ~/.ssh/config 
rsync  -aP  ~/Downloads/meuArquivo super-pc:~/
# caso não tenha configurado 
rsync  -aP  ~/Downloads/meuArquivo --rsh='ssh -p4422' -aP nomeDoUsuario@sc2.npad.ufrn.br:~/
```

*LEMBRE-SE* de substituir o **nomeDoUsuario** para o seu usuário. Perceba que o arquivo: **meuArquivo** a será copiado na pasta home do supercomputador. Perceba que  o arquivo **meuArquivo** está localizado na pasta Downloads.

## Copiar um arquivo DO SUPERCOMPUTADOR para o seu computador usando rsync

Para copiar o arquivo: **meuArquivo** DO SUPERCOMPUTADOR para o seu computador na pasta **Downloads** usando o programa **rsync**. Abra um terminal Linux, use o seguinte comando:

```bash
# caso tenha configurado o ~/.ssh/config 
rsync super-pc:~/meuArquivo  ~/Downloads
# caso não tenha configurado 
rsync --rsh='ssh -p4422' -aP nomeDoUsuario@sc2.npad.ufrn.br:~/meuArquivo  ~/Downloads
```

*LEMBRE-SE* de substituir o **nomeDoUsuario** para o seu usuário. Perceba que o arquivo a ser copiado está na pasta home do supercomputador
