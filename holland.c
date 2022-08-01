#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define TAM_CROMO 50

int geracao = 0;

// --- ORDENAR A POPULAÇÃO POR ADAPTAÇÃO ---
void ordenarPop(int pop[][TAM_CROMO], int adap[]){
    int aux;
    for (int i = 0; i < 9; i++){
        for(int j = i + 1; j < 10; j++){
            if(adap[i] < adap[j]){
                for(int k = 0; k < TAM_CROMO; k++){
                    aux = pop[i][k];
                    pop[i][k] = pop[j][k];
                    pop[j][k] = aux;
                }
                aux = adap[i];
                adap[i] = adap[j];
                adap[j] = aux;
            }
        }
    }
}

// --- PRINTAR POPULAÇÃO --- 
void printarPop(int pop[][TAM_CROMO]){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < TAM_CROMO; j++){
            printf("%d ",pop[i][j]);        
        }
        printf("\n");
    }
}

// --- CHECAR ADAPTAÇÃO ---
void checarAdap(int pop[TAM_CROMO], int adap[], int nAdap){
    adap[nAdap] = 0;
    for (int i = 0; i < TAM_CROMO; i++){
        if(i < TAM_CROMO - 1){
            if(pop[i] == 0 && pop[i+1] == 1){
                adap[nAdap]++;
            }
        }
    }
}

void checarAdapDesc(int desc[][TAM_CROMO], int adapDesc[], int *individuo){
    for(int i = 0; i < *individuo; i++){
        adapDesc[i] = 0;
        for (int j = 0; j < TAM_CROMO; j++){
            if(j < TAM_CROMO - 1){
                if(desc[i][j] == 0 && desc[i][j+1] == 1){
                    adapDesc[i]++;
                }
            }
        }
    }
}

void ordenarDesc(int desc[][TAM_CROMO], int adapDesc[], int *individuo){
    for(int i = 0; i < *individuo - 1; i++){
        int aux;
        for(int j = i + 1; j < *individuo; j++){
            if(adapDesc[i] < adapDesc[j]){
                for(int k = 0; k < TAM_CROMO; k++){
                    aux = desc[i][k];
                    desc[i][k] = desc[j][k];
                    desc[j][k] = aux;
                }
                aux = adapDesc[i];
                adapDesc[i] = adapDesc[j];
                adapDesc[j] = aux;
            }
        }
    }
}

// --- PRINTAR ADAPTAÇÃO --- 
void printarAdap(int adap[]){
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", adap[i]);
    }
    
}

// --- PRINTAR ADAPTAÇÃO --- 
void printarAdapDesc(int adapDesc[], int *individuo){
    for (int i = 0; i < *individuo; i++)
    {
        printf("%d ", adapDesc[i]);
    }
    
}
// --- INICIAR UMA POPULAÇÃO (Dar valores [0 & 1]) ---
void iniciarPop(int pop[][TAM_CROMO]){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < TAM_CROMO; j++){
            pop[i][j] = rand() % 2; 
        }
    }
}

void cruzamento(int pop[][TAM_CROMO], int descPop[][TAM_CROMO], int *individuo){   
    for(int i = 0; i < 4; i++){
        for(int j = i + 1; j < 5; j++){
            int prob = (rand() % 100) + 1;
            
            if(prob > 60){
                int cortar = (rand() % TAM_CROMO);

                for(int k = 0; k <= cortar; k++){
                    descPop[*individuo][k] = pop[i][k];
                    descPop[*individuo + 1][k] = pop[j][k];
                }

                for(int l = cortar + 1; l < TAM_CROMO; l++){
                    descPop[*individuo][l] = pop[j][l];
                    descPop[*individuo + 1][l] = pop[i][l];
                }
                *individuo += 2;
            }
        }
    }
}

