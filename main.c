#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "otfunc.h"
#include "prfunc.h"

//MAIN DO PROGRAMA

int main(){

  //Variável do comando. ans = answer.
  int ans = 0;

  //Enquanto o comando for diferente de -1 (-1 fecha o programa).
  while(ans != -1){
    //Imprime na tela o "cardápio" de comandos.
    printf("Digite os respectivos números para executar ações:\n1 - Criar Tabela\n2 - Listar Tabelas\n3 - Criar Tupla\n4 - Listar Dados\n5 - Pesquisar Valor\n6 - Apagar Tupla\n7 - Apagar Tabela\n-1 - Sair\nComando: ");
    //Usuário escreve o comando desejado.
    scanf("%d", &ans);
    //Se o comando for 1.
    if(ans == 1){

      //Executa a função CriarTabela().
      printf("\n");
      CriarTabela();
      printf("\n");

      //Se o comando for 2.
    } else if(ans == 2){

      //Executa a função ListarTabelas().
      printf("\n");
      ListarTabelas();
      printf("\n");

      //Se o comando for 3.
    }else if(ans == 3){

      //Coleta o nome da tabela com o usuário e executa a função CriarTupla() com parâmetro nt (nome da tabela).
      int tamnt = 0;
      char *nt = NULL;
      char ch;
      LimparEntrada();
      printf("Digite o nome da tabela: ");
      while((ch = getchar()) != '\n'){
        nt = (char *)realloc(nt, sizeof(char)*(tamnt+1));
        nt[tamnt] = ch;
        tamnt++;
      }
      nt = (char *)realloc(nt, sizeof(char)*(tamnt+1));
      nt[tamnt] = '\0';
      printf("\n");
      CriarTupla(nt);
      printf("\n");
      free(nt);

      //Se o comando for 4
    } else if(ans == 4){

      //Coleta o nome da tabela com o usuário e executa a função ListarDados() com parâmetro nt (nome da tabela). 
      int tamnt = 0;
      char *nt = NULL;
      char ch;
      LimparEntrada();
      printf("Digite o nome da tabela: ");
      while((ch = getchar()) != '\n'){
        nt = (char *)realloc(nt, sizeof(char)*(tamnt+1));
        nt[tamnt] = ch;
        tamnt++;
      }
      nt = (char *)realloc(nt, sizeof(char)*(tamnt+1));
      nt[tamnt] = '\0'; 
      printf("\n");
      ListarDados(nt);
      printf("\n");
      free(nt);

      //Se o comando for 5.
    } else if(ans == 5){

      //Coleta o nome da tabela com o usuário e executa a função PesqVal() com parâmetro nt (nome da tabela).
      int tamnt = 0;
      int pk = 0;
      char *nt = NULL;
      char ch;

      LimparEntrada();
      printf("Digite o nome da tabela: ");
      while((ch = getchar()) != '\n'){
        nt = (char *)realloc(nt, sizeof(char)*(tamnt+1));
        nt[tamnt] = ch;
        tamnt++;
      }
      nt = (char *)realloc(nt, sizeof(char)*(tamnt+1));
      nt[tamnt] = '\0';
      printf("\n");
      PesqVal(nt);
      printf("\n");
      free(nt);

      //Se o comando for 6.
    } else if(ans == 6){

      //Coleta o nome da tabela com o usuário e executa a função DelTupla() com parâmetros nt (nome da tabela) e pk (número da Primary Key) que tem a Tupla a ser deletada.
      int tamnt = 0;
      int pk = 0;
      char *nt = NULL;
      char ch;

      LimparEntrada();
      printf("Digite o nome da tabela: ");
      while((ch = getchar()) != '\n'){
        nt = (char *)realloc(nt, sizeof(char)*(tamnt+1));
        nt[tamnt] = ch;
        tamnt++;
      }
      nt = (char *)realloc(nt, sizeof(char)*(tamnt+1));
      nt[tamnt] = '\0';
      printf("Digite a chave primária da tupla que deseja apagar: ");
      scanf("%d", &pk);
      printf("\n");
      DelTupla(nt, pk);
      printf("\n");
      free(nt);

      //Se o comando for 7.
    } else if(ans == 7){

      //Coleta o nome da tabela com o usuário e executa a função ApagarTabela() com parâmetro nt (nome da tabela).
      int tamnt = 0;
      char *nt = NULL;
      char ch;
      LimparEntrada();
      printf("Digite o nome da tabela: ");
      while((ch = getchar()) != '\n'){
        nt = (char *)realloc(nt, sizeof(char)*(tamnt+1));
        nt[tamnt] = ch;
        tamnt++;
      }
      nt = (char *)realloc(nt, sizeof(char)*(tamnt+1));
      nt[tamnt] = '\0';
      printf("\n");
      ApagarTabela(nt);
      printf("\n");
      free(nt);

      //Caso não seja nenhum dos casos
    } else if(ans != -1 && ans != 1 && ans != 2 && ans != 3 && ans != 4 && ans != 5 && ans != 6 && ans != 7){
      //Retorna um problema e dá loop.
      printf("\nComando Inválido\n\n");
    }
  }

  //Agradecimentos!!
  printf("\nObrigado por usar meu programa!\nCreated by: Pedro Paulo\nYear: 2023\n");

  return 0;
}