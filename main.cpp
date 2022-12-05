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

// Prot�tipos

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
void manualUsuario(void);


// Variaveis Globais e instancias das Structs

static int qtd = 0;
logon maximo[tamanho];
clienteTipo cliente[tamanho];
funcionarioTipo funcionario[tamanho];
vendaTipo venda[tamanho];
produtoTipo produto[tamanho];

// Fun��es

int autoIncrement(int escolha){ // fun��o responsavel para pesquisar no arquivo a quantidade de itens e aumentar 1 para acrescentar ao c�digo de produto, cliente ou venda.
	int i = 0, returnIncrement = 1, increment; // variav�is inteirias para controle do incremento
	
	switch(escolha){ // switch que recebe o parametro escolha para encaminhar em qual tabela do banco de dados incrementar ao ID.
		
		case 1:
			arquivoProduto = fopen("produto.txt", "r"); // atribui��o para abrir o arquivo produto.txt
	
			returnIncrement = fread(&produto[i], sizeof(produtoTipo), 1, arquivoProduto); // fun��o que le o arquivo e retornar 1 caso encontrou algo no arquivo.
			while(returnIncrement == 1) {// la�o de repeti��o para adicionar a struct produto todas as informa��es que tiver em posi��es i diferentes
				
			i++;
			returnIncrement = fread(&produto[i], sizeof(produtoTipo), 1, arquivoProduto);
			}
		break; 
		
		case 2:
			arquivoCliente = fopen("cliente.txt", "r"); // atribui��o para abrir o arquivo cliente.txt
	
			returnIncrement = fread(&cliente[i], sizeof(clienteTipo), 1, arquivoCliente); // fun��o que le o arquivo e retornar 1 caso encontrou algo no arquivo.
			while(returnIncrement == 1) {// la�o de repeti��o para adicionar a struct produto todas as informa��es que tiver em posi��es i diferentes
		
			i++;
			returnIncrement = fread(&cliente[i], sizeof(clienteTipo), 1, arquivoCliente);
			}	
		break;
		
		case 3:
			arquivoVenda = fopen("vendas.txt", "r"); // atribui��o para abrir o arquivo vendas.txt
	
			returnIncrement = fread(&venda[i], sizeof(vendaTipo), 1, arquivoVenda);// fun��o que le o arquivo e retornar 1 caso encontrou algo no arquivo.
			while(returnIncrement == 1) {
		
			i++;
			returnIncrement = fread(&venda[i], sizeof(vendaTipo), 1, arquivoVenda); // la�o de repeti��o para adicionar a struct produto todas as informa��es que tiver em posi��es i diferentes
			}
		break;
	}
	increment = i + 1; // Cada vez que era encontrado algo no arquivo era adicionar um valor a i, portanto a quantidade de itens que tem eu somo +1 que vai ser o proximo item a ser adicionar.
	
	
	
	return increment; // retorno do increment como int 
}

void listarVendas(){ // fun��o responsavel por listar todas as vendas que est�o no banco de dados no arquivo vendas.txt
	int retornoVenda, i = 0; // variav�is inteiras para controle
	vendaTipo vendaLista[tamanho]; // inst�ncia da struct vendaTipo para receber as informa��es do arquivo vendas.txt
	char t; // variav�l para receber o valor para voltar ao menu anterior
	
	
	arquivoVenda = fopen("vendas.txt", "a+"); // atribui��o para abrir o arquivo produto.txt
	
	if(arquivoVenda == NULL){ // se der algum erro e retornar NULL , informar na tela que n�o foi possivel abrir/criar o arquivo.
		cout << "N�o foi possivel abrir o arquivo";
		exit(0);
	}
	
	retornoVenda = fread(&vendaLista[i], sizeof(vendaTipo), 1, arquivoVenda); // fun��o que le o arquivo e retornar 1 caso encontrou algo no arquivo.
	
	while(retornoVenda == 1){ // la�o de repeti��o para adicionar a struct produto todas as informa��es que tiver em posi��es i diferentes
		
		i++;
		retornoVenda = fread(&vendaLista[i], sizeof(vendaTipo), 1, arquivoVenda);
	}
	
	fclose(arquivoVenda); // fun��o para fechar o arquivo
	system("cls");
	cout << "***********************************************VENDAS*******************************************" << endl;
	cout << "*                                                                                              *" << endl;
	cout << "* n�Venda        n�Cliente         n�Produto         Quantidade             Total              *" << endl;
	cout << "*                                                                                              *" << endl;
	for(int j = 0; j < i; j++){ // la�o de repeti��o responsavel por adicionar os valores do arquivo txt a instancia da struct vendaTipo na mem�ria.
		char idVenda = vendaLista[j].codVendas;
		char idCliente = vendaLista[j].codCliente;
		char idProduto = vendaLista[j].codProduto;
		int qtdVendida = atoi(vendaLista[j].quantidadeVenda);
		int totalVendido = atoi(vendaLista[j].totalVenda);
		cout << "* " << idVenda <<"                " << idCliente << "                 " << idProduto << "                 " << qtdVendida << "                    " << totalVendido << "              *" << endl; // imprimir na tela 
	
	}
	cout << "************************************************************************************************" << endl;
	
	cout << endl << endl << endl ;
	t = getch();
	if(t == 27){ // 27 = ESC , para voltar ao menu anterior
		menuRelatorio();
		
	}

	
}

