#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Professor {
    int matricula;
    char nome[20];
    double salario;
} Professor; // 1

typedef struct Aluno {
    int matricula;
    char nome[20];
    char curso[20];
    int anoIngresso;
} Aluno; // 2

typedef struct lista {
    int tipo;
    void* item;
    struct lista* prox;
} lista;

lista* inserir(lista* l, void* info, int tipo) {
    lista* no = (lista*)malloc(sizeof(lista));
    no->tipo = tipo;
    no->item = info;
    no->prox = NULL;

    if (l == NULL) {
        l = no;
    }
    else {
        lista* temp = l;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = no;
    }
    return l;
}


// Como matricula se assume ser uma coisa única
// Não seria necessário deletar varias ocorrências da mesma
// em um dos tipos (aluno ou professor)
// essa função deleta todo aluno ou professor com a matricula dada
// considerando que não há repetição de matricula em professores ou alunos
lista* remover(lista* l, int matricula, int tipo) {
    lista* temp = l;
    lista* anterior = NULL;

    while (temp != NULL && !((tipo == 2 && ((Aluno*)temp->item)->matricula == matricula) ||
                             (tipo == 1 && (((Professor*)temp->item)->matricula == matricula)))) {
        anterior = temp;
        temp = temp->prox;
    }

    if (temp == NULL) {
        printf("Elemento nao encontrado!\n");
        return l;
    }
    else {
        if (anterior == NULL) {
            l = temp->prox;
        }
        else {
            anterior->prox = temp->prox;
        }
        free(temp->item);
        free(temp);
        return l;
    }

}

void buscar(lista* l, int matricula, int tipo) {
    lista* temp = l;
    while (temp != NULL && !((tipo == 2 && ((Aluno*)temp->item)->matricula == matricula) ||
                             (tipo == 1 && (((Professor*)temp->item)->matricula == matricula)))) {

        temp = temp->prox;
    }
   if (temp == NULL) {
        printf("Elemento nao encontrado!\n");
        return;
    }
    if (temp->tipo == 1 && tipo == 1) {
        Professor* prof = (Professor*)temp->item;
        printf("Professor %s, Matricula: %d, Salario: %.2f\n", prof->nome, prof->matricula, prof->salario);
        
    }
    else if(temp->tipo == 2 && tipo == 2) {
        Aluno* alu = (Aluno*)temp->item;
        printf("Aluno %s, Matricula: %d, curso: %s,Ano de Ingresso: %d\n", alu->nome, alu->matricula, alu->curso, alu->anoIngresso);
    }
    else{
        printf("Elemento nao encontrado!\n");
        return;
    }
}

int nAluCurso(lista* l, char* curso) {
    int cont = 0;
    lista* temp = l;

    while (temp != NULL) {
        if (temp->tipo == 2) {
            Aluno* alu = (Aluno*)temp->item;
            if (strcmp(alu->curso, curso) == 0) {

                cont++;
            }
        }

        temp = temp->prox;
    }
    return cont;
}

void imprimirProfMaiorSal(lista* l) {
    double maiorSalario = 0.0;
    lista* temp = l;

    while (temp != NULL) {
        if (temp->tipo == 1) {
            Professor* professor = (Professor*)temp->item;
            if (professor->salario > maiorSalario) {
                maiorSalario = professor->salario;
            }
        }
        temp = temp->prox;
    }

    temp = l;
    printf("Professores com o maior salário (%.2f):\n", maiorSalario);
    while (temp != NULL) {
        if (temp->tipo == 1) {
            Professor* professor = (Professor*)temp->item;
            if (professor->salario == maiorSalario) {
                printf("Nome: %s, Salário: %.2f\n", professor->nome, professor->salario);
            }
        }
        temp = temp->prox;
    }
}

Aluno* criarAluno(int matricula, int anoIngresso, const char* nome, const char* curso) {
    Aluno* a = (Aluno*)malloc(sizeof(Aluno));
    a->matricula = matricula;
    a->anoIngresso = anoIngresso;
    strcpy(a->nome, nome);
    strcpy(a->curso, curso);
    return a;
}
Professor* criarProfessor(int matricula, const char* nome, float salario) {
    Professor* p = (Professor*)malloc(sizeof(Professor));
    p->matricula = matricula;
    strcpy(p->nome, nome);
    p->salario = salario;
    return p;
}

void destruirLista(lista* l) {
    if (l == NULL) {
        return;
    }
    destruirLista(l->prox);
    free(l->item);
    free(l);
}

void menu1(lista* l) {

    int entrada = 0;
    int controle = 1;
    while (controle) {
        printf("1 - Inserir uma pessoa na lista\n");
        printf("2 - Remover uma pessoa pela matricula\n");
        printf("3 - Buscar uma pessoa pelo sua matricula-caso encontre, imprimir seus dados\n");
        printf("4 - Contar o numero de alunos em um determinado curso\n");
        printf("5 - Imprimir os professores de maior salario\n");
        printf("6 - Sair\n");

        scanf(" %d", &entrada);

        system("clear");

        switch (entrada) {
        case 1:
            int input1 = 0;
            printf("Selecione Professor (1) Aluno (2): ");
            scanf(" %d", &input1);
            if (input1 == 1) {
                int mat;
                float sal;
                char nome[20];
                printf("Digite nome matricula salario: ");
                scanf(" %s %d %f", &nome, &mat, &sal);
                Professor* a = criarProfessor(mat, nome, sal);
                l = inserir(l, a, 1);
            }
            else {
                int mat, ano;
                char nome[20];
                char curso[20];
                printf("Digite nome matricula curso ano de ingresso: ");
                scanf(" %s %d %s %d", &nome, &mat, &curso, &ano);
                Aluno* alu = criarAluno(mat, ano, nome, curso);
                l = inserir(l, alu, 2);
            }
            printf("\n");
            break;
        case 2:
            int mat2;
            int tipo2;

            printf("Digite a matricula: ");
            scanf(" %d", &mat2);
            // Caso aluno e prof tenham mesma matricula
            printf("Selecione Professor (1) Aluno(2): ");
            scanf(" %d", &tipo2);
            if (tipo2 == 1) {
                l = remover(l, mat2, 1);
            }
            else {

                l = remover(l, mat2, 2);
            }
            break;
        case 3:
            int mat3;
            int tipo3;
            printf("Digite a matricula: ");
            scanf(" %d", &mat3);
            
            printf("Selecione Professor (1) Aluno(2): ");
            scanf(" %d", &tipo3);
            if (tipo3 == 1) {
                buscar(l, mat3, 1);
            }
            else {
                buscar(l, mat3, 2);
            }
            break;
        case 4:
            char curso[20];
            printf("Digite o curso: ");
            scanf(" %[^\n]s", &curso);
            printf("%d Aluno(s) no Curso: %s\n", nAluCurso(l, curso), curso);
            break;
        case 5:
            imprimirProfMaiorSal(l);
            printf("\n");
            break;
        case 6:
            controle = 0;
            destruirLista(l);
            break;

        default:
            printf("Opcao nao existe");
            break;
        }
    }
}


int main(int argc, char const* argv[]) {
    lista* l = NULL;
    menu1(l);
    return 0;
}
