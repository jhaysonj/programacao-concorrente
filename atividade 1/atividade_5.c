#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <stdbool.h>

#define M_THREADS 100 //total de threads a serem criadas
#define N_NUMEROS 50 //quantidade de números no meu vetor

int vetor[N_NUMEROS]; // vetor a ser manipulado pelas 'M' threads
int vetor_original[N_NUMEROS]; // vetor que mantem o mesmo valor para validarmos as operações feitas

//cria a estrutura de dados para armazenar os argumentos da thread
typedef struct {
   int idThread, index_inicial, index_final;
} t_Args;




// função que a thread irá executar
void * eleva_ao_quadrado (void * arg){
    t_Args args = *(t_Args*) arg;
    
    /* // tmp, apenas para fiz de teste
    printf("Thread %d\n", args.idThread);
    printf("Index_inicial %d\n", args.index_inicial);
    printf("Index_final %d\n", args.index_final);
    */
    for(int i=args.index_inicial; i<args.index_final; i++){
        vetor[i] = vetor[i] * vetor[i];
    }

    free(arg); //libera a memoria que foi alocada na main

    pthread_exit(NULL); // retorna de forma implicita, pois a sua chamada tambem sera de forma implicita, como argumento de outra funcao.
}


// defini arbitrariamente que o vetor de teste seria iniciado de 1 até N_NUMEROS
void inicializa_vetor(){
    printf("Vetor original:\n");
    // inicializa o vetor
    for(int w=1; w<=N_NUMEROS; w++){
        vetor_original[w-1] = w;
        vetor[w-1] = w;

    }
    // printa o vetor
    for(int i=0; i<N_NUMEROS; i++){
        printf("%d\n", vetor_original[i]);
    }
}

bool valida_resultado(){
    // lida com o caso de divisão por zero
    for(int i = 0; i<N_NUMEROS; i++){
        if((vetor[i] == 0) && (vetor[i] == vetor_original[i])){
            printf("Nenhum erro encontrado, vetor validado com sucesso!\n");
            return true;
        }
        if(vetor[i]/vetor_original[i] != vetor_original[i]){
            printf("ERRO %d² != %d\n", vetor_original[i], vetor[i]);
            return false;
        }
    }

    printf("Nenhum erro encontrado, vetor validado com sucesso!\n");
    return true;
}

// funcao principal                 
int main(int argc, char *argv[]){
    int quantidade_de_tarefas;
    pthread_t tid_sistema[M_THREADS]; // identificadores das threads no sistema 

    // atribuição de tarefas: define a quantidade de elementos do vetor que cada thread elevará ao quadrado
    
    if(M_THREADS>N_NUMEROS){
        quantidade_de_tarefas = 1;
    }else{
        quantidade_de_tarefas = N_NUMEROS/M_THREADS;
    }
    
    inicializa_vetor();

    printf("\n\n");
    t_Args *args; //receberá os argumentos para a thread
    for(int i=0; i<M_THREADS; i++){
        
        // lida com os casos em que falta há mais thread do que tarefas
        if(i>=N_NUMEROS){
            break;
        }

        // Aloca e preenche argumentos para I-ésima thread
        args = malloc(sizeof(t_Args));
        
        args->idThread = i; 
        // index_inicial e index_final definem o range do vetor[N_NUMEROS] em que a I-ésima thread vai modificar
        args->index_inicial = i * quantidade_de_tarefas;
        
        // lida com o caso em que a variavel N_NUMEROS não é múltiplo de M_THREADS, ou seja, alguma thread tem que fazer mais operações do que as outras
        // condição ? valor_se_verdadeiro : valor_se_falso;
        args->index_final = (i == M_THREADS - 1) ? N_NUMEROS :  args->index_inicial + quantidade_de_tarefas;
        // Cria a thread
        if (pthread_create(&tid_sistema[i], NULL, eleva_ao_quadrado, (void*) args)) {
        printf("--ERRO: pthread_create()\n"); exit(-1);
        }
        

    }    

    // espera todas as M_THREADS terminarem
    for (int i=0; i<M_THREADS; i++) {
        // lida com os casos em que falta há mais thread do que tarefas
        if(i>=N_NUMEROS){
            break;
        }
        if (pthread_join(tid_sistema[i], NULL)) {
            printf("--ERRO: pthread_join() \n"); exit(-1); 
        } 
    }
    
    if(valida_resultado()){
        printf("Vetor elevado:\n");
        for (int i=0; i<N_NUMEROS; i++) {
            printf("%d\n", vetor[i]);
                
        }
    }
   

    // Thread principal terminou
    pthread_exit(NULL);



    return 0;
}