void adicionarValorProduto(char codigo, char quantidade[50]){ // fun��o responsavel por adicionar quantidade a um produto j� existente no banco de dados
	int retorno, i = 0; // vari�vis para controle
	produtoTipo novoValorAdd[tamanho]; // inst�ncia da struct produtoTipo para receber as informa��es do arquivo produto.txt
	
	arquivoProduto = fopen("produto.txt", "r+"); // atribui��o para abrir o arquivo no modo leitura produto.txt
	
	if(arquivoProduto == NULL){ // se der algum erro e retornar NULL , informar na tela que n�o foi possivel abrir/criar o arquivo.
		cout << "N�o foi possivel abrir o arquivo";
		exit(0);
	}
	
	retorno = fread(&novoValorAdd[i], sizeof(produtoTipo), 1, arquivoProduto); // fun��o que le o arquivo e retornar 1 caso encontrou algo no arquivo.
	
	while(retorno == 1){ // la�o de repeti��o responsavel por verificar se o c�digo adicionado na venda � igual a algum produto existente, se for adicionar valor ao existente.
		
		if(codigo == novoValorAdd[i].codProduto){ // se os c�digos forem iguais, executar a soma.
			int controle = atoi(novoValorAdd[i].qntVendida); // transforma de char * para int
			int controle2 = atoi(quantidade); // recebe valor por parametro e transformar de char* para int
			int result = controle + controle2; // faz a soma dos valores como inteiros
			snprintf(novoValorAdd[i].qntVendida, 50, "%d", result);	// adiciona o valor modificado a struct		
			
		}
		i++;
		retorno = fread(&novoValorAdd[i], sizeof(produtoTipo), 1, arquivoProduto);
	}
	
	fclose(arquivoProduto); // fecha o arquivo produto.txt
	arquivoProduto = fopen("produto.txt", "w+"); // atribui��o para abrir um arquivo limpo com nome de produto.txt
	for(int k = 0; k < i ; k++){ // la�o de repeti��o para adicionar ao arquivo cada elemento em cada posi��o na struct
		
		fwrite(&novoValorAdd[k], sizeof(produtoTipo), 1, arquivoProduto);

	}
	fclose(arquivoProduto); // fecha o arquivo produto.txt
}

void adicionarValorCliente(char codigo, char quantidade[50]){ // fun��o resposanvel por adicionar valor vendido ao cliente
	int retorno,i = 0; // vari�veis repsonsaveis para controle
	clienteTipo novoClienteAdd[tamanho]; // inst�ncia da struct clienteTipo para receber as informa��es do arquivo cliente.txt
	
	arquivoCliente = fopen("cliente.txt", "r+"); // atribui��o para abrir o arquivo no modo leitura produto.txt
	
	if(arquivoCliente == NULL){ // se der algum erro e retornar NULL , informar na tela que n�o foi possivel abrir/criar o arquivo.
		cout << "N�o foi possivel abrir o arquivo";
		exit(0);
	}
	
	retorno = fread(&novoClienteAdd[i], sizeof(clienteTipo), 1, arquivoCliente); // fun��o que le o arquivo e retornar 1 caso encontrou algo no arquivo.
	
	while(retorno == 1){ // la�o de repeti��o responsavel por verificar se o c�digo da venda bate com algum c�digo de um cliente e adicionar valor de venda ao valor vendido do cliente
		
		if(codigo == novoClienteAdd[i].idCliente){
			int controle = atoi(novoClienteAdd[i].quantidadeVendida); // modificar o valor char* para int
			int controle2 = atoi(quantidade); // modificar o valor recebido do parametro de char* para int
			int result = controle + controle2; // soma dos valores int
			snprintf(novoClienteAdd[i].quantidadeVendida, 50, "%d", result); // adiciona o valor modificado a struc			
			
		}
		i++;
		retorno = fread(&novoClienteAdd[i], sizeof(clienteTipo), 1, arquivoCliente);
	}
	
	fclose(arquivoCliente); // fecha o arquivo cliente.txt
	arquivoProduto = fopen("cliente.txt", "w+"); // atribui��o para abrir um arquivo limpo com nome de cliente.txt
	for(int k = 0; k < i ; k++){ // la�o de repeti��o para adicionar ao arquivo cada elemento em cada posi��o na struct
		
		fwrite(&novoClienteAdd[k], sizeof(clienteTipo), 1, arquivoCliente);

	}
	fclose(arquivoCliente); // fechar o arquivo cliente.txt
}

