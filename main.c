#include <stdio.h>
#include <string.h>

#define MAX 50
#define CORREDORES 3
#define PRATELEIRAS 4



// Struct do Livro
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
struct Livro acervo[MAX];
int totalLivros = 0;


struct Leitor {
int id;
char nome[50];
char telefone[20];
int idade;
int ativo;        
};
struct Leitor leitores[MAX];
int totalLeitores = 0;

// Struct do Emprestimo
struct Emprestimo {
int id;
int idLivro;
int idLeitor;
int diasPrazo;
int devolvido;    
int ativo;        
};
struct Emprestimo emprestimos[MAX];
int totalEmprestimos = 0;


int matrizEstante[CORREDORES][PRATELEIRAS];


void exibirCabecalho() {
printf("\n======================================================\n");
printf("   BIBLIOTECA CLASSICA - FICHARIO RETRO (1985)        \n");
printf("======================================================\n");
}

void limparTeclado() {
int c;
c = getchar();
while (c != '\n' && c != EOF) {
c = getchar();
}
}

int lerNumero() {
int n;
if (scanf("%d", &n) != 1) {
n = -1;
}
limparTeclado();
return n;
}

void lerTexto(char destino[], int tamanho) {
fgets(destino, tamanho, stdin);
destino[strcspn(destino, "\n")] = '\0';
}

int buscarLivro(int id) {
int i;
for (i = 0; i < totalLivros; i++) {
if (acervo[i].id == id && acervo[i].ativo == 1) {
return i;
}
}
return -1;
}

int buscarLeitor(int id) {
int i;
for (i = 0; i < totalLeitores; i++) {
if (leitores[i].id == id && leitores[i].ativo == 1) {
return i;
}
}
return -1;
}

int buscarEmprestimo(int id) {
int i;
for (i = 0; i < totalEmprestimos; i++) {
if (emprestimos[i].id == id && emprestimos[i].ativo == 1) {
return i;
}
}
return -1;
}

void inicializarMatriz() {
int i, j;
for (i = 0; i < CORREDORES; i++) {
for (j = 0; j < PRATELEIRAS; j++) {
matrizEstante[i][j] = 0;
}
}
}


void cadastrarLivro() {
int id, corredor, prateleira;

if (totalLivros >= MAX) {
    printf("\nNao e possivel cadastrar novos livros, limite de %d atingido!\n", MAX);
    return;
}

printf("\n--- Cadastro de Novo Livro (Posicao %d/%d) ---\n", totalLivros + 1, MAX);

printf("Digite o ID do livro: ");
id = lerNumero();
if (id <= 0) {
    printf("\nERRO! ID invalido (use um numero maior que zero).\n");
    return;
}
if (buscarLivro(id) != -1) {
    printf("\nERRO! Ja existe um livro com o ID %d.\n", id);
    return;
}

printf("Escolha o Corredor (0 a %d): ", CORREDORES - 1);
corredor = lerNumero();
printf("Escolha a Prateleira (0 a %d): ", PRATELEIRAS - 1);
prateleira = lerNumero();

if (corredor < 0 || corredor >= CORREDORES || prateleira < 0 || prateleira >= PRATELEIRAS) {
    printf("\nERRO! Localizacao fora dos limites da estante.\n");
    return;
}
if (matrizEstante[corredor][prateleira] != 0) {
    printf("\nERRO! A posicao [Corredor %d, Prateleira %d] ja esta ocupada pelo livro ID %d.\n",
           corredor, prateleira, matrizEstante[corredor][prateleira]);
    return;
}

acervo[totalLivros].id = id;

printf("Digite o titulo do livro: ");
lerTexto(acervo[totalLivros].titulo, 50);

printf("Digite o autor do livro: ");
lerTexto(acervo[totalLivros].autor, 50);

printf("Digite o ano de publicacao: ");
acervo[totalLivros].ano = lerNumero();
if (acervo[totalLivros].ano <= 0 || acervo[totalLivros].ano > 2026) {
    printf("\nERRO! Ano invalido. Cadastro cancelado.\n");
    return;
}

acervo[totalLivros].disponivel = 1;
acervo[totalLivros].ativo = 1;
acervo[totalLivros].corredor = corredor;
acervo[totalLivros].prateleira = prateleira;

matrizEstante[corredor][prateleira] = id;
totalLivros++;

printf("\nLivro registrado com sucesso na estante [Corredor %d, Prateleira %d]!\n", corredor, prateleira);


}

