#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>


int termos;
int M_THREADS;
double aproxima_pi_global = 0.0; // variável compartilhada entre as threads
pthread_mutex_t mutex; //variavel de lock para exclusao mutua

// Função executada pelas threads
void* aproxima_pi(void* arg) {
    int thread_index = *(int*)arg; // deferencia o valor passado como parametro
    double aproxima_pi_local = 0;
    for(int i = thread_index; i<termos; i+=M_THREADS){
        aproxima_pi_local +=  ( (4.0 / (8 * i + 1) 
                - 2.0 / (8 * i + 4) 
                - 1.0 / (8 * i + 5) 
                - 1.0 / (8 * i + 6)    ) 
                * (1.0/pow(16,i))  );  
    }
    // realiza o lock para manipular variavel global
    pthread_mutex_lock(&mutex);

    aproxima_pi_global += aproxima_pi_local;
    
    // realiza o unlock liberando a variavel global
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL); // Sai da thread
}


int main(int argc, char* argv[]){    

    // valida a quantidade de argumentos
    if(argc != 3){
        printf("Modo de uso: ./%s <num_de_termos> <num_de_threads>\n", argv[0]);
        return(-1);
    }

    termos = atoi(argv[1]);
    M_THREADS = atoi(argv[2]);

    // garante que chamaremos sempre menos threads do que a quantidade de tarefas
    if(termos < M_THREADS){
        M_THREADS = termos;
    }

    // Inicializa o mutex
    pthread_mutex_init(&mutex, NULL);

    // Array para identificadores de threads
    pthread_t tid_sistema[M_THREADS]; 
    int thread_indices[M_THREADS]; // Array para índices das threads

    // loop de n termos para aproximar pi
    for(int i = 0; i<M_THREADS; i++){
        thread_indices[i] = i;
        // arg 1: referencia para identificador da thread       arg2: null      arg3: função executada pelas threads        
        // arg4: argumento enviado à função que é executada pela thread, ( tem que ser ponteiro pra void) 
        pthread_create(&tid_sistema[i], NULL, aproxima_pi, (void*)&thread_indices[i]);
    }


    // Aguarda as threads finalizarem
    for (int i = 0; i < M_THREADS; i++) {
        pthread_join(tid_sistema[i], NULL);
    }


    printf("Para N_termos = %d\nAproximação de Pi = %.10f\n", termos, aproxima_pi_global);
    return 0;
}