void adicionarEstoque(char codigo, char quantidade[50]){ // fun��o responsavel por adicionar quantidade de produtos no estoque caso o produto j� foi criado.
	int retorno,i = 0; // variav�is de controle

	produtoTipo novoProdutoAdd[tamanho]; // inst�ncia da struct produtoTipo para receber as informa��es do arquivo produto.txt
	
	arquivoProduto = fopen("produto.txt", "r+");  // atribui��o para abrir o arquivo no modo leitura produto.txt
	
	if(arquivoProduto == NULL){ // se der algum erro e retornar NULL , informar na tela que n�o foi possivel abrir/criar o arquivo.
		cout << "N�o foi possivel abrir o arquivo";
		exit(0);
	}
	
	retorno = fread(&novoProdutoAdd[i], sizeof(produtoTipo), 1, arquivoProduto); // fun��o que le o arquivo e retornar 1 caso encontrou algo no arquivo.
	
	while(retorno == 1){ // la�o de repeti��o responsavel por verificar se o c�digo da venda bate com algum c�digo de um produto e adicionar a quantidade ao estoque do produto
		
		if(codigo == novoProdutoAdd[i].codProduto){ // verificar se o c�digo passado bate com algum c�digo de um produto existete
			int controle = atoi(novoProdutoAdd[i].qntEstoque); // altera o valor de char* para int
			int controle2 = atoi(quantidade); // altera o valor recebido como parametro de char* para int
			int result = controle + controle2; // faz a soma dos valores
			snprintf(novoProdutoAdd[i].qntEstoque, 50, "%d", result);// adiciona o valor modificado a struc	
			
		}
		i++;
		retorno = fread(&novoProdutoAdd[i], sizeof(produtoTipo), 1, arquivoProduto);
	}
	
	fclose(arquivoProduto); // fecha o arquivo produto.txt
	arquivoProduto = fopen("produto.txt", "w+"); // atribui��o para abrir um arquivo limpo com nome de produto.txt
	for(int k = 0; k < i ; k++){ // la�o de repeti��o para adicionar ao arquivo cada elemento em cada posi��o na struct
		
		fwrite(&novoProdutoAdd[k], sizeof(produtoTipo), 1, arquivoProduto);

	}
	cout << "Adicionado ao estoque com sucesso" << endl;
	fclose(arquivoProduto); // fecha o arquivo produto.txt
	
}

void abaterEstoque(char codigo, char quantidade[50]){ // fun��o responsavel por abater a quantidade vendida do estoque da tabela produto no banco de dados.
	int retorno, i = 0;
	produtoTipo novoProduto[tamanho]; // inst�ncia da struct produtoTipo para receber as informa��es do arquivo produto.txt
	
	arquivoProduto = fopen("produto.txt", "r+"); // atribui��o para abrir o arquivo no modo leitura produto.txt
	
	if(arquivoProduto == NULL){ // se der algum erro e retornar NULL , informar na tela que n�o foi possivel abrir/criar o arquivo.
		cout << "N�o foi possivel abrir o arquivo";
		exit(0);
	}
	
	retorno = fread(&novoProduto[i], sizeof(produtoTipo), 1, arquivoProduto); // fun��o que le o arquivo e retornar 1 caso encontrou algo no arquivo.
	
	while(retorno == 1){ // la�o de repeti��o responsavel por verificar se o c�digo da venda bate com algum c�digo de um produto e abater a quantidade ao estoque do produto
		
		if(codigo == novoProduto[i].codProduto){ // verificar se o c�digo passado bate com algum c�digo de um produto existete
			int controle = atoi(novoProduto[i].qntEstoque); // altera o valor de char* para int
			int controle2 = atoi(quantidade); // altera o valor recebido como parametro de char* para int
			int result = controle - controle2;// faz a subtra��o dos valores
			snprintf(novoProduto[i].qntEstoque, 50, "%d", result); // adiciona o valor modificado a struc	
			
		}
		i++;
		retorno = fread(&novoProduto[i], sizeof(produtoTipo), 1, arquivoProduto);
	}
	
	fclose(arquivoProduto); // fecha o arquivo produto.txt
	arquivoProduto = fopen("produto.txt", "w+"); // atribui��o para abrir um arquivo limpo com nome de produto.txt
	for(int k = 0; k < i ; k++){ // la�o de repeti��o para adicionar ao arquivo cada elemento em cada posi��o na struct
		
		fwrite(&novoProduto[k], sizeof(produtoTipo), 1, arquivoProduto);

	}
	fclose(arquivoProduto); // fecha o arquivo produto.txt
	
}

