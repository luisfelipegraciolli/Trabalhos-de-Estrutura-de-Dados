// Luis Felipe da Silva Graciolli
// Matricula: 123060038

#include <stdio.h>
#include <stdlib.h>

void func1(char *v, int pos, int n)
{
    // ascii valores :)

    int a = 'a';
    int e = 'e';
    int i = 'i';

    if (pos == n)
    {
        int contA = 0;
        int contE = 0;
        int contI = 0;

        for (int i = 0; i < n; i++)
        {
            if (v[i] == 'a')
            {
                contA++;
            }
            if (v[i] == 'e')
            {
                contE++;
            }
            if (v[i] == 'i')
            {
                contI++;
            }
        }
        int lim = contE + contI;
        if (contA > lim)
        {
            for (int i = 0; i < n; i++)
            {
                printf("%c ", v[i]);
            }
            printf("\n");
        }
    }
    else
    {
        for (int index = a; index <= i; index = index + 4)
        {
            v[pos] = index;
            func1(v, pos + 1, n);
        }
    }
}
void func2()
{
    printf("entre1 2");
}
void func3()
{
    printf("entre1 3");
}

void menu1()
{

    int entrada = 0;
    int controle = 1;
    while (controle)
    {
        printf("1 - Todas as combinações de {a,e,i} de tamanho n, que o número de a's é maior que a soma\nde totais de e's e de i's\n");
        printf("2 - Todas as combinações de {15,31,55,44}, de tamanho n, cuja soma dos elementos da\ncombinação é par\n");
        printf("3 - Dado um valor em centavos, imprimir todas as maneiras de representá-lo utilizando\nmoedas de 1, 5, 10, 25 e 50 centavos\n");
        printf("4 - sair\n");
        scanf(" %d", &entrada);

        system("clear");

        switch (entrada)
        {
        case 1:
            char v[3] = {'a', 'e', 'i'};
            func1(v, 0, 5);
            printf("\n");
            
            break;
        case 2:
            func2();
            printf("\n");
            break;
        case 3:
            func3();
            printf("\n");
            break;
        case 4:
            controle = 0;
            break;
        default:
            printf("Opcao nao existe");
            break;
        }
    }
}

int main()
{
    menu1();
}