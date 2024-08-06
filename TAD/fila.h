#ifndef fila_h
#define fila_h

typedef struct fila *Fila;
int enqueue(Fila f, int x);
int dequeue(Fila f, int *x);
void imprimirFila(Fila f);
Fila inicializarFila();
Fila destruirFila(Fila f);

#endif
