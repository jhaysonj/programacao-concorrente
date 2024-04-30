# Questão 2
(a) O que é seção crítica do código em um programa concorrente?
é um trecho do código executado por mais de uma thread em que ocorre leitura/escrita de uma variável compartilhada, permitindo que haja inconsistências por conta de diferentes fluxos de "baixo nivel" 
de execução manipulando (lendo/escrevendo) sob uma mesma variável.

(b) O que é corrida de dados em um programa concorrente?
é o erro gerado pelo não tratamento seção crítica, ou seja, pela falta de sincronização. Neste caso, múltiplas threads podem escrever diferentes resultados sob uma mesma variável, mas 
devido ao não tratamento, apenas uma das escritas sob essa variável é salvo, gerando assim um erro.

(c) O que é violação da atomicidade em um programa concorrente?
Atomicidade é quando o código torna as operações realizadas pelas threads atomicas, ou seja, apenas uma thread executa bloco do código, enquanto as outras threads esperam essa única thread
terminar a execução de todo o bloco, com isso apenas uma variável manipula variáveis compartilhadas por vez.
Com isso, definimos violar a atomicidade quando esse bloco que deveria ser "indivisivel" é interrompido antes de sua execução terminar por completo, levando a resultados incorretos e 
incosistentes

(d) o que é violação de ordem em um programa concorrente?
são inconsistências de "baixo nivel" em que o hardware/compilador alteram a ordem das instruções para gerar otimização e com isso geram inconsistências.

thread 1:
(1)     mov eax, 2
(2)     mov ebx, 1
(3)     add eax, ebx

thread 2:
(4)    mov eax, 0
(5)    mov ebx, 20

no exemplo de violação de ordem é: se executarmos a instrução (1), (2), (5) e (3) , respectivamente, o resultado é diferente de executarmos (1), (2) e (3), também respectivamente.



(e) como funciona a sincronização por exclusão mútua com bloqueio (que usa locks)?
Na exclusão mútua, "cercamos" o trecho de código em que há seção crítica com a seção de entrada e seção de saida.

// seção de entrada
// seção critica
// seção de saida

Dessa forma, quando a thread for entrar na seção crítica ela "locka" esse bloco de código, com isso, apenas essa thread tem permissão de execução desse trecho, as outras threads
não conseguem executar esse mesmo bloco. Quando a thread que "lockou" a seção crítica terminar de executar o bloco chegando na seção de saida, ela dá "unlock", liberando para que
outra thread execute a seção crítica.
Com essa técnica, garantimos que apenas uma thread acesse uma seção crítica de cada vez.

(f) Como funciona a sincronização condicional com bloqueio (que usa as funcões wait, signal e broadcast)?
FALTA FAZER

(g) Por que mecanismos de comunicação e sincronização são necessários para a programação concorrente?
A comunicação é importante em diversos casos, um deles é para utilização da técnica bolsa de tarefas, onde há necessidade de comunicação entre as threads para que as threads
não executem a mesma tarefa mais de uma vez, melhorando o desempenho.
Um caso importante de sincronização é que: na programação concorrente, podemos dividir uma tarefa grande entre as threads disponíveis, com isso surge a necessidade de
sincronização, um exemplo disso é que se eu não sincronizo as threads, abro margem para uma thread mais rápida terminar a sua execução e o programa finalizar sem que
as outras threads terminem de realizar as suas tarefas, gerando resultandos inconsistêntes.
Neste caso, a sincronização nos permite garantir que todas as threads terminaram de realizar as suas tarefas e os resultados estão de acordo com o que é esperado.

# questão 3
## caso 1
Nesse caso, temos duas threads (Thread 1 e Thread 2). Como nós, programadores, estamos mais acostumados a pensar de forma sequencial, tendemos a assumir que pequenos trechos de código 
serão executados de forma atômica. Os programadores assumiram que, se o valor avaliado na sentença 1 (S1) for diferente de NULL, então esse mesmo valor será usado na sentença 2 (S2).
No entanto, pode ocorrer, em uma execução concorrente, que a sentença 3 (S3) quebre essa premissa de atomicidade, causando um erro na aplicação.

Thread 1:
```
S1: if (thd->proc_info) { 
S2: fputs(thd->proc_info,...);
}
```

Thread 2:
```
S3: thd->proc_info=NULL;
```

(a) Mostre qual ordem de execução das sentenças pode gerar o erro.
s1, s3 e s2
(b) Proponha uma correção no código para evitar esse erro.
A correção é respeitar a atomicidade das operações feitas, usando exclusão mútua na leitura/escrita da variável compartilha, da seguinte forma:
thread 1:
```
lock(identificador_thread, mutex)
S1: if (thd->proc_info) { 
S2: fputs(thd->proc_info,...);
}
unlock(identificador_thread, mutex)
```

thread 2:
```
lock(identificador_thread, mutex)
S3: thd->proc_info=NULL;
...
unlock(identificador_thread, mutex)
```


## caso 2 (falta fazer)
Nesse caso, também temos duas threads (Thread 1 e Thread 2). A Thread 2 só deveria acessar a variável mThread depois que ela fosse devidamente inicializada.

(c) Proponha uma correção no código para garantir que essa condição seja sempre satisfeita.
Thread 1:
```
void init(...) {
    mThread = PR_CreateThread(mMain, ...);
    // Mais código de inicialização...
}

```

Thread 2:
```
void mMain(...) {
    mState = mThread->State;
    // Mais código para executar...
}
```


Uma aplicação dispara três threads (T1, T2 e T3) para execução (códigos mostrados abaixo). Verifique se os valores 1, -1, 0, 2, -2, 3, -3, 4, -4 podem ser impressos na saida padrão quando essa aplicação é executada. Em caso afirmativo, mostre uma sequência de execução das threads que gere o valor correspondente:

int x = 0; // variável global
Thread 1:
```
(1)     x = x-1;
(2)     x = x+1;
(3)     x = x-1;
(4)     if (x == -1)
(5)         printf("%d",x);
```

Thread 2:
```
(6)     x = x+1;
(7)     x = x-1;
```

Thread 3:
```
(8)     x = x+1;
(9)     if(x == 1)
(10)        printf("%d",x);
```

Para o valor 1, a ordem da execução é: (8), (9) e (10), respectivamente

Para o valor -1, a ordem de execução é: (1), (2), (3) e (4)

Para o valor 0, a ordem de execução é: (8), (9), (1) e (10)


Para o valor 2, a ordem de execução é: (8), (9), (6) e (10)

Para o valor -2, a ordem de execução é: (1), (2 e 6 ao "mesmo tempo", de forma que só uma escrita de x++ seja computada), (3), (4), (7) e (5)

Para o valor 3, a ordem de execução é: (8), (9), (1 e 6 ao "mesmo tempo", de forma que só x++ seja escrita na memória), (2) e (10)