void buscarVendasProduto(){ // fun��o responsavel por filtar pelo produto solicitado e listar todas suas vendas
	char codigoBuscar; // variav�l para receber o c�digo do produto solicitado
	int retornoVendaProduto, i = 0; // vari�veis de controle
	vendaTipo vendaListaProduto[tamanho]; // inst�ncia da struct vendaTipo para receber as informa��es do arquivo vendas.txt
	char t; // variav�l responsavel por receber o valor de Esc para retornar ao menu anterior

	
	
	arquivoVenda = fopen("vendas.txt", "a+"); // abre o arquivo vendas.txt para ler/editar
	
	if(arquivoVenda == NULL){ // se der algum erro e retornar NULL , informar na tela que n�o foi possivel abrir/criar o arquivo
		cout << "N�o foi possivel abrir o arquivo";
		exit(0);
	}
	
	retornoVendaProduto = fread(&vendaListaProduto[i], sizeof(vendaTipo), 1, arquivoVenda); // fun��o que le o arquivo e retornar 1 caso encontrou algo no arquivo.
	
	cout << "Digite o c�digo do produto" << endl; 
	cin >> codigoBuscar; // salva na vari�vel o valor do c�digo do produto
	
	system("cls");
	cout << "***********************************************VENDAS*******************************************" << endl;
	cout << "*                                                                                              *" << endl;
	cout << "* n�Venda        n�Cliente         n�Produto         Quantidade             Total              *" << endl;
	cout << "*                                                                                              *" << endl;
	
	while(retornoVendaProduto == 1){ // la�o de repeti��o responsavel por passar por todos valores do arquivo e verificar qual o c�digo digitado pelo cliente bate e depois adicionar todos seus atribuitos as vari�veis
			if(codigoBuscar == vendaListaProduto[i].codProduto){
					char idVenda = vendaListaProduto[i].codVendas;
					char idCliente = vendaListaProduto[i].codCliente;
					char idProduto = vendaListaProduto[i].codProduto;
					int qtdVendida = atoi(vendaListaProduto[i].quantidadeVenda);
					int totalVendido = atoi(vendaListaProduto[i].totalVenda);
					cout << "* " << idVenda <<"                " << idCliente << "                 " << idProduto << "                 " << qtdVendida << "                    " << totalVendido << "              *" << endl;
	
				
			}
		i++;
		retornoVendaProduto = fread(&vendaListaProduto[i], sizeof(vendaTipo), 1, arquivoVenda);
	}	
	fclose(arquivoVenda); // fecha o arquivo vendas.txt
	cout << "************************************************************************************************" << endl;
	
	cout << endl << endl << endl ;
	
	t = getch();
	if(t == 27){ // condi��o para voltar ao menu atenrior caso o usuario aperte ESC
		menuRelatorio();
		
	}

	
}

void buscarVendasCliente(){ // fun��o responsavel por filtrar por cliente solicitado e listar todas suas vendas
	char codigoBuscar;  // variav�l para receber o c�digo do produto solicitado
	int retornoVendaCliente, i = 0; // vari�veis de controle
	vendaTipo vendaListaCliente[tamanho]; // inst�ncia da struct vendaTipo para receber as informa��es do arquivo vendas.txt
	char t; // variav�l responsavel por receber o valor de Esc para retornar ao menu anterior
	
	
	arquivoVenda = fopen("vendas.txt", "a+"); // abre o arquivo vendas.txt para ler/editar
	
	if(arquivoVenda == NULL){ // se der algum erro e retornar NULL , informar na tela que n�o foi possivel abrir/criar o arquivo
		cout << "N�o foi possivel abrir o arquivo";
		exit(0);
	}
	
	retornoVendaCliente = fread(&vendaListaCliente[i], sizeof(vendaTipo), 1, arquivoVenda); // fun��o que le o arquivo e retornar 1 caso encontrou algo no arquivo.
	
	cout << "Digite o c�digo do cliente" << endl;
	cin >> codigoBuscar; // salva na vari�vel o valor do c�digo do produto
	
	system("cls");
	cout << "***********************************************VENDAS*******************************************" << endl;
	cout << "                                                                                                " << endl;
	cout << "        n�Venda        n�Cliente         n�Produto         Quantidade             Total               " << endl;
	cout << "                                                                                                " << endl;
	
	while(retornoVendaCliente == 1){ // la�o de repeti��o responsavel por passar por todos valores do arquivo e verificar qual o c�digo digitado pelo cliente bate e depois adicionar todos seus atribuitos as vari�veis
			if(codigoBuscar == vendaListaCliente[i].codCliente){
					char idVenda = vendaListaCliente[i].codVendas;
					char idCliente = vendaListaCliente[i].codCliente;
					char idProduto = vendaListaCliente[i].codProduto;
					int qtdVendida = atoi(vendaListaCliente[i].quantidadeVenda);
					int totalVendido = atoi(vendaListaCliente[i].totalVenda);
					cout << "        " << idVenda <<"                " << idCliente << "                 " << idProduto << "                 " << qtdVendida << "                    " << totalVendido << "              " << endl;
	
				
			}
		i++;
		retornoVendaCliente = fread(&vendaListaCliente[i], sizeof(vendaTipo), 1, arquivoVenda);
	}	
	fclose(arquivoVenda); // fecha o arquivo vendas.txt
	cout << "************************************************************************************************" << endl;
	cout << endl << endl << endl ;
	cout << "Para voltar ao menu anterior pressione ESC" << endl;
	cout << "Tentar novamente digite qualquer tecla" << endl;
	t = getch(); 
	if(t == 27){ // condi��o para voltar ao menu atenrior caso o usuario aperte ESC
		menuRelatorio();
		
	}
}

