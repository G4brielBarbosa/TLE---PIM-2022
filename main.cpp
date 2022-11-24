// Imports

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sstream>
#include <locale.h>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#define tamanho 100

using namespace std;


// Classes

typedef struct tim {
int tm_sec; //representa os segundos de 0 a 59
int tm_min; //representa os minutos de 0 a 59
int tm_hour; //representa as horas de 0 a 24
int tm_mday; //dia do mês de 1 a 31
int tm_year; //representa o ano a partir de 1900
int tm_wday; //dia da semana de 0 (domingo) até 6 (sábado)
int tm_yday; // dia do ano de 1 a 365
int tm_isdst; //indica horário de verão se for diferente de zero
};

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
	char idCliente;
	char nomeCliente[50];
	char quantidadeVendida[50];
} clienteTipo;

typedef struct Vendas{
	char codVendas;
	char codProduto;
	char codCliente;
	char quantidadeVenda[50];
	char totalVenda[50];
	char dataVenda[50];	
} vendaTipo;

typedef struct Produto{
	char codProduto;
	char nomeProduto[50];
	char valorProduto[50];
	char qntEstoque[50];
	char qntVendida[50];
} produtoTipo;

// Arquivos

FILE *arquivo;
FILE *arquivoCliente;
FILE *arquivoFuncionario;
FILE *arquivoVenda;
FILE *arquivoProduto;

// Protótipos

void Cadastrar(void);
void Pesquisar(void);
void menu(void);
void cadastrarCliente(void);
void menuOpcoes(void);
void cadastrarFuncionario(void);
void cadastrarVenda(void);
void cadastrarProduto(void);
void menuRelatorio(void);
void abaterEstoque(void);
void adicionarEstoque(void);
void adicionarValorCliente(void);
void adicionarValorProduto(void);
void buscarVendasCliente(void);
void buscarVendasProduto(void);
void listarVendas(void);


// Variaveis Globais

static int qtd = 0;
logon maximo[tamanho];
clienteTipo cliente[tamanho];
funcionarioTipo funcionario[tamanho];
vendaTipo venda[tamanho];
produtoTipo produto[tamanho];

// Funções
void Data(void){
	double horario;
	double dia;
	double mes;
	double ano;
	struct tm *data_hora_atual;  
	
  	  //variável do tipo time_t para armazenar o tempo em segundos  
	time_t segundos;
	  
    //obtendo o tempo em segundos  
	time(&segundos);   
	  
	  //para converter de segundos para o tempo local  
	  //utilizamos a função localtime  

	data_hora_atual = localtime(&segundos);  
	dia = data_hora_atual->tm_mday;
	mes = data_hora_atual->tm_mon+1;
	ano =   data_hora_atual->tm_year+1900;
	cout << dia  << "/" << mes << "/" << ano;
  	
}

int autoIncrement(int escolha){
	int i = 0, returnIncrement = 1, increment;
	
	switch(escolha){
		
		case 1:
			arquivoProduto = fopen("produto.txt", "r");
	
			returnIncrement = fread(&produto[i], sizeof(produtoTipo), 1, arquivoProduto);
			while(returnIncrement == 1) {
				
			i++;
			returnIncrement = fread(&produto[i], sizeof(produtoTipo), 1, arquivoProduto);
			}
		break;
		
		case 2:
			arquivoCliente = fopen("cliente.txt", "r");
	
			returnIncrement = fread(&cliente[i], sizeof(clienteTipo), 1, arquivoCliente);
			while(returnIncrement == 1) {
		
			i++;
			returnIncrement = fread(&cliente[i], sizeof(clienteTipo), 1, arquivoCliente);
			}	
		break;
		
		case 3:
			arquivoVenda = fopen("vendas.txt", "r");
	
			returnIncrement = fread(&venda[i], sizeof(vendaTipo), 1, arquivoVenda);
			while(returnIncrement == 1) {
		
			i++;
			returnIncrement = fread(&venda[i], sizeof(vendaTipo), 1, arquivoVenda);
			}
		break;
	}
	increment = i + 1;
	
	
	
	return increment;
}

