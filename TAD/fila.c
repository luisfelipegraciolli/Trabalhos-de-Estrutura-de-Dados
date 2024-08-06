#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

#define N 1024

struct fila{
    int vet[N];
    int n;
    int primeiro;
};

Fila inicializarFila(){
    Fila f = (Fila)malloc(sizeof(struct fila));
    f->primeiro = 0;
    f->n = 0;
    return f;
}

Fila destruirFila(Fila f){
    free(f);
    return NULL;
}

int enqueue(Fila f, int x){
    //verifica se n de elementos na fila é maior que n máximo do vetor
    if(f->n >= N){
        return 0;
    }       
    else{
        int index = (f->primeiro + f->n)%N;
        f->vet[index] = x;
        f->n++;
        return 1;
    }
}

int dequeue(Fila f, int* x){
    if(f->n <= 0){
        return 0;
    }
    else{
        int item = f->vet[f->primeiro];
        f->primeiro = (f->primeiro+1)%N;
        *x = item;
        f->n--;
        return 1;
    }
}

void imprimirFila(Fila f){
    printf("Elementos: \n");
    for (int i = 0; i < f->n; i++)
    {
        int index = (f->primeiro + i) % N;
        printf("%d ", f->vet[index]);
    }
    printf("\n");
}