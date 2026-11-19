#include "biblioteca.h"
// Renan cadastro de livros e leitores
struct Livro acervo[MAX];
int totalLivros = 0;

struct Leitor leitores[MAX];
int totalLeitores = 0;

struct Emprestimo emprestimos[MAX];
int totalEmprestimos = 0;

// Marcela matriz de posição física do livro
int matrizEstante[CORREDORES][PRATELEIRAS];

// Renan e Marcela estrutura de cabeçalho
void exibirCabecalho() {
	printf("\n======================================================\n");
	printf("                  BIBLIOTECA CLASSICA            \n");
	printf("======================================================\n");
}

// Renan buscar livros e leitores

void limparTela() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}


void limparTeclado() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
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
	// Lê o texto digitado pelo usuário
	if (fgets(destino, tamanho, stdin) != NULL) {
		// Remove a quebra de linha '\n' do final, se existir
		size_t len = strlen(destino);
		if (len > 0 && destino[len - 1] == '\n') {
			destino[len - 1] = '\0';
		}
	}
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
// Marcela inicialização em 0 da matriz corredores/prateleiras sempre que o terminal for iniciado
void inicializarMatriz() {
	int i, j;
	for (i = 0; i < CORREDORES; i++) {
		for (j = 0; j < PRATELEIRAS; j++) {
			matrizEstante[i][j] = 0;
		}
	}
}

void reescreverArquivoLivros() {
	FILE *arqLivros = fopen("livros.txt", "w");
	if (arqLivros == NULL) return;

	for (int i = 0; i < totalLivros; i++) {
		if (acervo[i].ativo == 1) {
			fprintf(arqLivros, "ID: %d | Corredor: %d | Prateleira: %d | Titulo: %s | Autor: %s | Ano: %d\n",
			        acervo[i].id, acervo[i].corredor, acervo[i].prateleira,
			        acervo[i].titulo, acervo[i].autor, acervo[i].ano);
		}
	}
	fclose(arqLivros);
}

void reescreverArquivoLeitores() {
	FILE *arqLeitores = fopen("leitores.txt", "w");
	if (arqLeitores == NULL) return;

	for (int i = 0; i < totalLeitores; i++) {
		if (leitores[i].ativo == 1) {
			fprintf(arqLeitores, "Carteirinha: %d | Nome: %s | Telefone: %s | Idade: %d\n",
			        leitores[i].id, leitores[i].nome, leitores[i].telefone, leitores[i].idade);
		}
	}
	fclose(arqLeitores);
}

void reescreverArquivoEmprestimos() {
	FILE *arqEmp = fopen("emprestimos.txt", "w");
	if (arqEmp == NULL) return;

	for (int i = 0; i < totalEmprestimos; i++) {
		if (emprestimos[i].ativo == 1) {
			fprintf(arqEmp, "ID: %d | ID Livro: %d | Titulo: %s | ID Leitor: %d | Nome Leitor: %s | Prazo: %d | Devolvido: %d | Multa: %.2f\n",
			        emprestimos[i].id, emprestimos[i].idLivro, emprestimos[i].tituloLivro,
			        emprestimos[i].idLeitor, emprestimos[i].nomeLeitor, emprestimos[i].diasPrazo,
			        emprestimos[i].devolvido, emprestimos[i].multa);
		}
	}
	fclose(arqEmp);
}

// Corrigido o nome do arquivo para "livros.txt"
void livrosArq(struct Livro l) {
	FILE *arqLivros = fopen("livros.txt", "a");

	if (arqLivros == NULL) {
		printf("\nErro! Nao foi possivel acessar o arquivo de livros.\n");
		return;
	}

	fprintf(arqLivros, "ID: %d | Corredor: %d | Prateleira: %d | Titulo: %s | Autor: %s | Ano: %d\n",
	        l.id, l.corredor, l.prateleira, l.titulo, l.autor, l.ano);

	fclose(arqLivros);
}

