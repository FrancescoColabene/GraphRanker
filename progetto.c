#include<stdio.h>
#include<math.h>

// Struttura di un nodo: serve per l'algoritmo di Dijkstra
typedef struct node{
    int dist;
    int index;
}Node;


//------------PROTOTIPI----------------

//AggiungiGrafo - ritorna il costo del grafo appena aggiunto
int AggiungiGrafo(int n, int graphs[n][n]);

// TopK - stampo la classifica attuale
void TopK(int index[], int length, int *g);

// Tutte le funzioni qui sotto sono per la gestione del minHeap per l'algoritmo di Dijkstra

// Dato un vettore di elementi non mucchificati, crea un minHeap.
void createMinHeapify(Node heap[], int *hsP, int len);

// Funzione di supporto per le altre: assumendo che i sottoheap dei figlio del nodo passato siano heap, mucchifico anche questi 3 nodi.
// Nel caso di scambi di posizione, dovrò richiamare la funzione sui nodi inferiori per garantire la relazione padre<figlio
void minHeapify(Node heap[], int n, int *hsP);

// Ritorna la radice dell'heap, o -1 se è vuoto. Se non è vuoto, mette l'ultima foglia come radice
// e chiama minHeapify sulla radice per sistemare l'heap rimasto.
struct node deleteMin(Node heap[], int *hsP);

// Scambia i valori di due posizioni in un vettore
void swap(Node heap[],int x, int y);

// Ritorna il figlio sinistro del nodo passato
int left(int n);

// Ritorna il figlio destro del nodo passato
int right(int n);



// updateRank - aggiorno la attuale classifica con il peso del nuovo grafo.
void updateRank(int newIndex, int newPoint, int index[], int point[], int rLength, int *g);
// Le funzioni successive servono a gestire la classifica - vengono usate anche left e right
// L'heap è gestito con i pesi dei grafi, ma in tutte le funzioni è presente anche il vettore
// di indici che segue gli swap e gli spostamenti dell'altro.
// Inizialmente la classifica non è un heap, lo diventa solamente quando diventa pieno:
// le varie funzioni quindi assumono di lavorare sempre con un heap pieno.

// Dato un vettore di elementi non mucchificati (heap), crea un maxHeap con indici che seguono.
void createMaxHeapifyR(int heap[], int heapI[], int len);

// Funzione di supporto per le altre: assumendo che i sottoheap dei figlio del nodo passato siano heap,
// mucchifico anche questi 3 nodi. Nel caso di scambi di posizione, dovrò richiamare la funzione
// sui nodi inferiori per garantire la relazione padre>figlio.
void maxHeapifyR(int heap[], int heapI[], int n, int len);

// Aggiunge un nuovo peso al grafo in ultima posizione dell'array (assumo che sia sempre pieno), poi
// lo sposto verso la radice in base al suo peso.
void insertMaxR(int newP, int newI, int heap[], int heapI[], int len);

// Elimina la radice dell'heap e assumendo che l'heap sia sempre pieno, mette l'ultima foglia
// come radice (che sarà sempre lunghezza-1); chiama poi maxHeapifyR sulla radice per sistemare l'heap rimasto.
void deleteMaxR(int heap[], int heapI[], int len);

// Scambia i valori di due posizioni in un due vettori.
void swapR(int heap[], int heapI[], int x, int y);