void listarVendas(){
	char codigoBuscar;
	int retornoVenda, i = 0;
	vendaTipo vendaLista[tamanho];
	char t;
	
	
	arquivoVenda = fopen("vendas.txt", "a+");
	
	if(arquivoVenda == NULL){
		cout << "Não foi possivel abrir o arquivo";
		exit(0);
	}
	
	retornoVenda = fread(&vendaLista[i], sizeof(vendaTipo), 1, arquivoVenda);
	
	while(retornoVenda == 1){
		
		i++;
		retornoVenda = fread(&vendaLista[i], sizeof(vendaTipo), 1, arquivoVenda);
	}
	
	fclose(arquivoVenda);
	system("cls");
	cout << "***********************************************VENDAS*******************************************" << endl;
	cout << "*                                                                                              *" << endl;
	cout << "* nºVenda        nºCliente         nºProduto         Quantidade             Total              *" << endl;
	cout << "*                                                                                              *" << endl;
	for(int j = 0; j < i; j++){
		char idVenda = vendaLista[j].codVendas;
		char idCliente = vendaLista[j].codCliente;
		char idProduto = vendaLista[j].codProduto;
		int qtdVendida = atoi(vendaLista[j].quantidadeVenda);
		int totalVendido = atoi(vendaLista[j].totalVenda);
		cout << "* " << idVenda <<"                " << idCliente << "                 " << idProduto << "                 " << qtdVendida << "                    " << totalVendido << "              *" << endl;
	
	}
	cout << "************************************************************************************************" << endl;
	
	cout << endl << endl << endl ;
	t = getch();
	if(t == 27){
		menuRelatorio();
		
	}

	
}

void adicionarValorProduto(char codigo, char quantidade[50]){
	int retorno;
	int i = 0;
	produtoTipo novoValorAdd[tamanho];
	
	arquivoProduto = fopen("produto.txt", "r+");
	
	if(arquivoProduto == NULL){
		cout << "Não foi possivel abrir o arquivo";
		exit(0);
	}
	
	retorno = fread(&novoValorAdd[i], sizeof(produtoTipo), 1, arquivoProduto);
	
	while(retorno == 1){
		
		if(codigo == novoValorAdd[i].codProduto){
			int controle = atoi(novoValorAdd[i].qntVendida);
			int controle2 = atoi(quantidade);
			int result = controle + controle2;
			snprintf(novoValorAdd[i].qntVendida, 50, "%d", result);			
			
		}
		i++;
		retorno = fread(&novoValorAdd[i], sizeof(produtoTipo), 1, arquivoProduto);
	}
	
	fclose(arquivoProduto);
	arquivoProduto = fopen("produto.txt", "w+");
	for(int k = 0; k < i ; k++){
		
		fwrite(&novoValorAdd[k], sizeof(produtoTipo), 1, arquivoProduto);

	}
	fclose(arquivoProduto);
}

void adicionarValorCliente(char codigo, char quantidade[50]){
	int retorno;
	int i = 0;
	clienteTipo novoClienteAdd[tamanho];
	
	arquivoCliente = fopen("cliente.txt", "r+");
	
	if(arquivoCliente == NULL){
		cout << "Não foi possivel abrir o arquivo";
		exit(0);
	}
	
	retorno = fread(&novoClienteAdd[i], sizeof(clienteTipo), 1, arquivoCliente);
	
	while(retorno == 1){
		
		if(codigo == novoClienteAdd[i].idCliente){
			int controle = atoi(novoClienteAdd[i].quantidadeVendida);
			int controle2 = atoi(quantidade);
			int result = controle + controle2;
			snprintf(novoClienteAdd[i].quantidadeVendida, 50, "%d", result);				
			
		}
		i++;
		retorno = fread(&novoClienteAdd[i], sizeof(clienteTipo), 1, arquivoCliente);
	}
	
	fclose(arquivoCliente);
	arquivoProduto = fopen("cliente.txt", "w+");
	for(int k = 0; k < i ; k++){
		
		fwrite(&novoClienteAdd[k], sizeof(clienteTipo), 1, arquivoCliente);

	}
	fclose(arquivoCliente);
}

void adicionarEstoque(char codigo, char quantidade[50]){
	int retorno;
	int i = 0;
	produtoTipo novoProdutoAdd[tamanho];
	
	arquivoProduto = fopen("produto.txt", "r+");
	
	if(arquivoProduto == NULL){
		cout << "Não foi possivel abrir o arquivo";
		exit(0);
	}
	
	retorno = fread(&novoProdutoAdd[i], sizeof(produtoTipo), 1, arquivoProduto);
	
	while(retorno == 1){
		
		if(codigo == novoProdutoAdd[i].codProduto){
			int controle = atoi(novoProdutoAdd[i].qntEstoque);
			int controle2 = atoi(quantidade);
			int result = controle + controle2;
			snprintf(novoProdutoAdd[i].qntEstoque, 50, "%d", result);				
			
		}
		i++;
		retorno = fread(&novoProdutoAdd[i], sizeof(produtoTipo), 1, arquivoProduto);
	}
	
	fclose(arquivoProduto);
	arquivoProduto = fopen("produto.txt", "w+");
	for(int k = 0; k < i ; k++){
		
		fwrite(&novoProdutoAdd[k], sizeof(produtoTipo), 1, arquivoProduto);

	}
	cout << "Adicionado ao estoque com sucesso" << endl;
	fclose(arquivoProduto);
	
}

