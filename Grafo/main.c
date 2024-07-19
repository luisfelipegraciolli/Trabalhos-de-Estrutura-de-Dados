#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int destino;
    int custo;
    struct lista* prox;
} lista;

lista* removeNoLista(lista* l) {
    if (l == NULL) {
        return NULL;
    }
    lista* aux = l->prox;
    free(l);
    return aux;
}

lista* removeAresta(lista** g, int origem, int x) {
    g[origem] = removeNoLista(g[origem]);
}

lista* inserirLista(lista* l, int destino, int custo) {
    lista* no = (lista*)malloc(sizeof(lista));
    no->destino = destino;
    no->custo = custo;
    no->prox = l;
    return no;
}

void inicializar(lista** g, int n) {
    //? No slide estava i+1, why?
    for (int i = 0; i <= n; i++) {
        g[i] == NULL;
    }
}

void inserirAresta(lista** g, int origem, int destino, int custo) {
    g[origem] = inserirLista(g[origem], destino, custo);
}

void imprimirLista(lista* l, int n) {
    if (l != NULL) {
        printf("-(%d %d)", l->destino, l->custo);
        imprimirLista(l->prox, n);
    }
}
void imprimirGrafo(lista** g, int n) {
    for (int i = 1; i <= n; i++) {
        printf("\n\t%d", i);
        imprimirLista(g[i], n);
    }
    printf("\n");
}

int getGrauEntrada(lista** g, int v, int N) {
    int grauEntrada = 0;

    if (v > N || v <= 0) {
        return -1;
    }
    for (int i = 1; i <= N; i++) {
        for (lista* l = g[i]; l != NULL; l = l->prox) {
            if (l->destino == v) {
                grauEntrada++;
            }
        }
    }
    return grauEntrada;
}

int getGrauSaida(lista** g, int v, int N) {
    int grauSaida = 0;

    if (v > N || v <= 0) {

        return -1;
    }

    for (lista* p = g[v]; p != NULL; p = p->prox) {
        grauSaida++;
    }
    return grauSaida++;
}

void imprimirGrau(lista** g, int v, int N) {
    int grauEntrada, grauSaida;
    grauEntrada = getGrauEntrada(g, v, N);
    grauSaida = getGrauSaida(g, v, N);
    if (grauEntrada == -1 || grauSaida == -1) {
        printf("Vertice nao exite!");
    }
    else {
        printf("Grau de Entrada: %d\n", grauEntrada);
        printf("Grau de Saida: %d\n", grauSaida);
    }
}

int isGrafoCompleto(lista** g, int N) {
    /*
    ESTRATEGIA: VERIFICAR TODOS OS VERTICES COM SEUS
    GRAUS DE ENTRADA E SAIDA

    O GRAU DE ENTRADA DEVE SER IGUAL AO NUMERO DE SAIDA
    E AMBOS DEVEM SER IGUAIS A O NUMERO DE VERTICES

    */
    int grauE;
    int grauS;
    for (int i = 1; i <= N; i++) {
        grauE = getGrauEntrada(g, i, N);
        grauS = getGrauSaida(g, i, N);

        if (grauE != grauS) {
            return 0;
        }
    }
    if ((grauE < N-1) || (grauS < N-1)) {
        return 0;
    }
    else {

        return 1;
    }
}


void menu1(lista** grafo, int nElemGrafo) {

    int entrada = 0;
    int controle = 1;
    while (controle) {
        printf("1 - Inserir uma aresta no grafo\n");
        printf("2 - remover uma aresta do grafo\n");
        printf("3 - Imprimir Grafo\n");
        printf("4 - Imprimir os graus de entrada e saída de um vértice\n");
        printf("5 - Verificar se um grafo é completo\n");
        printf("6 - \n");
        printf("7 - \n");
        printf("8 - \n");
        printf("9 - sair\n");
        scanf(" %d", &entrada);

        system("clear");

        switch (entrada) {
        case 1:
            int inputOrigem1 = 0;
            int inputDestino1 = 0;
            int inputCusto1 = 0;

            printf("Digite o valor da origem?: ");
            scanf(" %d", &inputOrigem1);
            printf("Digite o valor do destino?: ");
            scanf(" %d", &inputDestino1);

            printf("Digite o custo da aresta?: ");
            scanf(" %d", &inputCusto1);
            inserirAresta(grafo, inputOrigem1, inputDestino1, inputCusto1);
            break;
        case 2:
            int inputOrigem2 = 0;
            int inputDestino2 = 0;

            printf("Digite o valor da origem?: ");
            scanf(" %d", &inputOrigem2);
            printf("Digite o valor do destino a ser deletado?: ");
            scanf(" %d", &inputDestino2);
            removeAresta(grafo, inputOrigem2, inputDestino2);
            break;
        case 3:
            imprimirGrafo(grafo, nElemGrafo);

            break;
        case 4:
            int inputOrigem4 = 0;
            printf("Digite o valor do vértice: ");
            scanf(" %d", &inputOrigem4);
            imprimirGrau(grafo, inputOrigem4, nElemGrafo);

            break;
        case 5:
            int isCompGrafo = isGrafoCompleto(grafo, nElemGrafo);

            if (isCompGrafo) {
                printf("Grafo Completo\n");
            }
            else {
                printf("Grafo nao e completo\n");
            }
            break;
        case 6:

            break;
        case 7:

            break;
        case 8:

            break;
        case 9:
            controle = 0;
            break;
        default:
            printf("Opcao nao existe");
            break;
        }
    }
}

int main() {
    int nElemGrafo = 4;
    lista** g;
    g = (lista**)malloc(sizeof(lista*) * (nElemGrafo + 1)); // * Anotação: n+1 pois a primeira posição é nula
    inicializar(g, nElemGrafo);
    menu1(g, nElemGrafo);

    return 0;
}