void mutacao(int pop[][TAM_CROMO], int descPop[][TAM_CROMO], int *individuo){
    for (int i = 0; i < 5; i++){
        int prob = (rand() % 100) + 1;  

        if(prob > 90){
            for(int j = 0; j < TAM_CROMO; j++){
                int alelo = (rand() % 2);

                if(alelo == 0){
                    if(pop[i][j] == 0){
                        descPop[*individuo][j] = 1;
                    }
                    else descPop[*individuo][j] = 0; 
                }
                else descPop[*individuo][j] = pop[i][j];
            }
            *individuo += 1; 
        }
    }
}

void inversao(int pop[][TAM_CROMO], int descPop[][TAM_CROMO], int *individuo){
    for(int i = 0; i < 5; i++){
        int prob = (rand() % 100) + 1;

        if(prob > 90){
            for(int j = 0; j < TAM_CROMO; j++){
                descPop[*individuo][j] = pop[i][j];
            }

            int p1 = (rand() % TAM_CROMO - 1);
            int p2 = (rand() % TAM_CROMO);

            while(p2 < p1){
                p2 = (rand() % TAM_CROMO);
            }
            int aux = (p2 - p1)/2;

            for (int k = 0; k <= aux; k++){
                int aux2 = descPop[*individuo][p1 + k];
                descPop[*individuo][p1 + k] = descPop[*individuo][p2 - k];
                descPop[*individuo][p2 - k] = aux2;
            }

            *individuo += 1;
            
        }
    }

}

void printarDesc(int descPop[][TAM_CROMO], int *individuo){
    for (int i = 0; i < *individuo; i++){
        for (int j = 0; j < TAM_CROMO; j++){
            printf("%d ",descPop[i][j]);        
        }
        printf("\n");
    }
}

void substituir(int pop[][TAM_CROMO], int popDesc[][TAM_CROMO], int adap[], int adapDesc[], int *individuo){
    int aux1 = 0, aux2 = 0;
    int novaAdap[10];
    int novaPop[10][TAM_CROMO];
    for(int i = 0; i < 10; i++){
        if(aux2 < (*individuo - 1)){
            if(adap[aux1] > adapDesc[aux2]){
                for(int j = 0; j < TAM_CROMO; j++){
                    novaPop[i][j] = pop[aux1][j];
                }
                novaAdap[i] = adap[aux1];
                aux1++;
            }
            else {
                for(int j = 0; j < TAM_CROMO; j++){
                    novaPop[i][j] = popDesc[aux2][j];
                }
                novaAdap[i] = adapDesc[aux2];
                aux2++;
            }
        }
        else {
            for(int j = 0; j < TAM_CROMO; j++){
                novaPop[i][j] = pop[aux1][j];
            }
            novaAdap[i] = adap[aux1];
            aux1++;
        }
    }

    for(int i = 0; i < 10; i++){
        for (int j = 0; j < TAM_CROMO; j++){
            pop[i][j] = novaPop[i][j];
        }
        adap[i] = novaAdap[i];
    }
}

int main(){

    int pop[10][TAM_CROMO];
    int descPop[60][TAM_CROMO];
    int aux;
    int adap[10];
    int adapDesc[60];
    int *individuo = (int*)malloc(sizeof(int));
    FILE *arq;
    
    
    srand(time(NULL));

    iniciarPop(pop);

    for (int i = 0; i < 10; i++)
    {
        checarAdap(pop[i], adap, i);
    }

    ordenarPop(pop, adap);


    arq = fopen("dados.csv", "w+");
    fprintf(arq, "Geracao, Adaptacao\n");
    while(adap[0] != TAM_CROMO/2){

        geracao++;

        *individuo = 0;

        cruzamento(pop, descPop, individuo);
    
        mutacao(pop, descPop, individuo);

        inversao(pop, descPop, individuo);

        checarAdapDesc(descPop, adapDesc, individuo);

        ordenarDesc(descPop, adapDesc, individuo);

        substituir(pop, descPop, adap, adapDesc, individuo);

        
        printf("loops : %d\n", geracao);

        fprintf(arq, "%d, %d\n", geracao, adap[0]);
    
    }
    fclose(arq);

    free(individuo);
    printarPop(pop);
    printf("\n\nloops : %d\n\n", geracao); 
    printarAdap(adap);
    printf("\n");
    return 0;
}