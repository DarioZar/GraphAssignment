#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "graph.h"


/* Implementation of Knuth shuffling algorithm
 * Shuffles randomly the array of int, int* array of size int size
 */
void shuffle(int* array, int size) {
	int i,j,tmp;
	for(i=0; i<size-1; i++) {
		// j is a random int between i and size-1
		// m + rand()/(RAND_MAX/(M-1 - m) + 1)
		// or m + rand()%(M-1 - m)
		j = i + rand() / (RAND_MAX / (size - i) + 1);

		// swap the values
		tmp=array[i];
		array[i] = array[j];
		array[j] = tmp;
	}
}

/* Dall'array di int della degree sequence crea un array di semicollegamenti
 * grande quanto la somma degli elementi della degree sequence
 */
int* to_stublist(int* degree_seq, int size, int sum) {
	int i, j, n;
	int* stublist = calloc(sum, sizeof(int));
	
	n=0;
	for(i=0; i<size; i++){
		for(j=0; j<degree_seq[i]; j++) {
			stublist[n + j] = i;
		}
		n+=degree_seq[i];
	}

	return stublist;
}

/* Ritorna la somma degli elementi dell'array di int */
int array_sum(int* array, int size){
	int i, sum=0;
	for(i=0; i<size; i++) sum+=array[i];
	return sum;
}

Graph* gen_configuration_model(int* degree_seq, int vertices) {

	Graph* graph = createGraph(vertices);
	// Se la somma dei gradi non è pari allora non è un grafo
	// ritorno il grafo vuoto
	int sum = array_sum(degree_seq, vertices);
	if(sum%2) {
		printf("La somma dei gradi è %d\n", sum);
		printf("ERRORE. UN GRAFO HA SOMMA DEI GRADI PARI.\n");
	} else {
		int i;
		// Creo una lista dei semicollegamenti e la mischio
		int* stublist = to_stublist(degree_seq, vertices, sum);
		shuffle(stublist, sum);
		// Passo dalla "Edgelist" al grafo
		for(i=0; i<sum; i+=2) {
			printf("Adding edge %d--%d\n", stublist[i], stublist[i+1]);
			addEdge(graph, stublist[i], stublist[i+1]);
		}
	}

	return graph;

}


int main() {
	
	int i;
	int size, maxgrad, sum;
	int* degree_seq;
	FILE* fp;
	char* degree_seq_filename = "degree_seq.txt";
	char* print_graph_filename = "graph.txt";
	char* gen_graph_degree_filename = "gen_degree_seq.txt";

	printf("Inserire numero di vertici del grafo da generare:\t");
	scanf("%d", &size);
	printf("\nInserire massimo grado dei nodi\t");
	scanf("%d", &maxgrad);
	printf("\nGenero una degree-sequence e la stampo sul file %s\n", degree_seq_filename);

	degree_seq = calloc(size, sizeof(int));

	// Genera una degree_sequence pari
	// Potrei aumentare di uno un elemento a caso, ma aumenterei il maxgrad
	do {
		srand(time(NULL));
		for(i=0; i<size; i++) {
			degree_seq[i] = (int) rand() % maxgrad;
		}
		sum = array_sum(degree_seq, size);
	} while(sum%2);

	// Stampa la degree_seq su file
	fp = fopen(degree_seq_filename, "w");
	for(i=0; i<size; i++) {
		fprintf(fp, "%d: %d\n", i, degree_seq[i]);
	}
	fclose(fp);

	printf("\nGenero un grafo e lo stampo sul file %s\n", print_graph_filename);
	Graph* graph = gen_configuration_model(degree_seq, size);

	// Stampo su file il grafo generato
	fp = fopen(print_graph_filename, "w");
	fprintGraph(fp, graph);
	fclose(fp);

	printf("\nLa degree sequence del grafo generato è nel file %s\n", gen_graph_degree_filename);
	// Stampo su file la degree_seq di graph
	fp = fopen(gen_graph_degree_filename, "w");
	for(i=0; i<size; i++) {
		fprintf(fp, "%d: %d\n", i, nodeDegree(graph, i));
	}
	fclose(fp);
	
	return 0;
}
