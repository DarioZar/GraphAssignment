# GraphAssignment
Assignment per il corso di Informatica e programmazione, corso di laurea in Scienze Fisiche, Anno 2017/2018

## graph
La libreria graph implementa una semplice rappresentazione di un grafo non diretto, facendo uso di una **Adjacency List**. Un grafo è rappresentato da un array di Nodi, ognuno identificato con un intero (`int vertex`). Ogni nodo si riferisce al nodo adiacente (`next`).

Alla creazione di un edge tra `src` e `dest`:
- il nodo `dest` si riferisce a `src`
- la adjacency list di `src` si riferisce a `dest`
- il nodo `src` si riferisce a `dest`
- la adjacency list di `dest` si riferisce a `src`

In questo modo si creano i collegamenti nei due sensi, e la adjacency list è solo un array di nodi, ognuno dei quali si riferisce a quello adiacente, come una catena.

## Configuration Model
Data una sequenza di gradi dei nodi, la sequenza (se valida, ovvero se ha somma pari) viene trasformata in una **stublist**, ovvero una lista di semicollegamenti esistenti tra i nodi.
Allo shuffling della stublist, ogni coppia rappresenta un edge del grafo: si ottiene così una *Edge List*, che può venire subito inserita nel grafo attraverso vari `addEdge`.

Il main di `conf.c` contiene una demo in cui viene generata una sequenza di gradi random e viene stampata su un file. Una volta generato il grafo, ne viene estratta la sequenza di gradi e stampata su un altro file. I file generati sono identici, come si può notare usando, ad esempio
```
cmp degree_seq.txt gen_degree_seq.txt
```

## Core-Periphery
Dati un numero di vertici e un numero di nodi core, il grafo viene generato con probabilità scelta dall'utente che un collegamento core-core, core-periphery o periphery-periphery esista.

Il collegamento tra i e j viene aggiunto solo se il numero random tra 0 e 1 generato con `rand` risulta minore della probabilità scelta.

Se le probabilità sono scelte nel modo corretto (alta che sia core-core o core-periphery, bassa che sia periphery-periphery) e dato che i nodi core sono quelli con identificativo più basso, si notano subito le proprietà di questo tipo di grafo guardando la sequenza di gradi e la matrice di adiacenza, stampati su file.

Dalla sequenza di gradi i primi nodi (i nodi core) hanno gradi molto più alti degli altri.

Dalla matrice di adiacenza si nota come il "quadrante" in alto a sinistra (collegamenti core-core) è piena, così come i quadranti in basso a sinistra e in alto a destra (collegamenti core-periphery). Nel quadrante in basso a destra (periphery-periphery), invece, la matrice risulta sparsa.