#include "GRAFOmatriz.h"
#include "FILA.h"
#include "PILHA.h"

#define INF 1000000

/********** TAD GRAFO **********/

/* Cria matriz [ l ] [ c ] vazia */
int **MATRIZint(int l, int c){
    int i, j;
    int ** m = (int **) malloc(l * sizeof(int *));
    for (i = 0; i < l; i++)
        m[i] = (int *) malloc(c * sizeof(int));
    for (i = 0; i < l; i++)
        for (j = 0; j < c; j++)
            m[i][j] = 0;
    return m;
}

/* Cria vetor [ n ] vazio */
int *VETORint(int n){
    int i;
    int *v = (int *) malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        v[i] = 0;
    return v;
}

/* Cria um grafo vazio de n vertices */
Grafo GRAFOcria(int n){
    Grafo G = (Grafo) malloc(sizeof(Grafo));
    G->n = n;
    G->m = 0;
    G->adj = MATRIZint(n,n);
    
    return G;
}

/* Funcao para inserir uma aresta em um grafo */
void GRAFOinsereA(Grafo G, Aresta e){
    int v = e.v;
    int w = e.w;
    if (G->adj[v][w] == 0) {
        G->m++;
        G->adj[v][w] = 1;
        G->adj[w][v] = 1;
    }
}

/* Funcao para inserir uma aresta em um grafo com peso */
void GRAFOinsereApeso(Grafo G, Aresta e, int peso){
    int v = e.v;
    int w = e.w;
    
    if (G->adj[v][w] == 0) {
        G->m++;
        G->adj[v][w] = peso;
        G->adj[w][v] = peso;
    }
}

/* Funcao para inserir um arco em um grafo direcionado com peso */
void GRAFOinsereDpeso(Grafo G, Aresta e, int peso){
    int v = e.v;
    int w = e.w;
    if (G->adj[v][w] == 0) {
        G->m++;
        G->adj[v][w] = peso;
    }
}

/* Funcao para remover uma aresta de um grafo */
void GRAFOremoveA(Grafo G, Aresta e){
    int v = e.v;
    int w = e.w;
    if (G->adj[v][w] == 1) {
        G->m--;
        G->adj[v][w] = 0;
        G->adj[w][v] = 0;
    }
}

/* Funcao para imprimir um grafo */
void GRAFOimprime(Grafo G) {
    int v, w;
    
    printf("%d vertices, %d arestas\n", G->n, G->m);
    for (v = 0; v < G->n; v++) {
        printf( "%2d:", v);

        for (w = 0; w < G->n; w++){
            if (G->adj[v][w])
                printf( " %2d", w);
        }
        printf( "\n");
    }
}

/* Funcao para destruir um grafo */
void GRAFOdestroi(Grafo G){
    int i;
    for (i = 0; i < G->n; i++) {
        free(G->adj[i]);
    }
    free(G->adj);
    free(G);
}

/* Funcao para exibir os graus dos vertices de um grafo */
void GRAFOgrau(Grafo G){
    int v, w, grau;
    
    printf("Grau:\n");
       
    for (v = 0; v < G->n; v++) {
        grau = 0;
        for (w = 0; w < G->n; w++){
            if (G->adj[v][w] != 0) {
                grau++;
            }
        }
        printf("grau[%d] = %d\n", v, grau);
    }
}

/********** IO **********/

// Leitura do arquivo
Grafo GRAFOleitura(const char *nomearq)
{
    int n, m, t, peso;
    Aresta e;
    FILE *arquivo;
    arquivo = fopen(nomearq,"r");
    
    if (!arquivo) {
        printf("O Arquivo %s nao pode ser aberto.\n", nomearq);
        getchar();
        exit(1);
    }

    // n
    fscanf(arquivo, "%d %d %d", &n, &m, &t);
    Grafo G = GRAFOcria(n);

    // nao direcionado
    if (t == 0){
        while (!feof(arquivo)){
            fscanf(arquivo, "%d %d %d", &e.v, &e.w, &peso);
            GRAFOinsereApeso(G, e, peso);
        }
    }
    // direcionado
    else{
        while (!feof(arquivo)){
            fscanf(arquivo, "%d %d %d", &e.v, &e.w, &peso);
            GRAFOinsereDpeso(G, e, peso);
        }
    }
    
    fclose(arquivo);
    
    printf("Leitura OK!\n");
    
    return G;
}

