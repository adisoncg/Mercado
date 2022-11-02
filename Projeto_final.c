#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdio.h>
#include <conio.h>

FILE *database;

typedef struct {
	char nom_produto[30];
	char quantidade[4];
	char preco[6];
}cad_prod;

cad_prod produto;

void cadastrar (void);
void alterar (void);
void mostrar (void);
void listar (void);

	//	MENU
int main () {
	setlocale (LC_ALL,"Portuguese");
	int esco_menu;
	char exit = 'n';
	do {
		
		puts("|======================================================================|");
		puts(" Projeto LP1: ADISON COSTA, IGOR VINICIUS, PEDRO HENRIQUE, RENAN GABRIEL");
		puts("|======================================================================|");
		puts("|========================= CONTROLE DE ESTOQUE ========================|");
		puts("|======================================================================|");
		puts("|=========================== MENU PRINCIPAL ===========================|");
		puts("");
		puts("1 - Cadastrar Produto.");
		puts("2 - Alterar Produto.");
		puts("3 - Mostrar Produto.");
		puts("4 - Listar Produtos.");
		puts("5 - Encerrar o Programa.");
		printf("Escolha uma opção: ");
		fflush(stdin);
		scanf("%i", &esco_menu);
	
		switch (esco_menu){	
			case 1: 
				cadastrar ();
				break;
			case 2:
				alterar ();
				break;
			case 3:
				mostrar ();
				break;
			case 4:
				listar (); 
				break;
			case 5:
				do{
					system("cls");
					printf("Deseja sair do programa?:(s/n) ");
					fflush(stdin);
					scanf("%c", &exit);
					if(exit!='s' && exit!='S' && exit!='n' && exit!='N') {
						puts("==============================");
						puts("Valor inválido! Digite S ou N");
						puts("==============================");
						system("pause");
						system("cls");
					}
				} while(exit!='s' && exit!='S' && exit!='n' && exit!='N');
				break;
			default:
				puts("Valor inválido");	
		}
		system("pause");
		system("cls");
	}while(exit == 'n' || exit == 'N');
	
	return(0);
}
	//	CADASTAR PRODUTOS
void cadastrar (void) {
    char escolha;
    char gravar;
    
    if ((database = fopen("estoque.dat", "r+b")) == NULL) {
	       if ((database = fopen("estoque.dat", "w+b")) == NULL) {
	            puts("ERRO!!! BANCO DE DADOS NÃO ENCONTRADO\n");
	            exit(1);
	        }
	    }
    fclose(database);
	
    do {
    	system ("cls");
    	puts ("Cadastro de Produtos\n");
    	database = fopen("estoque.dat","a+b"); 
	        printf ("Nome do produto: ");
	        fflush (stdin);
	        gets (produto.nom_produto);
		        printf ("Quantidade: ");
		        fflush (stdin);
		        gets (produto.quantidade);
			        printf ("Preço por unidade: ");
			        fflush (stdin);
			        gets (produto.preco); 
				        fflush (stdin);
	        system ("cls");
	        puts ("\nPRODUTO A SER ADICIONADO AO ESTOQUE:\n");
	        printf ("Produto: %s\n", produto.nom_produto);
	        printf ("Quantidade: %s unidade(es)\n", produto.quantidade);
	        printf ("Preço: R$%s\n", produto.preco);
	        
	        printf ("\nDeseja realmente adicionar esse produto ao estoque?\n\nDigite (S ou N): ");
	        scanf ("%c", &gravar);
	    	if (gravar == 's' || gravar == 'S') {
	    		puts ("\nProduto Adicionado!\n");
	    		fwrite(&produto, sizeof(cad_prod), 1, database);
			} 
		fclose (database);
	    printf ("Deseja cadastrar outro produto? (S ou N): ");
	    fflush (stdin);
	    scanf ("%c", &escolha);
    } while (escolha == 'S' || escolha == 's');
    
    
}
	//	ALTERAR PRODUTO
