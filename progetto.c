#include<stdio.h>
#include<string.h>

typedef struct{
//bho
} Nodo;

//AggiungiGrafo - ritorna il costo del grafo appena aggiunto
int AggiungiGrafo(int n, int graph[n][n]){
    //for (int i = 0; i < n; ++i) {
    //    for (int j = 0; j < n; ++j) {
    //        printf("%d,",graph[i][j]);
    //    }
    //    printf("\n");
    //}
    //stampa il grafo
    int weight=0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {

        }
    }
    return weight;
}

void TopK(int index[], int length){
    for (int i = 0; i < length; ++i) {
        if(index[i]!=-1) printf(" %d", index[i]);   // Potrei avere problemi con la formattazione dell'output
    }
}

void updateRank(int newIndex,int newPoint, int index[],int point[],int length){
    if(point[length-1] != - 1) {
        // Classifica piena, controllo se il nuovo grafo può stare in classifica
        if (newPoint > point[length - 1]) return;
        for (int i = 0; i < length; ++i) {
            // Per ogni grafo partendo da inizio classifica, confronto il suo peso con il nuovo
            if(newPoint < point[i]){
                // Salvo quelli precedenti e sovrascrivo
                int pointTemp = point[i];
                point[i] = newPoint;
                int indexTemp = index[i];
                index[i] = newIndex;
                // Nel loop salvo a dal vettore, sovrascrivo la posizione di a nel vettore con b, salvo a in b
                for (int j = i+1; j < length; ++j) {
                    newPoint = point[j];
                    point[j] = pointTemp;
                    pointTemp = newPoint;
                    newIndex = index[j];
                    index[i] = indexTemp;
                    indexTemp = newIndex;
                }
                break;
            }
        }
    }
    // Classifica non piena
    else{
        for (int i = 0; i < length; ++i) {
            if(point[i]!=-1){
                // Se sto guardando un altro peso ed è maggiore di quello nuovo
                if(newPoint < point[i]){
                    // Ciclo in cui sposto gli indici a destra di una posizione partendo dalla fine
                    for (int j = length-2; j > i; --j) {
                        point[j+1] = point[j];
                        index[j+1] = index[j];
                    }
                    // Salvo il nuovo peso in classifica
                    point[i] = newPoint;
                    index[i] = newIndex;
                    break;
                }
            }
            // Se ho trovato uno spazio vuoto, salvo il valore in classifica
            else{
                point[i] = newPoint;
                index[i] = newIndex;
                break;
            }
        }
    }
}


//strtol invece di scanf?
int main() {
    int nodes,topLength,trash, graphs=0;
    if (scanf("%d %d",&nodes,&topLength)){}
    if(nodes<2 || topLength<1){
        // ho un solo nodo/nodi negativi/classifica vuota: wtf?
        return 0;
    }
    int rankIndex[topLength-1];
    int rankPoints[topLength-1];
    for (int i = 0; i < topLength; ++i) {
        rankIndex[i]=-1;
        rankPoints[i]=-1;
    }
    int actualIndex=0;
    char input[15];
    int in;
    while(1) {
        in = getchar();
        if (in == EOF) break;
        if (scanf("%s", input)){}
        trash = printf("ho letto %s\n", input);
        if (strcmp(input, "AggiungiGrafo") == 0) {
            graphs++;
            int tempMat[nodes][nodes];
            for (int i = 0; i < nodes; ++i) {
                for (int j = 0; j < nodes; ++j) {
                    trash = getchar();
                    tempMat[i][j] = getchar() - 48;
                    //printf("ho letto: %d trash: %d\n",tempMat[i][j],trash);
                }
            }
            in = AggiungiGrafo(nodes, tempMat);
            updateRank(actualIndex,in,rankIndex,rankPoints,topLength);
        } else {
            if (graphs) {
                printf(" %d",rankIndex[0]);
                for (int i = 1; i < topLength; ++i) {
                    printf(" %d",rankIndex[i]);
                }
            }
        }
        ++actualIndex;
    }

    if(trash){
        //per non far rompere il cazzo alla scanf
    }
    return 0;
}