# Graph Ranker

**Graph Ranker** è un progetto sviluppato per gestire una classifica di grafi in base al loro "peso", definito come la somma dei percorsi minimi dal nodo 0 a tutti gli altri nodi. Il progetto è stato realizzato come prova finale per il corso di **Algoritmi e Principi dell'Informatica**.

## 📌 Descrizione

Il programma:
- Calcola il peso di ciascun grafo dato in input con comando "AggiungiGrafo" con algoritmi efficienti per il calcolo dei percorsi minimi.
- Ordina i grafi in una classifica dal più leggero al più pesante usando mucchi (Heaps).
- Stampa in output la classifica quando specificato con il comando "TopK"
- Garantisce gestione della memoria e performance, verificati con l'uso di Valgrind.

## 🛠 Tecnologie e Strumenti

- **C** – Linguaggio principale del progetto.
- **Valgrind** – Utilizzato per:
  - `memcheck`: verifica della gestione della memoria.
  - `callgrind`/`kcachegrind`: analisi e viualizzazione delle prestazioni.
  - `massif`: profiling dell'utilizzo della memoria.
- **Python** – Utilizzato per generare automaticamente file di test/input.

## ▶️ Come usare il progetto

1. **Compila il sorgente**:
   ```bash
   gcc -Wall -Werror -O2 -g3 progetto.c -o graph_ranker
   ```

2. **Genera un file di input** (usando inputget.py):
   ```bash
   python3 inputgen.py filename d k size --topk_end
   ```
   ### Flag necessarie
   - **filename**, Nome del file da generare
   - **d**, type=int, Numero di nodi dei grafi da generare
   - **k**, type=int, Lunghezza della classifica
   - **size**, type=int, Numero di grafi da generare
   ### Flag opzionali
   - **--edge_prob**, type=float, default=0.5, Probabilità con cui inserire un arco nel grafo
   - **--weight_min**, type=int, default=0, Valore minimo dei pesi dei grafi
   - **--weight_max** type=int, default=2**32-1 Valore massimo dei pesi dei grafi
   - **--decreasing** Rendi i pesi degli archi tendenzialmente decrescenti
   - **--topk_start** Aggiungi comando TopK all'inizio
   - **--topk_end**, Aggiungi TopK alla fine
   - **--topk_every**, type=int, Aggiungi TopK ogni TOPK_EVERY matrici
   - **--topk_prob**, type=float, Aggiungi TopK con una certa probabilità

4. **Esegui il programma**:
   ```bash
   ./graph_ranker < input.txt
   ```

5. *(Opzionale)*: usa Valgrind per verificare memoria e performance:
   ```bash
   valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./graph_ranker < input.txt
   
   valgrind --tool=callgrind --callgrind-out-file=outputfile ./graph_ranker < input.txt
   kcachegrind outputfile

   valgrind --tool=massif --massif-out-file=outputfile ./graph_ranker < input.txt
   massif-visualizer outputfile
   ```

## 📊 Risultati

Il progetto implementato ha superato tutti i test, ottenendo una valutazione di 30 Cum Laude. Il codice è stato testato sia nella gestione dello spazio sia nel tempo richiesto, variando diversi parametri:
- Numero di grafi
- Grandezza dei grafi
- Numero di elementi della classifica
- Numero di stampe della classifica

## 👤 Autore

Progetto sviluppato da [Francesco Colabene](https://github.com/FrancescoColabene) come parte dell’esame del corso **Algoritmi e Principi dell’Informatica**, Politecnico di Milano, A.A. 2020/2021.