/********** CONSTRUTORES **********/

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

Grafo GRAFOconstroiPontes(int n){
    int i, j;
    Grafo G = GRAFOcria(n);
    // Clique 0 a 3
    for (i = 0; i < 4; i++){
        for (j = i+1; j < 4; j++){
            Aresta e;
            e.v = i;
            e.w = j;
            GRAFOinsereA(G, e);
        }
    }
    
    // Aresta 3-4
    Aresta e;
    e.v = 3;
    e.w = 4;
    GRAFOinsereA(G, e);

    // Aresta 3-5
    e.v = 3;
    e.w = 5;
    GRAFOinsereA(G, e);

    // Clique 5 a 7
    for (i = 5; i < 8; i++){
        for (j = i+1; j < 8; j++){
            Aresta e;
            e.v = i;
            e.w = j;
            GRAFOinsereA(G, e);
        }
    }
    
    // Aresta 7-8
    e.v = 7;
    e.w = 8;
    GRAFOinsereA(G, e);

    // Clique 8 a 10
    for (i = 8; i < 11; i++){
        for (j = i+1; j < 11; j++){
            Aresta e;
            e.v = i;
            e.w = j;
            GRAFOinsereA(G, e);
        }
    }
    
    return G;
}

/********** ALGORITMOS **********/
int cont;
int *ordem, *pai, *menor;

// Profundidade
void BPrec(Grafo G){ 
    int i;
    ordem = VETORint(G->n);
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
    int j;
    ordem[v] = cont++;
    printf("%d ", v);

    for (j = 0; j < G->n; j++){
        if (G->adj[v][j] != 0 && ordem[j] == -1){
            visitaBP(G,j);
        }
    }
}

// Largura
void BL(Grafo G){
    int i;
    ordem = VETORint(G->n);
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

    while(!FILAvazia()) {
        v = FILAremove(); // remove primeiro da fila
        if (ordem[v] == -1){
            ordem[v] = cont++;
            printf("%d ", v);

            for (j = 0; j < G->n; j++){
                if (G->adj[v][j] != 0 && ordem[j] == -1){
                    FILAinsere(j);
                }
            }
        }
    }

    FILAdestroi();
}

// Pontes
void Pontes(Grafo G){
    int i;
    
    ordem = VETORint(G->n);
    pai = VETORint(G->n);
    menor = VETORint(G->n);
    cont = 0;
    
    printf("Pontes:\n");
    
    for (i = 0; i < G->n; i++)
        ordem[i] = pai[i] = menor[i] = -1;
    
    for (i = 0; i < G->n; i++){
        if (ordem[i] == -1){
            pai[i] = i;
            pontesRec(G,i);
        }
    }
    
    for (i = 0; i < G->n; i++) {
        if (menor[i] == ordem[i] && pai[i] != i){
            printf("%d -- %d\n", pai[i], i);
        }
    }
    
    printf("\n");
    free(ordem);
    free(pai);
    free(menor);
}

void pontesRec(Grafo G, int v){
    int j;
    int min;
    ordem[v] = cont++;
    min = ordem[v];
    
    for (j = 0; j < G->n; j++){
        if (G->adj[v][j] != 0 && ordem[j] == -1){
            pai[j] = v;
            pontesRec(G,j);
            // descendente tem aresta de retorno
            if (menor[j] < min){
                min = menor[j];
            }
        }
        else if (G->adj[v][j] != 0){
            // aresta de retorno a partir de v
            if (ordem[j] < min && j != pai[v]){
                min = ordem[j];
            }
        }
    }
    menor[v] = min;
    
    
}