void abaterEstoque(char codigo, char quantidade[50]){
	int retorno;
	int i = 0;
	produtoTipo novoProduto[tamanho];
	
	arquivoProduto = fopen("produto.txt", "r+");
	
	if(arquivoProduto == NULL){
		cout << "Não foi possivel abrir o arquivo";
		exit(0);
	}
	
	retorno = fread(&novoProduto[i], sizeof(produtoTipo), 1, arquivoProduto);
	
	while(retorno == 1){
		
		if(codigo == novoProduto[i].codProduto){
			int controle = atoi(novoProduto[i].qntEstoque);
			int controle2 = atoi(quantidade);
			int result = controle - controle2;
			snprintf(novoProduto[i].qntEstoque, 50, "%d", result);				
			
		}
		i++;
		retorno = fread(&novoProduto[i], sizeof(produtoTipo), 1, arquivoProduto);
	}
	
	fclose(arquivoProduto);
	arquivoProduto = fopen("produto.txt", "w+");
	for(int k = 0; k < i ; k++){
		
		fwrite(&novoProduto[k], sizeof(produtoTipo), 1, arquivoProduto);

	}
	fclose(arquivoProduto);
	
}

void buscarVendasProduto(){
	char codigoBuscar;
	int retornoVendaProduto, i = 0;
	vendaTipo vendaListaProduto[tamanho];
	char t;

	
	
	arquivoVenda = fopen("vendas.txt", "a+");
	
	if(arquivoVenda == NULL){
		cout << "Não foi possivel abrir o arquivo";
		exit(0);
	}
	
	retornoVendaProduto = fread(&vendaListaProduto[i], sizeof(vendaTipo), 1, arquivoVenda);
	
	cout << "Digite o código do produto" << endl;
	cin >> codigoBuscar;
	
	system("cls");
	cout << "***********************************************VENDAS*******************************************" << endl;
	cout << "*                                                                                              *" << endl;
	cout << "* nºVenda        nºCliente         nºProduto         Quantidade             Total              *" << endl;
	cout << "*                                                                                              *" << endl;
	
	while(retornoVendaProduto == 1){
			if(codigoBuscar == vendaListaProduto[i].codProduto){
				for(int j = 0; j < i; j++){
					char idVenda = vendaListaProduto[j].codVendas;
					char idCliente = vendaListaProduto[j].codCliente;
					char idProduto = vendaListaProduto[j].codProduto;
					int qtdVendida = atoi(vendaListaProduto[j].quantidadeVenda);
					int totalVendido = atoi(vendaListaProduto[j].totalVenda);
					cout << "* " << idVenda <<"                " << idCliente << "                 " << idProduto << "                 " << qtdVendida << "                    " << totalVendido << "              *" << endl;
	
				}
			}
		i++;
		retornoVendaProduto = fread(&vendaListaProduto[i], sizeof(vendaTipo), 1, arquivoVenda);
	}	
	fclose(arquivoVenda);
	cout << "************************************************************************************************" << endl;
	
	cout << endl << endl << endl ;
	
	t = getch();
	if(t == 27){
		menuRelatorio();
		
	}

	
}

void buscarVendasCliente(){
	char codigoBuscar;
	int retornoVendaCliente, i = 0;
	vendaTipo vendaListaCliente[tamanho];
	char t;
	
	
	arquivoVenda = fopen("vendas.txt", "a+");
	
	if(arquivoVenda == NULL){
		cout << "Não foi possivel abrir o arquivo";
		exit(0);
	}
	
	retornoVendaCliente = fread(&vendaListaCliente[i], sizeof(vendaTipo), 1, arquivoVenda);
	
	cout << "Digite o código do cliente" << endl;
	cin >> codigoBuscar;
	
	system("cls");
	cout << "***********************************************VENDAS*******************************************" << endl;
	cout << "                                                                                                " << endl;
	cout << "        nºVenda        nºCliente         nºProduto         Quantidade             Total               " << endl;
	cout << "                                                                                                " << endl;
	
	while(retornoVendaCliente == 1){
			if(codigoBuscar == vendaListaCliente[i].codCliente){
				for(int j = 0; j < i; j++){
					char idVenda = vendaListaCliente[j].codVendas;
					char idCliente = vendaListaCliente[j].codCliente;
					char idProduto = vendaListaCliente[j].codProduto;
					int qtdVendida = atoi(vendaListaCliente[j].quantidadeVenda);
					int totalVendido = atoi(vendaListaCliente[j].totalVenda);
					cout << "        " << idVenda <<"                " << idCliente << "                 " << idProduto << "                 " << qtdVendida << "                    " << totalVendido << "              " << endl;
	
				}
			}
		i++;
		retornoVendaCliente = fread(&vendaListaCliente[i], sizeof(vendaTipo), 1, arquivoVenda);
	}	
	fclose(arquivoVenda);
	cout << "************************************************************************************************" << endl;
	
	cout << endl << endl << endl ;
	cout << "Para voltar ao menu anterior pressione ESC" << endl;
	cout << "Tentar novamente digite qualquer tecla" << endl;
	t = getch();
	if(t == 27){
		menuRelatorio();
		
	}
}

