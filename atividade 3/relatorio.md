
# Relatorio


# Modo de Execução e Descrição dos Arquivos
   
   ./gera_matriz_binario 500 500 matrizA_500x500.bin --> gera a matriz com `I=linhas` e ` J=colunas`, respectivamente, e joga a saída para o arquivo `matrizA_500x500.bin`.
<br>
   ./atividade_sequencial_tempo matrizA_1000x1000.bin matrizB_1000x1000.bin  --> realiza a multiplicação da matriz A.B (de forma sequencial), marcando o tempo de execução.
<br>    
   ./atividade_concorrente_tempo matrizA_1000x1000.bin matrizB_1000x1000.bin  7 --> realiza multiplicação da matriz A.B de forma concorrente usando 7 threads, onde cada thread é responsável por calcular uma linha da matriz resultante. O programa também marca o tempo de execução.
<br>    
   matrizA_IxJ.bin -> I = linha; J = coluna
   matrizB_IxJ.bin -> I = linha; J = coluna
<br>
   O arquivo `atividade_sequencial_tempo_output` faz o mesmo o programa `atividade_sequencial_tempo` mas na versão output o programa a única coisa que é printada é o tempo de execução em segundos. O mesmo vale para os arquivos `atividade_concorrente_tempo_output` e `atividade_concorrente_tempo`
<br>
   O arquivos `tempo_exec_8_500x500.txt` armazena o tempo de execução/média da multiplicação das matrizes A.B (de proporção 500x500), usando oito threads. No arquivo possuimos 4 linhas, as três primeiras linhas são marcações do tempo, a quarta linha é a média dessas três execuções. O mesmo vale para os programas `tempo_exec_4_500x500.txt`, `tempo_exec_2_500x500.txt` e `tempo_exec_1_500x500.txt`
<br>
   O arquivo `tempo_exec_sequencial_500x500.txt` armazena o tempo de execução/média da multiplicação das matrizes A.B (de proporção 500x500). No arquivo possuimos 4 linhas, as três primeiras linhas são marcações do tempo, a quarta linha é a média dessas três execuções. O mesmo vale para os programas `tempo_exec_sequencial_1000x1000.txt` e `tempo_exec_sequencial_2000x2000.txt`




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
    Adaptei o código concorrente de nome `atividade_concorrente.c` para marcar o tempo de execução, o arquivo que marca o tempo é `atividade_concorrente_tempo.c`


 ## Concorrente 8 threads
 | Proporção Matricial              |Primeira Execução | Segunda Execução | terceira Execução | Tempo médio das Execuções |
|------------------------------------|------------------------------|--------------------|--------------------|--------------------|
|  A_500x500 . B_500x500        |     0.085104          | 0.063207  | 0.054768 | 0.067693 |
|  A_1000x1000 . B_1000x1000    |     0.674220        | 0.701084  | 0.636321 | 0.670541|
|   A_2000x2000 . B_2000x2000   |     3.517383        | 3.813261 | 3.836993  | 3.722545|


 ## Concorrente 4 threads
 | Proporção Matricial              |Primeira Execução | Segunda Execução | Terceira Execução | Tempo médio das Execuções |
|------------------------------------|------------------------------|--------------------|--------------------|--------------------|
|  A_500x500 . B_500x500        |   0.103148   |0.102794  | 0.102399 | 0.102780
|  A_1000x1000 . B_1000x1000    |  0.935894    | 0.895576 | 0.952828 |0.928099
|   A_2000x2000 . B_2000x2000   |   7.294940   | 7.396435 | 7.528636 |7.406670


 ## Concorrente 2 threads
 | Proporção Matricial              |Primeira Execução | Segunda Execução | Terceira Execução | Tempo médio das Execuções |
|------------------------------------|------------------------------|--------------------|--------------------|--------------------|
|  A_500x500 . B_500x500        |   0.201540     |  0.204210 |  0.211041 | 0.205597 | 
|  A_1000x1000 . B_1000x1000    |   1.833039     |  1.816652 |  1.922438 | 1.857376 |
|   A_2000x2000 . B_2000x2000   |  14.652272     | 14.480858 | 14.415987 | 14.51637 |


 ## Concorrente 1 thread
 | Proporção Matricial              |Primeira Execução | Segunda Execução | terceira Execução | Tempo médio das Execuções |
|------------------------------------|------------------------------|--------------------|--------------------|--------------------|
|  A_500x500 . B_500x500        |  0.401758    | 0.412664  |0.400439  | 0.404953 |
|  A_1000x1000 . B_1000x1000    |   3.537170   | 3.586013  |3.434316  | 3.519166 |
|   A_2000x2000 . B_2000x2000   |   27.749604  | 28.130647 |27.487149 | 27.789133 |




## Sequencial
 | Proporção Matricial              |Primeira Execução | Segunda Execução | terceira Execução | Tempo médio das Execuções |
|------------------------------------|------------------------------|--------------------|--------------------|--------------------|
|  A_500x500 . B_500x500        |       0.333889   |  0.336449   |   0.334188  | 0.334842 |
|  A_1000x1000 . B_1000x1000    |    2.670733      |  2.672200   |   2.668152  | 2.668947 |
|   A_2000x2000 . B_2000x2000   |      23.418286   | 23.322102   |  23.700522  | 23.480303 |
 |


## Configuração da Máquina
CPU: AMD Ryzen 7 3800X (16) @ 4.200GHz 
GPU: NVIDIA GeForce RTX 3060 Lite Hash Rate 
Memory: 23941MiB 

## Aceleração e Eficiência
Os dados obtidos durante a execução concorrente foram utilizados no colab para plotar o gráfico de aceleração e eficiência.
https://colab.research.google.com/drive/1KW-AZaG68V3BK5TnKy6nIPrg_UEq_JMa?usp=sharing

# Conclusão
Como era esperado o programa concorrente possui tempo médio de execução mais rápido. Esse "ganho de tempo" é notório para os casos em que possuimos mais tarefas, cenário em que poupamos tempo dividindo as tarefas entre as threads. Um comportamento que vale destacar é que o programa sequencial executa a tarefa mais rápido do que o programa concorrente de 1 thread, isso se dá pela quantidade de instruções em cada implementação, em que o programa concorrente executa uma série de blocos "inúteis" para o caso de possuir 1 única thread, enquanto o programa sequencial não e, consequentemente, o programa sequencial calcula a multiplicação de A.B de forma mais direta e rápida.


    
# Links de Referencia:
video para leitura de binários - https://www.youtube.com/watch?v=RzUtyDjJQzw
material escrito para leitura de binários - https://www.ic.unicamp.br/~cmartins/Cursos/mc102/slides/mc102z-a27-4pp.pdf
