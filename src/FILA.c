#include "FILA.h"

int *queue;
int inicioFila, fimFila;

/* Cria uma fila vazia */
void FILAcria(int maxN){
	queue = (int*) malloc(maxN*sizeof(int));
	inicioFila = 0;
	fimFila = 0;
}

/* Verifica se a fila esta vazia */
int FILAvazia(){
	return inicioFila == fimFila;
}
 /* Insere item na fila */
void FILAinsere (int item) {
	queue[fimFila++] = item;
}

/* Recupera item da fila */
int FILAremove() {
	return queue[inicioFila++];
}

/* Destroi fila */
void FILAdestroi(){
	free(queue);
}
