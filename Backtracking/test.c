#include <stdio.h>

// Função recursiva para encontrar todas as combinações de moedas
void func3(int *moedas, int centavo, int n, int pos, int *auxVet)
{
    if (centavo == 0)
    {
        int c1 = 0, c5 = 0, c10 = 0, c25 = 0, c50 = 0;

        for (int i = 0; i < pos; i++)
        {
            if (moedas[i] == 1) c1++;
            else if (moedas[i] == 5) c5++;
            else if (moedas[i] == 10) c10++;
            else if (moedas[i] == 25) c25++;
            else if (moedas[i] == 50) c50++;
        }

        printf("Voce precisa de %d de 1, %d de 5, %d de 10, %d de 25, %d de 50\n", c1, c5, c10, c25, c50);
        return;
    }

    if (centavo < 0 || pos == n)
        return;

    for (int index = 0; index < 5; index++)
    {
        moedas[pos] = auxVet[index];
        func3(moedas, centavo - auxVet[index], n, pos + 1, auxVet);
    }
}

int main()
{
    int centavo;
    printf("Digite o valor em centavos: ");
    scanf("%d", &centavo);

    int moedas[100];  // Array para armazenar as combinações
    int auxVet[5] = {1, 5, 10, 25, 50};  // As denominações das moedas

    // Chama a função recursiva
    func3(moedas, centavo, 100, 0, auxVet);

    return 0;
}