// Articulacao
void Articulacao(Grafo G){
    int i;
    
    ordem = VETORint(G->n);
    pai = VETORint(G->n);
    menor = VETORint(G->n);
    cont = 0;
    
    printf("Articulacoes:\n");
    
    for (i = 0; i < G->n; i++)
        ordem[i] = pai[i] = menor[i] = -1;
    

    for (i = 0; i < G->n; i++){
        if (ordem[i] == -1){
            pai[i] = i;
            artRec(G,i);
        }
    }
    
    int v, w;
    int *grau = malloc(G->n * sizeof(int));
    
    for (v = 0; v < G->n; v++) {
        grau[v] = 0;
        for (w = 0; w < G->n; w++){
            if (G->adj[v][w] == 1) {
                grau[v]++;
            }
        }
    }
    
    for (i = 0; i < G->n; i++) {
        if (menor[i] == ordem[i] && pai[i] != i){
            //printf("%d -- %d\n", pai[i], i);
	    // Testar se pai[i] eh articulacao
	    if (grau[pai[i]] > 1) printf("%d, ", pai[i]);

	    // Testar se i eh articulacao
	    if (grau[i] > 1) printf("%d, ", i);
        }
    }
    
    printf("\n");
    free(ordem);
    free(pai);
    free(menor);
}

void artRec(Grafo G, int v){
    int j;
    int min;
    ordem[v] = cont++;
    min = ordem[v];
    
    for (j = 0; j < G->n; j++){
        if (G->adj[v][j] != 0 && ordem[j] == -1){
            pai[j] = v;
            artRec(G,j);
            // descendente tem aresta de retorno
            if (menor[j] < min){
                min = menor[j];
            }
        }
        else if (G->adj[v][j] != 0){
            // aresta de retorno a partir de v
            if (ordem[j] < min && j != pai[v]){
                min = ordem[j];
            }
        }
    }
    menor[v] = min;
    
}

void Dijkstra(Grafo G, int v){
    int *dist = VETORint(G->n);
    int *pred = VETORint(G->n);
    
    int *aberto = VETORint(G->n);
    int acabou = 0;
    
    for (int i = 0; i < G->n; i++) {
        dist[i] = INF;
        pred[i] = -1;
        aberto[i] = 1;
    }
    dist[v] = 0;
    pred[v] = v;
    aberto[v] = 1;
    
    int r, menor;
    
    while(!acabou){
        menor = INF;
        for (int i = 0; i < G->n; i++){
            if (aberto[i] && dist[i] < menor){
                r = i;
                menor = dist[i];
            }
        }
        
        if (menor == INF) acabou = 1;
        else {
            aberto[r] = 0;
            for (int  i = 0; i < G->n; i++){
                if (i != r && aberto[i] && G->adj[r][i] > 0) {
                    
                    if (dist[r] + G->adj[r][i] < dist[i]) {
                        dist[i] = dist[r] + G->adj[r][i];
                        pred[i] = r;
                    }
                }
            }
        }
    }
    
    printf("\n** Dijkstra **\n\n");
    for (int i = 0; i < G->n; i++){
        printf("%d -- %d : %d\n", v, i, dist[i]);
    }
}


void BellmanFord(Grafo G, int v){
    int *dist = malloc(G->n * sizeof(int));
    int *pred = malloc(G->n * sizeof(int));
    int altera = 0;
    
    for (int i = 0; i < G->n; i++) {
        if (G->adj[v][i] > 0){
            dist[i] = G->adj[v][i];
            pred[i] = v;
        }
        else{
            dist[i] = INF;
            pred[i] = -1;
        }
    }
    dist[v] = 0;
    pred[v] = v;

    for (int k = 0; k < G->n - 1; k++){
        altera = 0;
        for (int i = 0; i < G->n; i++) {
            if (i != v){
                for (int j = 0; j < G->n; j++) {
                    if (G->adj[j][i] != 0){
                        if (dist[i] > dist[j] + G->adj[j][i]){
                            dist[i] = dist[j] + G->adj[j][i];
                            pred[i] = j;
                            altera = 1;
                        }
                    }
                }
            }
        }
        if (altera == 0) break;
    }
    printf("\n** Bellman Ford **\n\n");
    for (int i = 0; i < G->n; i++){
        printf("%d -- %d : %d\n", v, i, dist[i]);
    }
}