int main() {
    // Numero di nomi
    int nodes=0;
    // Lunghezza della classifica
    int rankLength=0;
    // Indice del grafo attuale e numero di tutti i grafi considerati
    int graphs=0;
    // Puntatore al numero di grafi per formattazione
    int *g = &graphs;

    // Variabile salva il risultato delle getchar, per leggere ogni input
    int buffer;
    // Vettore di interi in cui vengono salvate le cifre dei numeri
    int in[10];
    // Variabile utile al ciclo di lettura dell'input
    int order;
    // Variabile utile al ciclo di lettura dell'input
    int inCount;
    // Variabile utile al ciclo di lettura dell'input
    int pop=1;

    // Inizializzazione: lettura del numero di nodi e lunghezza della classifica
    //if (scanf("%d %d",&nodes,&rankLength)){}

    buffer = getchar_unlocked() - 48;
    for (inCount = 0; inCount < 10 && buffer >= 0; ++inCount) {
        in[inCount] = buffer;
        buffer = getchar_unlocked() - 48;
    }
    order = --inCount;
    for (; order >=0 ; --order) {
        for (int k = 0; k < order; ++k) {
            pop*=10;
        }
        nodes += in[inCount-order] * pop;
        pop=1;
    }
    buffer = getchar_unlocked() - 48;
    for (inCount = 0; inCount < 10 && buffer >= 0; ++inCount) {
        in[inCount] = buffer;
        buffer = getchar_unlocked() - 48;
    }
    order = --inCount;
    for (; order >=0 ; --order) {
        for (int k = 0; k < order; ++k) {
            pop*=10;
        }
        rankLength += in[inCount-order] * pop;
        pop=1;
    }

    if(nodes<2 || rankLength < 1){
        // ho un solo nodo/nodi negativi/classifica vuota: wtf?
        return 0;
    }

    // Matrice di adiacenza del nuovo grafo
    int tempMat[nodes][nodes];

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
        rankPoints[i] = 0;
    }

    // Inizio del ciclo
    while(1) {
        // Questo getchar legge sempre '\n' oppure l'EOF
        buffer = getchar_unlocked();
        // Controllo se sono alla fine del file
        if (buffer == EOF){break;}
        // Check della stringa per capire la prossima funzione
        // ASSUNZIONE DI INPUT CORRETTA, se leggo 'A' farò AggiungiGrafo,
        // altrimenti TopK
        if (buffer == 'A'){
            // Devo finire di leggere la parola "AggiungiGrafo" + '\n'
            for (int i = 0; i < 13; ++i) {
                buffer = getchar_unlocked();
            }
            // Inserimento dei valori nella matrice
            for (int i = 0; i < nodes; ++i) {
                for (int j = 0; j < nodes; ++j) {
                    // In questo ciclo leggo una cifra alla volta fino alla virgola e la salvo in un vettore.
                    // Poi nel ciclo successivo ripristino il numero originale e lo salvo nella posizione corretta dell'array
                    int zerocount=0;
                    buffer = getchar_unlocked() - 48;
                    for (inCount = 0; inCount < 10 && buffer >=0; ++inCount) {  // rallenta
                        in[inCount] = buffer;
                        if(buffer == 0) ++zerocount;
                        buffer = getchar_unlocked() - 48;
                    }
                    // Gli archi che portano al nodo 0 non servono per il calcolo del percorso, li imposto a 0 per riutilizzarli successivamente
                    buffer = 0;
                    if(j!=0 && inCount!=zerocount) {
                        order = --inCount;
                        for (; order >= 0; --order) {
                            if(in[inCount-order] != 0) {
                                for (int k = 0; k < order; ++k) {   // rallenta
                                    pop *= 10;
                                }
                                buffer += in[inCount-order] * pop;
                                pop=1;
                            }
                        }
                    }
                    tempMat[i][j] = buffer;
                }
            }
            // Se possibile, aggiorno la classifica passandogli tutti i parametri necessari:
            // indice, il peso del nuovo grafo dato dalla funzione AggiungiGrafo (che a sua volta ha bisogno della dimensione della matrice e della matrice stessa),
            // i vettori che contengono punteggi e indici dei grafi già presenti e infine la lunghezza della classifica.
            #ifndef EVAL
            printf("\nGrafo numero %d:\n", graphs);
            #endif
            int weight = AggiungiGrafo(nodes, tempMat);     // rallenta
            //if(weight==-20) return 2;
            #ifndef EVAL
            printf("Fine grafo numero %d.\n", graphs);
            #endif
            if(graphs >= rankLength && rankPoints[0] <= weight){
                // In questo caso ho la classifica piena e il nuovo peso è più grande del mio ultimo peso, quindi non aggiorno la classifica
                }
            else{
                updateRank(graphs, weight, rankIndex, rankPoints, rankLength, g);
            }
            // Incremento l'indice del grafo
            graphs++;
        } else {
            for (int i = 0; i < 4; ++i) {
                buffer = getchar_unlocked();
            }
            TopK(rankIndex, rankLength, g);
        }
    }
    return 0;
}