void leitoresArq(struct Leitor l) {
	FILE *arqLeitores = fopen("leitores.txt", "a");

	if (arqLeitores == NULL) {
		printf("\nErro ao abrir o arquivo de leitores!\n");
		return;
	}

	fprintf(arqLeitores, "Carteirinha: %d | Nome: %s | Telefone: %s | Idade: %d\n",
	        l.id, l.nome, l.telefone, l.idade);

	fclose(arqLeitores);
}

void empArq(struct Emprestimo e) {
	FILE *arqEmp = fopen("emprestimos.txt", "a");

	if (arqEmp == NULL) {
		printf("\nErro! Nao foi possivel acessar o arquivo de emprestimos.\n");
		return;
	}

	fprintf(arqEmp, "ID: %d | ID Livro: %d | Titulo: %s | ID Leitor: %d | Nome Leitor: %s | Prazo: %d | Devolvido: %d | Multa: %.2f\n",
	        e.id, e.idLivro, e.tituloLivro, e.idLeitor, e.nomeLeitor, e.diasPrazo, e.devolvido, e.multa);

	fclose(arqEmp);
}

void carregarLeitoresDoArquivo() {
	FILE *arqleitores = fopen("leitores.txt", "r");
	if (arqleitores == NULL) {
		return;
	}

	char linha[256];
	// fgets l� linha por linha e garante que o arquivo sempre avance at� o fim
	while (fgets(linha, sizeof(linha), arqleitores) != NULL && totalLeitores < MAX) {
		struct Leitor l;

		// %49[^|] l� tudo at� a barra '|' (permitindo nomes compostos com espa�o)
		int res = sscanf(linha, "Carteirinha: %d | Nome: %49[^|] | Telefone: %19[^|] | Idade: %d",
		                 &l.id, l.nome, l.telefone, &l.idade);

		if (res == 4) {
			// Remove o espa�o em branco extra que fica no final antes da '|'
			int lenNome = strlen(l.nome);
			if (lenNome > 0 && l.nome[lenNome - 1] == ' ') l.nome[lenNome - 1] = '\0';

			int lenTel = strlen(l.telefone);
			if (lenTel > 0 && l.telefone[lenTel - 1] == ' ') l.telefone[lenTel - 1] = '\0';

			l.ativo = 1;
			leitores[totalLeitores] = l;
			totalLeitores++;
		}
	}

	fclose(arqleitores);
}

void carregarLivrosDoArquivo() {
	FILE *arqLivros = fopen("livros.txt", "r");
	if (arqLivros == NULL) {
		return;
	}

	char linha[256];
	while (fgets(linha, sizeof(linha), arqLivros) != NULL && totalLivros < MAX) {
		struct Livro l;

		int res = sscanf(linha, "ID: %d | Corredor: %d | Prateleira: %d | Titulo: %49[^|] | Autor: %49[^|] | Ano: %d",
		                 &l.id, &l.corredor, &l.prateleira, l.titulo, l.autor, &l.ano);

		if (res == 6) {
			// Remove o espa�o em branco extra que fica no final antes da '|'
			int lenTit = strlen(l.titulo);
			if (lenTit > 0 && l.titulo[lenTit - 1] == ' ') l.titulo[lenTit - 1] = '\0';

			int lenAut = strlen(l.autor);
			if (lenAut > 0 && l.autor[lenAut - 1] == ' ') l.autor[lenAut - 1] = '\0';

			l.disponivel = 1;
			l.ativo = 1;
			acervo[totalLivros] = l;

			// Garante que n�o acesse fora da matriz caso o arquivo tenha sido editado manualmente
			if (l.corredor >= 0 && l.corredor < CORREDORES && l.prateleira >= 0 && l.prateleira < PRATELEIRAS) {
				matrizEstante[l.corredor][l.prateleira] = l.id;
			}
			totalLivros++;
		}
	}

	fclose(arqLivros);
}

