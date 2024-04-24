# Tempos de execução
com 10⁶ e 4 threads:
Tempo de processamento: 0.057146 segundos
Tempo de processamento: 0.058984 segundos
Tempo de processamento: 0.058568 segundos
Tempo de processamento: 0.059033 segundos
Tempo de processamento: 0.059147 segundos



com 10⁶ e 2 threads:
Tempo de processamento: 0.096655 segundos
Tempo de processamento: 0.096477 segundos
Tempo de processamento: 0.096932 segundos                                                                                                                                         
Tempo de processamento: 0.096760 segundos
Tempo de processamento: 0.097077 segundos


com 10⁶ e 1 thread:
Tempo de processamento: 0.170146 segundos
Tempo de processamento: 0.168899 segundos
Tempo de processamento: 0.168670 segundos
Tempo de processamento: 0.169326 segundos
Tempo de processamento: 0.168964 segundos
                                            



com 10³ e 4 threads:
Tempo de processamento: 0.000202 segundos
Tempo de processamento: 0.000217 segundos
Tempo de processamento: 0.000179 segundos
Tempo de processamento: 0.000156 segundos
Tempo de processamento: 0.000191 segundos


com 10³ e 2 threads:
Tempo de processamento: 0.000197 segundos
Tempo de processamento: 0.000183 segundos
Tempo de processamento: 0.000203 segundos
Tempo de processamento: 0.000178 segundos                                                                                                                                           
Tempo de processamento: 0.000200 segundos



com 10³ e 1 threads:
Tempo de processamento: 0.000205 segundos
Tempo de processamento: 0.000204 segundos
Tempo de processamento: 0.000197 segundos
Tempo de processamento: 0.000193 segundos
Tempo de processamento: 0.000186 segundos


# Relatório

## Tempo médio de processamento
base_10e6_1 = 0.169201
base_10e6_2 = 0.096780
base_10e6_4 = 0.058575

Com isso, temos que o tempo de é bastante reduzido conforme aumentamos o número de threads


base_10e3_1 = 0.000197
base_10e3_2 = 0.000192
base_10e3_4 = 0.000188
Apesar da redução no tempo de execução, o ganho de tempo é quase nulo, o que nos leva a concluir que a quantidade de tarefas realizadas é bastante pequena, consequentemente, ganha-se pouco ao acrescentar uma maior quantidade de threads


## Aceleração
os dados obtidos para acelaração são:
Aceleração para 10⁶
com 2 threads: 1.7483054350072327
com 4 threads: 2.8886214255228335
Ao analisarmos o cenário com 10⁶ temos muitas tarefas, cenário onde a aceleração é beneficiada de acordo que aumentamos a quantidade de threds  


Aceleração para 10³
com 2 threads: 1.0260416666666665
com 4 threads: 1.047872340425532
Com isso, podemos entender que, a quantidade de tarefas com 10³ é pequena e, com isso não conseguimos uma aceleração suficientemente boa, ou seja, temos muito processamento para poucas tarefas, cenário em que o aumento das threads gera pouco benefícios de aceleração.


## Eficiência
Eficiência para 10⁶
com 2 threads: 0.8741527175036163
com 4 threads: 0.7221553563807084
Como esperado pela análise feita no tempo de execução do 10⁶, a eficiencia para 10⁶ é suficientemente boa pois o tempo reduzido foi muito grande, , ou seja, acrescentar uma maior quantidade de threads trouxe grandes benefícios de redução de tempo, aumentando a eficiência.


Eficiência para 10³
com 2 threads: 0.5130208333333333
com 4 threads: 0.261968085106383
Como esperado pela análise feita no tempo de execução do 10³, a eficiencia para 10³ é bastante ruim pois o tempo reduzido foi muito pequeno, ou seja, acrescentar uma maior quantidade de threads não trouxe grandes benefícios de redução de tempo, diminuindo a eficiência.


Link para os gráficos:
https://colab.research.google.com/drive/1hcQ-y7KzEk-3wJZu9LikdLD_9sXTBfSq?usp=sharing