//AggiungiGrafo - ritorna il costo del grafo appena aggiunto
int AggiungiGrafo(int n, int graph[n][n]){

    #ifndef EVAL
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d,",graph[i][j]);
        }
        printf("\n");
    }
    #endif
    Node tempGraph[n];
    // Inizializzo l'insieme contenente ogni nodo
    tempGraph[0].dist = 0;
    tempGraph[0].index = 0;
    for (int i = 1; i < n; ++i) {
        tempGraph[i].dist = 2147483647;
        tempGraph[i].index = i;
    }
    int hs=n;
    int *hsP = &hs;

    // Algoritmo di Dijkstra
    createMinHeapify(tempGraph,hsP,n);
    while(hs > 0){
        // Estrazione del nodo con distanza minima
        struct node temp = deleteMin(tempGraph,hsP);
        int tempIndex = temp.index;
        if(temp.dist == 2147483647) break;
        int cont=0;
        // Ciclo sui nodi cercando un successore di temp
        while(cont<n){
            int i = tempGraph[cont].index;
            // Se trovo un successore (evitando gli autoanelli)
            if(i != tempIndex && graph[tempIndex][i] > 0){
                int newDist = temp.dist + graph[tempIndex][i];
                // Calcolo la nuova distanza e la confronto con la precedente, se è minore allora la sovrascrivo sia nell'heap
                // sia nella prima colonna della matrice, poi sposto il nodo  modificato verso la radice confrontandolo ciclicamente con suo padre
                if(tempGraph[cont].dist > newDist){
                    tempGraph[cont].dist = newDist;
                    graph[i][0] = newDist;
                    int k = ceil((double) cont/2) - 1;
                    while(cont>0 && tempGraph[k].dist > tempGraph[cont].dist){
                        swap(tempGraph,k,cont);
                        cont = ceil((double) cont/2) - 1;
                        k = ceil((double) k/2) - 1;
                    }
                }
            }
            cont++;
        }
    }
    int weight=0;
    for (int i = 0; i < n; ++i) {
        weight += graph[i][0];
        #ifndef EVAL
        printf("Un peso è %d\n",tempGraph[i].dist);
        #endif
    }
    #ifndef EVAL
    printf("Il peso del grafo è %d\n",weight);
    #endif
    return weight;
}

// TopK - stampo la classifica attuale
void TopK(int index[], int length, int *g){
    for (int i = 0; i < length; ++i) {
        if(index[i]!=-1) printf("%d", index[i]);
        if(i<*g-1) printf(" ");
    }
    printf("\n");
}

// updateRank - aggiorno la attuale classifica con il peso del nuovo grafo.
void updateRank(int newIndex, int newPoint, int index[], int point[], int rLength, int *g){
    // Se la classifica non è ancora piena, inserisco il nuovo peso nella prima posizione libera
    if(rLength > *g){
        point[*g] = newPoint;
        index[*g] = newIndex;
        // Se ho appena riempito la classifica, la rendo un maxHeap chiamando la funzione adatta.
        if(rLength == *g+1){
            createMaxHeapifyR(point,index,rLength);
        }
    }
    // In questo caso la classifica è piena, ho già un heap, e se la funzione updateRank è stata chiamata,
    // significa che il nuovo peso può stare in classifica: cancello l'ultimo e inserisco quello nuovo.
    else{
        deleteMaxR(point,index,rLength);
        insertMaxR(newPoint,newIndex,point,index,rLength);
    }
}

// Tutte le funzioni qui sotto sono per la gestione del minHeap per l'algoritmo di Dijkstra

// Dato un vettore di elementi non mucchificati, crea un minHeap.
void createMinHeapify(struct node heap[], int *hsP, int len){
    *hsP = len;
    for (int i = floor((double) len/2)-1; i >=0 ; --i) {
        minHeapify(heap,i,hsP);
    }
}

