# <center> EP2 – MAC0422 - Sistemas Operacionais
<center> Lucas Moretto da Silva - 9778602</center>
<br>

## Informações da VDI

O minix foi instalado em d0p0. Caso o usuário seja deslogado ou o minix seja desligado (shutdown),
favor logar com usuário root (não precisa de senha) e bootar em d0p0 (boot d0p0).

- **Teclado padrão:** br-abnt2
- **Usuário:** root
- **Senha do usuário:** não possui senha

## Implementação

Esse trabalho implementa a chamada de sistema
`lockpriority(pid, priority)` e `unlockpriority(pid)`, que altera a prioridade de um processo
filho (PID passado como parametro) para `priority`. 

A chamada `lockpriority` retorna
`priority` se a alteração foi feita com sucesso, -1 se `pid` não for de
um processo filho e -2 se `priority` não for um valor permitido pelo
sistema.

Foi criado um simples programa em C para testar a nova chamada de sistema.
O arquivo de código fonte é `/usr/local/src/teste.c`. Seu executável é
`/usr/local/bin/teste-priority`. Para rodar basta acessar `/usr/local/bin/` e
rodar:

```shell
./teste-priority
```

Todos os arquivos alterados possuem sessões de comentário do tipo abaixo,
nos locais onde o código foi incluído ou alterado:

```
/* ################################################# */
/* ##################codigo alterado################ */
/* #############Lucas Moretto da Silva############## */

... <bloco de código alterado>

/* ################################################# */

```

Abaixo segue a lista dos arquivos alterados ou criados e qual papel eles
desempenham na implementação:

### Diretório: `/usr/src/servers/pm/`

    -   Arquivos: `proto.h, table.c, lockpriority.c, Makefile`

    -   Função: Implementa as chamadas de sistema no nível do *Process
        Manager* (PM) e manda a chamada pro *kernel* alterar a
        prioridade do processo.

### Diretório: `/usr/src/servers/is/`

    -   Arquivos: `dmp_kernel.c, dmp.c, proto.h`

    -   Função: Altera o funcionamento da tecla `F4`, para mostrar a
        lista de processos, com suas prioridades, PIDs, tempos de CPU e
        de sistema e endereço do ponteiro na pilha.

### Diretório: `/usr/src/lib/posix/`

    -   Arquivos: `_lockpriority.c, Makefile.in`

    -   Função: Implementa as funções lockpriority e unlockpriority de nível de usuário, que faz a
        chamada para o PM.

### Diretório: `/usr/src/lib/syslib/`

    -   Arquivos: `sys_lockpriority.c`

    -   Função: Implementa a função que permite que o PM chame o *system
        task*, que então faz a chamada para o *kernel*.

### Diretório: `/usr/src/include/`

    -   Arquivos: `unistd.h, minix/callnr.h, minix/com.h`

    -   Função: Define os macros `LOCKPRIORITY`, `UNLOCKPRIORITY` e `SYS_LOCKPRIORITY`
        para os números da chamada de sistema no nível do PM e do
        *kernel*, respectivamente e também o protótipo de `lockpriority`
        para o usuário.

### Diretório: `/usr/src/kernel/`

    -   Arquivos: `system.h, system.c, system/do_lockpriority.c`

    -   Função: Implementa a chamada no nível do kernel.
