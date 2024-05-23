#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Função para verificar se um número é primo
int ehPrimo(long long int n) {
    if (n <= 1)
        return 0; // não é primo
    if (n <= 3)
        return 1; // 2 e 3 são primos

    if (n % 2 == 0 || n % 3 == 0)
        return 0; // não é primo

    for (long long int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return 0; // não é primo
    }
    return 1; // é primo
}

// Função principal
int main(int argc, char **argv) {
    FILE *file;
    long long int *numeros;
    long long int tamanho_arquivo;
    int termos;
    int cont_primo = 0; 
    int cont_nao_primo = 0;

    // Verifica se o nome do arquivo foi passado como argumento
    if (argc != 2) {
        fprintf(stderr, "Modo de uso: %s <nome do arquivo>\n", argv[0]);
        return 1;
    }

    // Abre o arquivo para leitura binária
    file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 2;
    }

    // Descobre o tamanho do arquivo
    fseek(file, 0, SEEK_END); // move o ponteiro para o final do arquivo
    tamanho_arquivo = ftell(file); // pega o tamanho total do arquivo
    fseek(file, 0, SEEK_SET); // move o ponteiro de volta para o começo do arquivo

    // calcula a quantidade de termos no arquivo
    termos = tamanho_arquivo / sizeof(long long int); 

    // aloca memória para armazenar os números inteiros do arquivo binário
    numeros = (long long int *)malloc(tamanho_arquivo);
    if (numeros == NULL) {
        perror("Erro ao alocar memória");
        fclose(file);
        return 4;
    }

    // lê os números do arquivo
    int lidos = fread(numeros, sizeof(long long int), termos, file);
    if (lidos != termos) {
        perror("Erro ao ler do arquivo");
        free(numeros);
        fclose(file);
        return 5;
    }

    // fecha o arquivo
    fclose(file);

    // imprime os números lidos
    printf("Números lidos do arquivo %s:\n", argv[1]);
    for (int i = 0; i < termos; i++) {
        if (ehPrimo(numeros[i]) == 1) {
            printf("O número %lld é primo\n", numeros[i]);
            cont_primo++;
        } else {
            cont_nao_primo++;
            printf("NÃO É PRIMO: %lld \n", numeros[i]);
        }
    }
    printf("\n");
    printf("Total de primos: %d\n", cont_primo);
    printf("Total de NÃO-primos: %d\n", cont_nao_primo);

    // Libera a memória alocada
    free(numeros);

    return 0;
}
