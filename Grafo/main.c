#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int destino;
    int custo;
    struct lista* prox;
} lista;

lista* removeNoLista(lista* l, int destino) {
    lista* ant = NULL;
    lista* p = l;

    while (p != NULL && p->destino != destino) {
        ant = p;
        p = p->prox;
    }

    if (p == NULL) {
        return l;
    }

    if (ant == NULL) {
        l = p->prox;
    }
    else {
        ant->prox = p->prox;
    }
    free(p);
    return l;
}

lista* removeAresta(lista** g, int origem, int destino) {
    g[origem] = removeNoLista(g[origem], destino);
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
    if ((grauE < N - 1) || (grauS < N - 1)) {
        return 0;
    }
    else {

        return 1;
    }
}

int existe(int* vet, int valor, int n) {
    for (int i = 0; i < n; i++) {
        if (vet[i] == valor) {
            return 1;
        }
    }
    return 0;
}

void caminhos(lista** g, int destino, int* vet, int pos) {
    if (vet[pos - 1] == destino) {
        printf("\n");
        for (int i = 0; i < pos; i++) {
            printf("%d ", vet[i]);
        }
    }
    else {
        lista* l = g[vet[pos - 1]];
        while (l != NULL) {
            if (!existe(vet, l->destino, pos)) {
                vet[pos] = l->destino;
                caminhos(g, destino, vet, pos + 1);
            }
            l = l->prox;
        }
    }
}

void caminhoCurto(lista** g, int destino, int* vet, int pos, int* menorCaminho, int* menorTamanho) {
    if (vet[pos - 1] == destino) {
        if (pos <= *menorTamanho) {
            *menorTamanho = pos;
            for (int i = 0; i < pos; i++) {
                menorCaminho[i] = vet[i];
            }
        }
    }
    else {
        lista* l = g[vet[pos - 1]];
        while (l != NULL) {
            if (!existe(vet, l->destino, pos)) {
                vet[pos] = l->destino;
                caminhoCurto(g, destino, vet, pos + 1, menorCaminho, menorTamanho);
            }
            l = l->prox;
        }
    }
}

void caminhoCusto(lista** g, int destino, int* vet, int pos, int* caminho, int* tamanhoCaminho, int* menorCusto, int custo) {
    if (vet[pos - 1] == destino) {
        if (custo < *menorCusto) {
            *tamanhoCaminho = pos; // manter conta do tamanho do vetor para imprimir na main com o este valor
            *menorCusto = custo;
            //salva o caminho atual de menor custo
            for (int i = 0; i < pos; i++) {
                caminho[i] = vet[i];
            }
        }
    }
    else {
        lista* l = g[vet[pos - 1]];
        while (l != NULL) {
            if (!existe(vet, l->destino, pos)) {
                vet[pos] = l->destino;
                caminhoCusto(g, destino, vet, pos + 1, caminho, tamanhoCaminho, menorCusto, (custo + l->custo));
            }
            l = l->prox;
        }
    }
}

void liberaGrafo(lista** g, int N) {
    for (int i = 0; i < N; i++) {
        lista* l = g[i];
        while (l != NULL) {
            lista* temp = l;
            l = l->prox;
            free(temp);
        }
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
        printf("6 - Imprimir todos os caminhos entre uma origem e um destino\n");
        printf("7 - Imprimir o caminho mais curto (menor numero de arestas)\n");
        printf("8 - Imprimir o caminho de menor custo (menor soma dos custos das arestas)\n");
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
            int inputOrigem6 = 0;
            int inputDestino6 = 0;
            printf("Digite o valor da origem: ");
            scanf(" %d", &inputOrigem6);
            printf("Digite o valor do destino: ");
            scanf(" %d", &inputDestino6);
            int* vet = (int*)malloc(nElemGrafo * sizeof(int));
            vet[0] = inputOrigem6;
            caminhos(grafo, inputDestino6, vet, 1);
            printf("\n");

            free(vet);
            break;
        case 7:
            int inputOrigem7 = 0;
            int inputDestino7 = 0;

            printf("Digite o valor da origem: ");
            scanf(" %d", &inputOrigem7);
            printf("Digite o valor do destino: ");
            scanf(" %d", &inputDestino7);

            int* vetAux = (int*)malloc(nElemGrafo * sizeof(int));
            vetAux[0] = inputOrigem7;
            int menorTamanho = nElemGrafo;
            int* menorCaminho = (int*)malloc(nElemGrafo * sizeof(int));

            caminhoCurto(grafo, inputDestino7, vetAux, 1, menorCaminho, &menorTamanho);
            for (int i = 0; i < menorTamanho; i++) {
                printf("%d ", menorCaminho[i]);
            }

            printf("\n");
            break;
        case 8:
            int inputOrigem8 = 0;
            int inputDestino8 = 0;

            printf("Digite o valor da origem: ");
            scanf(" %d", &inputOrigem8);
            printf("Digite o valor do destino: ");
            scanf(" %d", &inputDestino8);
            
            int menorCusto = 1024;
            int* vetAux2 = (int*)malloc(nElemGrafo * sizeof(int));
            vetAux2[0] = inputOrigem8;
            //Tamanho percorrido iniciado com o maior numero possível que se pode percorrer 
            int tamanhoCaminhoPercorrido = nElemGrafo;
            int* caminhoPercorrido = (int*)malloc(nElemGrafo * sizeof(int));

            //Custo iniciado com um valor inicial grande para comparação começar
            caminhoCusto(grafo, inputDestino8, vetAux2, 1, caminhoPercorrido, &tamanhoCaminhoPercorrido, &menorCusto, 0);
            for (int i = 0; i < tamanhoCaminhoPercorrido; i++) {
                printf("%d ", caminhoPercorrido[i]);
            }
            printf(" custo do caminho: %d", menorCusto);
            printf("\n");
            break;
        case 9:
            controle = 0;
            liberaGrafo(grafo, nElemGrafo);
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
