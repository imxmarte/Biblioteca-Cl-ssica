#include <stdio.h>
#include <string.h>

#define MAX_LIVROS 5

typedef struct {
    int id;
    char titulo[50];
    char autor[50];
    int ano;
} Livro;

int cadastrarLivro(Livro acervo[], int *total) {
    
    if (*total >= MAX_LIVROS) {
        printf("\nNao e possivel cadastrar novos livros, limite atingido!\n", *total, MAX_LIVROS);
        return 0;
    }

    printf("\n--- Cadastro de Novo Livro (Posicao %d/%d) ---\n", *total + 1, MAX_LIVROS);
    
    
    printf("Digite o ID do livro: ");
    scanf("%d", &acervo[*total].id);
    getchar();

    
    printf("Digite o titulo do livro: ");
    fgets(acervo[*total].titulo, sizeof(acervo[*total].titulo), stdin);
    
    acervo[*total].titulo[strcspn(acervo[*total].titulo, "\n")] = '\0';

    printf("Digite o autor do livro: ");
    fgets(acervo[*total].autor, sizeof(acervo[*total].autor), stdin);
    acervo[*total].autor[strcspn(acervo[*total].autor, "\n")] = '\0';

    printf("Digite o ano de publicacao: ");
    scanf("%d", &acervo[*total].ano);
    getchar();

    (*total)++;

    printf("\nLivro registado com sucesso!\n");
    return 1;
}

int main() {
    Livro acervo[MAX_LIVROS];
    int total_livros = 0;
    int opcao;

    do {
        printf("\n------------ SISTEMA DE BIBLIOTECA ------------\n");
        printf("1. Cadastrar Livro\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarLivro(acervo, &total_livros);
                break;
            case 0:
                printf("\nEncerrando...\n");
                break;
            default:
                printf("\nERRO! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}