void cadastrarProduto(void){
	int i = 0;
	int back;
	int lerProduto;
	char acessoCod;
	produtoTipo quantidadeAdicionar[tamanho];
	char stringIncrement = autoIncrement(1) + '0';
	
	


	arquivoProduto = fopen("produto.txt", "a+");
	
	if(arquivoProduto == NULL){
		cout << "Não foi possivel abrir o arquivo";
		exit(0);
	}
	
	int opcao;
	system("cls");
	cout << stringIncrement;
	cout << "********************CADASTRO DE PRODUTO*****************" << endl;
	cout << "*                                                      *" << endl;
	cout << "***********SELECIONE QUAL OPÇÃO QUER ACESSAR************" << endl;
	cout << "*                                                      *" << endl;
	cout << "*               1 - CADASTRAR PRODUTO NOVO             *" << endl;
	cout << "*               2 - ADICIONAR A PRODUTO EXISTENTE      *" << endl;
	cout << "*                                                      *" << endl;
	cout << "********************************************************" << endl;
	opcao = getch();
	switch(opcao){
		
		case '1':
			
			for(int h = 0; h < 1; h++){
		
				produto[h].codProduto = stringIncrement;
				snprintf(produto[h].qntVendida, 50, "%c", '0' );
		
			}
		
			cout << "Digite o nome do produto" << endl;
			gets(produto[i].nomeProduto);
	
			cout << "Digite o valor do produto" << endl;
			gets(produto[i].valorProduto);
	
			cout << "Digite a quantidade do produto" << endl;
			gets(produto[i].qntEstoque);
			
			
		
			lerProduto = fwrite(produto, sizeof(produtoTipo), 1, arquivoProduto);
			
			
			
			if(lerProduto == 1){
				cout << "Cadastro efetuado com sucesso" << endl;
			}
		
			
			fclose(arquivoProduto);
			cout << "Para voltar ao menu anterior pressione ESC" << endl;
			back = getch();
				if (back == 27){
				menuOpcoes();
			}
			break;
		
		case '2':
			
			cout << "Digite o código do produto" << endl;
			cin >> produto[i].codProduto;
			acessoCod = produto[i].codProduto;
			getchar();
			cout << "Digite a quantidade de produtos" << endl;
			gets(quantidadeAdicionar[i].qntEstoque);
			adicionarEstoque(acessoCod, quantidadeAdicionar[i].qntEstoque);
		break;	
	}
	fclose(arquivoProduto);
	
	
}

