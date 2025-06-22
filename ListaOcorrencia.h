#ifndef LISTAOCORRENCIA_H
#define LISTAOCORRENCIA_H

typedef struct ItemPal
{
    int id, qtde;
}ItemPal;


typedef struct Ocorrencia
{
    ItemPal item;
    struct Ocorrencia *prox;
}Ocorrencia;

typedef struct ListaOcorrencias 
{
    Ocorrencia *Primeiro, *Ultimo ;
}ListaOcorrencias;

void FLOVazia(ListaOcorrencias *lista);
int insereOuAtualizaOcorrencia(ListaOcorrencias *lista, int idDoc);

#endif