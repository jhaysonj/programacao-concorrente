# atividade 1
## questão 2
Qual e a finalidade das variáveis in e out e por que foram definidas como variáveis static?
A variável `in` faz o controle lógico que mantém o índice do próximo local de inserção no buffer. Cada vez que um produtor insere um item no buffer, a variável `in` é incrementada e, se atingir o final do buffer, volta ao início (graças à operação `in = (in + 1) % N`), o que caracteriza o comportamento circular do buffer.

Já a variável `out` faz o controle lógico que mantém o índice do próximo local de remoção do buffer. Cada vez que um consumidor remove um item do buffer, a variável `out` é incrementada e, se atingir o final do buffer, volta ao inicio (pela operação  `out = (out + 1) % N`), o que caracteriza o comportamento circular do buffer.

## questão 4
O programa executou corretamente? Como isso foi demonstrado? (falta fazer)
Sim, o código funciona porque implementa corretamente o padrão de sincronização necessário para o problema de Produtores e Consumidores usando semáforos para garantir exclusão mútua e condições de buffer (cheio e vazio).

**Descrição do Programa:**
As variaveis `sem_t`, `slotCheio`, `slotVazio`; são semáforos para controlar a condição do buffer.
A variável `sem_t mutexGeral` é um semáforo binário para garantir a exclusão mútua durante o acesso ao buffer.
O vetor `int Buffer[N]` é o buffer compartilhado de tamanho N.

A variável `mutexGeral` começa com 1 para permitir o primeiro acesso.
A variável `slotCheio` começa com 0 porque o buffer inicialmente está vazio.
A variável `slotVazio` começa com N porque todos os slots estão inicialmente vazios.

**Descrição da função `Insere`:**
1. Realiza o `sem_wait(&slotVazio)` para aguardar um slot vazio
2. Adquire mutexGeral para exclusão mútua (sem_wait(&mutexGeral)).
3. Insere o item no buffer.
4. Libera mutexGeral `sem_post(&mutexGeral)`.
5. Sinaliza que há um slot cheio `sem_post(&slotCheio)`.


**Descrição da função `Retira`:**
1. Aguarda um slot cheio `sem_wait(&slotCheio)`.
2. Adquire mutexGeral para exclusão mútua `sem_wait(&mutexGeral)`.
3. Remove o item do buffer.
4. Libera mutexGeral `sem_post(&mutexGeral)`.
5. Sinaliza que há um slot vazio `sem_post(&slotVazio)`.

**Funções produtor e consumidor:**
- Ambas as funções entram em loops infinitos onde os produtores inserem itens no buffer e os consumidores retiram itens do buffer, segundo a professora essa função tem como objetivo simular uma aplicação que funciona a todo instante.
- Após inserir ou retirar um item, as funções executam algum processamento simulado com laços que não fazem nada de significativo (for loops).

**Criação das Threads:**

- São criados PRODUTORES threads para os produtores e CONSUMIDORES threads para os consumidores.
- Cada thread recebe um identificador exclusivo (id) alocado dinamicamente.

**Execução do Programa:**

- A função pthread_exit(NULL) na função main permite que o programa continue a execução das threads criados indefinidamente.

**Sincronização:**

- O uso de sem_wait e sem_post em slotCheio e slotVazio garante que os produtores só inserem quando há espaço e os consumidores só retiram quando há itens.
- O uso de sem_wait e sem_post em mutexGeral garante que apenas um produtor ou consumidor acessa o buffer de cada vez, evitando condições de corrida.

**Analisando um Output do Programa:**
```
1 0 0 0 0  // Produtor 1 insere o valor 1
1 3 0 0 0  // Produtor 2 insere o valor 3
1 3 2 0 0  // Produtor 3 insere o valor 2
1 3 2 4 0  // Produtor 4 insere o valor 4
1 3 2 4 3  // Produtor 5 insere o valor 3
```

1. **Buffer inicial:** O primeiro produtor inseriu o valor 1 no buffer, anteriormente vazio `1 0 0 0 0`

2. **inserções subsequentes:** Outros produtores inseriram 3, 2, 4 e 3 respectivamente. Isso mostra que os produtores estão operando corretamente, preenchendo slots vazios no buffer. Ficamos com:
    ```
    1 3 0 0 0 
    1 3 2 0 0 
    1 3 2 4 0 
    1 3 2 4 3 

    ```

3. **Remoção e Novas Inserções:** Um consumidor removeu o valor 1, liberando o primeiro slot, e um produtor inseriu 10 no slot vazio. Isso demonstra a interação correta entre produtores e consumidores, com sincronização adequada.

