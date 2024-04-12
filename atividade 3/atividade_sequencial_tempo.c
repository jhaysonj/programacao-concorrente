#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// estrutura Matriz
typedef struct {
    int linhas;
    int colunas;
    float *dados;
} Matriz;

// declaração das funções
Matriz *criar_matriz(int linhas, int colunas);
void liberar_matriz(Matriz *matriz);
Matriz *ler_matriz(char *nome_arquivo);
Matriz *multiplicar_matrizes(Matriz *matrizA, Matriz *matrizB);

// função para alocar uma matriz dinamicamente
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

    // abre e realiza leitura do arquivo binário
    arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    // leitura do número de linhas e colunas
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
Matriz *multiplicar_matrizes(Matriz *matrizA, Matriz *matrizB) {
    // verifica se as dimensões das matrizes são compatíveis para multiplicação
    if (matrizA->colunas != matrizB->linhas) {
        fprintf(stderr, "Erro: Dimensões das matrizes incompatíveis para multiplicação\n");
        exit(1);
    }

    // aloca memória para a matriz resultante
    Matriz *resultado = criar_matriz(matrizA->linhas, matrizB->colunas);

    // realiza a multiplicação das matrizes
    for (int i = 0; i < matrizA->linhas; i++) {
        for (int j = 0; j < matrizB->colunas; j++) {
            float soma = 0.0;
            for (int k = 0; k < matrizA->colunas; k++) {
                soma += matrizA->dados[i * matrizA->colunas + k] * matrizB->dados[k * matrizB->colunas + j];
            }
            resultado->dados[i * resultado->colunas + j] = soma;
        }
    }

    return resultado;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <Matriz1.bin> <Matriz2.bin> <resultado.bin>\n", argv[0]);
        return 1;
    }

    // realiza medição do tempo (em segundos)
    struct timespec program_start, process_init, process_end, program_end;
    double cpu_time_used, start_time, process_time, finalization_time;

    // começa a contagem de inicialização
    clock_gettime(CLOCK_MONOTONIC, &program_start);

    // realiza leitura das matrizes A e B dos arquivos binários (fornecidos como argumentos)
    Matriz *matrizA = ler_matriz(argv[1]);
    Matriz *matrizB = ler_matriz(argv[2]);

    // começa a contagem de tempo de processamento
    clock_gettime(CLOCK_MONOTONIC, &process_init);

    Matriz *resultado = multiplicar_matrizes(matrizA, matrizB);

    // finaliza a contagem de tempo de processamento
    clock_gettime(CLOCK_MONOTONIC, &process_end);

    // escreve a matriz resultante no arquivo
    FILE *descritorArquivo = fopen(argv[3], "wb");
    if (!descritorArquivo)
    {
        fprintf(stderr, "Erro de abertura do arquivo\n");
        return 3;
    }
    // escreve numero de linhas e de colunas
    size_t ret = fwrite(&resultado->linhas, sizeof(int), 1, descritorArquivo);
    ret = fwrite(&resultado->colunas, sizeof(int), 1, descritorArquivo);
    // escreve os elementos da matriz
    ret = fwrite(resultado->dados, sizeof(float), resultado->colunas * resultado->linhas, descritorArquivo);
    if (ret < resultado->colunas * resultado->linhas)
    {
        fprintf(stderr, "Erro de escrita no arquivo\n");
        return 4;
    }

    // liberar memória alocada para as matrizes
    liberar_matriz(matrizA);
    liberar_matriz(matrizB);
    liberar_matriz(resultado);

    // finaliza a contagem do tempo (em segundos), para convertermos de nanosegundos para segundos dividimos por 1.0e9
    clock_gettime(CLOCK_MONOTONIC, &program_end);
    cpu_time_used = (program_end.tv_sec - program_start.tv_sec) + (program_end.tv_nsec - program_start.tv_nsec) / 1.0e9;  // segundos com precisão decimal 
    start_time = (process_init.tv_sec - program_start.tv_sec) + (process_init.tv_nsec - program_start.tv_nsec) / 1.0e9;   // segundos com precisão decimal 
    process_time = (process_end.tv_sec - process_init.tv_sec) + (process_end.tv_nsec - process_init.tv_nsec) / 1.0e9;     // segundos com precisão decimal 
    finalization_time = (program_end.tv_sec - process_end.tv_sec) + (program_end.tv_nsec - process_end.tv_nsec) / 1.0e9;  // segundos com precisão decimal 

    printf("Tempo de execução total: %f segundos\n", cpu_time_used);      // tempo total do programa
    printf("Tempo de inicialização: %f segundos\n", start_time);          // tempo de inicialização
    printf("Tempo de processamento: %f segundos\n", process_time);        // tempo do processamento
    printf("Tempo de finalização: %f segundos\n", finalization_time);     // tempo de finalização

    return 0;
}
