#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// definição da estrutura Matriz
typedef struct {
    int linhas;
    int colunas;
    float *dados;
} Matriz;

// declaração das funções
Matriz *criar_matriz(int linhas, int colunas);
void liberar_matriz(Matriz *matriz);
Matriz *ler_matriz(char *nome_arquivo);
Matriz *multiplicar_matrizes(Matriz *matrizA, Matriz *matrizB, int num_threads);
void *thread_multiplicacao(void *args);

// estrutura de argumentos para as threads
typedef struct {
    Matriz *matrizA;
    Matriz *matrizB;
    Matriz *resultado;
    int linha_inicial;
    int linha_final;
} ThreadArgs;

// função para alocar a matriz dinamicamente
Matriz *criar_matriz(int linhas, int colunas) {
    Matriz *matriz = malloc(sizeof(Matriz));
    if (matriz == NULL) {
        fprintf(stderr, "Erro de alocação de memória para matriz\n");
        exit(1);
    }
    matriz->linhas = linhas;
    matriz->colunas = colunas;
    matriz->dados = malloc(sizeof(float) * linhas * colunas);
    if (matriz->dados == NULL) {
        fprintf(stderr, "Erro de alocação de memória para dados da matriz\n");
        free(matriz);
        exit(1);
    }
    return matriz;
}

// função para liberar a memória alocada para uma matriz
void liberar_matriz(Matriz *matriz) {
    free(matriz->dados);
    free(matriz);
}

// função para ler uma matriz de um arquivo binário
Matriz *ler_matriz(char *nome_arquivo) {
    FILE *arquivo;
    int linhas, colunas;
    size_t ret;

    // abre o arquivo binário para leitura
    arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    // lê o número de linhas e colunas
    ret = fread(&linhas, sizeof(int), 1, arquivo);
    if (ret != 1) {
        fprintf(stderr, "Erro ao ler o número de linhas\n");
        fclose(arquivo);
        exit(1);
    }

    ret = fread(&colunas, sizeof(int), 1, arquivo);
    if (ret != 1) {
        fprintf(stderr, "Erro ao ler o número de colunas\n");
        fclose(arquivo);
        exit(1);
    }

    // aloca memória para a matriz
    Matriz *matriz = criar_matriz(linhas, colunas);

    // lê os elementos da matriz
    ret = fread(matriz->dados, sizeof(float), linhas * colunas, arquivo);
    if (ret != linhas * colunas) {
        fprintf(stderr, "Erro ao ler os elementos da matriz\n");
        fclose(arquivo);
        liberar_matriz(matriz);
        exit(1);
    }

    fclose(arquivo);
    return matriz;
}

// função para multiplicar duas matrizes
Matriz *multiplicar_matrizes(Matriz *matrizA, Matriz *matrizB, int num_threads) {
    // verifica se as dimensões das matrizes são compatíveis para multiplicação
    if (matrizA->colunas != matrizB->linhas) {
        fprintf(stderr, "Erro: Dimensões das matrizes incompatíveis para multiplicação\n");
        exit(1);
    }

    // aloca memória para a matriz resultante
    Matriz *resultado = criar_matriz(matrizA->linhas, matrizB->colunas);

    // calcula o número de linhas que cada thread será responsável
    int linhas_por_thread;
    if (num_threads > resultado->linhas) {
        // caso a quantidade de threads seja maior que o número de linhas, usa-se a quantidade de linhas como threads
        num_threads = resultado->linhas;
        linhas_por_thread = 1;
    } else {
        // divide as linhas entre as threads, com tratamento para o caso de sobra de linhas
        linhas_por_thread = resultado->linhas / num_threads;
    }

    // cria as threads para calcular as linhas da matriz resultante
    pthread_t threads[num_threads];
    ThreadArgs args[num_threads];

    int linha_inicial = 0;
    int linha_final = 0;

    for (int i = 0; i < num_threads; i++) {
        // define a linha inicial e final que a thread será responsável
        linha_inicial = i * linhas_por_thread;
        linha_final = (i + 1) * linhas_por_thread - 1;

        // atribui à última thread as linhas restantes, caso haja
        if (i == num_threads - 1 && linha_final < resultado->linhas - 1) {
            linha_final = resultado->linhas - 1;
        }

        // preenche os argumentos para a thread
        args[i].matrizA = matrizA;
        args[i].matrizB = matrizB;
        args[i].resultado = resultado;
        args[i].linha_inicial = linha_inicial;
        args[i].linha_final = linha_final;

        // cria a thread
        if (pthread_create(&threads[i], NULL, thread_multiplicacao, (void *)&args[i]) != 0) {
            fprintf(stderr, "Erro ao criar a thread\n");
            exit(1);
        }
    }

    // aguarda o término de todas as threads
    for (int i = 0; i < num_threads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Erro ao aguardar a thread\n");
            exit(1);
        }
    }

    return resultado;
}

// função executada por cada thread para calcular uma parte da matriz resultante
void *thread_multiplicacao(void *args) {
    ThreadArgs *thread_args = (ThreadArgs *)args;

    for (int i = thread_args->linha_inicial; i <= thread_args->linha_final; i++) {
        for (int j = 0; j < thread_args->matrizB->colunas; j++) {
            float soma = 0.0;
            for (int k = 0; k < thread_args->matrizA->colunas; k++) {
                soma += thread_args->matrizA->dados[i * thread_args->matrizA->colunas + k] * thread_args->matrizB->dados[k * thread_args->matrizB->colunas + j];
            }
            thread_args->resultado->dados[i * thread_args->resultado->colunas + j] = soma;
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <arquivo_1.bin> <arquivo_2.bin> <num_threads>\n", argv[0]);
        return 1;
    }

    // realiza medição do tempo (em segundos)
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // realiza a leitura das matrizes A e B dos arquivos binários fornecidos como argumentos
    Matriz *matrizA = ler_matriz(argv[1]);
    Matriz *matrizB = ler_matriz(argv[2]);

    int num_threads = atoi(argv[3]);

    // verifica se a quantidade de threads é válida
    if (num_threads <= 0) {
        fprintf(stderr, "Erro: Quantidade inválida de threads\n");
        return 1;
    }


    // multiplicar as matrizes
    Matriz *resultado = multiplicar_matrizes(matrizA, matrizB, num_threads);


    // imprime a matriz resultante
    printf("Resultado da multiplicação de A.B :\n");
    for (int i = 0; i < resultado->linhas; i++) {
        for (int j = 0; j < resultado->colunas; j++) {
            printf("%f ", resultado->dados[i * resultado->colunas + j]);
        }
        printf("\n");
    }

    // libera memória alocada para as matrizes
    liberar_matriz(matrizA);
    liberar_matriz(matrizB);
    liberar_matriz(resultado);


    
    // finaliza a contagem do tempo (em segundos)
    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsedTime = (end.tv_sec - start.tv_sec);     
    printf("Tempo de execução: %f segundos\n", elapsedTime);


    return 0;
}