4. Operações Simultaneas: Consumidores estão removendo valores do buffer e liberando slots, enquanto produtores continuam inserindo valores, preenchendo esses slots. A operação é consistente com a lógica esperada do problema.
    ```
    10 0 2 4 3 // Consumidor removeu 3
    10 4 0 4 3 // Consumidor removeu 2
    ```

    O mesmo ocorre em 
    ```
    10 4 10 4 3 // Produtor inseriu 10
    10 4 10 0 3 // Consumidor removeu 4
    ```
Portanto, a saída demonstra a execução correta do programa.

# Atividade 2
**Explicações gerais `gera_numeros.c`:**
o arquivo `gera_numeros.c` é o responsável por gerar `n` números primos de 1 até n, do tipo long long int, armazenando-os em um arquivo binário que será utilizado pela implementação sequencial e concorrente

**Compilação:**
```
gcc -o gera_numeros gera_numeros.c -Wall
```
**Execução:**
```
./gera_numeros <quantidade_termos> <arquivo_de_saida>
```
**Exemplo:** 
```
./gera_numeros 1000 lista_de_numeros
```


**Explicações gerais `valida_gera_numeros.c`** 
O arquivo `valida_gera_numeros.c` serve para printar o conteudo do binário gerado no arquivo `gera_numeros.c`, validando que a escrita foi feita corretamente
Compilação: 
```
gcc -o valida_gera_numeros valida_gera_numeros.c -Wall
```
Execução: 
```
./gera_numeros <numeros_de_termos> <arquivo.bin>
```
obs: `arquivo.bin` é o arquivo de onde vamos realizar a leitura

**Exemplo:**
```
./gera_numeros 1000 lista_de_numeros.bin
```


**Explicações gerais `atividade2_sequencial.c`:**
O programa `aividade2_sequencial.c` implementa a lógica do que é pedido na atividade 2, mas de forma sequencial, para validar os resultados do programa concorrente.

**Compilação:** 
```
gcc -o atividade2_sequencial atividade2_sequencial.c -Wall -lm
```
**Execução:** 
```
./atividade2_sequencial arquivo.bin
```
**Exemplo:** 
```
./atividade2_sequencial lista_de_numeros.bin
```

obs: vale destacar que o programa sequencial serve apenas para validar o resultado do programa concorrente. 
O programa sequencial realiza a leitura de todo o arquivo binário enviando cada um dos valores para a função `ehPrimo`.


**Explicações gerais `atividade2_concorrente.c`:**
**Compilação:**
```
gcc -o atividade2_concorrente atividade2_concorrente.c -Wall -lpthread -lm
```

**Modo de Execução de `ativdade2.c`: 
```
./atividade2 <arquivo.bin> <tamanho_do_buffer> <quantidade_de_threads_consumidoras>
```
Exemplo: 
```
./atividade2_concorrente lista_de_numeros_10000.bin 10 2
```


**A função produtor realiza a leitura do arquivo binário:**
    Abre o arquivo binário para leitura (fopen).
    Lê números inteiros de 64 bits (long long int) um a um (fread).
    Após ler todos os números, fecha o arquivo (fclose).

**Armazenamento em Buffer:**
	Cada número lido é armazenado no buffer compartilhado.
	Usa semáforos para controlar o acesso ao buffer (sem_wait(&slotVazio), sem_wait(&mutex)).
	Insere o número no buffer na posição indicada pela variável estática in.
	Atualiza a posição de inserção (in).
	Libera os semáforos após inserir o número (sem_post(&mutex), sem_post(&slotCheio)).

Processamento por Threads Consumidoras
    Espera por um número no buffer (sem_wait(&slotCheio), sem_wait(&mutex)).
    Remove o número da posição indicada pela variável estática out.
    Atualiza a posição de remoção (out).
    Libera os semáforos após remover o número (sem_post(&mutex), sem_post(&slotVazio)).
    Verifica se o número é primo (ehPrimo).
    Incrementa o contador de primos encontrados se o número for primo.
    Se o número removido for -1, a thread termina e armazena seu contador de primos no array primos_por_thread.


**Validação do Resultado:**
A fim de validar o resultado, como os testas são feitos com entradas dinamicas, é necessário executar a versão sequencial e concorrente para a mesma entrada de arquivo binário.

**Considerações Finais:**
É possível gerar uma nova lista de números usando o arquivo `gera_numeros.c`, eu realizei os testes de validação com dois arquivos, um com 1.000 números e outro com 10.000 números.

