#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <windows.h>
#include "otfunc.h"
#include "prfunc.h"

#define tamax 100

//Struct da coluna.
typedef struct {
  char *nome;
  char tipo[32];
} col;

//Struct da tabela.
typedef struct {
  char *nome;
  char *chave_nome;
  int qtcol;
  col *coluna;
} tab;

//FUNÇÕES DO PROGRAMA

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//Função de pular a linha.
void PulaLinha(FILE *arquivo, int numlinha){
  //Variáveis da função.
  long int pos = 0;
  int c;

  //Verificação se o número de linha é menor ou igual de 0, caso seja, retorna um erro e finaliza a função.
  if (numlinha <= 0) {
    printf("Número de linha inválido.\n");
    return;
  }

  //Bota o ponteiro do arquivo no início.
  rewind(arquivo);

  //Enquanto pos for menor que numlinha-1 e não está no fim do arquivo (EOF).
  while (pos < numlinha - 1 && (c = fgetc(arquivo)) != EOF) {
    if (c == '\n') {
      pos++;
    }
  }

  //Verificação se atingiu o número desejado de linhas.
  if (pos < numlinha - 1) {
    printf("Número de linha excede o total de linhas no arquivo.\n");
    return;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

void Coleta(FILE *arquivo, char str[], char substr[]){
  //Bota o ponteiro do arquivo no início.
  fseek(arquivo, 0, SEEK_SET);
  //Variável inteiro i.
  int i;
  //Enquanto a linha do arquivo for diferente de NULL.
  while(fgets(str, tamax, arquivo) != NULL){
    //Se str possui substring substr.
    if(strstr(str, substr) != NULL){
      //size1 = tamanho de str.
      int size1 = strlen(str);
      //size2 = tamanho de substr.
      int size2 = strlen(substr)+1;
      //Loop enquanto i for menor que size1.
      for(i=0;i<size1;i++){
        //Separa a substring (DEVE ESTAR NO INÌCIO DA STRING PARA QUE DÊ CERTO) sobrando apenas o resto (sem a substring).
        str[i] = str[i+size2];
      }
      //Variável inteiro que recebe o tamanho novo de str.
      int newsize = strlen(str);
      //Troca \n por \0.
      str[newsize-1] = '\0';
      //Termina o loop.
      break;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//Função para limpar o buffer de entrada.
void LimparEntrada(){
  int c;
  while((c = getchar()) != '\n' && c != EOF);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//Função para criar a tabela.
void CriarTabela(){
  //Variáveis da função.
  FILE *arquivo;
  int qtcoluna, i;
  int tam = 0, teste = 0;
  char *nome_tabela = NULL;
  char c;

  //Imprime a pergunta.
  printf("Escreva o nome da tabela: ");
  //Pede o valor de c.
  scanf("%c", &c);
  //Coleta o valor de c.
  c = getchar();
  //Enquanto c for diferente de \n, no caso, enquanto o usuário não der Enter.
  while(c != '\n'){
    //Realoca o tamanho de memória de nome_tabela.
    nome_tabela = (char *)realloc(nome_tabela, sizeof(char)*(tam+1));
    //caractere tam de nome_tabela é igual ao caractere digitado (c).
    nome_tabela[tam] = c;
    //Variável tam incrementado em 1.
    tam++;
    //Coleta novamente o valor de c para que cada vez mais se forme uma frase.
    c = getchar();
  }
  //Realoca mais uma vez o tamanho de memória de nome_tabela.
  nome_tabela = (char *)realloc(nome_tabela, sizeof(char)*(tam+1));
  //Bota no fim da string nome_tabela o caractere nulo \0 para evitar bugs.
  nome_tabela[tam] = '\0';

  //Cria uma Struct do tipo tab de nome "tabela".
  tab tabela;
  //Variável inteiro nome_tam que recebe o tamanho de nome_tabela.
  int nome_tam = strlen(nome_tabela);

  //Aloca o dado "nome" do struct tabela com tamanho nome_tam.
  tabela.nome = (char *)malloc(sizeof(char)*nome_tam);
  //Dado "nome" do struct tabela igual nome_tabela.
  strcpy(tabela.nome, nome_tabela);

  //Troca os espaços de nome_tabela por underline.
  for(i=0;i<nome_tam;i++){
    if(nome_tabela[i] == ' '){
      nome_tabela[i] = '_';
    }
  }

  //Formata a string para nome_tabela ficar com um .txt no final.
  sprintf(nome_tabela, "%s.txt", nome_tabela);

  //Pergunta a quantidade de colunas.
  printf("Diga quantas colunas terá: ");
  scanf("%d", &qtcoluna);

  //Dado "qtcol" do struct tabela recebe o valor de qtcoluna perguntado anteriormente.
  tabela.qtcol = qtcoluna;
  tabela.coluna = (col *)malloc(sizeof(col)*qtcoluna);

  //Loop que repete qtcoluna vezes (a quantidade de colunas) para coletar e armazenar os dados da coluna na struct coluna dentro da struct tabela.
  for(i=0;i<qtcoluna;i++){
    tam = 0;
    tabela.coluna[i].nome = (char *)malloc(sizeof(char)*(tam+1));
    printf("Digite o nome da coluna %d: ", i+1);

    LimparEntrada();
    while((c = getchar()) != '\n'){
      tabela.coluna[i].nome = (char *)realloc(tabela.coluna[i].nome, sizeof(char)*(tam+1));
      tabela.coluna[i].nome[tam] = c;
      tam++;
    }
    tabela.coluna[i].nome = (char *)realloc(tabela.coluna[i].nome, sizeof(char)*(tam+1));
    tabela.coluna[i].nome[tam] = '\0';

    teste = 0;
    //Teste para saber se o usuário está digitando um tipo válido.
    while(teste == 0){
      printf("Digite o tipo de dados da coluna %d: ", i+1);
      scanf("%32s", tabela.coluna[i].tipo);
      if(strcmp(tabela.coluna[i].tipo, "string") == 0 ||
         strcmp(tabela.coluna[i].tipo, "float") == 0 ||
         strcmp(tabela.coluna[i].tipo, "double") == 0 ||
         strcmp(tabela.coluna[i].tipo, "char") == 0 ||
         strcmp(tabela.coluna[i].tipo, "int") == 0){
        teste = 1;
      } else{
        printf("\nO tipo  '%s' não existe ou não foi configurado para funcionar no programa, por favor, insira um tipo válido. (Tipos válidos: string, char, int, float e double)\n\n", tabela.coluna[i].tipo);
        teste = 0;
      }
    }
  }

  //Pergunta o nome da Primary Key.
  printf("Digite o nome da chave primária: ");
  //Limpa a entrada.
  LimparEntrada();
  //Mesma lógica do nome_tabela, porém para o dado chave_nome da struct tabela.
  tam = 0;
  tabela.chave_nome = NULL;
  while((c = getchar()) != '\n'){
    tabela.chave_nome = (char *)realloc(tabela.chave_nome, sizeof(char)*(tam+1));
    tabela.chave_nome[tam] = c;
    tam++;
  }
  tabela.chave_nome = (char *)realloc(tabela.chave_nome, sizeof(char)*(tam+1));
  tabela.chave_nome[tam] = '\0';

  //Abre o arquivo apenas para escrita.
  arquivo = fopen(nome_tabela, "w");
  //Testa se deu certo de abrir o arquivo.
  if(arquivo == NULL){
    printf("Falha ao abrir o arquivo.\n");
    return;
    //Caso dê certo...
  } else{
    //Formata do jeito escolhido por mim os dados guardados na struct.
      fprintf(arquivo, "Name: %s\nQtCol: %i\n", tabela.nome, tabela.qtcol);
    for(i=0;i<tabela.qtcol;i++){
      fprintf(arquivo, "NCol%i: %s\nTCol%i: %s\n", i+1, tabela.coluna[i].nome, i+1, tabela.coluna[i].tipo);
    }
    fprintf(arquivo, "PK: %s\n", tabela.chave_nome);

    //Fecha o arquivo.
    fclose(arquivo);
    //Loop para liberar a memória do dado "nome" da struct coluna dentro da struct tabela.
    for(i=0;i<tabela.qtcol;i++){
      free(tabela.coluna[i].nome);
    }
    //Libera memória da struct coluna.
    free(tabela.coluna);
    //Libera memória da nome_tabela.
    free(nome_tabela);
    //Libera memória do dado "nome" da struct tabela.
    free(tabela.nome);
    //Libera memória do dado "chave_nome" da struct tabela.
    free(tabela.chave_nome);
  }

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//Função para Listar as tabelas existentes.
void ListarTabelas(){
  //Variáveis da função.
  //Variável DIR que leva ao diretório do executável compilado do código.
  char path[MAX_PATH];
  GetCurrentDirectory(MAX_PATH, path);
  DIR *dir = opendir(path);
  int tamline = 0;
  int i;
  char *dest = NULL;

  //Se a variável dir for igual a NULL.
  if(dir == NULL){
    //Imprime um erro e para a função.
    printf("Erro ao abrir o diretório.\n");
    return;
  }
  
  //Imprime o texto para introdução às tabelas existentes.
  printf("As tabelas existentes são:\n");

  //Cria um struct entry que armazena as informações do diretório e seus arquivos.
  struct dirent *entry;
  //Uma variável FILE.
  FILE *arquivo;

  //Enquanto a leitura do diretório for diferente de NULL.
  while((entry = readdir(dir)) != NULL){
    //Se entry->d_name (nome do arquivo visto no diretório) possuir ".txt" como substring.
    if(strstr(entry->d_name, ".txt") != NULL){
      //Variável tamline é igual a 0.
      tamline = 0;
      //Abre o arquivo de nome entry->d_name (já explicado antes).
      arquivo = fopen(entry->d_name, "r");
      //Se o arquivo for diferente de NULL.
      if(arquivo != NULL){
        char c;
        //Enquanto o caractece c for diferente de \n (percorrendo o arquivo, letra por letra).
        while((c = fgetc(arquivo)) != '\n'){
          //Variável tamline é incrementada em 1
          tamline++;
        }
        //Pega o nome da coluna através dos seguintes passos:
        //Entra no arquivo e tenta achar a formatação "Name:".
        //Armazena a linha na qual "Name:" está presente.
        //Coleta apenas o conteúdo de "Name:".
        //Imprime o conteúdo para ser exibido no programa.
        char SSN[] = "Name: ";
        char line[tamline+1];
        rewind(arquivo);
        fgets(line, tamline+1, arquivo);
        dest = strstr(line, SSN);
        if(dest != NULL){
          size_t SSNlen = strlen(SSN);
          memmove(dest, dest+SSNlen, strlen(dest+SSNlen)+1);
          int tdest = strlen(dest);
          dest[tdest] = '\0';
          printf("%s\n", dest);
        }
      } else{
        printf("Não foi possível abrir o arquivo.");
        return;
      }
      //Fecha o arquivo.
      fclose(arquivo);
    }
  }
  //Fecha o diretório.
  closedir(dir);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//Função para criar uma tupla para uma determinada tabela.
void CriarTupla(char nome_tabela[]){
  //Variáveis da função.
  FILE *arquivo;
  int pks, i, j = 0;
  int size = strlen(nome_tabela);
  char palavra[tamax], palavra2[tamax], palavra3[tamax], palavra4[tamax], prov[tamax], qtup_t[tamax];
  char qtup_c, charact, *frase = NULL;
  int test = 1, qtup, t = 0;

  //Loop enquanto i for menor que size (tamanho do nome_tabela).
  for(i=0;i<size;i++){ 
    //Transforma os espaços de nome_tabela em underline.
    if(nome_tabela[i] == ' '){
      nome_tabela[i] = '_';
    }
  }
  //Concatena nome_tabela com .txt para criar um arquivo.txt
  strcat(nome_tabela, ".txt");

  //Abre o arquivo com o nome_tabela em leitura e escrita, porém sem criar arquivo novo.
  arquivo = fopen(nome_tabela, "r+");
  //Se arquivo for igual a NULL, retorna um erro de que o arquivo não existe e finaliza a função.
  if(arquivo == NULL){
    printf("Esse arquivo não existe!\n");
    return;
  }

  //Criação das variáveis string com as formatações do arquivo para quantidade de colunas (QtCol), Primary Key (PK), quantidade de tuplas (QtTup).
  char ssq[] = "QtCol:";
  char ssk[] = "PK:";
  char sst[] = "QtTup:";

  //Uso da função Coleta para pegar o conteúdo de QtCol (quantidade de colunas).
  Coleta(arquivo, palavra, ssq);
  //Transforma o conteúdo de QtCol em inteiro e armazena na variável ncol.
  int ncol = atoi(palavra);
 
  //Fechando arquivo.
  fclose(arquivo);
  //Abrindo arquivo de nome nome_tabela em leitura e escrita, porém sem criar arquivo novo.
  arquivo = fopen(nome_tabela, "r+");
  
  //Uso da Função Coleta para pegar o conteúdo de PK (Primary Key).
  Coleta(arquivo, palavra3, ssk);

  //Enquanto não chegar no fim do arquivo (EOF).
  while(fscanf(arquivo, "%s", palavra4) != EOF){
    //Se palavra4 e sst (QtTup) forem iguais.
    if(strcmp(palavra4, sst) == 0){
      //Coleta o conteúdo de QtTup.
      fscanf(arquivo, "%s", palavra4);
      //Variável test recebe 1.
      test = 1;
      //Para o loop.
      break;
      //Caso não.
    } else{
      //Variável test recebe 0.
      test = 0;
    }
  }

  //Variável inteiro qttLine recebe 5+(ncol*2) ()
  int qttLine = 5+(ncol*2);
  //Transforma o conteúdo de QtTup em inteiro e armazena na variável qtup.
  qtup = atoi(palavra4);

  //Se a variável test for diferente de 0.
  if(test != 0){
    //Coleta a última linha (que possui o conteúdo de QtTup, que seria a quantidade de tuplas) e tokeniza para separar de "QtTup: ". 
    char delim[] = " ";
    char *token;
    fseek(arquivo, 0, SEEK_SET);
    char tl[tamax];
    while(fgets(tl, tamax, arquivo) != NULL){
      strcpy(qtup_t, tl);
    }

    token = strtok(qtup_t, delim);
    token = strtok(NULL, delim); 
    strcpy(qtup_t, token);
  }
  
  //Transforma qtup_t (conteúdo de QtTup da última linha) em inteiro e armazena na variável qtup.
  qtup = atoi(qtup_t);

  //Loop enquanto i for menor que ncol.
  for(i=0;i<ncol;i++){
    //Volta o ponteiro do arquivo para o início.
    fseek(arquivo, 0, SEEK_SET);
    //Formata uma string e armazena em ssq.
    sprintf(ssq, "NCol%d:", i+1);
    //Coleta o valor de ssq no arquivo.
    Coleta(arquivo, palavra, ssq);
    //Formata uma string e armazena em ssq.
    sprintf(ssq, "TCol%d:", i+1);
    //Coleta o valor de ssq no arquivo.
    Coleta(arquivo, palavra2, ssq);
    
    //Se i for igual a 0.
    if(i == 0){
      //Pergunta qual o valor da Primary Key, abre chaves ("{}") e analisa se o valor já existe.
      printf("%s: ", palavra3);
      int pk = 0;
      scanf("%d", &pk);
      if(qtup > 0){
        for(j=0;j<qtup;j++){
          frase = NULL;
          t = 0;
          fseek(arquivo, 0, SEEK_SET); 
          PulaLinha(arquivo, (4+(ncol*2)+((ncol+4)*j)));
          while((charact = fgetc(arquivo)) != '\n'){
            frase = (char *)realloc(frase, sizeof(char)*(t+1));
            frase[t] = charact;
            t++;
          }
          frase = (char *)realloc(frase, sizeof(char)*(t+1));
          frase[t] = '\0';
          
          char delim[] = " ";
          char *token;
          token = strtok(frase, delim);
          token = strtok(NULL, delim);
          strcpy(frase, token);
          int cmp = atoi(frase);
          if(pk == cmp){
            printf("Chave Primária já existente!\n");
            free(frase);
            return;
          }
          free(frase);
        }
      }
      fseek(arquivo, 0, SEEK_END);
      fprintf(arquivo, "%s: %d\n{\n", palavra3, pk);
    }

    //Se a coluna atual for do tipo string.
    if(strcmp(palavra2, "string") == 0){
      //Pede o dado dessa coluna em string.
      int tam = 0;
      char c;
      char *dadostr = NULL;
      printf("Digite o dado da coluna %d (%s): ", i+1, palavra);
      if(i == 0){
        LimparEntrada();
      }
      while((c = getchar()) != '\n'){
        dadostr = (char *)realloc(dadostr, sizeof(char)*(tam+1));
        dadostr[tam] = c;
        tam++;
      }
      dadostr = (char *)realloc(dadostr, sizeof(char)*(tam+1));
      dadostr[tam] = '\0';

      fseek(arquivo, 0, SEEK_END);
      fprintf(arquivo, "ColD%d: %s\n", i+1, dadostr);
      free(dadostr);
      //Caso não seja string, mas seja inteiro.
    } else if(strcmp(palavra2, "int") == 0){
      //Pede o dado dessa coluna em inteiro.
      int dadoint;
      printf("Digite o dado da coluna %d (%s): ", i+1, palavra);
      scanf("%d", &dadoint);
      fseek(arquivo, 0, SEEK_END); 
      fprintf(arquivo, "ColD%d: %d\n", i+1, dadoint);
      LimparEntrada();
      //Caso não seja string nem inteiro, mas seja char.
    } else if(strcmp(palavra2, "char") == 0){
      //Pede o dado dessa coluna em char.
      char dadochar;
      printf("Digite o dado da coluna %d (%s): ", i+1, palavra);
      scanf(" %c", &dadochar);
      fseek(arquivo, 0, SEEK_END); 
      fprintf(arquivo, "ColD%d: %c\n", i+1, dadochar);
      LimparEntrada();
      //Caso não seja string, inteiro nem char, mas seja float.
    } else if(strcmp(palavra2, "float") == 0){
      //Pede o dado dessa coluna em float.
      float dadofloat;
      printf("Digite o dado da coluna %d (%s): ", i+1, palavra);
      scanf("%f", &dadofloat);
      fseek(arquivo, 0, SEEK_END); 
      fprintf(arquivo, "ColD%d: %0.2f\n", i+1, dadofloat);
      LimparEntrada();
      //Caso não seja string, inteiro, char nem float, mas seja double.
    } else if(strcmp(palavra2, "double") == 0){
      //Pede o dado dessa coluna em double.
      double dadodouble;
      printf("Digite o dado da coluna %d (%s): ", i+1, palavra);
      scanf("%lf", &dadodouble);
      fseek(arquivo, 0, SEEK_END); 
      fprintf(arquivo, "ColD%d: %0.2lf\n", i+1, dadodouble);
      LimparEntrada();
    }
    //Fecha o arquivo.
    fclose(arquivo);
    //Abre o arquivo com nome nome_tabela em leitura e escrita, porém sem criar arquivo novo.
    arquivo = fopen(nome_tabela, "r+");
  }
 
  //Bota o ponteiro do arquivo no fim.
  fseek(arquivo, 0, SEEK_END);
  //Fecha chaves e pula linha
  fprintf(arquivo, "}\n");

  //Se a variável test for igual a 0.
  if(test == 0){
    //Bota o ponteiro do arquivo no fim.
    fseek(arquivo, 0, SEEK_END);
    //Digita "QtTup: 1" no arquivo para definir a quantidade de Tuplas e ter um controle melhor.
    fprintf(arquivo, "QtTup: 1\n");
    //Caso não.
  } else{
    //Bota o ponteiro do arquivo no fim.
    fseek(arquivo, 0, SEEK_END);
    //Digita "QtTup: x", tal que x é a quantidade de tuplas (qtup) + 1 para que seja diferente do caso anterior (QtTup: 1).
    fprintf(arquivo, "QtTup: %d\n", qtup+1);
  }

  //Fecha o arquivo.
  fclose(arquivo);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//Função para listar os dados de uma tabela.
void ListarDados(char nome_tabela[]){
  //Variáveis da função.
  FILE *arquivo;
  int qtup = 0, i, j, k, l;
  int size = strlen(nome_tabela);
  char delim[] = " ";
  char qtup_t[tamax], pkn[tamax], palavra[tamax];
  char tst1[tamax], tst2[tamax];
  char *token;

  //Trocar os espaços por underline.
  for(i=0;i<size;i++){
    if(nome_tabela[i] == ' '){
      nome_tabela[i] = '_';
    }
  }

  //Concatena o nome da tabela com .txt.
  strcat(nome_tabela, ".txt");

  //Abre o arquivo apenas para leitura e testando sua existênia, caso não exista, para a função.
  arquivo = fopen(nome_tabela, "r");
  if(arquivo == NULL){
    printf("Esse arquivo não existe.\n");
    return;
  }

  //Pega a informação da ultima linha (que seria a quantidade de tuplas, no caso QtTup).
  while(fscanf(arquivo, "%s", qtup_t) != EOF);
  //O valor da ultima linha (conteúdo de QtTup) transoformado em inteiro e armazenado na variável qtup.
  qtup = atoi(qtup_t);

  //O ponteiro do arquivo irá para o início dele.
  fseek(arquivo, 0, SEEK_SET);
  //Pega o conteúdo de QtCol (Quantidade de colunas), transforma em inteiro e armazena na variável ncol.
  char ssq[] = "QtCol:";
  Coleta(arquivo, palavra, ssq);
  int ncol = atoi(palavra);

  //O ponteiro do arquivo irá para o início dele.
  fseek(arquivo, 0, SEEK_SET);
  //Utilizando a função PulaLinha para pular para a linha desejada, que seria a linha na qual mostra o nome da Primary Key.
  PulaLinha(arquivo, 3+(ncol*2));
  fgets(pkn, tamax, arquivo);
  //Tokeniza para poder separar o "PK:" do nome do ID.
  token = strtok(pkn, delim);
  token = strtok(NULL, delim);
  //Armazena o valor do token na variável pkn.
  strcpy(pkn, token);
  //Troca o \n por \0.
  pkn[strlen(pkn)-1] = '\0';
  //Imprime o nome da Primary Key com uma formatação na string.
  printf(" %-10s| ", pkn);

  //Loop enquanto j for menor que o número de colunas (ncol).
  for(j=0;j<ncol;j++){
    //Define uma variável string com "NColX:" como conteúdo, pois é a formatação base do nome das colunas em meu arquivo.
    char ssnc[] = "NColX:";
    //Retorna o ponteiro do arquivo para o início.
    fseek(arquivo, 0, SEEK_SET);
    //Pula para a linha na qual possui o nome da coluna e multiplica por j, pois a cada número de j é um nome diferente da coluna.
    PulaLinha(arquivo, 3+(2*j));
    //pega a linha e armazena na variável tst2.
    fgets(tst2, tamax, arquivo);
    //sizestr = tamanho de tst2 (string).
    int sizestr = strlen(tst2);
    //sizesstr = tamanho de ssnc (substring) + 1 por causa do espaço de "NColX: ".
    int sizesstr = strlen(ssnc)+1;
    //Loop enquanto k for menor que o tamanho de tst2.
    for(k=0;k<sizestr;k++){
      //Ele irá armazenar char por char as letras após o "NColX: ".
      tst2[k] = tst2[k+sizesstr];
    }
    //sizetst2 = Tamanho de tst2 após a separação.
    int sizetst2 = strlen(tst2);
    //Loop enquanto k for menor que o tamanho de tst2 (sizetst2).
    for(k=0;k<sizetst2;k++){
      //Troca o \n da string pelo \0 para evitar pulo de linha indesejado.
      if(tst2[k] == '\n'){
        tst2[k] = '\0';
      }
    }
    //Imprime com a formatação.
    printf(" %-20s| ", tst2);
  }

  //Loop enquanto i for menor que qtup (quantidade de tuplas).
  for(i=0;i<qtup;i++){
    //Variáveis do loop.
    char c;
    int pk; 
    
    //Retorna o ponteiro para o inicio do arquivo.
    fseek(arquivo, 0, SEEK_SET);
    //Pula para a linha desejada (a linha onde fica o número da Primary Key) e multiplica por i pois altera o número do Primary Key conforme o i é incrementado.
    PulaLinha(arquivo, (4+(ncol*2))+((ncol+4)*i));
    //Pega a linha desejada e armazena na variável tst1.
    fgets(tst1, tamax, arquivo);
    //Tokeniza para pegar apenas o número.
    token = strtok(tst1, delim);
    token = strtok(NULL, delim);
    //Armazena o valor do token no tst1.
    strcpy(tst1, token);
    //Transforma tst1 em int e armazena na variável pk. 
    pk = atoi(tst1);
    //Imprime com a formatação.
    printf("\n %-10d|", pk);
    //Loop enquanto j for menor que ncol (número de colunas).
    for(j=0;j<ncol;j++){
      //Define uma variável string com "ColDX:" como conteúdo, pois é a formatação base dos dados da coluna no meu arquivo.
      char sscol[] = "ColDX:";
      //Criação de uma variável string de tamanho "tamax" (100).
      char prov[tamax];
      //Volta o ponteiro do arquivo para o início.
      fseek(arquivo, 0, SEEK_SET);
      //Pula para a linha desejada, que é a linha do dado desejado.
      //É multiplicado por i para que troque os dados de coluna em coluna e é incrementado ao j para que ele acesse os diferentes dados da coluna atual.
      PulaLinha(arquivo, 6+(ncol*2)+(ncol+4)*i+j);
      //Pega a linha e guarda na variável prov.
      fgets(prov, tamax, arquivo);
      //mesma lógica do anterior.
      int sizestr = strlen(prov);
      int sizesstr = strlen(sscol)+1;
      for(k=0;k<sizestr;k++){
        prov[k] = prov[k+sizesstr];
      }
      int sizeprov = strlen(prov);
      for(k=0;k<sizeprov;k++){
        if(prov[k] == '\n'){
          prov[k] = '\0';
        }
      }
      //Imprime com a formatação.
      printf(" %-21s|", prov);
    }
  }
  //Pula uma linha.
  printf("\n");

  //Fecha o arquivo.
  fclose(arquivo);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

void PesqVal(char nome_tabela[]){
  //Variáveis da função.
  FILE *arquivo;
  int qcol = 0, answer = 0, qtup = 0, tam = 0, check = 0, i, j, k;
  int size = strlen(nome_tabela);
  char palavra[tamax];
  char ssq[] = "QtCol:", ssc[] = "NCol:", sst[] = "TCol:", nil[] = ".";
  char c;
  char *val = NULL;

  //Troca os espaços por underline.
  for(i=0;i<size;i++){
    if(nome_tabela[i] == ' '){
      nome_tabela[i] = '_';
    }
  }
  //Concatena o nome_tabela com .txt para criar um nome_tabela.txt.
  strcat(nome_tabela, ".txt");

  //Abrir arquivo com o nome nome_tabela apenas para leitura, sendo que, não cria arquivo novo.
  arquivo = fopen(nome_tabela, "r");
  //Checa se existe o arquivo, se não, retorna um erro e para a função.
  if(arquivo == NULL){
    printf("Esse arquivo não existe.\n");
    return;
  }

  //Coleta o valor de QtCol (quantidade de colunas).
  Coleta(arquivo, palavra, ssq);
  //Transforma o valor de QtCol em inteiro e armazena na variável qcol.
  qcol = atoi(palavra);

  //Imprime o texto para mostrar as colunas disponíveis.
  printf("As colunas disponíveis são:\n");
  //Loop para pegar os conteúdos de NColX (Nome da coluna x, tal que x é o número da coluna).
  for(i=0;i<qcol;i++){
    sprintf(ssc, "NCol%d:", i+1);
    Coleta(arquivo, palavra, ssc);
    printf("Coluna %d: %s\n", i+1, palavra);
  }
  //Pula linha.
  printf("\n");

  //Pequena lógica para o usuário escolher o número da coluna na qual ele deseja pesquisar o dado.
  printf("Escolha uma das colunas (apenas o número): ");
  scanf("%d", &answer);
  sprintf(sst, "TCol%d:", answer);
  Coleta(arquivo, palavra, sst);
  //Se a escolha da coluna for igual ou menor que 0 (não pode ser igual pois não há uma "Coluna 0", começa no 1, NCol1 e por aí vai)
  //(não pode ser menor que zero, pois não há "Coluna -1" ou "Coluna -2", somente igual ou acima de 1).
  //Ou se a escolha for maior que a quantidade de colunas (qcol) (se há apenas 4 colunas, não seria certo eu querer a coluna 6, ela nem existe).
  if(answer <= 0 || answer > qcol){
    //Mensagem de erro e finaliza a função (Coluna inválida pelos motivos citados anteriormente).
    printf("Coluna inválida.\n");
    return;

    //Se o tipo da coluna (TColx, tal que x é o número da coluna, como mostrado na lógica acima dos últimos comentários, os que estão antes desse...) não for string.
  } else if(strcmp(palavra, "string") != 0){
    //Mensagem de erro e finaliza a função (A pesquisa só funciona com colunas do tipo string).
    printf("A coluna deve ser do tipo STRING!\n");
    return;
  }

  //Pede ao usuário qual será o dado a ser pesquisado.
  printf("Qual o dado para pesquisa? (apenas strings): ");
  LimparEntrada();
  while((c = getchar()) != '\n'){
    val = (char *)realloc(val, sizeof(char)*(tam+1));
    val[tam] = c;
    tam++;
  }
  val = (char *)realloc(val, sizeof(char)*(tam+1));
  val[tam] = '\0';

  //Coleta o valor da última linha do arquivo, que é a quantidade de tuplas, pois no fim do arquivo há o valor de QtTup (quantidade de tuplas).
  while(fscanf(arquivo, "%s", palavra) != EOF);
  //Transforma o valor em int e armazena na variável qtup.
  qtup = atoi(palavra);

  //Loop para fazer os testes.
  for(i=0;i<qcol;i++){
    if(answer == i+1){
      check = 0;
      //Imprimir a mensagem que mostrará os valores maiores.
      printf("Valor(es) maior(es): ");
      //Loop para coletar os dados da coluna da numeração almejada pelo usuário. Lógica tendo em vista a formatação do meu arquivo (Formatação do arquivo mostrado no final do código).
      for(j=0;j<qtup;j++){
        PulaLinha(arquivo, ((6+(qcol*2))+((qcol+4)*j))+i);
        for(k=0;k<2;k++){
          //Pega o valor do dado, pois no primeiro Loop, irá pegar o ColDX, tal que x é o número da coluna na qual esse dado está. E no segundo loop irá pegar o conteúdo de ColDX.
          fscanf(arquivo, "%s", palavra);
        }
        //Se a comparação das duas strings for maior que zero, significa que o dado da coluna é maior que o dado da pesquisa.
        if(strcmp(val, palavra) > 0){
          printf(" |%s| ", palavra);
        } else{
          check++;
        }
      }
      //Se a variável check for igual a quantidade de tuplas, é sinal que nenhum valor é maior que o da pesquisa.
      if(check == qtup){
        printf(" Nenhum.\n");
      } else{
        printf(".\n");
      }

      check = 0;
      //Imprimir mensagem que mostrará os valores iguais.
      printf("Valor(es) igual(is): ");
      //Similar à anterior.
      for(j=0;j<qtup;j++){
        PulaLinha(arquivo, ((6+(qcol*2))+((qcol+4)*j))+i);
        for(k=0;k<2;k++){
          fscanf(arquivo, "%s", palavra);
        }
        //Se a comparação das duas strings for igual a zero, significa que o dado da coluna é igual ao dado da pesquisa.
        if(strcmp(val, palavra) == 0){
          printf(" |%s| ", palavra);
        } else{
          check++;
        }
      }
      //Se a variável check for igual a quantidade de tuplas, é sinal que nenhum valor é maior que o da pesquisa.
      if(check == qtup){
        printf(" Nenhum.\n");
      } else{
        printf(".\n");
      }   

      check = 0;
      //Imprimir mensagem que mostrará os valores iguais.
      printf("Valor(es) menor(es): ");
      //Similar à anterior.
      for(j=0;j<qtup;j++){
        PulaLinha(arquivo, ((6+(qcol*2))+((qcol+4)*j))+i);
        for(k=0;k<2;k++){
          fscanf(arquivo, "%s", palavra);
        }
        //Se a comparação das duas strings for menor que zero, significa que o dado da coluna é menor que o dado da pesquisa.
        if(strcmp(val, palavra) < 0){
          printf(" |%s| ", palavra);
        } else{
          check++;
        }
      }
      //Se a variável check for igual a quantidade de tuplas, é sinal que nenhum valor é menor que o da pesquisa.
      if(check == qtup){
        printf(" Nenhum.\n");
      } else{
        printf(".\n");
      }
    }
  }

  
  //Fecha arquivo.
  fclose(arquivo);
  //Libera a memória da variável val.
  free(val);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//Função para deletar uma tupla.
void DelTupla(char nome_tabela[], int primkey){
  //Variáveis da função.
  FILE *arquivo;
  FILE *temp;
  int posatual = 1, posdel1 = 0, posdel2 = 0;
  int qcol = 0, qtup = 0, check = 0, qcont = 1, i;
  int size = strlen(nome_tabela);
  char linha[tamax], palavra[tamax], qtcol[tamax];
  char ssk[] = "PK:", ssc[] = "QtCol:", nil[] = ".";

  //Transformando os espaços em underlines.
  for(i=0;i<size;i++){
    if(nome_tabela[i] == ' '){
      nome_tabela[i] = '_';
    }
  }

  //Concatena o nome_tabela sem os espaços com o ".txt" para gerar um nome de arquivo.txt.
  strcat(nome_tabela, ".txt");
  
  //Abre o arquivo com o nome_tabela em modo apenas leitura ("r") e testa se existe o arquivo.
  arquivo = fopen(nome_tabela, "r");
  //Caso não tenha, retorna uma mensagem de erro e encerra a função.
  if(arquivo == NULL){
    printf("Esse arquivo não existe.\n");
    return;
  }
  //Abre um arquivo de nome "temporario.txt" em modo de apenas escrita ("w").
  temp = fopen("temporario.txt", "w");

  //Usa a função Coleta para pegar o conteúdo de PK dentro do arquivo.
  //Dentro do arquivo, em uma certa linha há "PK: nome_do_pk", logo, quero apenas o "nome_do_pk".
  //PK = Primary Key.
  Coleta(arquivo, palavra, ssk);
  //Formata a string para receber o conteúdo do PK (palavra) e o número da chave dada pelo usuário.
  sprintf(ssk, "%s: %d", palavra, primkey);

  //Usa a função Coleta para pegar o conteúdo de QtCol dentro do arquivo.
  //Dentro do arquivo, em uma certa linha há "QtCol: quantidade_de_colunas", logo, quero apenas o "quantidade_de_colunas".
  //QtCol = Quantidade de Colunas.
  Coleta(arquivo, palavra, ssc);
  //Transforma o conteúdo de QtCol em inteiro e armazena em qcol.
  qcol = atoi(palavra);

  //Pega o conteúdo da última linha. Que é o conteúdo de QtTup.
  //QtTup é a quantidade de tuplas que a tabela tem, ele fica sempre no final das informações da tupla, logo, o último deles fica no fim do arquivo.
  while(fscanf(arquivo, "%s", palavra) != EOF);
  //Transforma o conteúdo de QtTup em inteiro e armazena em qtup.
  qtup = atoi(palavra);

  //Volta o ponteiro para o início do arquivo.
  fseek(arquivo, 0, SEEK_SET);
  //Enquanto a linha do arquivo não for NULL.
  while(fgets(linha, tamax, arquivo) != NULL){
    //Variável que armazena o tamanho da string "linha".
    int lintam = strlen(linha);
    //Loop até que i seja menor que o tamanho da string "linha".
    for(i=0;i<lintam;i++){
      //If apenas para substituir o '\n' da string por '\0' para que não pule a linha indesejadamente.
      if(linha[i] == '\n'){
        linha[i] = '\0';
      }
    }
    //Se a string "linha" e a string "ssk" forem iguais.
    if(strcmp(linha, ssk) == 0){
      //Variável posdel1 vai ser igual a posição atual do ponteiro.
      posdel1 = posatual;
      //Variável posdel2 vai ser igual a posição atual do ponteiro + a quantidade de colunas + 3.
      //Isso tudo para definir as informações a serem apagadas (irá da posatual até a posatual+blablabla).
      posdel2 = posatual+(qcol+3);
      //Para o loop.
      break;
    }
    //Incrementa na posatual para "simular" o ponteiro do arquivo.
    posatual++;
  }

  //Define a postual para 1.
  posatual = 1;

  //Volta o ponteiro do arquivo para o início.
  fseek(arquivo, 0, SEEK_SET);
  //Enquanto a linha for diferente de NULL.
  while(fgets(linha, tamax, arquivo) != NULL){
    //Variável check recebe 0.
    check = 0;
    //Se posatual for menor que posdel1 ou for maior que posdel2 (área na qual defini para ser deletada, será ignorada).
    if(posatual < posdel1 || posatual > posdel2){
      //Loop enquanto i for menor que qtup (quantidade de tuplas).
      for(i=0;i<qtup;i++){
        //Se a posatual for diferente dessa equação (equação que mostra as posições dos QtTup falados anteriormente).
        if(posatual != (((qcol*2)+4)+(qcol+3))+(qcol+4)*i){
          //check é incrementado em 1.
          check++;
        }
      }
      //Se check for igual a quantidade de tuplas (qtup). Isso mostra que a posatual é menor que posdel1 ou maior que posdel2 e não está na posição de algum "QtTup".
      if(check == qtup){
        //Escreverá no arquivo temporário a linha da posatual.
        fprintf(temp, "%s", linha);
        //Caso não.
      } else{
        //Vamos seguir a seguinte lógica, se a cada tupla, no fim das informações tem um QtTup indicando a quantidade de tuplas naquele momento, logo...
        //Se apagamos uma certa Tupla, essa info "QtTup: x" será excluída, sendo assim, no fim do arquivo terá dizendo que há x QtTup's, sendo que...
        //Depois de apagar uma Tupla, terá x-1 QtTup's, porém, sem fazer isso que estou fazendo, irá indicar que tem x QtTup's ao invés de x-1.
        /*
        Exemplo: 3 tuplas
        PK: 1.
        {
        Dados da tupla 1
        {
        QtTup: 1.
        PK: 2.
        }
        Dados da tupla 2.
        }
        QtTup: 2.
        PK: 3.
        {
        Dados da tupla 3.
        }
        QtTup 3.

        Se apagar a Tupla de PK: 2, sem a lógica que apliquei, ficaria assim:

        PK: 1.
        {
        Dados da tupla 1
        {
        QtTup: 1.
        PK: 3.
        {
        Dados da tupla 3.
        }
        QtTup 3.

        Percebe que na ultima linha do arquivo mostra que tem 3 tuplas? Mas agora só tem 2, logo, no fim deveria ser QtTup: 2.
        Pois é, a minha lógica evita isso, e ordena novamente os QtTup. Maneira possivelmente longa? Apenas na lógica, no código é bem econômico.
        */
        fprintf(temp, "QtTup: %d\n", qcont);
        //Incrementa a variável qcont (variável de ordenação dos QtTup) em 1.
        qcont++;
      }
    }
    //Incrementa a variável posatual em 1.
    posatual++;
  } 

  //Fecha o arquivo "arquivo".
  fclose(arquivo);
  //Fecha o arquivo "temp".
  fclose(temp);

  //Remove o arquivo de nome "nome_tabela" para deletar as informações anteriores.
  remove(nome_tabela);
  //Renomeia o arquivo de nome "temporario.txt" que possui as informações novas, após apagar a tupla desejada, pelo "nome_tabela", criando uma impressão de que na verdade...
  //Apenas as informações foram apagadas, ao invés de movidas para um novo arquivo. Maneira mais simples que pensei de executar uma exclusão de informações de um arquivo.
  rename("temporario.txt", nome_tabela);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//Função para apagar a tabela.
void ApagarTabela(char nome_tabela[]){
  //Variáveis da função.
  FILE *arquivo;
  int i;
  int size = strlen(nome_tabela);

  //Loop para trocar os espaços de "nome_tabela" por underlines.
  for(i=0;i<size;i++){
    if(nome_tabela[i] == ' '){
      nome_tabela[i] = '_';
    }
  }
  //Concatena o "nome_tabela" já alterado com ".txt" para criar um nome de um arquivo.txt.
  strcat(nome_tabela, ".txt");

  //Abre um arquivo com o nome "nome_tabela" apenas para leitura.
  arquivo = fopen(nome_tabela, "r");
  //Se arquivo retornar NULL, mostra um erro de que o arquivo não existe e para a função.
  if(arquivo == NULL){
    printf("Esse arquivo não existe!");
    return;
  }
  //Fecha o arquivo "arquivo". Pois a intenção de abrir era apenas para saber se o arquivo existe.
  fclose(arquivo);
  //Remove o arquivo de nome "nome_tabela".
  remove(nome_tabela);

  printf("Tabela apagada com sucesso!\n");
}

/*
 * (Informações precedidas por "*" e conteúdos com "()" não estão no arquivo, são apenas comentários).
  * Formatação do meu arquivo:
Name: Nome da tabela.
QtCol: Quantidade de colunas.
NColX: Nome da coluna x.
TColX: Tipo da coluna x.
NColY: Nome da coluna y.
TColY: Tipo da coluna y.
...
PK: Nome da Primary Key.
Nome da Primary Key: X.
{
ColDX: Dado da coluna x.
ColDY: Dado da coluna y.
...
}
QtTup: 1.
Nome da Primary Key: Y.
{
ColDX: Dado da coluna x.
ColDY: Dado da coluna y.
}
QtTup: 2.
...
Nome da Primary Key: Z.
{
ColDX: Dado da coluna x.
ColDY: Dado da coluna y.
}
QtTup: N (N = quantidade de tuplas atual).
  * Fim do arquivo.
*/