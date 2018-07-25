#include <stdlib.h>
#include <stdio.h>

/* Struct Aresta */
typedef struct{
    int v;
    int w;
} Aresta;

/* Struct Link é um ponteiro para um No */
typedef struct No *Link;

/* Struct No (lista encadeada) */
struct No{
    int w;
    Link prox;
};

/* Struct grafo representado por lista */
struct grafo{
    int n;
    int m;
    Link *adj;
};

/* Um Grafo é um ponteiro para um grafo, ou seja, Grafo contém o endereço de um grafo. */
typedef struct grafo *Grafo;

/* TAD GRAFO */
Grafo GRAFOcria(int);
void GRAFOinsereA(Grafo, Aresta);
void GRAFOremoveA(Grafo, Aresta);
void GRAFOimprime(Grafo);
void GRAFOdestroi(Grafo);
void GRAFOgrau(Grafo);

/* Construtores de grafos */
Grafo GRAFOconstroiCompleto(int);
Grafo GRAFOconstroiCiclo(int);

/* Algoritmos */
void BPrec(Grafo G);
void visitaBP(Grafo G, int v);
void BL(Grafo G);
void visitaBL(Grafo G, int v);