void buscarEListarLivros() {
int id, pos;
if (totalLivros == 0) {
printf("\nNenhum livro cadastrado no acervo.\n");
return;
}

printf("\n--- Listagem e Busca de Livros ---\n");
printf("Digite o ID do livro para buscar (ou 0 para listar todos): ");
id = lerNumero();

if (id == 0) {
    printf("\n%-5s | %-25s | %-20s | %-5s | %-12s | %-10s\n", "ID", "TITULO", "AUTOR", "ANO", "STATUS", "LOCALIZACAO");
    printf("-------------------------------------------------------------------------------------\n");
    for (int i = 0; i < totalLivros; i++) {
        if (acervo[i].ativo == 1) {
            printf("%-5d | %-25s | %-20s | %-5d | %-12s | [Corr: %d, Prat: %d]\n",
                   acervo[i].id, acervo[i].titulo, acervo[i].autor, acervo[i].ano,
                   acervo[i].disponivel ? "Disponivel" : "Emprestado",
                   acervo[i].corredor, acervo[i].prateleira);
        }
    }
} else {
    pos = buscarLivro(id);
    if (pos == -1) {
        printf("\nERRO! Livro com ID %d nao encontrado.\n", id);
    } else {
        printf("\nID: %d\nTitulo: %s\nAutor: %s\nAno: %d\nStatus: %s\nLocalizacao: Corredor %d, Prateleira %d\n",
               acervo[pos].id, acervo[pos].titulo, acervo[pos].autor, acervo[pos].ano,
               acervo[pos].disponivel ? "Disponivel" : "Emprestado",
               acervo[pos].corredor, acervo[pos].prateleira);
    }
}


}

void editarLivro() {
int id, pos;
printf("\n--- Editar Dados de um Livro ---\n");
printf("Digite o ID do livro que deseja editar: ");
id = lerNumero();

pos = buscarLivro(id);
if (pos == -1) {
    printf("\nERRO! Livro nao encontrado.\n");
    return;
}

printf("Livro selecionado: %s\n", acervo[pos].titulo);
printf("Digite o novo titulo (ou pressione ENTER para manter): ");
char novoTitulo[50];
lerTexto(novoTitulo, 50);
if (strlen(novoTitulo) > 0) {
    strcpy(acervo[pos].titulo, novoTitulo);
}

printf("Digite o novo autor (ou pressione ENTER para manter): ");
char novoAutor[50];
lerTexto(novoAutor, 50);
if (strlen(novoAutor) > 0) {
    strcpy(acervo[pos].autor, novoAutor);
}

printf("\nDados do livro atualizados com sucesso!\n");


}

void removerLivro() {
int id, pos;
printf("\n--- Remover Livro do Acervo ---\n");
printf("Digite o ID do livro a ser removido: ");
id = lerNumero();

pos = buscarLivro(id);
if (pos == -1) {
    printf("\nERRO! Livro nao encontrado.\n");
    return;
}

if (acervo[pos].disponivel == 0) {
    printf("\nERRO! Nao e possivel remover um livro que esta atualmente emprestado.\n");
    return;
}

acervo[pos].ativo = 0;
matrizEstante[acervo[pos].corredor][acervo[pos].prateleira] = 0;

printf("\nLivro \"%s\" removido do acervo e posicao na estante liberada com sucesso!\n", acervo[pos].titulo);


}

void moduloLivros() {
int opcao;
do {
printf("\n--- [MODULO 1: ACERVO DE LIVROS] ---\n");
printf("1. Cadastrar Novo Livro\n");
printf("2. Listar / Buscar Livros\n");
printf("3. Editar Dados de um Livro\n");
printf("4. Remover Livro do Acervo\n");
printf("0. Voltar ao Menu Principal\n");
printf("Escolha uma acao: ");
opcao = lerNumero();

    switch (opcao) {
        case 1: cadastrarLivro(); break;
        case 2: buscarEListarLivros(); break;
        case 3: editarLivro(); break;
        case 4: removerLivro(); break;
        case 0: printf("\nRetornando ao menu principal...\n"); break;
        default: printf("\nERRO! Opcao invalida no Modulo de Livros.\n");
    }
} while (opcao != 0);


}

// ----------------------------------------------------------------------------
// MODULO 2: LEITORES (Integrantes A, B, C)
// ----------------------------------------------------------------------------

