#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]){

    int num_de_termos;
    double aproxima_pi = 0;

    // valida a quantidade de argumentos
    if(argc != 2){
        printf("Modo de uso: ./%s <num_de_termos>\n", argv[0]);
        return(-1);
    }

    num_de_termos = atoi(argv[1]);

    // loop de n termos para aproximar pi
    for(int i = 0; i<num_de_termos; i++){
        
        // formula de aproximação
        aproxima_pi +=  ( (4.0 / (8 * i + 1) 
                        - 2.0 / (8 * i + 4) 
                        - 1.0 / (8 * i + 5) 
                        - 1.0 / (8 * i + 6)    ) 
                        * (1.0/pow(16,i))  );  
    }


    printf("Para N_termos = %d\nAproximação de Pi = %.10f\n", num_de_termos, aproxima_pi);
    return 0;
}




