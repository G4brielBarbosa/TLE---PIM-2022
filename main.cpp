#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#define tamanho 100

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct Login{
	char user[20];
	char senha[20];
} logon;

FILE *arquivo;

// Funções

void Cadastrar	(void);
void Pesquisar(void);
void menu(void);
// Variaveis Globais

static int qtd = 0;
logon maximo[tamanho];

void Cadastrar(void){
	int i = 0;
	int t;
	int testando;
	arquivo = fopen("teste.txt", "a+");
	
	if(arquivo == NULL){
		cout << "Não foi possivel abrir o arquivo";
		exit(0);
	}
	cout << "Digite um nome de usuario: ";
	gets(maximo[i].user);	
	cout << "Digite uma senha: ";
	gets(maximo[i].senha);
	
	testando = fwrite (&maximo[i], sizeof (logon), 1, arquivo);
	
	if( testando == 1){
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
	cout << "*                   3 - GERAR RELATORIO                *" << endl;
	cout << "*                   4 - VENDAS                         *" << endl;
	cout << "*                                                      *" << endl;
	cout << "********************************************************" << endl;
	opcao = getch();
	switch(opcao){
		case '1':
			cout << "Ir para Tela de Cadastro de cliente";
			break;
		case '2':
			cout << "Ir para Tela de Cadastro de produto";
			break;
		case '3':
			cout << "Ir para Tela de relatorios";
			break;
		case '4':
			cout << "Ir para vendas";
			break;
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
		
		default :
			cout << "oiioioi";
	}
}



int main() {
	int var;
	system("title Login");
	system("color 5F");
	setlocale(LC_ALL, "Portuguese");
	menu();
	
	
	return 0;
}