void alterar (void) {
	char wnom_produto[30];
	char wquantidade[4];
	char wpreco[6];
	char wativo;
	int a = -1;
	int status = 0, verificar=0;
	system("cls");
	
	if ((database = fopen("estoque.dat", "r+b")) == NULL){
		printf("ERRO!!! BANCO DE DADOS NÃO ENCONTRADO\n");         
    }    
	else {       
		puts("SOLICITANDO O PRODUTO QUE SERÁ ALTERADO...\n");         
		printf("Insira o nome do produto: ");         
		fflush(stdin);         
		gets(wnom_produto);        
		while (fread(&produto, sizeof(cad_prod), 1, database) == 1) {              
		    if (strcmp(produto.nom_produto, wnom_produto) == 0){                  
			verificar = 1;                  
			break;               
			}        
		}
			
        if (verificar == 0) {            
			puts("PRODUTO INEXISTENTE!!!\n");            
			puts("O PROGRAMA SERÁ ENCERRADO...");            
		system("pause");             
		system("cls");         
		}           
		 
		else {          
			puts("\nO PRODUTO FOI ENCONTRADO!!!\n");              
			puts ("DADOS DO PRODUTO A SER ALTERADO...");
			puts("=========================================");            
			printf("Nome do produto encontrado: %s \n", produto.nom_produto);              
			printf("Quantidade: %s \n", produto.quantidade);              
			printf("Preço: %s \n", produto.preco);
			puts("=========================================");
 
		                          
			puts("\nDIGITE AS ALTERAÇÕES DO PRODUTO\n");
		                              
			printf("Digite o nome do produto: ");              
			fflush(stdin);              
			gets(wnom_produto); 
		                
			printf("Digite a quantidade do produto: ");              
			fflush(stdin);              
			gets(wquantidade);
		   
			printf("Digite o preço do produto: ");              
			fflush(stdin);              
			gets(wpreco);  
		               
			strcpy(produto.nom_produto,wnom_produto);              
			strcpy(produto.quantidade,wquantidade);  
			strcpy(produto.preco,wpreco); 
		               
			puts("\n===============ALTERAÇÕES================");              
			printf("Novo Nome do produto: %s \n", produto.nom_produto);              
			printf("Nova quantidade do produto: %s \n", produto.quantidade);  
			printf("Novo preço do produto: %s \n", produto.preco);
			puts("=========================================");
		               
			puts("\nSalvando novos dados...");              
			fseek(database, a*sizeof(cad_prod), SEEK_CUR);              
			status = fwrite(&produto, sizeof(cad_prod), 1, database);              
			fclose(database);              
				if (status == 1) {                 
					puts("Produto cadastrado com SUCESSO!!!\n");                      
				}              
		   else {             
				puts("ERRO NA GRAVAÇÃO DO PRODUTO!!!");                             
		   }
		}
	}
}

	//	MOSTRAR PRODUTOS
void mostrar (void) {
	system("cls"); 
    char wnom_produto[30];
    char wquantidade[4];
    char wpreco[6];
    int search=0; //não encontrado = 0   encontrado = 1
     
    if ((database = fopen("estoque.dat","rb")) == NULL) {
        fclose(database);
        printf("ERRO!!! BANCO DE DADOS NÃO ENCONTRADO\n");
    }
    else {
        database=fopen("estoque.dat","rb"); 
        rewind(database);
        printf("Digite o nome do produto: ");
        fflush(stdin);
        gets(wnom_produto);
             
        while (fread(&produto, sizeof(cad_prod), 1, database) == 1) {
               if (strcmp(produto.nom_produto, wnom_produto) == 0){
                search = 1;
                puts("\nProduto Encontrado!!!");
                puts("=============================");
                printf("Nome do produto: %s \n", produto.nom_produto);
                printf("Quantidade do Produto: %s \n", produto.quantidade);
                printf("Preço: %s \n", produto.preco);
                puts("=============================");
                fclose(database);
                break;
            }
        }
        if (search == 0) {
            puts("PRODUTO NÃO ENCONTRADO!\n");
            fclose(database);
        }
    }
}
	//	LISTAR PRODUTOS
void listar (void) {
	system("cls");
	//Se nenhum produto estiver cadastrado 
    if ((database = fopen("estoque.dat","rb")) == NULL) {//Abre arquivo para leitura
        fclose(database);
        printf("ERRO!!! BANCO DE DADOS NÃO ENCONTRADO\n");
    }
    else{
        database=fopen("estoque.dat","rb"); 
        rewind(database);
        while (fread(&produto, sizeof(cad_prod), 1, database) == 1) {//fread retorna 1 quando dá certo
                printf("Nome do Produto: %s \n", produto.nom_produto);
                printf("Quantidade: %s \n", produto.quantidade);
                printf("Preço por Unidade: %s \n", produto.preco);
                puts("=============================");
        }
        fclose(database);
    }
}