void cadastrarVenda(void){
	int i = 0;
	int back;
	int lerVenda;
	char codAcessoProduto;
	char codAcessoCliente;
	char stringIncrement = autoIncrement(3) + '0';
	
	arquivoVenda = fopen("vendas.txt", "a+");
	
	if(arquivoVenda == NULL){
		cout << "Não foi possivel abrir o arquivo";
		exit(0);
	}
	
	for(int h = 0; h < 1; h++){
		
		venda[h].codVendas = stringIncrement;
		
	}
	
	cout << "Digite a data da venda" << endl;
	gets(venda[i].dataVenda);
		
	cout << "Digite o código do cliente" << endl;
	cin >> venda[i].codCliente;
	codAcessoCliente = venda[i].codCliente;
	getchar();
	cout << "Digite o código do produto" << endl;
	cin >> venda[i].codProduto;
	codAcessoProduto = venda[i].codProduto;
	getchar();
	
	cout << "Digite o valor total da venda" << endl;
	gets(venda[i].totalVenda);
	
	cout << "Digite a quantidade de produtos vendidos" << endl;
	gets(venda[i].quantidadeVenda);
	
	adicionarValorProduto(codAcessoCliente, venda[i].totalVenda);
	adicionarValorCliente(codAcessoCliente, venda[i].totalVenda);
	abaterEstoque(codAcessoProduto, venda[i].quantidadeVenda);
	
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
	
	char stringIncrement = autoIncrement(2) + '0';
	
	for(int h = 0; h < 1; h++){
		
		cliente[h].idCliente = stringIncrement;
		
	}

	cout << "Digite o nome do cliente" << endl;
	gets(cliente[i].nomeCliente);
	
	cout << "Digite o valor que o cliente já comprou" << endl;
	gets(cliente[i].quantidadeVendida);
	
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
	arquivo = fopen("login.txt", "a+");
	
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
	char opcao;
	char t;
	system("cls");
	cout << "                                     ***************SEJA BEM-VINDO A TLC COMPANY*************" << endl;
	cout << "                                     *                                                      *" << endl;
	cout << "                                     ***********SELECIONE QUAL OPÇÃO QUER ACESSAR************" << endl;
	cout << "                                     *                                                      *" << endl;
	cout << "                                     *                   1 - CADASTRAR CLIENTE              *" << endl;
	cout << "                                     *                   2 - CADASTRAR PRODUTO              *" << endl;
	cout << "                                     *                   3 - CADASTRAR FUNCIONARIO          *" << endl;	
	cout << "                                     *                   4 - CADASTRAR VENDA                *" << endl;	
	cout << "                                     *                   5 - GERAR RELATORIO                *" << endl;
	cout << "                                     *                   6 - VENDAS                         *" << endl;
	cout << "                                     *                                                      *" << endl;
	cout << "                                     ********************************************************" << endl;
	cout << endl;
	cout << "                                                        LOGOUT - APERTE ESC                  " << endl;
	opcao = getch();
	switch(opcao){
		case 1:
			system("cls");
			cadastrarCliente();
			break;
		case 2:
			system("cls");
			cadastrarProduto();
			break;
		case 3:
			system("cls");
			cadastrarFuncionario();
			break;
		case 4:
			system("cls");
			cadastrarVenda();
			break;
		case 5:
			system("cls");
			menuRelatorio();
			break;
		case 27:			
			system("color 9");
			menu();
			break;
		default:
			cout << "Opção invalida";
			break;
	}
	

		
		
	}
	


void menuRelatorio(void){
	int opcao;
	system("cls");
	cout << "***********************RELATORIOS***********************" << endl;
	cout << "*                                                      *" << endl;
	cout << "***********SELECIONE QUAL OPÇÃO QUER ACESSAR************" << endl;
	cout << "*                                                      *" << endl;
	cout << "*                   1 - VENDAS P/ CLIENTE              *" << endl;
	cout << "*                   2 - VENDAS P/ PRODUTO              *" << endl;
	cout << "*                   3 - TOTAL DE VENDAS                *" << endl;	
	cout << "*                   4 - ESTOQUE                        *" << endl;	
	cout << "*                                                      *" << endl;
	cout << "********************************************************" << endl;
	opcao = getch();
	switch(opcao){
		case '1':
			buscarVendasCliente();
			break;
		case '2':
			buscarVendasProduto();
			break;
		case '3':
			listarVendas();
			break;
		case '4':
			cout << "ESTOQUE";
			break;
		default:
			cout << "OPCAO INVALIDA";
			break;
	}
}

void Pesquisar(void){
	int i = 0, retorno = 1, cont= 0;
	char login[50], op, senhas[50];
	int t;
	
	arquivo = fopen("login.txt", "r");
	
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
		system("color 4");
		cout << endl;
		cout << endl;
		cout << "Login invalido" << endl;
		cout << endl;
		cout << endl;
	}	
	
	fclose(arquivo);
	cout << "Para voltar ao menu anterior pressione ESC" << endl;
	cout << "Tentar novamente digite qualquer tecla" << endl;
	t = getch();
	if(t == 27){
		system("color ");
		menu();
		
		
	}else{
		login[50] = 0;
		system("cls");
		system("color 2");
		Pesquisar();
	}
}

void menu(void){
	int opcao;
	system("cls");
	cout << "                                 ***************SEJA BEM-VINDO A TLC COMPANY*************" << endl;
	cout << "                                 *                                                      *" << endl;
	cout << "                                 ***********SELECIONE QUAL OPÇÃO QUER ACESSAR************" << endl;
	cout << "                                 *                                                      *" << endl;
	cout << "                                 *                      1 - LOGIN                       *" << endl;
	cout << "                                 *                      2 - CADASTRAR                   *" << endl;
	cout << "                                 *                                                      *" << endl;
	cout << "                                 ********************************************************" << endl;
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
	system("color 2");
	setlocale(LC_ALL, "Portuguese");
	menu();
	

	return 0;
}
