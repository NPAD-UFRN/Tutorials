
# Geração de chave SSH pública

A chave ssh é um protocolo de autenticação que permite ao usuário trocar informações de maneira rápida e segura. Após criada a chave ssh pública, o usuário deverá realizar o cadastro e informar a chave gerada.

Para gerar sua chave ssh pública, abra Windows PowerShell e digite o comando a seguir:

```bash
ssh-keygen -t rsa
```

Irá ser realizado uma sequência de perguntas, apenas pressione enter em todas elas.

Para visualizar sua chave pública, digite o comando a seguir:

```ps1
cat .\.ssh\id_rsa.pub
```

Se você pretende acessar o supercomputador a partir de mais de um computador, você precisará gerar novas chaves RSA para cada máquina diferente que você pretende utilizar e, então, deverá associá-las à sua conta do supercomputador, através da nossa Página de Adição de Chave. Posteriormente, você será informado via email e, confirmando que foi você mesmo que fez a solicitação, basta você clicar no link indicado para validar a nova chave. Repita esse procedimento cada nova chave a ser cadastrada.