void cadastrarLeitor() {
int id;
if (totalLeitores >= MAX) {
printf("\nNao e possivel cadastrar novos leitores, limite de %d atingido!\n", MAX);
return;
}

printf("\n--- Cadastro de Novo Leitor (Posicao %d/%d) ---\n", totalLeitores + 1, MAX);
printf("Digite o numero da carteirinha: ");
id = lerNumero();
if (id <= 0) {
    printf("\nERRO! Numero invalido.\n");
    return;
}
if (buscarLeitor(id) != -1) {
    printf("\nERRO! Ja existe um leitor com a carteirinha %d.\n", id);
    return;
}

leitores[totalLeitores].id = id;
printf("Digite o nome completo: ");
lerTexto(leitores[totalLeitores].nome, 50);

printf("Digite o telefone: ");
lerTexto(leitores[totalLeitores].telefone, 20);

printf("Digite a idade: ");
leitores[totalLeitores].idade = lerNumero();
if (leitores[totalLeitores].idade < 5 || leitores[totalLeitores].idade > 120) {
    printf("\nERRO! Idade invalida.\n");
    return;
}

leitores[totalLeitores].ativo = 1;
totalLeitores++;
printf("\nLeitor registrado com sucesso!\n");


}

void buscarEListarLeitores() {
int id, pos;
if (totalLeitores == 0) {
printf("\nNenhum leitor cadastrado.\n");
return;
}

printf("\n--- Listagem e Busca de Leitores ---\n");
printf("Digite a carteirinha para buscar (ou 0 para listar todos): ");
id = lerNumero();

if (id == 0) {
    printf("\n%-12s | %-30s | %-15s | %-5s\n", "CARTEIRINHA", "NOME", "TELEFONE", "IDADE");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < totalLeitores; i++) {
        if (leitores[i].ativo == 1) {
            printf("%-12d | %-30s | %-15s | %-5d\n",
                   leitores[i].id, leitores[i].nome, leitores[i].telefone, leitores[i].idade);
        }
    }
} else {
    pos = buscarLeitor(id);
    if (pos == -1) {
        printf("\nERRO! Leitor com carteirinha %d nao encontrado.\n", id);
    } else {
        printf("\nCarteirinha: %d\nNome: %s\nTelefone: %s\nIdade: %d\n",
               leitores[pos].id, leitores[pos].nome, leitores[pos].telefone, leitores[pos].idade);
    }
}


}

void editarLeitor() {
int id, pos;
printf("\n--- Editar Dados de um Leitor ---\n");
printf("Digite a carteirinha do leitor: ");
id = lerNumero();

pos = buscarLeitor(id);
if (pos == -1) {
    printf("\nERRO! Leitor nao encontrado.\n");
    return;
}

printf("Leitor selecionado: %s\n", leitores[pos].nome);
printf("Digite o novo telefone (ou ENTER para manter): ");
char novoTel[20];
lerTexto(novoTel, 20);
if (strlen(novoTel) > 0) {
    strcpy(leitores[pos].telefone, novoTel);
}

printf("\nDados atualizados com sucesso!\n");


}

void removerLeitor() {
int id, pos;
printf("\n--- Cancelar Carteirinha (Remover Leitor) ---\n");
printf("Digite a carteirinha a ser cancelada: ");
id = lerNumero();

pos = buscarLeitor(id);
if (pos == -1) {
    printf("\nERRO! Leitor nao encontrado.\n");
    return;
}

for (int i = 0; i < totalEmprestimos; i++) {
    if (emprestimos[i].idLeitor == id && emprestimos[i].devolvido == 0 && emprestimos[i].ativo == 1) {
        printf("\nERRO! Leitor possui pendencias de emprestimo ativas.\n");
        return;
    }
}

leitores[pos].ativo = 0;
printf("\nCarteirinha %d cancelada com sucesso!\n", id);


}

void moduloLeitores() {
int opcao;
do {
printf("1. Cadastrar Novo Leitor\n");
printf("2. Listar / Buscar Leitores\n");
printf("3. Editar Dados de um Leitor\n");
printf("4. Cancelar Carteirinha (Remover)\n");
printf("0. Voltar ao Menu Principal\n");
printf("Escolha uma acao: ");
opcao = lerNumero();

    switch (opcao) {
        case 1: cadastrarLeitor(); break;
        case 2: buscarEListarLeitores(); break;
        case 3: editarLeitor(); break;
        case 4: removerLeitor(); break;
        case 0: printf("\nRetornando ao menu principal...\n"); break;
        default: printf("\nERRO! Opcao invalida no Modulo de Leitores.\n");
    }
} while (opcao != 0);


}


