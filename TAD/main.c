#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

void menu1(Fila myFila) {

    int entrada = 0;
    int controle = 1;
    while (controle) {
        printf("1 - Inserir um elemento na fila\n");
        printf("2 - Remover um elemento da fila (imprime o elemento removido)\n");
        printf("3 - Imprimir fila\n");
        printf("4 - Sair\n");
        scanf(" %d", &entrada);

        system("clear");

        switch (entrada) {
        case 1:
            int input1 = 0;
            printf("Digite o valor a ser inserido: ");
            scanf(" %d", &input1);
            enqueue(myFila, input1);
            printf("\n");
            break;
        case 2:
            int valorRemovido = 0;
            dequeue(myFila, &valorRemovido);
            printf("Valor removido: %d\n", valorRemovido);
            break;
        case 3:
            imprimirFila(myFila);
            break;
        case 4:
            controle = 0;
            destruirFila(myFila);
            break;
        default:
            printf("Opcao nao existe");
            break;
        }
    }
}

int main() {
    Fila myFila = inicializarFila();
    menu1(myFila);
}