void carregarEmprestimosDoArquivo() {
	FILE *arqEmp = fopen("emprestimos.txt", "r");
	if (arqEmp == NULL) {
		return;
	}

	char linha[300];
	while (fgets(linha, sizeof(linha), arqEmp) != NULL && totalEmprestimos < MAX) {
		struct Emprestimo e;

		int res = sscanf(linha, "ID: %d | ID Livro: %d | Titulo: %49[^|] | ID Leitor: %d | Nome Leitor: %49[^|] | Prazo: %d | Devolvido: %d | Multa: %f",
		                 &e.id, &e.idLivro, e.tituloLivro, &e.idLeitor, e.nomeLeitor,
		                 &e.diasPrazo, &e.devolvido, &e.multa);

		if (res == 8) {
			// Remove espaco extra antes da barra '|'
			int lenTit = strlen(e.tituloLivro);
			if (lenTit > 0 && e.tituloLivro[lenTit - 1] == ' ') e.tituloLivro[lenTit - 1] = '\0';

			int lenLeitor = strlen(e.nomeLeitor);
			if (lenLeitor > 0 && e.nomeLeitor[lenLeitor - 1] == ' ') e.nomeLeitor[lenLeitor - 1] = '\0';

			e.ativo = 1;
			emprestimos[totalEmprestimos] = e;
			totalEmprestimos++;

			// Se o emprestimo ainda esta em aberto, marca o livro como indisponivel no acervo
			if (e.devolvido == 0) {
				int posLivro = buscarLivro(e.idLivro);
				if (posLivro != -1) {
					acervo[posLivro].disponivel = 0;
				}
			}
		}
	}

	fclose(arqEmp);
}


// Renan e Marcela módulo de cadastro e busca de livros e leitores junto com matriz
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

	//chama função de escrever livro cadastrado no arquivo
	livrosArq(acervo[totalLivros]);

	//Adiciona +1 no contador de livros no total do acervo
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
	limparTela();
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

	reescreverArquivoLivros();

	printf("\nDados do livro atualizados com sucesso!\n");
}

void removerLivro() {
	limparTela();
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

	reescreverArquivoLivros();

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
		case 1:
			cadastrarLivro();
			break;
		case 2:
			buscarEListarLivros();
			break;
		case 3:
			editarLivro();
			break;
		case 4:
			removerLivro();
			break;
		case 0:
			printf("\nRetornando ao menu principal...\n");
			break;
		default:
			printf("\nERRO! Opcao invalida no Modulo de Livros.\n");
		}
	} while (opcao != 0);
}

void cadastrarLeitor() {
	limparTela();
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

	// Se o nome foi lido em branco por causa de \n pendente, pede novamente
	if (strlen(leitores[totalLeitores].nome) == 0) {
		lerTexto(leitores[totalLeitores].nome, 50);
	}

	printf("Digite o telefone: ");
	lerTexto(leitores[totalLeitores].telefone, 20);

	printf("Digite a idade: ");
	int idade = lerNumero();
	if (idade < 5 || idade > 120) {
		printf("\nERRO! Idade invalida (deve ser entre 5 e 120). Cadastro cancelado.\n");
		return;
	}
	leitores[totalLeitores].idade = idade;

	leitores[totalLeitores].ativo = 1;

	leitoresArq(leitores[totalLeitores]);

	totalLeitores++;

	printf("\nLeitor registrado! Total de leitores ativos: %d\n", totalLeitores);
}

void buscarEListarLeitores() {
	limparTela();
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
	limparTela();
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
	reescreverArquivoLeitores();
	printf("\nDados atualizados com sucesso!\n");
}

void removerLeitor() {
	limparTela();
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
	reescreverArquivoLeitores();
	printf("\nCarteirinha %d cancelada com sucesso!\n", id);
}

void moduloLeitores() {
	limparTela();
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
		case 1:
			cadastrarLeitor();
			break;
		case 2:
			buscarEListarLeitores();
			break;
		case 3:
			editarLeitor();
			break;
		case 4:
			removerLeitor();
			break;
		case 0:
			printf("\nRetornando ao menu principal...\n");
			break;
		default:
			printf("\nERRO! Opcao invalida no Modulo de Leitores.\n");
		}
	} while (opcao != 0);
}