void registrarEmprestimo() {
int idLeitor, idLivro, posLeitor, posLivro;

if (totalEmprestimos >= MAX) {
    printf("\nNao e possivel registrar novos emprestimos, limite de %d atingido!\n", MAX);
    return;
}

printf("\n--- Registrar Emprestimo ---\n");

printf("Digite a carteirinha do leitor: ");
idLeitor = lerNumero();
posLeitor = buscarLeitor(idLeitor);
if (posLeitor == -1) {
    printf("\nERRO! Leitor nao cadastrado.\n");
    return;
}

printf("Digite o ID do livro: ");
idLivro = lerNumero();
posLivro = buscarLivro(idLivro);
if (posLivro == -1) {
    printf("\nERRO! Livro nao encontrado no acervo.\n");
    return;
}
if (acervo[posLivro].disponivel == 0) {
    printf("\nERRO! O livro \"%s\" ja esta emprestado.\n", acervo[posLivro].titulo);
    return;
}

emprestimos[totalEmprestimos].id = totalEmprestimos + 1;
emprestimos[totalEmprestimos].idLivro = idLivro;
emprestimos[totalEmprestimos].idLeitor = idLeitor;
emprestimos[totalEmprestimos].diasPrazo = 7;
emprestimos[totalEmprestimos].devolvido = 0;
emprestimos[totalEmprestimos].ativo = 1;
totalEmprestimos++;

acervo[posLivro].disponivel = 0;

printf("\nEmprestimo registrado: \"%s\" para %s (prazo: 7 dias).\n",
       acervo[posLivro].titulo, leitores[posLeitor].nome);


}

void listarEmprestimos() {
if (totalEmprestimos == 0) {
printf("\nNenhum emprestimo registrado.\n");
return;
}

printf("\n%-5s | %-25s | %-25s | %-8s | %-10s\n", "ID", "LIVRO", "LEITOR", "PRAZO", "STATUS");
printf("--------------------------------------------------------------------------------\n");
for (int i = 0; i < totalEmprestimos; i++) {
    if (emprestimos[i].ativo == 1) {
        int posL = buscarLivro(emprestimos[i].idLivro);
        int posR = buscarLeitor(emprestimos[i].idLeitor);
        printf("%-5d | %-25s | %-25s | %d dias  | %-10s\n",
               emprestimos[i].id,
               posL != -1 ? acervo[posL].titulo : "Desconhecido",
               posR != -1 ? leitores[posR].nome : "Desconhecido",
               emprestimos[i].diasPrazo,
               emprestimos[i].devolvido ? "Devolvido" : "Em Aberto");
    }
}


}

void registrarDevolucao() {
int idEmp, posEmp;
printf("\n--- Registrar Devolucao ---\n");
printf("Digite o ID do emprestimo: ");
idEmp = lerNumero();

posEmp = buscarEmprestimo(idEmp);
if (posEmp == -1) {
    printf("\nERRO! Emprestimo nao encontrado.\n");
    return;
}

if (emprestimos[posEmp].devolvido == 1) {
    printf("\nEste emprestimo ja consta como devolvido.\n");
    return;
}

emprestimos[posEmp].devolvido = 1;
int posLivro = buscarLivro(emprestimos[posEmp].idLivro);
if (posLivro != -1) {
    acervo[posLivro].disponivel = 1;
}

printf("\nDevolucao concluida com sucesso! O livro esta novamente disponivel na estante.\n");


}

void cancelarEmprestimo() {
int idEmp, posEmp;
printf("\n--- Cancelar Registro de Emprestimo ---\n");
printf("Digite o ID do emprestimo a cancelar: ");
idEmp = lerNumero();

posEmp = buscarEmprestimo(idEmp);
if (posEmp == -1) {
    printf("\nERRO! Registro de emprestimo nao encontrado.\n");
    return;
}

emprestimos[posEmp].ativo = 0;
if (emprestimos[posEmp].devolvido == 0) {
    int posLivro = buscarLivro(emprestimos[posEmp].idLivro);
    if (posLivro != -1) {
        acervo[posLivro].disponivel = 1;
    }
}

printf("\nRegistro de emprestimo cancelado com sucesso.\n");


}

