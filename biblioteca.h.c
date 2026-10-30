#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <string.h>

#define MAX 50
#define CORREDORES 3
#define PRATELEIRAS 4

struct Livro {
int id;
char titulo[50];
char autor[50];
int ano;
int disponivel;   
int ativo;       
int corredor;     
int prateleira;  
};

struct Leitor {
int id;
char nome[50];
char telefone[20];
int idade;
int ativo;        
};

struct Emprestimo {
int id;
int idLivro;
int idLeitor;
int diasPrazo;
int devolvido;    
int ativo;        
};

extern struct Livro acervo[MAX];
extern int totalLivros;

extern struct Leitor leitores[MAX];
extern int totalLeitores;

extern struct Emprestimo emprestimos[MAX];
extern int totalEmprestimos;

extern int matrizEstante[CORREDORES][PRATELEIRAS];

void exibirCabecalho();
void limparTeclado();
int lerNumero();
void lerTexto(char destino[], int tamanho);
int buscarLivro(int id);
int buscarLeitor(int id);
int buscarEmprestimo(int id);
void inicializarMatriz();

void cadastrarLivro();
void buscarEListarLivros();
void editarLivro();
void removerLivro();
void moduloLivros();

void cadastrarLeitor();
void buscarEListarLeitores();
void editarLeitor();
void removerLeitor();
void moduloLeitores();

void registrarEmprestimo();
void listarEmprestimos();
void registrarDevolucao();
void cancelarEmprestimo();
void moduloEmprestimos();

void exibirMatrizEstante();
void ordenarLivrosPorTitulo();
void ordenarLivrosPorID();
void relatorioEstatistico();
void moduloRelatoriosMatriz();

#endif