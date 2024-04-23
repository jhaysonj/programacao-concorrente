# Q2
com o `pthread_mutex_lock(&mutex);` sinalizamos que nenhuma outra thread, que não a atual, deve acessar a variável soma para leitura/escrita. Com isso conseguimos iterar no loop de 0 até 100.000 e escrever o valor correto da variavel soma, após toda iteração, desbloqueamos o acesso à variavel soma com `pthread_mutex_unlock(&mutex);`. O mesmo raciocínio é aplicado à outra thread.
Com isso, conseguimos realizar somatório correto da variavel soma = 200.000




