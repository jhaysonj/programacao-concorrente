#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
    FILE *file;
    long long int termos;
    long long int *numeros;

    if (argc != 3) {
        printf("Modo de uso: %s <numero de termos> <nome do arquivo>\n", argv[0]);
        return 1;
    }

    termos = atoll(argv[1]); // Usando atoll para converter para long long int

    numeros = (long long int *)malloc(termos * sizeof(long long int));
    if (numeros == NULL) {
        perror("Erro ao alocar memória");
        return 2;
    }

    // Inicializando o gerador de números aleatórios
    srand(time(NULL));

    for (long long int i = 0; i < termos; i++) {
        numeros[i] = rand() % 100000; // Gerando números aleatórios entre 0 e 99.999
    }

    file = fopen(argv[2], "wb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        free(numeros);
        return 3;
    }

    size_t written = fwrite(numeros, sizeof(long long int), termos, file);
    if (written != termos) {
        perror("Erro ao escrever no arquivo");
        fclose(file);
        free(numeros);
        return 4;
    }

    fclose(file);
    free(numeros);

    printf("Valores aleatórios gerados e escritos no arquivo %s com sucesso.\n", argv[2]);
    return 0;
}
