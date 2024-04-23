# Q3
A variavel soma é lida/escrita por mais de uma thread, cada thread é responsável por iterar o valor num loop de 0 até 100.000, mas enquanto há essa iteração, as duas threads realizam a mesma operação de escrita/leitura num loop de 0 até 100.000 simultaneamente. 

Com isso podemos ter o cenário em que uma thread esteja prestes a ler o valor atual de soma, enquanto outra thread já o incrementou, mas esse incremento ainda não foi refletido na leitura da primeira thread. Isso poderia resultar em uma contagem final menor do que o esperado.

# Q4
o loop for impede que o incremento da variável soma passe dos 200.000, ainda que não haja acesso de leitura/escrita simultanea, o loop itera de 0 até 100.000 para cada uma das duas threads, ou seja, no melhor a variavel soma seria incrementada em 200.000



