#include<stdio.h>

//AggiungiGrafo - ritorna il costo del grafo appena aggiunto
int AggiungiGrafo(int n, int graph[n][n]){
    //for (int i = 0; i < n; ++i) {
    //    for (int j = 0; j < n; ++j) {
    //        printf("%d,",graph[i][j]);
    //    }
    //    printf("\n");
    //}
    // Stampa il grafo
    int weight;

    // Test per grafi con 2 nodi:
    weight = graph[0][1];

    return weight;
}

// TopK - stampo la classifica attuale
void TopK(int index[], int length){
    for (int i = 0; i < length; ++i) {
        if(index[i]!=-1) printf(" %d", index[i]);   // Potrei avere problemi con la formattazione dell'output
    }
}

// updateRank - aggiorno la attuale classifica con il peso del nuovo grafo.
void updateRank(int newIndex, int newPoint, int index[], int point[], int rLength){
    if(point[rLength - 1] != - 1) {
        // Classifica piena, controllo se il nuovo grafo può stare in classifica
        if (newPoint > point[rLength - 1]) return;
        for (int i = 0; i < rLength; ++i) {
            // Per ogni grafo partendo da inizio classifica, confronto il suo peso con il nuovo
            if(newPoint < point[i]){
                // Salvo quelli precedenti e sovrascrivo
                int pointTemp = point[i];
                point[i] = newPoint;
                int indexTemp = index[i];
                index[i] = newIndex;
                // Nel loop salvo a dal vettore, sovrascrivo la posizione di a nel vettore con b, salvo a in b - ripeto fino alla fine
                for (int j = i+1; j < rLength; ++j) {
                    newPoint = point[j];
                    point[j] = pointTemp;
                    pointTemp = newPoint;
                    newIndex = index[j];
                    index[j] = indexTemp;
                    indexTemp = newIndex;
                }
                break;
            }
        }
    }
    // Classifica non piena
    else{
        // Scorro la classifica cercando uno spazio vuoto, se prima trovo un peso maggiore del nuovo shifto tutto il vettore rimanente a destra di una posizione
        for (int i = 0; i < rLength; ++i) {
            if(point[i]!=-1){
                if(newPoint < point[i]){
                    // Ciclo in cui sposto gli indici a destra di una posizione partendo dalla fine
                    for (int j = rLength - 2; j >= i; --j) {
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

// limite troppo piccolo di caratteri?
//strtol invece di scanf?
int main() {
    // Numero di nomi
    int nodes;
    // Lunghezza della classifica
    int rankLength;
    // Variabile usata come risultato di getchar per evitare warning
    int trash;
    // Indice del grafo attuale e numero di tutti i grafi considerati
    int graphs=0;
    // Stringa in cui viene salvato l'input
    char input[15];

    // Inizializzazione: lettura del numero di nodi e lunghezza della classifica
    if (scanf("%d %d",&nodes,&rankLength)){}
    if(nodes<2 || rankLength < 1){
        // ho un solo nodo/nodi negativi/classifica vuota: wtf?
        return 0;
    }

    // Si potrebbe allocare un po' di classifica alla volta
    // forse è meglio? tenere in considerazione la cosa
    // nel caso, andrebbe modificata leggermente la funzione updateRank

    // Classifica contenente gli indici dei grafi
    int rankIndex[rankLength];
    // Classifica contenete i punti dei grafi
    int rankPoints[rankLength];

    // Inizializzazione della classifica con valori vuoti di default
    for (int i = 0; i < rankLength; ++i) {
        rankIndex[i] = -1;
        rankPoints[i] = -1;
    }

    // Inizio del ciclo
    while(1) {
        // Questo getchar() legge sempre '\n'
        trash = getchar();
        // Leggo input e controllo se sono alla fine del file
        if (scanf("%s", input) == EOF){break;}
        // Check della stringa per capire la prossima funzione
        // ASSUNZIONE DI INPUT CORRETTA, se leggo 'A' farò AggiungiGrafo,
        // altrimenti TopK
        if (input[0] == 'A'){
            // Matrice di adiacenza del nuovo grafo
            int tempMat[nodes][nodes];
            // Inserimento dei valori nella matrice
            for (int i = 0; i < nodes; ++i) {
                for (int j = 0; j < nodes; ++j) {
                    // Questo getchar() legge '\n' e ','
                    trash = getchar();
                    // Invece di scanf potrei leggere carattere per carattere e poi sistemarlo in un intero - da fare post funzionamento della logica
                    if(scanf("%d", &tempMat[i][j])){}
                }
            }
            // Aggiorno la classifica passandogli tutti i parametri necessari:
            // indice, il peso del nuovo grafo dato dalla funzione AggiungiGrafo (che a sua volta ha bisogno della dimensione della matrice e della matrice stessa),
            // i vettori che contengono punteggi e indici dei grafi già presenti e infine la lunghezza della classifica.
            updateRank(graphs, AggiungiGrafo(nodes, tempMat), rankIndex, rankPoints, rankLength);
            // Incremento l'indice del grafo
            graphs++;
        } else {
            //Se non ho nemmeno un grafo non stampo nulla
            if (graphs) {
                TopK(rankIndex, rankLength);
            }
        }
    }
    // Check del valore di trash per evitare warning
    if(trash){}
    return 0;
}