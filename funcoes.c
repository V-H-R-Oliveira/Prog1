#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 50

typedef struct ficha
{
  char titulo[SIZE];
  char autor[SIZE];
}FICHA;

void menu()
{
  puts("======================================");
  puts("Bem-vindo ao sistema de biblioteca");
  puts("Digite 1 para cadastrar novos livros");
  puts("Digite 2 para excluir algum livro existente");
  puts("Digite 3 para atualizar o catalogo");
  puts("Digite 4 para buscar um livro por autor");
  puts("Digite 5 para buscar um livro por titulo");
  puts("Digite 6 para listar todo o catalogo");
  puts("Digite 7 para sair do sistema");
  puts("======================================");
}

void cadastrar()
{
  char *arquivoCaminho = "catalogo.txt";
  char op;
  FICHA cad;
  FILE *arquivo = fopen(arquivoCaminho, "ab");

  if(arquivo != NULL)
  {

    do
    {
      getchar();
      printf("Digite o titulo do livro: ");
      fgets(cad.titulo,SIZE,stdin);
      printf("Digite o nome do autor: ");
      fgets(cad.autor,SIZE,stdin);
      fwrite(&cad, sizeof(FICHA), 1, arquivo);
      printf("Deseja continuar o cadastro de livros?: ");
      scanf("%c", &op);
      op = tolower(op);
    }while(op != 'n');
  }else
  {
    fprintf(stderr, "Nao foi possivel abrir esse arquivo");
  }

  fclose(arquivo);
  system("cls");
  menu();
}

void atualizar()
{
  char *arquivoCaminho = "catalogo.txt";
  FICHA cad;
  FILE *arquivo = fopen(arquivoCaminho, "rb+");
  int contador = 0, n;

  if(arquivo != NULL)
  {
    while (fread(&cad, sizeof(FICHA), 1, arquivo) == 1)
    {
      contador++;
    }

    printf("Digite o numero do livro que pretende alterar os dados: ");
    scanf("%d", &n);

    if(n <= contador && n > 0)
    {
      fread(&cad, sizeof(FICHA), 1, arquivo);
      getchar();
      printf("Digite o nome do autor: ");
      fgets(cad.autor, SIZE, stdin);
      printf("Digite o nome do titulo: ");
      fgets(cad.titulo, SIZE, stdin);
      fseek(arquivo, (n - 1) * sizeof(FICHA), SEEK_SET);
      fwrite(&cad, sizeof(FICHA), 1, arquivo);
    }else
    {
      printf("Livro nao foi atualizado");
    }

  }else
  {
    fprintf(stderr, "Nao foi possivel abrir o arquivo");
  }

  fclose(arquivo);
  system("cls");
  menu();
}

void listar()
{
  char *arquivoCaminho = "catalogo.txt";
  FICHA cad;
  FILE *arquivo = fopen(arquivoCaminho, "rb");
  int contador = 1;

  if(arquivo != NULL)
  {
    while (fread(&cad, sizeof(FICHA), 1, arquivo) == 1)
    {
      printf("-------------Livro[%d]--------------------\n", contador);
      printf("Titulo: %s", cad.titulo);
      printf("Autor: %s", cad.autor);
      puts("-----------------------------------------");
      contador++;
    }
  }else
  {
    fprintf(stderr, "Nao foi possivel abrir esse arquivo");
  }

  fclose(arquivo);
  system("pause");
  system("cls");
  menu();
}

void buscaAutor()
{
  char *arquivoCaminho = "catalogo.txt";
  FICHA cad;
  FILE *arquivo = fopen(arquivoCaminho, "rb");
  char nome[SIZE];

  if(arquivo != NULL)
  {
    getchar();
    printf("Digite o nome do autor: ");
    fgets(nome, SIZE, stdin);

    while(fread(&cad, sizeof(FICHA), 1, arquivo) == 1)
    {
      if(strcmp(nome, cad.autor) == 0)
      {
        printf("-------------Livro-----------------------\n");
        printf("Titulo: %s", cad.titulo);
        printf("Autor: %s", cad.autor);
        puts("-----------------------------------------");
      }
    }
  }else
  {
    fprintf(stderr, "Nao foi possivel abrir esse arquivo");
  }

  fclose(arquivo);
  system("pause");
  system("cls");
  menu();
}

void buscaTitulo()
{
  char *arquivoCaminho = "catalogo.txt";
  FICHA cad;
  FILE *arquivo = fopen(arquivoCaminho, "rb");
  char nome[SIZE];

  if(arquivo != NULL)
  {
    getchar();
    printf("Digite o nome do titulo: ");
    fgets(nome, SIZE, stdin);

    while(fread(&cad, sizeof(FICHA), 1, arquivo) == 1)
    {
      if(strcmp(nome, cad.titulo) == 0)
      {
        printf("-------------Livro-----------------------\n");
        printf("Titulo: %s", cad.titulo);
        printf("Autor: %s", cad.autor);
        puts("-----------------------------------------");
      }
    }
  }else
  {
    fprintf(stderr, "Nao foi possivel abrir esse arquivo");
  }

  fclose(arquivo);
  system("pause");
  system("cls");
  menu();
}

void excluir()
{
	char op;
  char *arquivoCaminho = "catalogo.txt";
  FILE *arquivo;
	do
  {
		int contador = 0, n, ex = 0;
		FICHA *cads;
		arquivo = fopen(arquivoCaminho, "rb");
    //Lista livros
		if (arquivo != NULL){
			FICHA cad;
			rewind(arquivo);
			while (fread(&cad, sizeof(FICHA), 1, arquivo)) {
				contador++;
        printf("-------------Livro[%d]--------------------\n", contador);
        printf("Titulo: %s", cad.titulo);
        printf("Autor: %s", cad.autor);
        puts("-----------------------------------------");
			}
      //Excluir livro
			if (contador > 0)
      {
				printf("\n\n");
				printf("Digite o numero do livro que pretende excluir: ");
				scanf("%i", &n);
				if (n > 0 && n <= contador)
        {
					cads = calloc(contador - 1, sizeof(FICHA));
					rewind(arquivo);
					FICHA cad2;
					int id1 = 0, id2 = 0;
					while (fread(&cad2, sizeof(FICHA), 1, arquivo))
          {
						if (id1 != (n - 1))
            {
							cads[id2] = cad2;
							id2++;
						}
						id1++;
					}
					ex = 1;
				} else
        {
					printf("\n\n");
					printf("Numero invalido");
				}
			} else
       {
				printf("\n\n");
				printf("Nao ha nenhum livro cadastrado");
				op = 'n';
			}
		} else
    {
			printf("\n\n");
			printf("Nao foi possivel abrir esse arquivo");
			op = 'n';
		}
		fclose(arquivo);
    //Regrava livros que não foram excluidos
		if (contador > 0)
    {
			if (ex == 1)
      {
				if ((arquivo = fopen(arquivoCaminho, "wb")) != NULL)
        {
					int id;
					for (id = 0; id < contador - 1; id++)
          {
						FICHA cad = cads[id];
						fwrite(&cad, sizeof(FICHA), 1, arquivo);
					}
					printf("\n\n");
					printf("Livro excluido com sucesso.");
				} else
        {
					printf("\n\n");
					printf("Não foi possivel abrir esse arquivo");
					op = 'n';
				}
				fclose(arquivo);
				free(cads);
			}
			fflush(stdin);
			printf("\n\n");
			printf("Excluir outro cadastro? (s/n): ");
			scanf("%c", &op);
		}
	} while(tolower(op) != 'n');
  system("cls");
  menu();
}
