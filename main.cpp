// Imports

#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <cstdlib>
#define tamanho 100

using namespace std;


// Classes

typedef struct Login{
	char user[50];
	char senha[50];
} logon;

typedef struct Funcionario{
	char nome[50];
	char cargo[50];
	char salario[50];
} funcionarioTipo;

typedef struct Cliente{
	char idCliente[50];
	char nomeCliente[50];
} clienteTipo;

typedef struct Vendas{
	char codVendas[50];
	char codProduto[50];
	char codCliente[50];
	char quantidadeVenda[50];
	char totalVenda[50];
	char dataVenda[50];	
} vendaTipo;

typedef struct Produto{
	char codProduto[50];
	char nomeProduto[50];
	char valorProduto[50];
	char qntEstoque[50];
} produtoTipo;

// Arquivos

FILE *arquivo;
FILE *arquivoCliente;
FILE *arquivoFuncionario;
FILE *arquivoVenda;
FILE *arquivoProduto;

// Protótipos

void Cadastrar	(void);
void Pesquisar(void);
void menu(void);
void cadastrarCliente(void);
void menuOpcoes(void);
void cadastrarFuncionario(void);
void cadastrarVenda(void);
void cadastrarProduto(void);

// Variaveis Globais

static int qtd = 0;
logon maximo[tamanho];
clienteTipo cliente[tamanho];
funcionarioTipo funcionario[tamanho];
vendaTipo venda[tamanho];
produtoTipo produto[tamanho];


// Funções
void cadastrarProduto(void){
	int i = 0;
	int back;
	int lerProduto;
	
	arquivoProduto = fopen("produto.txt", "a+");
	
	if(arquivoProduto == NULL){
		cout << "Não foi possivel abrir o arquivo";
		exit(0);
	}
	
	cout << "Digite o código do produto" << endl;
	gets(produto[i].codProduto);
	
	cout << "Digite o nome do produto" << endl;
	gets(produto[i].nomeProduto);
	
	cout << "Digite o valor do produto" << endl;
	gets(produto[i].valorProduto);
	
	cout << "Digite a quantidade do produto" << endl;
	gets(produto[i].qntEstoque);
	
	lerProduto = fwrite(&produto[i], sizeof(produtoTipo), 1, arquivoProduto);
	
	if(lerProduto == 1){
		cout << "Cadastro efetuado com sucesso" << endl;
	}
	
	fclose(arquivoProduto);
	cout << "Para voltar ao menu anterior pressione ESC" << endl;
	back = getch();
		if (back == 27){
		menuOpcoes();
	}
	
	
}

void cadastrarVenda(void){
	int i = 0;
	int back;
	int lerVenda;
	
	arquivoVenda = fopen("vendas.txt", "a+");
	
	if(arquivoVenda == NULL){
		cout << "Não foi possivel abrir o arquivo";
		exit(0);
	}
	
	cout << "Digite a data da venda" << endl;
	gets(venda[i].dataVenda);
	
	cout << "Digite o código da venda" <<  endl;
	gets(venda[i].codVendas);
	
	cout << "Digite o código do cliente" << endl;
	gets(venda[i].codCliente);
	
	cout << "Digite o código do produto" << endl;
	gets(venda[i].codProduto);
	
	cout << "Digite a quantidade de produtos vendidos" << endl;
	gets(venda[i].quantidadeVenda);
	
	cout << "Digite o valor total da venda" << endl;
	gets(venda[i].totalVenda);
	
	lerVenda = fwrite(&venda[i], sizeof(vendaTipo), 1, arquivoVenda);
	
	if(lerVenda == 1){
		cout << "Cadastro efetuado com sucesso" << endl;
	}
	
	fclose(arquivoVenda);
	cout << "Para voltar ao menu anterior pressione ESC" << endl;
	back = getch();
		if (back == 27){
		menuOpcoes();
	}

}

void cadastrarFuncionario(void){
	int i = 0;
	int back;
	int lerFuncionario;

	
	arquivoFuncionario = fopen("funcionario.txt", "a+");
	
	if(arquivoFuncionario == NULL){
		cout << "Não foi possivel abrir o arquivo";
		exit(0);
	}
	cout << "Digite o nome do funcionario" << endl;
	gets(funcionario[i].nome);
	cout << "Digite o cargo do funcionario" << endl;
	gets(funcionario[i].cargo);
	cout << "Digite o salario do funcionario" << endl;
	gets(funcionario[i].salario);


	
	lerFuncionario = fwrite(&funcionario[i], sizeof(clienteTipo), 1, arquivoFuncionario);
	
	if(lerFuncionario == 1){
		cout << "Cadastro efetuado com sucesso" << endl;
	}
	
	fclose(arquivoFuncionario);
	cout << "Para voltar ao menu anterior pressione ESC" << endl;
	back = getch();
		if (back == 27){
		menuOpcoes();
	}
	
}