void registrarEmprestimo() {
	limparTela();
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

	strcpy(emprestimos[totalEmprestimos].tituloLivro, acervo[posLivro].titulo);
	strcpy(emprestimos[totalEmprestimos].nomeLeitor, leitores[posLeitor].nome);

	emprestimos[totalEmprestimos].diasPrazo = 7;
	emprestimos[totalEmprestimos].devolvido = 0;
	emprestimos[totalEmprestimos].ativo = 1;
	emprestimos[totalEmprestimos].multa = 0.0f;

	acervo[posLivro].disponivel = 0;

	empArq(emprestimos[totalEmprestimos]);
	totalEmprestimos++;

	printf("\nEmprestimo registrado: \"%s\" para %s (prazo: 7 dias).\n",
	       acervo[posLivro].titulo, leitores[posLeitor].nome);
}


void listarEmprestimos() {
	limparTela();
	if (totalEmprestimos == 0) {
		printf("\nNenhum emprestimo registrado.\n");
		return;
	}

	printf("\n%-5s | %-25s | %-25s | %-8s | %-10s | %-10s\n", "ID", "LIVRO", "LEITOR", "PRAZO", "STATUS", "MULTA");
	printf("------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < totalEmprestimos; i++) {
		if (emprestimos[i].ativo == 1) {
			printf("%-5d | %-25s | %-25s | %d dias  | %-10s | R$ %-8.2f\n",
			       emprestimos[i].id,
			       emprestimos[i].tituloLivro,
			       emprestimos[i].nomeLeitor,
			       emprestimos[i].diasPrazo,
			       emprestimos[i].devolvido ? "Devolvido" : "Em Aberto",
			       emprestimos[i].multa);
		}
	}
}

void registrarDevolucao() {
	limparTela();
	int idEmp, posEmp, diasRealizados;
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

	printf("Quantos dias o leitor ficou com o livro ate devolver? ");
	diasRealizados = lerNumero();

	if (diasRealizados <= 0) {
		printf("\nERRO! Numero de dias invalido. Devolucao cancelada.\n");
		return;
	}

	if (diasRealizados > emprestimos[posEmp].diasPrazo) {
		int diasAtraso = diasRealizados - emprestimos[posEmp].diasPrazo;
		emprestimos[posEmp].multa = (float)diasAtraso * 2.50f;
		printf("\n[ATENCAO] Livro devolvido com %d dias de atraso!\n", diasAtraso);
		printf("Multa gerada: R$ %.2f\n", emprestimos[posEmp].multa);
	} else {
		emprestimos[posEmp].multa = 0.0f;
		printf("\nLivro devolvido dentro do prazo. Nao ha multas.\n");
	}

	emprestimos[posEmp].devolvido = 1;
	int posLivro = buscarLivro(emprestimos[posEmp].idLivro);
	if (posLivro != -1) {
		acervo[posLivro].disponivel = 1;
	}
	
    reescreverArquivoEmprestimos();
	printf("\nDevolucao concluida com sucesso! O livro esta novamente disponivel na estante.\n");
}

void cancelarEmprestimo() {
	limparTela();
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
    reescreverArquivoEmprestimos();
	printf("\nRegistro de emprestimo cancelado com sucesso.\n");
}
// Módulo de empréstimo de livros
void moduloEmprestimos() {
	limparTela();
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
		case 1:
			registrarEmprestimo();
			break;
		case 2:
			listarEmprestimos();
			break;
		case 3:
			registrarDevolucao();
			break;
		case 4:
			cancelarEmprestimo();
			break;
		case 0:
			printf("\nRetornando ao menu principal...\n");
			break;
		default:
			printf("\nERRO! Opcao invalida no Modulo de Emprestimos.\n");
		}
	} while (opcao != 0);
}

void exibirMatrizEstante() {
	limparTela();
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
// Ordenando os livros por título Renan
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
	limparTela();
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
//relátorio de estatistica do acervo 
	
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
	limparTela();
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
