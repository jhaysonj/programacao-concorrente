#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *file;
    long long int *numeros;
    long long int termos;

    if (argc != 2) {
        fprintf(stderr, "Modo de uso: %s <nome do arquivo>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 2;
    }

    fseek(file, 0, SEEK_END);
    long long int tamanho_arquivo = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (tamanho_arquivo % sizeof(long long int) != 0) {
        fprintf(stderr, "O tamanho do arquivo não é múltiplo do tamanho de long long int.\n");
        fclose(file);
        return 3;
    }

    termos = tamanho_arquivo / sizeof(long long int);

    numeros = (long long int *)malloc(tamanho_arquivo);
    if (numeros == NULL) {
        perror("Erro ao alocar memória");
        fclose(file);
        return 4;
    }

    long long int lidos = fread(numeros, sizeof(long long int), termos, file);
    if (lidos != termos) {
        perror("Erro ao ler do arquivo");
        free(numeros);
        fclose(file);
        return 5;
    }

    fclose(file);

    printf("Números lidos do arquivo %s:\n", argv[1]);
    for (long long int i = 0; i < termos; i++) {
        printf("%lld ", numeros[i]);
    }
    printf("\n");

    free(numeros);

    return 0;
}
