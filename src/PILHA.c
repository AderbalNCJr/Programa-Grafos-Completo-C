#include "PILHA.h"

int *pilha;
int inicioPilha, fimPilha;

/* Cria uma pilha vazia */
void PILHAcria(int maxN){
	pilha = (int*) malloc(maxN*sizeof(int));
	inicioPilha = 0;
	fimPilha = 0;
}

/* Verifica se a pilha esta vazia */
int PILHAvazia(){
	return inicioPilha == fimPilha;
}
 /* Insere item na pilha */
void PILHApush(int item) {
	pilha[fimPilha] = item;
    fimPilha++;
}

/* Recupera item da pilha */
int PILHApop() {
    fimPilha--;
	return pilha[fimPilha];
}

/* Destroi pilha */
void PILHAdestroi(){
	free(pilha);
}
