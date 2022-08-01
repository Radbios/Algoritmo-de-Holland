#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

void selecao(int pop[][8], int adap[]){
    int somaAdap = 0;
    int valorInd, roletaInd;
    for(int i = 0; i < 10; i++){
        somaAdap = somaAdap + adap[i];
    }
    
    int roleta[somaAdap], contador = 0;

    for(int j = 0; j < 10; j++){
        for(int k = 0; k < adap[j]; k++){
            roleta[contador] = j;
            contador++;
        }
    }

    for(int l = 0; l < 5; l++){
        valorInd = (rand() % somaAdap);
        roletaInd = roleta[valorInd];

        for(int a = 0; a < 8; a++){
            int aux = pop[l][a];
            pop[l][a] = pop[roletaInd][a];
            pop[roletaInd][a] = aux;
        }

        int aux = adap[l];
        adap[l] = adap[roletaInd];
        adap[roletaInd] = aux;

        int ultimo = somaAdap - 1;
        for(int n = 0; n < somaAdap; n++){
            if(roleta[n] == roletaInd){
                for(int y = n; y < somaAdap; y++){
                    if(n == somaAdap - 1){
                        break;
                    }
                    roleta[y] = roleta[y + 1];
                }
                roleta[ultimo] = roletaInd;
                ultimo--;
                somaAdap--;
            }
        }
    }

}

// --- ORDENAR A POPULAÇÃO POR ADAPTAÇÃO ---
void ordenarPop(int pop[][8], int adap[]){
    int aux;
    for (int i = 0; i < 9; i++){
        for(int j = i + 1; j < 10; j++){
            if(adap[i] < adap[j]){
                for(int k = 0; k < 8; k++){
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
void printarPop(int pop[][8]){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 8; j++){
            printf("%d ",pop[i][j]);        
        }
        printf("\n");
    }
}

// --- CHECAR ADAPTAÇÃO ---
void checarAdap(int pop[8], int adap[], int nAdap){
    adap[nAdap] = 0;
    for (int i = 0; i < 8; i++){
        if(i < 7){
            if(pop[i] == 0 && pop[i+1] == 1){
                adap[nAdap]++;
            }
        }
    }
}

void checarAdapDesc(int desc[][8], int adapDesc[], int *individuo){
    for(int i = 0; i < *individuo; i++){
        adapDesc[i] = 0;
        for (int j = 0; j < 8; j++){
            if(j < 7){
                if(desc[i][j] == 0 && desc[i][j+1] == 1){
                    adapDesc[i]++;
                }
            }
        }
    }
}

void ordenarDesc(int desc[][8], int adapDesc[], int *individuo){
    for(int i = 0; i < *individuo - 1; i++){
        int aux;
        for(int j = i + 1; j < *individuo; j++){
            if(adapDesc[i] < adapDesc[j]){
                for(int k = 0; k < 8; k++){
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
void iniciarPop(int pop[][8]){
    time_t t;

    srand(time(NULL));

    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 8; j++){
            pop[i][j] = rand() % 2; 
        }
    }
}

void cruzamento(int pop[][8], int descPop[][8], int *individuo){
    time_t t;
    srand(time(NULL));
    for(int i = 0; i < 4; i++){
        for(int j = i + 1; j < 5; j++){
            int prob = (rand() % 100) + 1;
            
            if(prob > 60){
                int cortar = (rand() % 8);

                for(int k = 0; k <= cortar; k++){
                    descPop[*individuo][k] = pop[i][k];
                    descPop[*individuo + 1][k] = pop[j][k];
                }

                for(int l = cortar + 1; l < 8; l++){
                    descPop[*individuo][l] = pop[j][l];
                    descPop[*individuo + 1][l] = pop[i][l];
                }
                *individuo += 2;
            }
        }
    }
}

void mutacao(int pop[][8], int descPop[][8], int *individuo){
    time_t t;
    srand(time(NULL));

    for (int i = 0; i < 5; i++){
        int prob = (rand() % 100) + 1;  

        if(prob > 80){
            for(int j = 0; j < 8; j++){
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

void inversao(int pop[][8], int descPop[][8], int *individuo){
    srand(time(NULL));

    for(int i = 0; i < 5; i++){
        int prob = (rand() % 100) + 1;

        if(prob > 80){
            for(int j = 0; j < 8; j++){
                descPop[*individuo][j] = pop[i][j];
            }

            int p1 = (rand() % 7);
            int p2 = (rand() % 8);

            while(p2 < p1){
                p2 = (rand() % 8);
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

void printarDesc(int descPop[][8], int *individuo){
    for (int i = 0; i < *individuo; i++){
        for (int j = 0; j < 8; j++){
            printf("%d ",descPop[i][j]);        
        }
        printf("\n");
    }
}

void substituir(int pop[][8], int popDesc[][8], int adap[], int adapDesc[], int *individuo){
    int aux1 = 0, aux2 = 0;
    int novaAdap[10];
    int novaPop[10][8];
    for(int i = 0; i < 10; i++){
        if(aux2 < (*individuo - 1)){
            if(adap[aux1] > adapDesc[aux2]){
                for(int j = 0; j < 8; j++){
                    novaPop[i][j] = pop[aux1][j];
                }
                novaAdap[i] = adap[aux1];
                aux1++;
            }
            else {
                for(int j = 0; j < 8; j++){
                    novaPop[i][j] = popDesc[aux2][j];
                }
                novaAdap[i] = adapDesc[aux2];
                aux2++;
            }
        }
        else {
            for(int j = 0; j < 8; j++){
                novaPop[i][j] = pop[aux1][j];
            }
            novaAdap[i] = adap[aux1];
            aux1++;
        }
    }

    for(int i = 0; i < 10; i++){
        for (int j = 0; j < 8; j++){
            pop[i][j] = novaPop[i][j];
        }
        adap[i] = novaAdap[i];
    }
}

int main(){

    int pop[10][8];
    int descPop[30][8];
    int aux;
    int adap[10];
    int adapDesc[30];
    int *individuo = (int*)malloc(sizeof(int));
    
    
    iniciarPop(pop);

    for (int i = 0; i < 10; i++)
    {
        checarAdap(pop[i], adap, i);
    }
    ordenarPop(pop, adap);
    while(adap[0] != 4){

        *individuo = 0;


        selecao(pop, adap);

        cruzamento(pop, descPop, individuo);
        mutacao(pop, descPop, individuo);
        inversao(pop, descPop, individuo);
        checarAdapDesc(descPop, adapDesc, individuo);

        ordenarDesc(descPop, adapDesc, individuo);

        substituir(pop, descPop, adap, adapDesc, individuo);
    }
    
    return 0;
}