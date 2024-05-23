#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <string.h>

long long int *buffer;  // buffer compartilhado
int buffer_size;        // tamanho do buffer
int num_consumidores;   // número de threads consumidoras
int total_primos = 0;   // contador global para total de primos encontrados
int *primos_por_thread; // array para contar a quantidade de primos encontrados por cada thread

sem_t slotCheio;        // semáforo para slots cheios
sem_t slotVazio;        // semáforo para slots vazios
sem_t mutex;            // semáforo para exclusão mútua

// função para verificar se um número é primo
int ehPrimo(long long int n) {
    int i;
    if (n <= 1)
        return 0;
    if (n == 2)
        return 1;
    if (n % 2 == 0)
        return 0;
    for (i = 3; i <= sqrt(n) + 1; i += 2)
        if (n % i == 0)
            return 0;
    return 1;
}

// função para o consumidor
void *consumidor(void *arg) {
    long id = (long)arg;
    long long int num;
    int primos_encontrados = 0;
    static int out = 0;  // variável estática para a posição de remoção no buffer

    while (1) {
        sem_wait(&slotCheio);
        sem_wait(&mutex);

        num = buffer[out];  // remove o número do buffer
        out = (out + 1) % buffer_size;  // atualiza a posição de remoção

        sem_post(&mutex);
        sem_post(&slotVazio);

        if (num == -1) {  // se encontrar o marcador de fim do arquivo
            primos_por_thread[id] = primos_encontrados;
            pthread_exit(NULL);
        }

        if (ehPrimo(num)) {
            primos_encontrados++;
        }
    }
}

// função para o produtor
void produtor(char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    long long int num;
    static int in = 0;  // variável estática para a posição de inserção no buffer

    while (fread(&num, sizeof(long long int), 1, file) == 1) {
        sem_wait(&slotVazio);
        sem_wait(&mutex);

        buffer[in] = num;  // inseri o número no buffer
        in = (in + 1) % buffer_size;  // atualiza a posição de inserção

        sem_post(&mutex);
        sem_post(&slotCheio);
    }

    fclose(file);  // fechar o arquivo

    // inseri o marcador de fim de arquivo no buffer para todas as threads consumidoras
    for (int i = 0; i < num_consumidores; i++) {
        sem_wait(&slotVazio);
        sem_wait(&mutex);

        buffer[in] = -1;  // inseri o marcador de fim de arquivo
        in = (in + 1) % buffer_size;  // atualizar a posição de inserção

        sem_post(&mutex);
        sem_post(&slotCheio);
    }
}

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Modo de uso: %s <arquivo.bin> <tamanho do buffer> <numero de threads consumidoras>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    buffer_size = atoi(argv[2]);
    num_consumidores = atoi(argv[3]);

    buffer = (long long int *)malloc(buffer_size * sizeof(long long int));
    if (buffer == NULL) {
        perror("Erro ao alocar memória para o buffer");
        return 1;
    }

    primos_por_thread = (int *)malloc(num_consumidores * sizeof(int));
    if (primos_por_thread == NULL) {
        perror("Erro ao alocar memória para o array de primos por thread");
        free(buffer);
        return 1;
    }
    memset(primos_por_thread, 0, num_consumidores * sizeof(int));

    sem_init(&slotCheio, 0, 0);
    sem_init(&slotVazio, 0, buffer_size);
    sem_init(&mutex, 0, 1);

    pthread_t cons[num_consumidores];
    int i;

    // inicializar threads consumidoras
    for (i = 0; i < num_consumidores; i++) {
        pthread_create(&cons[i], NULL, consumidor, (void *)(long)i);
    }

    // chamar a função do produtor
    produtor(filename);

    // aguardar término das threads consumidoras
    for (i = 0; i < num_consumidores; i++) {
        pthread_join(cons[i], NULL);
    }

    // calcular e exibir resultados
    int vencedora = 0;
    for (i = 1; i < num_consumidores; i++) {
        if (primos_por_thread[i] > primos_por_thread[vencedora]) {
            vencedora = i;
        }
    }

    for (i = 0; i < num_consumidores; i++) {
        total_primos += primos_por_thread[i];
    }

    printf("Total de primos encontrados: %d\n", total_primos);
    printf("Thread vencedora: %d com %d primos\n", vencedora, primos_por_thread[vencedora]);

    free(buffer);  // libera memória alocada para o buffer
    free(primos_por_thread);  // liberar memória alocada para o array de contagem de primos

    sem_destroy(&slotCheio);
    sem_destroy(&slotVazio);
    sem_destroy(&mutex);

    return 0;
}