void moduloEmprestimos() {
int opcao;
do {
printf("1. Registrar Emprestimo\n");
printf("2. Listar Emprestimos\n");
printf("3. Registrar Devolucao\n");
printf("4. Cancelar Registro de Emprestimo\n");
printf("0. Voltar ao Menu Principal\n");
printf("Escolha uma acao: ");
opcao = lerNumero();

    switch (opcao) {
        case 1: registrarEmprestimo(); break;
        case 2: listarEmprestimos(); break;
        case 3: registrarDevolucao(); break;
        case 4: cancelarEmprestimo(); break;
        case 0: printf("\nRetornando ao menu principal...\n"); break;
        default: printf("\nERRO! Opcao invalida no Modulo de Emprestimos.\n");
    }
} while (opcao != 0);


}

void exibirMatrizEstante() {
printf("            ");
for (int j = 0; j < PRATELEIRAS; j++) {
printf("Prateleira %d   ", j);
}
printf("\n");

for (int i = 0; i < CORREDORES; i++) {
    printf("Corredor %d: ", i);
    for (int j = 0; j < PRATELEIRAS; j++) {
        if (matrizEstante[i][j] == 0) {
            printf("[  LIVRE  ]    ");
        } else {
            printf("[ ID:%03d  ]    ", matrizEstante[i][j]);
        }
    }
    printf("\n");
}


}

void ordenarLivrosPorTitulo() {
int i, j;
struct Livro temp;

for (i = 0; i < totalLivros - 1; i++) {
    for (j = 0; j < totalLivros - i - 1; j++) {
        if (strcmp(acervo[j].titulo, acervo[j + 1].titulo) > 0) {
            temp = acervo[j];
            acervo[j] = acervo[j + 1];
            acervo[j + 1] = temp;
        }
    }
}
printf("\n[SUCESSO] Acervo ordenado alfabeticamente por Titulo.\n");


}

void ordenarLivrosPorID() {
int i, j;
struct Livro temp;

for (i = 0; i < totalLivros - 1; i++) {
    for (j = 0; j < totalLivros - i - 1; j++) {
        if (acervo[j].id > acervo[j + 1].id) {
            temp = acervo[j];
            acervo[j] = acervo[j + 1];
            acervo[j + 1] = temp;
        }
    }
}
printf("\n[SUCESSO] Acervo ordenado por ID!\n");


}

void relatorioEstatistico() {
int disponiveis = 0, emprestados = 0, removidos = 0;

for (int i = 0; i < totalLivros; i++) {
    if (acervo[i].ativo == 0) {
        removidos++;
    } else if (acervo[i].disponivel == 1) {
        disponiveis++;
    } else {
        emprestados++;
    }
}

printf("\n======================================================\n");
printf("         RELATORIO ESTATISTICO DO ACERVO              \n");
printf("======================================================\n");
printf(" Total de Livros Cadastrados: %d\n", totalLivros);
printf(" Livros Disponiveis na Estante: %d\n", disponiveis);
printf(" Livros Emprestados: %d\n", emprestados);
printf(" Livros Desativados/Removidos: %d\n", removidos);
printf(" Total de Leitores Ativos: %d\n", totalLeitores);
printf(" Total de Emprestimos Realizados: %d\n", totalEmprestimos);


}

void moduloRelatoriosMatriz() {
int opcao;
do {
printf("1. Exibir Grade de Controle da Estante (Matriz)\n");
printf("2. Ordenar Acervo por Titulo (Bubble Sort)\n");
printf("3. Ordenar Acervo por ID (Bubble Sort)\n");
printf("4. Relatorio Estatistico Geral\n");
printf("0. Voltar ao Menu Principal\n");
printf("Escolha uma acao: ");
opcao = lerNumero();

    switch (opcao) {
        case 1:
            exibirMatrizEstante();
            break;
        case 2:
            ordenarLivrosPorTitulo();
            buscarEListarLivros();
            break;
        case 3:
            ordenarLivrosPorID();
            buscarEListarLivros();
            break;
        case 4:
            relatorioEstatistico();
            break;
        case 0:
            printf("\nRetornando ao menu principal...\n");
            break;
        default:
            printf("\nERRO! Opcao invalida.\n");
    }
} while (opcao != 0);


}

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