void cadastrarCliente(void){
	
	int i = 0;
	int back;
	int lerCliente;
	arquivoCliente = fopen("cliente.txt", "a+");
	
	if(arquivoCliente == NULL){
		cout << "Não foi possivel abrir o arquivo";
		exit(0);
	}
	cout << "Digite o código do cliente" << endl;
	gets(cliente[i].idCliente);
	cout << "Digite o nome do cliente" << endl;
	gets(cliente[i].nomeCliente);
	
	lerCliente = fwrite (&cliente[i], sizeof (clienteTipo), 1, arquivoCliente);
	
	if( lerCliente == 1){
		cout << "Cadastro efetuado com sucesso" << endl;
	}
	
	fclose(arquivoCliente);
	cout << "Para voltar ao menu anterior pressione ESC" << endl;
	back = getch();
	if (back == 27){
		menuOpcoes();
	}
}

void Cadastrar(void){
	int i = 0;
	int t;
	int lerCadastro;
	arquivo = fopen("teste.txt", "a+");
	
	if(arquivo == NULL){
		cout << "Não foi possivel abrir o arquivo";
		exit(0);
	}
	cout << "Digite um nome de usuario:" << endl;
	gets(maximo[i].user);	
	cout << "Digite uma senha:" << endl;
	gets(maximo[i].senha);
	
	lerCadastro = fwrite (&maximo[i], sizeof (logon), 1, arquivo);
	
	if( lerCadastro == 1){
		cout << "Cadastro efetuado com sucesso" << endl;
		
	}		
	fclose(arquivo);
	cout << "Para voltar ao menu anterior pressione ESC" << endl;
	t = getch();
	if(t == 27){
		menu();
	}
	
}

void menuOpcoes(void){
	int opcao;
	system("cls");
	cout << "***************SEJA BEM-VINDO A TLC COMPANY*************" << endl;
	cout << "*                                                      *" << endl;
	cout << "***********SELECIONE QUAL OPÇÃO QUER ACESSAR************" << endl;
	cout << "*                                                      *" << endl;
	cout << "*                   1 - CADASTRAR CLIENTE              *" << endl;
	cout << "*                   2 - CADASTRAR PRODUTO              *" << endl;
	cout << "*                   3 - CADASTRAR FUNCIONARIO          *" << endl;	
	cout << "*                   4 - CADASTRAR VENDA                *" << endl;	
	cout << "*                   5 - GERAR RELATORIO                *" << endl;
	cout << "*                   6 - VENDAS                         *" << endl;
	cout << "*                                                      *" << endl;
	cout << "********************************************************" << endl;
	opcao = getch();
	switch(opcao){
		case '1':
			system("cls");
			cadastrarCliente();
			break;
		case '2':
			system("cls");
			cadastrarProduto();
			break;
		case '3':
			system("cls");
			cadastrarFuncionario();
			break;
		case '4':
			system("cls");
			cadastrarVenda();
			break;
		case '5':
			cout << "Relatorios";
			break;
		case '6':
			cout << "Vendas";
		default:
			cout << "Opção invalida";
			break;
	}
	
}

void Pesquisar(void){
	int i = 0, retorno = 1, cont= 0;
	char login[50], op, senhas[50];
	int t;
	
	arquivo = fopen("teste.txt", "r");
	
	if(arquivo == NULL){
		cout << "Não foi possivel abrir o arquivo";
		exit(0);
	}
	cout << "Digite seu usuario: " << endl;
	gets(login);
	cout << "Digite sua senha: " << endl;
	gets(senhas);
	retorno = fread(&maximo[i], sizeof(logon), 1, arquivo);
	while(retorno == 1) {
		if(strcmp(login, maximo[i].user) == 0 && strcmp(senhas, maximo[i].senha) == 0){
			menuOpcoes();
			cont++;

		}
		i++;
		retorno = fread(&maximo[i], sizeof(logon), 1, arquivo);
		

	}
	if(cont == 0){
		cout << "Login invalido" << endl;
	}	
	
	fclose(arquivo);
	cout << "Para voltar ao menu anterior pressione ESC" << endl;
	cout << "Tentar novamente digite qualquer tecla" << endl;
	t = getch();
	if(t == 27){
		menu();
		
	}else{
		login[50] = 0;
		system("cls");
		Pesquisar();
	}
}

void menu(void){
	int opcao;
	system("cls");
	cout << "***************SEJA BEM-VINDO A TLC COMPANY*************" << endl;
	cout << "*                                                      *" << endl;
	cout << "***********SELECIONE QUAL OPÇÃO QUER ACESSAR************" << endl;
	cout << "*                                                      *" << endl;
	cout << "*                      1 - LOGIN                       *" << endl;
	cout << "*                      2 - CADASTRAR                   *" << endl;
	cout << "*                                                      *" << endl;
	cout << "********************************************************" << endl;
	opcao = getch();
	switch(opcao){
		case '1':
			system("cls");
			Pesquisar();
			break;
		case '2':
			system("cls");
			Cadastrar();
			break;

	}
}

// Inicio Programa

int main() {
	int var;
	system("title Login");
	system("color 5F");
	setlocale(LC_ALL, "Portuguese");
	menu();
	
	return 0;
}
