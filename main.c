#include <stdio.h>
#include <stdlib.h>
#include "funcoes.c"

// cadastro, atualização, busca autor

int main()
{
  menu();
  int op;
  do {
    printf("Digite a sua opcao: ");
    scanf("%d", &op);

    switch(op)
    {
      case 1:
        cadastrar();
        break;
      case 2:
        excluir();
        break;
      case 3:
        atualizar();
        break;
      case 4:
        buscaAutor();
        break;
      case 5:
        buscaTitulo();
        break;
      case 6:
        listar();
        break;
      case 7:
        puts("Obrigado por utilizar o sistema!!!!");
        break;
      default:
        puts("Opcao invalida");
    }
    puts("");
  } while(op != 7);

  system("pause");
  return 0;
}
