#ifndef PRFUNC_H
#define PRFUNC_H

void CriarTabela();

void ListarTabelas();

void CriarTupla(char nome_tabela[]);

void ListarDados(char nome_tabela[]);

void PesqVal(char nome_tabela[]);

void DelTupla(char nome_tabela[], int primkey);

void ApagarTabela(char nome_tabela[]);

#endif