void FloydWarshall(Grafo G){
    int **L = MATRIZint(G->n, G->n);
    
    for (int i = 0; i < G->n; i++) {
        for (int j = 0; j < G->n; j++) {
            L[i][j] = INF;
        }
    }
    
    for (int i = 0; i < G->n; i++) {
        for (int j = 0; j < G->n; j++) {
            if (G->adj[i][j] != 0)
                L[i][j] = G->adj[i][j];
        }
    }
    
    for (int k = 0; k < G->n; k++){
        for (int i = 0; i < G->n; i++) {
            for (int j = 0; j < G->n; j++) {
                if (L[i][j] > (L[i][k]+L[k][j])){
                    L[i][j] = (L[i][k]+L[k][j]);
                }
            }
        }
    }
    
    printf("\n** Floyd Warshall **\n\n");
    for (int i = 0; i < G->n; i++){
        for (int j = 0; j < G->n; j++) {
            if (L[i][j] < INF - 100)
                printf("%d ", L[i][j]);
            else
                printf("M ");
        }
        printf("\n");
    }
    
}

void Prim(Grafo G){
  //printf("executou");
  int min, k = -1, l = -1;
  int *pai = (int*) malloc(G->n * (sizeof(int)));
  for(int v = 0 ; v < G->n ; v++){
    pai[v] = -1 ;

  }
  pai[0] = 0;

  while(1){
    min = 10000;
    for( int j = 0 ; j < G->n ; j++){
      if(pai[j] != -1){
        for(int v = 0 ; v < G->n ; v++){
          if(G->adj[j][v] > 0 ){
            if(pai[v] == -1 && min > G->adj[j][v]){
              min = G->adj[j][v];
              k = j ;
              l = v ;

            }

          }
        }
      }
      }
      if( min == 10000){
        break;
    }

      pai[l] = k;

  }
  printf("saiu\n" );
  for(int i = 0 ; i < G->n ; i++){
    printf("%d -- %d\n",i,pai[i] );
  }
  int soma = 0 ;
  for(int i = 0 ; i < G-> n ; i++){
    soma = soma+G->adj[i][pai[i]];
  }
  printf("%d\n", soma);
}

void Kruskal (Grafo G){
  int soma = 0;
  int min, k = -1, l = -1, x = -1, y = -1;
  int *comp = (int*) malloc(G->n * sizeof(int));

  for(int i = 0 ; i < G->n ; i++){
    comp[i] = i ;
  }


  while(1){
    min = 10000;
    for(int i = 0 ; i < G->n ; i++){
        for(int v = 0 ; v < G->n ; v++){
          if(G->adj[i][v] > 0 ){
            if(comp[i] != comp[v] && min > G->adj[i][v]){
              min = G->adj[i][v];
              k = i;
              l = v;
            }
          }
        }
    }
    if(min == 10000)
      break;

    soma+= G->adj[k][l];
    x = comp[k]; y = comp[l];
    for(int v = 0; v < G->n ;v++){
      if(comp[v] == y)
        comp[v] = x;
    }
  }

  printf(" %d\n",soma );
}