void cadastrarProduto(void){ // fun��o responsavel para cadastrar produtos
	int i = 0, back, lerProduto; // vari�veis de controle
	char acessoCod;
	produtoTipo quantidadeAdicionar[tamanho]; // inst�ncia da struct produtoTipo para receber as informa��es do arquivo produto.txt
	char stringIncrement = autoIncrement(1) + '0'; // vari�vel que recebe o increment da fun��o e transforma o int em char
	
	


	arquivoProduto = fopen("produto.txt", "a+"); // abre o arquivo produto.txt para ler/editar
	
	if(arquivoProduto == NULL){ // se der algum erro e retornar NULL , informar na tela que n�o foi possivel abrir/criar o arquivo
		cout << "N�o foi possivel abrir o arquivo";
		exit(0);
	}
	
	int opcao;
	system("cls");
	cout << "                                     ********************CADASTRO DE PRODUTO*****************" << endl;
	cout << "                                     *                                                      *" << endl;
	cout << "                                     ***********SELECIONE QUAL OP��O QUER ACESSAR************" << endl;
	cout << "                                     *                                                      *" << endl;
	cout << "                                     *               1 - CADASTRAR PRODUTO NOVO             *" << endl;
	cout << "                                     *               2 - ADICIONAR A PRODUTO EXISTENTE      *" << endl;
	cout << "                                     *                                                      *" << endl;
	cout << "                                     ********************************************************" << endl;
	cout << "                                                  VOLTAR AO MENU ANTERIOR - APERTE ESC       " << endl;
	opcao = getch(); // recebe a op��o do usuario de cadastrar um novo ou adicionar a um produto existente
	switch(opcao){
		
		case '1': // se o usuario quiser cadastrar um novo
			
			for(int h = 0; h < 1; h++){ // la�o de repeti��o que atribui o c�digo incrementado a struct e o valor 0 a valor vendido
		
				produto[h].codProduto = stringIncrement;
				snprintf(produto[h].qntVendida, 50, "%c", '0' );
		
			}
		
			cout << "Digite o nome do produto" << endl;
			gets(produto[i].nomeProduto);
	
			cout << "Digite o valor do produto" << endl;
			gets(produto[i].valorProduto);
	
			cout << "Digite a quantidade do produto" << endl;
			gets(produto[i].qntEstoque);
			
			
		
			lerProduto = fwrite(produto, sizeof(produtoTipo), 1, arquivoProduto); // fun��o responsavel por escrever no arquivo a struct com os valores digitados pelo usuario
			
			
			
			if(lerProduto == 1){ // verifica��o se foi retornado o valor 1 a vari�vel ler produto, se sim o arquivo foi editado
				cout << "Cadastro efetuado com sucesso" << endl;
			}
		
			
			fclose(arquivoProduto); // fecha o arquivo produto.txt
			cout << "Para voltar ao menu anterior pressione ESC" << endl;
			back = getch();
				if (back == 27){ // verificar para caso o usuario digitou esc para voltar ao menu atenrior
				menuOpcoes();
			}
			break;
		
		case '2': // caso o usuario queira aumentar o estoque de um produto existente 
			
			cout << "Digite o c�digo do produto" << endl;
			cin >> produto[i].codProduto; // recebe o c�digo do produto existente
			acessoCod = produto[i].codProduto;
			getchar();
			cout << "Digite a quantidade de produtos" << endl; 
			gets(quantidadeAdicionar[i].qntEstoque); // recebe a quantidade produtos
			adicionarEstoque(acessoCod, quantidadeAdicionar[i].qntEstoque); // executa a fun��o adicionarEstoque e passa como parametro o c�digo e a quantidade digitadas pelo usuario
		break;	
		
		case 27: // caso o usuario queira voltar ao menu anterior
			menuOpcoes();
			break;
	}
	fclose(arquivoProduto); // fecha o arquivo produto.txt
	
	
}

void cadastrarVenda(void){ // fun��o responsavel por cadastrar venda
	int i = 0, back, lerVenda; // vari�veis de controle
	char codAcessoProduto; // vari�vel para receber o codProduto
	char codAcessoCliente; // vari�vel para receber o codCliente
	char stringIncrement = autoIncrement(3) + '0'; // vari�vel que recebe o incremente executado pela fun��o e passado como parametro o 3 de vendas
	
	arquivoVenda = fopen("vendas.txt", "a+"); // abre o arquivo vendas.txt no modo ler/editar
	
	if(arquivoVenda == NULL){ // se der algum erro e retornar NULL , informar na tela que n�o foi possivel abrir/criar o arquivo
		cout << "N�o foi possivel abrir o arquivo";
		exit(0);
	}
	
	for(int h = 0; h < 1; h++){ // adicionar o valor do incremento a struct
		
		venda[h].codVendas = stringIncrement;
		
	}
			
	cout << "Digite o c�digo do cliente" << endl;
	cin >> venda[i].codCliente; // adicionar a struct o valor do codCliente
	codAcessoCliente = venda[i].codCliente;
	getchar();
	cout << "Digite o c�digo do produto" << endl;
	cin >> venda[i].codProduto; // adicionar a struct o valor do codProduto
	codAcessoProduto = venda[i].codProduto;
	getchar();
	
	cout << "Digite o valor total da venda" << endl;
	gets(venda[i].totalVenda); // adicionar a struct o valor total da venda
	
	cout << "Digite a quantidade de produtos vendidos" << endl;
	gets(venda[i].quantidadeVenda); // adicionar a struct a quantidade de produtos vendidos
	
	adicionarValorProduto(codAcessoCliente, venda[i].totalVenda); // executa a fun��o adicionarValorProduto e passado como parametro o c�digo do produto e o total vendido
	adicionarValorCliente(codAcessoCliente, venda[i].totalVenda); // executa a fun��o adicionarValorCliente e passado como parametro o c�digo do cliente e o tatal vendido
	abaterEstoque(codAcessoProduto, venda[i].quantidadeVenda); // executa a fun��o abaterEstoque e passado como parametro o c�digo do produto e a quantidade vendida
	
	lerVenda = fwrite(&venda[i], sizeof(vendaTipo), 1, arquivoVenda); // fun��o responsavel por escrever no arquivo a struct com os valores digitados pelo usuario
	
	if(lerVenda == 1){ // verifica��o se foi retornado o valor 1 a vari�vel ler produto, se sim o arquivo foi editado
		cout << "Cadastro efetuado com sucesso" << endl;
	}
	
	fclose(arquivoVenda); // fecha o arquivo vendas.txt
	cout << "Para voltar ao menu anterior pressione ESC" << endl;
	back = getch();
		if (back == 27){ // verifica��o caso o usuario digitou ESC para voltar ao menu anterior
		menuOpcoes();
	}

}

