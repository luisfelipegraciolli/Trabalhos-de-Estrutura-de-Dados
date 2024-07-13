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
void func2(int *v, int pos, int n, int *auxVet)
// Todas as combinações de {15,31,55,44}, de tamanho n, cuja soma dos elementos da combinação é par
{
    if (pos == n)
    {
        int soma = 0;
        for (int i = 0; i < n; i++)
        {
            soma += v[i];
        }

        if (soma % 2 == 0)
        {
            for (int i = 0; i < n; i++)
            {
                printf("%d ", v[i]);
            }
            printf("\n");
        }
    }
    else
    {
        for (int index = 0; index <= 3; index++)
        {
            v[pos] = auxVet[index];
            func2(v, pos + 1, n, auxVet);
        }
    }
}
void func3(int *moedas, int centavo, int n, int pos, int *auxVet, int startIndex)
{
    if (centavo == 0)
    {
        int c1, c5, c10, c25, c50;
        c1 = 0;
        c5 = 0;
        c10 = 0;
        c25 = 0;
        c50 = 0;

        for (int i = 0; i < pos; i++)
        {
            if (moedas[i] == 1)
            {
                c1++;
            }
            if (moedas[i] == 5)
            {
                c5++;
            }
            if (moedas[i] == 10)
            {
                c10++;
            }
            if (moedas[i] == 25)
            {
                c25++;
            }
            if (moedas[i] == 50)
            {
                c50++;
            }
        }

        printf("Voce precisa de %d de 1, %d de 5, %d de 10, %d de 25, %d de 50\nOU\n", c1, c5, c10, c25, c50);
        return;
    }
    if (centavo < 0 || pos == n)
    {
        return;
    }

    for (int index = startIndex; index < 5; index++)
    {
        moedas[pos] = auxVet[index];
        func3(moedas, centavo - auxVet[index], n, pos + 1, auxVet, index);
    }
}

int menu2(int option){
    system("clear");
    if(option == 0){

        printf("Qual o N desejado?: ");
        scanf(" %d", &option);
        return option;

    }
    if(option == 1){
        printf("Qual o valor em centavos desejado?: ");
        scanf(" %d", &option);
        return option;
    }
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
            char v0[3] = {'a', 'e', 'i'};
            int n = menu2(0);
            func1(v0, 0, n);
            printf("\n");

            break;
        case 2:
            int v1[4] = {15, 31, 55, 44};
            int vAux[4] = {15, 31, 55, 44};
            int n2 = menu2(0);
            func2(v1, 0, n2, vAux);
            printf("\n");
            break;
        case 3:
            int moedas[100];
            int vAux1[5] = {1, 5, 10, 25, 50};
            int centavo = menu2(1);
            func3(moedas, centavo, 100, 0, vAux1, 0);
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