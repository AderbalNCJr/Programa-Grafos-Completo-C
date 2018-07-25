#include <stdlib.h>
#include <stdio.h>

/* Struct Aresta */
typedef struct{
    int v;
    int w;
} Aresta;

/* Struct Grafo representado por matriz */
struct grafo{
    int n;
    int m;
    int **adj;
};

/* Um Grafo é um ponteiro para um grafo, ou seja, Grafo contém o endereço de um grafo. */
typedef struct grafo *Grafo;

/* TAD GRAFO */
Grafo GRAFOcria(int);
void GRAFOinsereA(Grafo, Aresta);
void GRAFOremoveA(Grafo, Aresta);
void GRAFOinsereApeso(Grafo, Aresta, int);
void GRAFOinsereDpeso(Grafo, Aresta, int);
void GRAFOimprime(Grafo);
void GRAFOdestroi(Grafo);
void GRAFOgrau(Grafo);

/* Construtores de grafos */
Grafo GRAFOconstroiCompleto(int);
Grafo GRAFOconstroiCiclo(int);
Grafo GRAFOconstroiGrade(int);
Grafo GRAFOconstroiPontes(int);

/* Algoritmos */
void BPrec(Grafo G);
void visitaBP(Grafo G, int v);
void BL(Grafo G);
void visitaBL(Grafo G, int v);
void Pontes(Grafo G);
void pontesRec(Grafo G, int v);
void Articulacao(Grafo G);
void artRec(Grafo G, int v);
void Dijkstra(Grafo G, int v);
void BellmanFord(Grafo G, int v);
void FloydWarshall(Grafo G);
void Prim(Grafo G);
Grafo Kruskal(Grafo G);
void Hierholzer(Grafo G);
void Fleury(Grafo G);
void Christofides(Grafo G);

// Leitura do arquivo
Grafo GRAFOleitura(const char *nomearq);