void cadastrarFuncionario(void){ // fun��o responsavel por cadastrar funcionarios
	int i = 0, back, lerFuncionario; // vari�veis de controle
	
	arquivoFuncionario = fopen("funcionario.txt", "a+"); // abre o arquivo funcionarios.txt no modo ler/editar
	
	if(arquivoFuncionario == NULL){ // se der algum erro e retornar NULL , informar na tela que n�o foi possivel abrir/criar o arquivo
		cout << "N�o foi possivel abrir o arquivo"; 
		exit(0);
	}
	cout << "Digite o nome do funcionario" << endl;
	gets(funcionario[i].nome); // adiciona a struct o valor digitado pelo usuario
	cout << "Digite o cargo do funcionario" << endl;
	gets(funcionario[i].cargo);// adiciona a struct o valor digitado pelo usuario
	cout << "Digite o salario do funcionario" << endl;
	gets(funcionario[i].salario);// adiciona a struct o valor digitado pelo usuario


	
	lerFuncionario = fwrite(&funcionario[i], sizeof(clienteTipo), 1, arquivoFuncionario); // fun��o responsavel por escrever no arquivo a struct com os valores digitados pelo usuario
	
	if(lerFuncionario == 1){ // verifica��o se foi retornado o valor 1 a vari�vel ler produto, se sim o arquivo foi editado
		cout << "Cadastro efetuado com sucesso" << endl;
	}
	
	fclose(arquivoFuncionario); // fecha o arquivo funcionario.txt
	cout << "Para voltar ao menu anterior pressione ESC" << endl;
	back = getch();
		if (back == 27){ // verifica��o caso o usuario digitou ESC e queira voltar ao menu anterior
		menuOpcoes();
	}
	
}

void cadastrarCliente(void){ // fun��o responsavel por cadastrar clientes
	
	int i = 0 , back, lerCliente;

	arquivoCliente = fopen("cliente.txt", "a+"); // abre o arquivo cliente.txt no modo ler/editar
	
	if(arquivoCliente == NULL){ // se der algum erro e retornar NULL , informar na tela que n�o foi possivel abrir/criar o arquivo
		cout << "N�o foi possivel abrir o arquivo";
		exit(0);
	}
	
	char stringIncrement = autoIncrement(2) + '0'; // adicionar o valor do incremento a struct
	
	for(int h = 0; h < 1; h++){  // adicionar o valor do incremento a struct
		
		cliente[h].idCliente = stringIncrement;
		
	}

	cout << "Digite o nome do cliente" << endl;
	gets(cliente[i].nomeCliente); // adiciona a struct o valor digitado pelo usuario
	
	cout << "Digite o valor que o cliente j� comprou" << endl;
	gets(cliente[i].quantidadeVendida); // adiciona a struct o valor digitado pelo usuario
	
	lerCliente = fwrite (&cliente[i], sizeof (clienteTipo), 1, arquivoCliente);  // fun��o responsavel por escrever no arquivo a struct com os valores digitados pelo usuario
	
	if( lerCliente == 1){ // verifica��o se foi retornado o valor 1 a vari�vel ler produto, se sim o arquivo foi editado
		cout << "Cadastro efetuado com sucesso" << endl;
	}
	
	fclose(arquivoCliente); // fecha o arquivo cliente.txt
	cout << "Para voltar ao menu anterior pressione ESC" << endl;
	back = getch();
	if (back == 27){ // verifica��o caso o usuario digitou ESC e queira voltar ao menu anterior
		menuOpcoes();
	}
}

