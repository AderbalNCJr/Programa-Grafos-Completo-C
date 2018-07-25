#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "GRAFOmatriz.h"
//#include "GRAFOlista.h"

int menuPrincipal(){
    int escolha, r;
    do {
        printf("********** GRAFOS **********\n\n");
        printf("1. Gerar grafo\n");
        printf("2. Manipular grafo\n");
        printf("3. Algoritmos\n");
        printf("0. Sair\n");
        printf("> ");
        r = scanf("%d",&escolha);
    } while (escolha < 0 || escolha > 3);
    return escolha;
}

int menuConstrucao(){
    int escolha, r;
    do {
        printf("*** Construcao ***\n\n");
        printf("1. Grafo vazio\n");
        printf("2. Grafo completo\n");
        printf("3. Grafo ciclo\n");
        printf("> ");
        r = scanf("%d",&escolha);
    } while (escolha < 1 || escolha > 3);
    return escolha;
}

int menuManipulacao(){
    int escolha, r;
    do {
        printf("*** Manipulacao ***\n\n");
        printf("1. Imprime\n");
        printf("2. Lista graus\n");
        printf("3. Destroi\n");
        printf("> ");
        r = scanf("%d",&escolha);
    } while (escolha < 1 || escolha > 3);
    return escolha;
}

int menuAlgoritmos(){
    int escolha, r;
    do {
        printf("*** Algoritmos ***\n\n");
        printf("1. Busca em Profundidade\n");
        printf("2. Busca em Largura\n");
        printf("3. Ponte\n");
	    printf("4. Articulacao\n");
        printf("5. Dijkstra\n");
        printf("6. Bellman Ford\n");
        printf("7. Floyd Warshall\n");
        printf("8. Prim\n");
        printf("9. Kruskal\n");
        printf("10. Hierholzer\n");
        printf("11. Fleury\n");
        printf("12. Christofides\n");
        printf("> ");
        r = scanf("%d",&escolha);
    } while (escolha < 1 || escolha > 12);
    return escolha;
}

int main(int argc, char *argv[]){

    int escolha, n, r;
    
    Grafo G;    

    do {
	escolha = menuPrincipal();
	switch (escolha) {
	    case 1: /* Geracao de um grafo */
		switch(menuConstrucao()) {
		    case 1: /* Grafo vazio */
			printf("Entre com o valor de n: ");
			r = scanf("%d",&n);
			G = GRAFOcria(n);        
    			GRAFOimprime(G);
			break;
		    case 2: /* Grafo completo */
		        printf("Entre com o valor de n: ");
			r = scanf("%d",&n);
			G = GRAFOconstroiCompleto(n);        
    			GRAFOimprime(G);
			break;
		    case 3: /* Grafo Ciclo */
			printf("Entre com o valor de n: ");
			r = scanf("%d",&n);
			G = GRAFOconstroiCiclo(n);        
    			GRAFOimprime(G);
			break;
		}
		break;
	    case 2: /* Manipulacao de um grafo */
		switch(menuManipulacao()) {
		    case 1: /* Imprime */
			GRAFOimprime(G);
			break;
		    case 2: /* Lista graus */
			GRAFOgrau(G);
			break;
		    case 3: /* Destroi */
			GRAFOdestroi(G);
			break;
		}
		break;
	    case 3: /* Algoritmos */
		switch(menuAlgoritmos()) {
                case 1: /* BP */
                		BPrec(G);
                		break;
	    		case 2: /* BL */
               			BL(G);
                        break;
	    		case 3: /* Ponte */
                		G = GRAFOconstroiPontes(12);
                		GRAFOimprime(G);
                		Pontes(G);
                		break;
                case 4: /* Articulacao */
                		G = GRAFOconstroiPontes(12);
                		GRAFOimprime(G);
                		Articulacao(G);
                		break;
            case 5: /* Dijkstra */
                G = GRAFOleitura("grafoDijkstra.txt");
                GRAFOimprime(G);
                Dijkstra(G, 0);
                break;
            case 6: /* Bellman Ford */
                G = GRAFOleitura("grafoBellmanFord.txt");
                GRAFOimprime(G);
                BellmanFord(G, 0);
                break;
            case 7: /* Floyd Warshall */
                G = GRAFOleitura("grafoFloydWarshall.txt");
                GRAFOimprime(G);
                FloydWarshall(G);
                break;
            case 8: /* AGM Prim */
                G = GRAFOleitura("grafoArvore.txt");
                GRAFOimprime(G);
                Prim(G);
                break;
            case 9: /* AGM Kruskal */
                G = GRAFOleitura("grafoArvore.txt");
                GRAFOimprime(G);
                Kruskal(G);
                break;
            case 10: /* Euleriano Hierholzer */
                G = GRAFOleitura("grafoEuleriano.txt");
                GRAFOimprime(G);
                Hierholzer(G);
                break;
            case 11: /* Euleriano Fleury */
                G = GRAFOleitura("grafoEuleriano2.txt");
                GRAFOimprime(G);
                Fleury(G);
                break;
            case 12: /* Hamiltoniano PCV Christofides */
                G = GRAFOleitura("berlin52.txt");
                GRAFOimprime(G);
                Christofides(G);
                break;
        }
		break;
	    default:
	        break;
	}
    } while (escolha != 0);
}
