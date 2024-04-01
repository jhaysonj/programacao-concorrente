#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// #define TESTE 

int tamanho_do_vetor;
float *vetor;

typedef struct {
   int idThread, index_inicial, index_final;
   float soma_parcial;
} t_Args;

void *soma(void *arg) {
    t_Args *args = (t_Args*)arg;
    
    float soma = 0;

    /*
    // tmp, apenas para fins de teste    
    printf("Thread %d\n", args->idThread);
    printf("Index_inicial %d\n", args->index_inicial);
    printf("Index_final %d\n", args->index_final);
    */

    // Calcula a soma parcial dos elementos atribuídos à thread
    for(int i = args->index_inicial; i < args->index_final; i++) {
        soma += vetor[i];
    }

    // Armazena a soma parcial na estrutura da thread
    args->soma_parcial = soma;

    // Termina a execução da thread
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    float resultado_validador;
    
    // Verifica se o número correto de argumentos está de acordo com o esperado
    if (argc != 2) {
        printf("Modo de Uso:\n./%s (quantidade_de_threads) < (file.txt)\n", argv[0]);
        exit(-1);
    }

    // Lê o número de threads a serem utilizadas
    int m_threads = atoi(argv[1]); // ascii to int
    printf("Quantidade de threads: %d\n", m_threads);

    pthread_t tid_sistema[m_threads];

    // Lê o tamanho do vetor e aloca memória para ele
    scanf("%d", &tamanho_do_vetor);
    vetor = (float *)malloc(tamanho_do_vetor * sizeof(float));
    if (vetor == NULL) {
        printf("Erro ao alocar memória para o vetor.\n");
        return 1;
    }

    // Lê os elementos do vetor a partir do arquivo ou da entrada padrão
    for (int i = 0; i < tamanho_do_vetor; i++) {
        scanf("%f", &vetor[i]);
    }

    // Lê o resultado válido esperado
    scanf("%f", &resultado_validador); // Lê o tamanho_do_vetor do vetor

    // Inicializa a estrutura de argumentos para as threads
    t_Args args[m_threads];
    int elementos_por_thread = tamanho_do_vetor / m_threads;
    int resto = tamanho_do_vetor % m_threads;

    // Divide o vetor em intervalos para cada thread e cria as threads
    int index_inicial = 0;
    for (int i = 0; i < m_threads; i++) {
        args[i].idThread = i;
        args[i].index_inicial = index_inicial;
        args[i].index_final = index_inicial + elementos_por_thread + (i < resto ? 1 : 0);

        // Ajusta o índice final para a última thread, garantindo que todos os elementos sejam processados. Para o caso em que (tamanho_do_vetor / m_threads != 0)
        if (i == m_threads - 1) {  
            args[i].index_final = tamanho_do_vetor;  
        }

        // Cria a thread
        pthread_create(&tid_sistema[i], NULL, soma, (void*)&args[i]);

        index_inicial = args[i].index_final;
    }

    // Aguarda todas as threads terminarem e calcula a soma total
    float soma_total = 0;
    for (int i = 0; i < m_threads; i++) {
        pthread_join(tid_sistema[i], NULL);
        soma_total += args[i].soma_parcial;
    }

#ifdef TESTE
    // Valida se a resposta encontrada está certa
    if(soma_total - resultado_validador < 0.0001 ){
        printf("Resposta está correta\n");
    } else {
        printf("Resposta está errada\n");
    }

    for(int i = 0; i < tamanho_do_vetor; i++){
        printf("\nvetor[%d] = %f\n", i, vetor[i]);
    }
#endif

    // Imprime a soma total e verifica se está correta
    printf("Soma total: %.2f\n", soma_total);

    // Libera a memória alocada para o vetor
    free(vetor);

    return 0;
}