void Cadastrar(void){ // fun��o responsavel por cadastrar usuarios para o login
	int i = 0, t, lerCadastro;

	arquivo = fopen("login.txt", "a+"); // abre ou cria o arquivo login.txt no modo ler/editar
	
	if(arquivo == NULL){ // se der algum erro e retornar NULL , informar na tela que n�o foi possivel abrir/criar o arquivo
		cout << "N�o foi possivel abrir o arquivo";
		exit(0);
	}
	cout << "Digite um nome de usuario:" << endl;
	gets(maximo[i].user);	// adicionar o valor do incremento a struct
	cout << "Digite uma senha:" << endl;
	gets(maximo[i].senha);// adicionar o valor do incremento a struct
	
	lerCadastro = fwrite (&maximo[i], sizeof (logon), 1, arquivo); // fun��o responsavel por escrever no arquivo a struct com os valores digitados pelo usuario
	
	if( lerCadastro == 1){ // verifica��o se foi retornado o valor 1 a vari�vel ler produto, se sim o arquivo foi editado
		cout << "Cadastro efetuado com sucesso" << endl;
		
	}		
	fclose(arquivo); // fecha o arquivo login.txt
	cout << "Para voltar ao menu anterior pressione ESC" << endl;
	t = getch();
	if(t == 27){ // verifica��o caso o usuario digitou ESC e queira voltar ao menu anterior
		menu();
	}
	
}

void menuOpcoes(void){ // fun��o responsavel por abrir o menu ap�s o login
	char opcao, t; // vari�veis de controle 
	system("cls");
	cout << "                                     ***************SEJA BEM-VINDO A TLC COMPANY*************" << endl;
	cout << "                                     *                                                      *" << endl;
	cout << "                                     ***********SELECIONE QUAL OP��O QUER ACESSAR************" << endl;
	cout << "                                     *                                                      *" << endl;
	cout << "                                     *                   1 - CADASTRAR CLIENTE              *" << endl;
	cout << "                                     *                   2 - CADASTRAR PRODUTO              *" << endl;
	cout << "                                     *                   3 - CADASTRAR FUNCIONARIO          *" << endl;	
	cout << "                                     *                   4 - CADASTRAR VENDA                *" << endl;	
	cout << "                                     *                   5 - GERAR RELATORIO                *" << endl;
	cout << "                                     *                                                      *" << endl;
	cout << "                                     ********************************************************" << endl;
	cout << endl;
	cout << "                                                        LOGOUT - APERTE ESC                  " << endl;
	opcao = getch();
	switch(opcao){ // condi��o para direcionar para onde o cliente deseja ir
		case '1': // caso selecionar executa a fun��o cadastrarCliente
			system("cls");
			cadastrarCliente();
			break;
		case '2': // caso selecionar executa a fun��o cadastrarProduto
			system("cls");
			cadastrarProduto();
			break;
		case '3': // caso selecionar executa a fun��o cadastrarFuncionario
			system("cls");
			cadastrarFuncionario();
			break;
		case '4': // caso selecionar executa a fun��o cadastrarVenda
			system("cls");
			cadastrarVenda();
			break;
		case '5': // caso selecionar executa a fun��o menuRelatorio
			system("cls");
			menuRelatorio();
			break;
		case 27: // caso selecionar executa a fun��o menu()
			system("color 2");
			menu();
			break;
		default:
			cout << "Op��o invalida";
			break;
	}
	

		
		
	}

void menuRelatorio(void){ // fun��o responsavel por abrir o menu de rel�torios
	int opcao;
	system("cls");
	cout << "                                     ***********************RELATORIOS***********************" << endl;
	cout << "                                     *                                                      *" << endl;
	cout << "                                     ***********SELECIONE QUAL OP��O QUER ACESSAR************" << endl;
	cout << "                                     *                                                      *" << endl;
	cout << "                                     *                   1 - VENDAS P/ CLIENTE              *" << endl;
	cout << "                                     *                   2 - VENDAS P/ PRODUTO              *" << endl;
	cout << "                                     *                   3 - TOTAL DE VENDAS                *" << endl;		
	cout << "                                     *                                                      *" << endl;
	cout << "                                     ********************************************************" << endl;
	cout << "                                             PARA VOLTAR AO MENU ANTERIOR - APERTE ESC       " << endl;
	opcao = getch();
	switch(opcao){ // condi��o para direcionar o usuario a op��o desejada
		case '1': // caso selecionar executa a fun��o buscarVendasCliente
			buscarVendasCliente();
			break;
		case '2': // caso selecionar executa a fun��o buscarVendasProduto
			buscarVendasProduto(); 
			break;
		case '3': // caso selecionar executa a fun��o listarVendas
			listarVendas();
			break;
		case 27: // caso selecionado voltar ao menu anterior executando a fun��o menuOpcoes()
			menuOpcoes();
			break;
		default:
			cout << "OPCAO INVALIDA";
			break;
	}
}