// Funzione di supporto per le altre: assumendo che i sottoheap dei figlio del nodo passato siano heap, mucchifico anche questi 3 nodi.
// Nel caso di scambi di posizione, dovrò richiamare la funzione sui nodi inferiori per garantire la relazione padre<figliore
void minHeapify(struct node heap[], int n, int *hsP){
    int l = left(n);
    int r = right(n);
    int min;

    // Controllo se il figlio sinistro ha valore minore del padre
    if(l < *hsP && heap[l].dist < heap[n].dist){
        min = l;
    }
    else{
        min = n;
    }
    // Controllo se il figlio destro ha valore minore del minore precedente
    if(r < *hsP && heap[r].dist < heap[min].dist){
        min = r;
    }
    // Se il minimo non è il padre, allora scambio la posizione con il minimo e mucchifico il nodo dove è avvenuto lo scambio
    if(min != n){
        swap(heap, n, min);
        minHeapify(heap, min , hsP);
    }
}

// Ritorna la radice dell'heap, o -1 se è vuoto. Se non è vuoto, mette l'ultima foglia come radice
// e chiama minHeapify sulla radice per sistemare l'heap rimasto.
struct node deleteMin(struct node heap[], int *hsP){
    if(*hsP == 0) {
        struct node n;
        n.dist=-1;
        n.index=-1;
        return n;
    }
    struct node res = heap[0];
    heap[0] = heap[*hsP-1];
    --*hsP;
    minHeapify(heap, 0, hsP);
    heap[*hsP] = res;
    return res;
}

// Scambia i valori di due posizioni in un vettore
void swap(struct node heap[],int x, int y){
    struct node temp;
    temp = heap[x];
    heap[x] = heap[y];
    heap[y]=temp;
}


// Ritorna il figlio sinistro del nodo passato
int left(int n){
    return 2*n+1;
}
// Ritorna il figlio destro del nodo passato
int right(int n){
    return 2*n+2;
}


// Dato un vettore di elementi non mucchificati (heap), crea un maxHeap con indici che seguono.
void createMaxHeapifyR(int heap[], int heapI[], int len){
    for (int i = floor((double) len/2)-1; i >=0 ; --i) {
        maxHeapifyR(heap,heapI,i,len);
    }
}

// Funzione di supporto per le altre: assumendo che i sottoheap dei figlio del nodo passato siano heap,
// mucchifico anche questi 3 nodi. Nel caso di scambi di posizione, dovrò richiamare la funzione
// sui nodi inferiori per garantire la relazione padre>figlio.
void maxHeapifyR(int heap[], int heapI[], int n, int len){
    int l = left(n);
    int r = right(n);
    int min;
    if(l < len && heap[l] > heap[n]){
        min = l;
    }
    else{
        min = n;
    }
    if(r < len && heap[r] > heap[min]){
        min = r;
    }
    if(min != n){
        swapR(heap, heapI, n, min);
        maxHeapifyR(heap, heapI, min , len);
    }
}

// Aggiunge un nuovo peso al grafo in ultima posizione dell'array (assumo che sia sempre pieno), poi
// lo sposto verso la radice in base al suo peso.
void insertMaxR(int newP, int newI, int heap[], int heapI[], int len){
    heap[len-1] = newP;
    heapI[len-1] = newI;
    int x = ceil((double) (len-1)/2) - 1;
    int y = len-1;
    while(y > 0 && heap[x] < heap[y]){
        swapR(heap,heapI,x,y);
        x = ceil((double) x/2) - 1;
        y = ceil((double) y/2) - 1;
    }
}

// Elimina la radice dell'heap e assumendo che l'heap sia sempre pieno, mette l'ultima foglia
// come radice (che sarà sempre lunghezza-1); chiama poi maxHeapifyR sulla radice per sistemare l'heap rimasto.
void deleteMaxR(int heap[], int heapI[], int len){
    heap[0] = heap[len-1];
    heapI[0] = heapI[len-1];
    maxHeapifyR(heap,heapI, 0, len-1);
}


// Scambia i valori di due posizioni in un due vettori.
void swapR(int heap[], int heapI[], int x, int y){
    long temp;
    temp = heap[x];
    heap[x] = heap[y];
    heap[y] = temp;
    temp = heapI[x];
    heapI[x] = heapI[y];
    heapI[y] = temp;
}