void Hierholzer (Grafo G){
int i, j, NV = G->n, impar = 0, verticeImpar, vertice, corrente, inicio, u, tamanhoTour = 0, v, posicaoVazia, fim = 0;
int grau[NV], tour[G->m], subtour[G->m], tamanhoSubtour = 0;

for (i = 0; i < NV; i++){
  grau[i] = 0;
  subtour[i] = -1;
  tour[i] = -1;
}

//encontra o numero de vertices de grau impar
for (i = 0; i < NV; i++){
  for (j = 0; j < NV;j++){
    if (G->adj[i][j] != 0 && i != j){
      grau[i]++;
    }
  }
}
for (i = 0; i < NV; i++){
  if (grau[i] % 2 != 0){
    impar ++;
    verticeImpar = i;
  }
}

//Verifica se é euleriano ou semi
if (impar > 2){
  printf(" ERRO: grafo não possui caminho ou ciclo euleriano\n");
} else {
  if (impar == 2){
    v = verticeImpar;
  } else {
    v = 1;
  }
}

tour[0] = v;
do {
  //encontra v
  int sair = 0;
  for (i = 0; i < NV; i++){
    vertice = tour[i];
    if(sair == 1){
      break;
    }
    for (j = 0; j < NV; j++){
      if (G->adj[vertice][j] != 0){
        v = vertice;
        sair = 1;
        break;
      }
    }
  }
  for (i = 0; i < NV; i++){
    subtour[i] = -1;
  }
  subtour[0] = v;
  corrente = v;

  do{
    //encontra u, sendo o proximo adj de v
    for (i = 0; i < NV; i++){
      if (G->adj[corrente][i] != 0){
        u = i;
      }
    }
    //marca a aresta
    G->adj[corrente][u] = 0;
    grau[corrente]--;
    grau[u]--;
    subtour[tamanhoSubtour] = u;
    tamanhoSubtour++;
    corrente = u;
  //  printf("%d\n", subtour[posicaoVazia]);
  } while (v != corrente);
  //integrar subtour
  for (i = 0; i < NV; i++){
    if(tour[i] == subtour[0]){
      inicio = i;
      break;
    }
  }
  tamanhoTour = 0;
  //encontra o numero de posicoes a partir do inicio
  for (i = inicio + 1; i < NV; i++){
    if(tour[i] != -1){
      tamanhoTour ++;
    }
  }
  //desloca o elementos de tour
  for(i = inicio + tamanhoTour; i != inicio; i--){
    tour[i + tamanhoSubtour] = tour[i];
  }

  //acrescenta o subtour
  for(i = 0; i < tamanhoSubtour; i++){
    tour[inicio + i + 1] = subtour[i];
  }

  //zera o subtour
  for (i = 0; i < NV; i++){
    subtour[i] = -1;
  }
  tamanhoSubtour = 0;

  //verifica se todas as arestas foram marcadas
  fim = 1;
  for (i = 0; i < NV; i++){
    for (j = 0; j < NV; j++){
      if (G->adj[i][j] != 0){
        fim = 0;
        break;
      }
    }
  }
} while (fim == 0);

//imprime Resultado
printf("Resultado:\n");
for(i = 0; i < NV; i++){
  printf(" %d - ", tour[i]);
}
}

void Fleury(Grafo G){
  int i, j, NV = G->n;
  int tour[NV], grau[NV], impar = 0, verticeImpar, v, posicaoTour = 1, u, fim = 0, adj, ponte, candidatoU;

  for (i = 0; i < NV; i++){
    grau[i] = 0;
    tour[i] = 0;
  }

  for (i = 0; i < NV; i++){
    for (j = 0; j < NV;j++){
      if (G->adj[i][j] != 0 && i != j){
        grau[i]++;
      }
    }
  }
  for (i = 0; i < NV; i++){
    if (grau[i] % 2 != 0){
      impar ++;
      verticeImpar = i;
    }
  }

  if (impar > 2){
    printf(" ERRO: grafo não possui caminho ou ciclo euleriano\n");
  } else {
    if (impar == 2){
      v = verticeImpar;
    } else {
      v = 1;
    }
  }

  tour[0] = v;
  printf("Caminho euleriano:\n");
  printf("%d - ", tour[0]);
  while(fim == 0){
    adj = 0; ponte = 0;
    for (i = 0; i < NV; i++){
      if (G->adj[v][i] != 0 && v != i){
        adj++;
        candidatoU = i;
        //verifica se v - u é ponte
        ponte = Pontes(G, candidatoU, v);
        if(ponte != -1){
          u = candidatoU;
          break;
        }
      }
    }
    if (adj == 1){
      u = candidatoU;
    }

    tour[posicaoTour] = u;
    printf(" %d - ", tour[posicaoTour]);
    posicaoTour ++;
    G->adj[u][v] = 0;
    G->adj[v][u] = 0;
    fim = 1;
    for (i = 0; i < NV; i++){
      for (j = 0; j < NV; j++){
        if (G->adj[i][j] != 0){
          fim = 0;
          break;
        }
      }
    }
    v = u;
  }
  if (impar != 2){
    printf("%d\n", tour[0]);
  }
  printf("\n");
}