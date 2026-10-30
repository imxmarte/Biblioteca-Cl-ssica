#include "biblioteca.h"

int main() {
int opcao;
inicializarMatriz();

do {
    exibirCabecalho();
    printf("1. Modulo de Livros / Acervo\n");
    printf("2. Modulo de Leitores\n");
    printf("3. Modulo de Emprestimos e Devolucoes\n");
    printf("4. Modulo de Matriz, Bubble Sort e Relatorios\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
    opcao = lerNumero();

    switch (opcao) {
        case 1: moduloLivros(); break;
        case 2: moduloLeitores(); break;
        case 3: moduloEmprestimos(); break;
        case 4: moduloRelatoriosMatriz(); break;
        case 0: printf("\nEncerrando o sistema...\n"); break;
        default: printf("\nERRO! Opcao invalida. Tente novamente.\n");
    }
} while (opcao != 0);

return 0;
}
