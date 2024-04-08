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
    if (argc != 3) {
        printf("Uso: %s <arquivo_1.bin> <arquivo_2.bin>\n", argv[0]);
        return 1;
    }

    // realiza medição do tempo (em segundos)
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // realiza leitura das matrizes A e B dos arquivos binários (fornecidos como argumentos)
    Matriz *matrizA = ler_matriz(argv[1]);
    Matriz *matrizB = ler_matriz(argv[2]);

    
    Matriz *resultado = multiplicar_matrizes(matrizA, matrizB);

    // imprime a matriz resultante
    printf("Resultado da multiplicação de A.B :\n");
    for (int i = 0; i < resultado->linhas; i++) {
        for (int j = 0; j < resultado->colunas; j++) {
            printf("%f ", resultado->dados[i * resultado->colunas + j]);
        }
        printf("\n");
    }


    // liberar memória alocada para as matrizes
    liberar_matriz(matrizA);
    liberar_matriz(matrizB);
    liberar_matriz(resultado);

     // finaliza a contagem do tempo (em segundos)
    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsedTime = (end.tv_sec - start.tv_sec);     
    printf("Tempo de execução: %f segundos\n", elapsedTime);
    return 0;
}
