#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>

// #define teste // define a variavel de teste

// Variável global para bolsa de tarefas
int i_global; 

// Variavel que controla a quantidade de primos
int quantidade_primos = 0;

// Mutex para exclusão mútua
pthread_mutex_t mutex;

// Função para verificar se um número é primo
int ehPrimo(long long int n) {
    if (n <= 1) return 0; // não é primo
    if (n == 2) return 1; // 2 é primo
    if (n % 2 == 0) return 0; // pares não são primos
    for (long long int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return 0; // divisível por outro número
    }
    return 1;
}

// Função executada pelas threads
void* checaPrimo(void* arg) {
    int limite = *((int*)arg);
    while (1) {
        int n;

        // Protege a variável global com mutex
        pthread_mutex_lock(&mutex);

        if (i_global >= limite) {
            pthread_mutex_unlock(&mutex); // Desbloqueia o mutex
            break; // Sai do loop se o limite for alcançado
        }

        n = i_global; // Obtém o valor atual
        i_global++; // Incrementa o valor global

        pthread_mutex_unlock(&mutex); // Desbloqueia o mutex

        int resultado = ehPrimo(n);
        
        // Se o resultado é true, incrementa a quantidade de primos
        if(resultado){
            pthread_mutex_lock(&mutex); // Bloqueia o mutex    
            quantidade_primos += 1;
            pthread_mutex_unlock(&mutex); // Desbloqueia o mutex
        }
        #ifdef teste
            printf("Número: %d, Primo: %s\n", n, resultado ? "Sim" : "Não");
        #endif
        
    }

    pthread_exit(NULL); // Sai da thread
}

// Função principal
int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Digite: %s <numero_limitante> <numero_de_threads>\n", argv[0]);
        return 1;
    }

    int limite = atoll(argv[1]); // Limite de tarefas, controla até qual número verificamos a primalidade
    int numero_de_threads = atoi(argv[2]); // Quantidade de threads
    
    // Variaveis de controle do tempo de processamento
    struct timespec process_init, process_end;
    double process_time;



    // Array para identificadores de threads
    pthread_t tid_sistema[numero_de_threads]; 

    // Inicializa o mutex
    pthread_mutex_init(&mutex, NULL);

    i_global = 0; // Inicializa a variável global


    // Cria as threads
    for (int i = 0; i < numero_de_threads; i++) {
        if (pthread_create(&tid_sistema[i], NULL, checaPrimo, (void*)&limite)) {
            fprintf(stderr, "Erro ao criar a thread.\n");
            return 1;
        }
    }
    // Inicia a contagem do tempo de processamento
    clock_gettime(CLOCK_MONOTONIC, &process_init);

    // Aguarda as threads finalizarem
    for (int i = 0; i < numero_de_threads; i++) {
        pthread_join(tid_sistema[i], NULL);
    }

    // Finaliza a contagem do tempo de processamento
    clock_gettime(CLOCK_MONOTONIC, &process_end);

    printf("No total, obtemos %d números primos\n", quantidade_primos);

    process_time = (process_end.tv_sec - process_init.tv_sec) + (process_end.tv_nsec - process_init.tv_nsec) / 1.0e9;     // segundos com precisão decimal 
    printf("Tempo de processamento: %f segundos\n", process_time);        // tempo do processamento

    // Destrói o mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
