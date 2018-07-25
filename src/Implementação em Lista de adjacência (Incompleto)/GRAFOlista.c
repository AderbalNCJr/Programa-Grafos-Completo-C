#include "GRAFOlista.h"
#include "FILA.h"

/********** Lista de adjacencia **********/

/* A função NovoNo() recebe um vértice v e o endereço prox de um nó e devolve o endereço a de um novo nó tal que a->v == v e a->prox == prox */
Link NovoNo(int v, Link prox){
    Link a = malloc (sizeof (struct No));
    a->w = v;
    a->prox = prox;
    return a;
}

/* Cria um grafo vazio de n vertices */
Grafo GRAFOcria(int n){
    int i;
    Grafo G = malloc(sizeof *G);
    G->n = n;
    G->m = 0;
    G->adj = malloc(n * sizeof (Link));
    for (i = 0; i < n; i++)
        G->adj[i] = NULL;
    return G;
}

/* Funcao para inserir uma aresta em um grafo */
void GRAFOinsereA(Grafo G, Aresta e){
    Link a;
    int v = e.v, w = e.w;
    
    // insere w na lista de v
    for (a = G->adj[v]; a != NULL; a = a->prox)
        if (a->w == w) return; // aresta existente
    G->adj[v] = NovoNo(w, G->adj[v]);
    
    // insere v na lista de w
    for (a = G->adj[w]; a != NULL; a = a->prox)
        if (a->w == v) return; // aresta existente
    G->adj[w] = NovoNo(v, G->adj[w]);
    
    G->m++;
}

/* Funcao para remover uma aresta de um grafo */
void GRAFOremoveA(Grafo G, Aresta e){
    Link a, pred;
    int v = e.v, w = e.w;
    
    // remove aresta da lista de v
    for (a = G->adj[v], pred = G->adj[v]; a->w != w; pred = a, a = a->prox);
    if (a != NULL) {
        if (a == pred) G->adj[v] = pred->prox; 
        else pred->prox = a->prox;
        free(a);
    }
    
    // remove aresta da lista de w
    for (a = G->adj[w], pred = G->adj[w]; a->w != v; pred = a, a = a->prox);
    if (a != NULL) {
        if (a == pred) G->adj[w] = pred->prox;
        else pred->prox = a->prox;
        free(a);
    }
    
    G->m--;
}

/* Funcao para imprimir um grafo */
void GRAFOimprime(Grafo G) {
    int v, w;
    Link a;
    if (G != NULL){
        printf("%d vertices, %d arestas\n", G->n, G->m);
        for (v = 0; v < G->n; v++) {
            printf( "%2d:", v);
            for (a = G->adj[v]; a != NULL; a = a->prox)
                printf( " %2d", a->w);
            printf( "\n");
        }
    }
}

/* Funcao para destruir um grafo */
void GRAFOdestroi(Grafo G){
    int i;
    for (i = 0; i < G->n; i++){
	if(G->adj[i] != NULL){
	    Link prox, atual;
	    atual = G->adj[i]->prox;
	    while(atual != NULL){
		prox = atual->prox;
		free(atual);
		atual = prox;
	    }
	}
	free(G->adj[i]);
    }
    free(G);  
    G = NULL;  
}

/* Funcao para exibir os graus dos vertices de um grafo */
void GRAFOgrau(Grafo G){
    int i, grau;
    Link a;

    for (i = 0; i < G->n; i++){
    	grau = 0;
	for (a = G->adj[i]; a != NULL; a = a->prox) grau++;
	printf("grau[%d] = %d\n", i, grau);
    }
}


/********** CONSTRUTORES **********/

/* Grafo completo */
Grafo GRAFOconstroiCompleto(int n){
    int i, j;
    Grafo G = GRAFOcria(n);
    for (i = 0; i < n; i++){
        for (j = i+1; j < n; j++){
            Aresta e;
            e.v = i;
            e.w = j;
            GRAFOinsereA(G, e);
        }
    }
    return G;
}

/* Grafo ciclo */
Grafo GRAFOconstroiCiclo(int n){
    int i;
    Grafo G = GRAFOcria(n);
    for (i = 0; i < n; i++){
        Aresta e;
        e.v = i;
        e.w = i+1;
        
        if (i == n-1) e.w = 0;
        
        GRAFOinsereA(G, e);
    }    
    return G;
}

/********** ALGORITMOS **********/
int cont;
int *ordem;

void BPrec(Grafo G){
    int i;
    ordem = malloc(G->n * sizeof(int));
    cont = 0;
    
    printf("Ordem BP: ");
    
    for (i = 0; i < G->n; i++)
        ordem[i] = -1;
    
    for (i = 0; i < G->n; i++){
        if (ordem[i] == -1){
            visitaBP(G,i);
        }
    }
    
    printf("\n");
    free(ordem);
}

void visitaBP(Grafo G, int v){
    Link a;
    int j;
    ordem[v] = cont++;
    printf("%d ", v);
    
    for (a = G->adj[v]; a != NULL; a = a->prox){
        if (ordem[a->w] == -1){
            visitaBP(G,a->w);
        }
    }
}

void BL(Grafo G){
    int i;
    ordem = malloc(G->n * sizeof(int));
    cont = 0;
    
    printf("Ordem BL: ");
    
    for (i = 0; i < G->n; i++)
        ordem[i] = -1;
    
    for (i = 0; i < G->n; i++){
        if (ordem[i] == -1){
            visitaBL(G,i);
        }
    }
    
    printf("\n");
    free(ordem);
}

void visitaBL(Grafo G, int i){
    int v, j;
    FILAcria(G->n);
    FILAinsere(i);
    Link a;
    
    while(!FILAvazia()) {
        v = FILAremove(); // remove primeiro da fila
        if (ordem[v] == -1){
            ordem[v] = cont++;
            printf("%d ", v);
            
            for (a = G->adj[v]; a != NULL; a = a->prox){
                if (ordem[a->w] == -1){
                    FILAinsere(a->w);
                }
            }
        }
    }
    
    FILAdestroi();
}
