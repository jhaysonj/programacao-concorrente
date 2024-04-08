
# Relatorio


# Modo de Execução e Descrição dos Arquivos
   
   ./gera_matriz_binario 3000 3000 matrizA_3000x3000.bin --> gera a matriz com `I=linhas` e ` J=colunas`, respectivamente, e joga a saída para o arquivo `matrizA_3000x3000.bin`.

   ./atividade_sequencial_tempo matrizA_1000x1000.bin matrizB_1000x1000.bin  --> realiza a multiplicação da matriz A.B (de forma sequencial), marcando o tempo de execução.
    
   ./atividade_concorrente_tempo matrizA_1000x1000.bin matrizB_1000x1000.bin  7 --> realiza multiplicação da matriz A.B de forma concorrente usando 7 threads, onde cada thread é responsável por calcular uma linha da matriz resultante. O programa também marca o tempo de execução.
    
   matrizA_IxJ.bin -> I = linha; J = coluna
   matrizB_IxJ.bin -> I = linha; J = coluna



# Etapas de Idealição da Atividade

No código implementado, a multiplicação das matrizes é realizada na ordem em que as matrizes são passadas como argumentos. 
Portanto, se chamarmos o programa como `./atividade_sequencial_tempo matrizA.bin matrizB.bin`, a multiplicação A.B será realizada, onde A é a matriz lida do arquivo matrizA.bin e B é a matriz lida do arquivo matrizB.bin. Para realizar a multiplicação de B.A, a chamada do arquivo deve ser `./atividade_sequencial_tempo matrizA.bin matrizB.bin`.

Assim como o recomendado, realizei a entrega desse trabalho dividindo-o em algumas partes, sendo elas:

1) Implementação/validação do código sequencial
   Desenvolvi o código sequencial cujo nome é atividade_sequencial.c


2) Implementação da marcação de tempo (código sequencial)
    Adaptei o código sequencial de nome `atividade_sequencial.c` para marcar o tempo de execução, o arquivo que marca o tempo é `atividade_sequencial_tempo.c`

    Para matrizes pequenas o tempo de execução era impercepitível, tivemos que escalar a quantidade de linhas e colunas para que seja possível concluirmos alguma melhora na implementação sequencial x concorrente

3) Implementação/validação do código concorrente
    Desenvolvi o código concorrente cujo nome é atividade_concorrente.c


4) Implementação da marcação do tempo (código concorrente)
    Adaptei o código sequencial de nome `atividade_concorrente.c` para marcar o tempo de execução, o arquivo que marca o tempo é `atividade_concorrente_tempo.c`



## concorrente

| Implementação | Proporção Matricial              | Tempo de execução médio <br> com 8 threads 
|---------------|---------------------------|------------------------------|
| Concorrente <br>   | A_1000x1000 . B_1000x1000 |  1s    |
|               | A_1500x1500 . B_1500x1500|                 2s             |
|               | A_2000x2000 . B_2000x2000|  6s           |
|               | A_3000x3000 . B_3000x3000|          19s           |



| Implementação | Proporção Matricial              | Tempo de execução médio <br> com 7 threads 
|---------------|---------------------------|------------------------------|
| Concorrente <br>   | A_1000x1000 . B_1000x1000 |    1s  |
|               | A_1500x1500 . B_1500x1500|      3s                       |
|               | A_2000x2000 . B_2000x2000|   6s          |
|               | A_3000x3000 . B_3000x3000|     21s                |


| Implementação | Proporção Matricial              | Tempo de execução médio <br> com 4 threads 
|---------------|---------------------------|------------------------------|
| Concorrente <br>   | A_1000x1000 . B_1000x1000 |   1s   |
|               | A_1500x1500 . B_1500x1500|         5s                    |
|               | A_2000x2000 . B_2000x2000|     9s        |
|               | A_3000x3000 . B_3000x3000|     35s                |





| Implementação | Proporção Matricial              | Tempo de execução médio <br> com 2 threads 
|---------------|---------------------------|------------------------------|
| Concorrente <br>   | A_1000x1000 . B_1000x1000 |   2s   |
|               | A_1500x1500 . B_1500x1500|        7s                     |
|               | A_2000x2000 . B_2000x2000|       16s      |
|               | A_3000x3000 . B_3000x3000|       69s              |




| Implementação | Proporção Matricial              | Tempo de execução médio <br> com 1 thread 
|---------------|---------------------------|------------------------------|
| Concorrente <br>   | A_1000x1000 . B_1000x1000 |   4s   |
|               | A_1500x1500 . B_1500x1500|        14s                     |
|               | A_2000x2000 . B_2000x2000|      30s       |
|               | A_3000x3000 . B_3000x3000|         136s            |

## sequencial

| Implementação | Proporção Matricial              | Tempo de execução médio |
|---------------|---------------------------|------------------------------|
| Sequencial    | A_1000x1000 . B_1000x1000|        3s           |
|               | A_1500x1500 . B_1500x1500|         9s                   |
|               | A_2000x2000 . B_2000x2000|    24s                         |
|               | A_3000x3000 . B_3000x3000| 112s                   |




# Conclusão
Como era esperado o programa concorrente possui tempo médio de execução mais rápido. Esse "ganho de tempo" é notório para os casos em que possuimos mais tarefas, cenário em que poupamos tempo dividindo as tarefas entre as threads. Um comportamento que vale destacar é que o programa sequencial executa a tarefa mais rápido do que o programa concorrente de 1 thread, isso se dá pela quantidade de instruções em cada implementação, em que o programa concorrente executa uma série de blocos "inúteis" para o caso de possuir 1 única thread, enquanto o programa sequencial não e, consequentemente, o programa sequencial calcula a multiplicação de A.B de forma mais direta e rápida.


    
# Links de Referencia:
video para leitura de binários - https://www.youtube.com/watch?v=RzUtyDjJQzw
material escrito para leitura de binários - https://www.ic.unicamp.br/~cmartins/Cursos/mc102/slides/mc102z-a27-4pp.pdf