void Pesquisar(void){ // fun��o respons�vel por pesquisar no arquivo login.txt se o login foi cadastrado
	int i = 0, retorno = 1, cont= 0; // vari�veis de controle
	char login[50], op, senhas[50]; // variav�is para receber os valores recebidos do usuario
	int t;
	
	arquivo = fopen("login.txt", "r"); // abre o arquivo login.txt em modo leitura
	
	if(arquivo == NULL){ // se der algum erro e retornar NULL , informar na tela que n�o foi possivel abrir/criar o arquivo
		cout << "N�o foi possivel abrir o arquivo";
		exit(0);
	}
	cout << "Digite seu usuario: " << endl;
	gets(login); // salvar a informa��o digitada pelo usuario na vari�vel
	cout << "Digite sua senha: " << endl;
	gets(senhas); // salvar a informa��o digitada pelo usuario na vari�vel
	retorno = fread(&maximo[i], sizeof(logon), 1, arquivo); // fun��o responsavel por ler no arquivo e salvar os dados na struct instanciada
	while(retorno == 1) { // la�o de repeti��o responsavel por passar por todos os logins criados no arquivo
		
		
		if(strcmp(login, maximo[i].user) == 0 && strcmp(senhas, maximo[i].senha) == 0){ // verificar se o que o usuario digitou bate com algum login cadastrado no login.txt, se sim executa a fun��o para ir para o menu
			menuOpcoes();
			cont++;

		}
		i++;
		retorno = fread(&maximo[i], sizeof(logon), 1, arquivo);
		

	}
	if(cont == 0){ // se o la�o de repeti��o n�o encontrar nenhuma compatibilidade, executar os comandos abaixo
		system("color 4"); // muda a cor do cmd
		cout << endl;
		cout << endl;
		cout << "Login invalido" << endl;
		cout << endl;
		cout << endl;
	}	
	
	fclose(arquivo);  // fecha o arquivo login.txt
	cout << "Para voltar ao menu anterior pressione ESC" << endl;
	cout << "Tentar novamente digite qualquer tecla" << endl;
	t = getch();
	if(t == 27){ // verificar se o usuario digitou esc e voltar ao menu anterior
		system("color 2");
		menu();
		
		
	}else{ // se o usuario digitou qualquer coisa sem ser ESC, para tentar efetuar o login novamente
		login[50] = 0;
		system("cls");
		system("color 2");
		Pesquisar();
	}
}

void manualUsuario(void){
	char t;
	system ("color 2");
	printf("                                                      -SEJA BEM VINDO-\n-");
	printf("                                                            AO\n"); 
	printf("                                                   -MANUAL DE INSTRUCOES-\n\n\n");
	
	
	printf("                        O programa consiste em armazenar e calcular suas vendas de acordo com o produto.\n");
	printf("                             No inicio, devemos iniciar criando Login e Senha efetuando seu cadastro.\n");  
	printf("                                                 Exemplo: USER123 e 41875.\n\n");
	
	printf("                        Em seguida, inserir os dados nos campos corretos de acordo com a solicitacao como:\n\n");
	
	printf("                        NOME.\n\n"); 
	
	printf("                        PRODUTO.\n\n"); 
	                    
	printf("                        VALOR DO PRODUTO.\n\n");
	 
	printf("                        QUANTIDADE DO PRODUTO.\n\n");
	
	
	printf("                             Apos a selecao dos dados desejados, os resultados serao imprimidos na tela!\n");
	                     
	printf("                  sendo possivel verficar a quantidade de estoque e quantidade de vendas do produto selecionado\n\n\n");
	
	printf("                                                          *ATENCAO*\n");
	printf("                   letras ou caracteres diferentes de numeros nao serao compreendidos, ocasionando um codigo invalido.\n\n");
	 
	printf("                           ----------------------------------------------------------------------------------\n\n\n\n\n");
		cout << "                                           PARA VOLTAR AO MENU ANTERIOR APERTE - ESC" << endl;
	
	t = getch();
	if(t == 27){ // verifica��o caso o usuario digitou ESC e queira voltar ao menu anterior
		menu();
	}

}

void menu(void){ // fun��o responsavel por abrir o menu principal
	int opcao;
	system("cls");
	cout << "                                 ***************SEJA BEM-VINDO A TLC COMPANY*************" << endl;
	cout << "                                 *                                                      *" << endl;
	cout << "                                 ***********SELECIONE QUAL OP��O QUER ACESSAR************" << endl;
	cout << "                                 *                                                      *" << endl;
	cout << "                                 *                      1 - LOGIN                       *" << endl;
	cout << "                                 *                      2 - CADASTRAR                   *" << endl;
	cout << "                                 *                      3 - MANUAL USUARIO              *" << endl;
	cout << "                                 *                                                      *" << endl;
	cout << "                                 ********************************************************" << endl;
	opcao = getch();
	switch(opcao){ // condi��o para direcionar o usuario na op��o escolhida
		case '1': // caso o usuario escolher essa op��o vai executar a fun��o Pesquisar
			system("cls");
			Pesquisar();
			break;
		case '2': // caso o usuario escolher essa op��o vai executar a fun��o Cadastrar
			system("cls");
			Cadastrar();
			break;
		case '3':
			system("cls");
			manualUsuario();

	}
}

// Inicio Programa

int main() { 
	system("title TLC COMPANY"); // atribui um titulo ao nosso programa
	system("color 2"); // altera a cor do nosso programa
	setlocale(LC_ALL, "Portuguese"); // fun��o responsavel por receber acentua��o
	menu(); // executa a fun��o do menu principal
	

	return 0;
}
