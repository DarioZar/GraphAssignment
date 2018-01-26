#include<stdio.h>
#include<stdlib.h>

#include "graph.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBIW_ASSERT(x)
#include "stb_image_write.h"

/* Stampa su un file fp una matrice rows x columns fatta di interi
 */
void fprintIntMatrix(FILE* fp, int** matrix, int rows, int columns) {
    int i,j;
    for(i=0;i<rows;i++) {
        for(j=0;j<columns;j++) {
            fprintf(fp, "%d", matrix[i][j]);
        }
        fprintf(fp, "\n");
    }
}

int main() {

    int i, j;
    int size, cores;
    int link;
    double pjoincorecore, pjoinperper, pjoincoreper;

    int **adjMatrix; // TODO: funzione che va da Graph* a adjMatrix
    FILE* fp;
    char* coreper_degree_filename = "coreper_degree_seq.txt";
    char* matrix_filename = "coreper_matrix.txt";


    // L'utente inserisce i parametri per la generazione del grafo
    printf("Inserire numero di vertici del grafo da generare:\t");
	scanf("%d", &size);
    do {
        printf("Inserire numero di core (minore del numero di vertici):\t");
	    scanf("%d", &cores);
    } while(cores>size);

    printf("Inserire probabilità dei collegamenti (0<p<1)\n");
    do {
        printf("core-core\t");
        scanf("%lf", &pjoincorecore);
    } while(pjoincorecore<0 || pjoincorecore>1);
    do {
        printf("periphery-periphery\t");
        scanf("%lf", &pjoinperper);
    } while(pjoinperper<0 || pjoinperper>1);
    do {
        printf("core-periphery\t");
        scanf("%lf", &pjoincoreper);
    } while(pjoincoreper<0 || pjoincoreper>1);
    

    // inizializzo la matrice di adiacenza
    adjMatrix = calloc(size, sizeof(int*));
    for(i=0;i<size;i++) {
        adjMatrix[i] = calloc(size, sizeof(int));
    }

    Graph* graph = createGraph(size);

    for(i=0;i<size;i++) {
        for(j=0;j<size;j++) {
            // se sono entrambi core
            if(i<cores && j<cores) link = (rand()/(double)RAND_MAX < pjoincorecore);
            // se sono entrambi per
            else if (i>=cores && j>=cores) link = (rand()/(double)RAND_MAX < pjoinperper);
            // se sono core-per
            else link = (rand()/(double)RAND_MAX < pjoincoreper);

            // se il valore è vero viene aggiunto l'edge
            if(link) {
                printf("Adding edge %d--%d\n", i, j);
                addEdge(graph, i, j);
                adjMatrix[i][j]++;
            }
        }
    }

    printf("\nLa degree sequence del grafo generato è nel file %s\n", coreper_degree_filename);
	// Stampo su file la degree_seq di graph
	fp = fopen(coreper_degree_filename, "w");
	for(i=0; i<size; i++) {
		fprintf(fp, "%d: %d\n", i, nodeDegree(graph, i));
	}
	fclose(fp);

    printf("\nLa matrice di adiacenza viene stampata sul file %s\n", matrix_filename);
    fp = fopen(matrix_filename, "w");
    fprintIntMatrix(fp, adjMatrix, size, size);
    fclose(fp);

    unsigned char img[size][size];
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            img[i][j] = (adjMatrix[i][j]==0)?200:0;
        }
    }

    stbi_write_jpg("matrix.jpg", size, size, 1, img, 70);

    return 0;

}