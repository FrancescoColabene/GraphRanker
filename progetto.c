#include<stdio.h>
#include<string.h>

//AggiungiGrafo - ritorna il costo del grafo appena aggiunto
int AggiungiGrafo(int n, int graph[n][n]){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d,",graph[i][j]);
        }
        printf("\n");
    }
    // Stampa il grafo
    int weight=0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ++weight;
        }
    }
    return weight;
}

// TopK - stampo la classifica attuale
void TopK(int index[], int length){
    for (int i = 0; i < length; ++i) {
        if(index[i]!=-1) printf(" %d", index[i]);   // Potrei avere problemi con la formattazione dell'output
    }
}

void updateRank(int newIndex, int newPoint, int index[], int point[], int length){
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
    // limite troppo piccolo di caratteri?
    // numero nomi, lunghezza classifica, evitare warning printf, indice del grafo attuale
    int nodes, topLength, trash, graphs=0;
    // Lettura di numero di nodi e lunghezza della classifica
    if (scanf("%d %d",&nodes,&topLength)){}
    if(nodes<2 || topLength<1){
        // ho un solo nodo/nodi negativi/classifica vuota: wtf?
        return 0;
    }
    int rankIndex[topLength - 1];
    int rankPoints[topLength - 1];
    // Inizializzazione della classifica con valori vuoti di default
    for (int i = 0; i < topLength; ++i) {
        rankIndex[i] = -1;
        rankPoints[i] = -1;
    }
    // Funzione letta
    char input[15];
    int in;
    // Inizio del ciclo - in legge sempre \n
    while(1) {
        in = getchar();
        if (in == EOF) break;
        // Non sono alla fine del file, leggo input
        if (scanf("%s", input)){}
        trash = printf("ho letto %s\n", input);
        if (strcmp(input, "AggiungiGrafo") == 0){
            // Devo aggiungere un grafo, quindi leggo la matrice di adiacenza
            int tempMat[nodes][nodes];
            for (int i = 0; i < nodes; ++i) {
                for (int j = 0; j < nodes; ++j) {
                    trash = getchar();
                    tempMat[i][j] = getchar() - 48;
                    //printf("ho letto: %d trash: %d\n",tempMat[i][j], trash);
                }
            }
            // Aggiorno la classifica passandogli tutti i parametri necessari:
            // indice, il peso del nuovo grafo dato dalla funzione AggiungiGrafo (che a sua volta ha bisogno della dimensione della matrice e della matrice stessa),
            // i vettori che contengono punteggi e indici dei grafi già presenti e infine la lunghezza della classifica. Dopo incremento l'indice dei grafi
            updateRank(graphs,AggiungiGrafo(nodes, tempMat),rankIndex,rankPoints,topLength);
            graphs++;
        } else {
            //Se non ho nemmeno un grafo non stampo nulla
            if (graphs) {
                TopK(rankIndex,topLength);

            }
        }
        if(strcmp(input, "quit") == 0) return 0;
    }
    if(trash){}
}