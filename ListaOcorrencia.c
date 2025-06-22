#include <stdio.h>
#include <stdlib.h>
#include "ListaOcorrencia.h"

void FLOVazia(ListaOcorrencias *lista) {
    lista->Primeiro = NULL;
    lista->Ultimo = lista->Primeiro;
}

int insereOuAtualizaOcorrencia(ListaOcorrencias *lista, int idDoc)
{
    if (lista == NULL)
    {
        printf("ListaOcorrencias nao inicializada.\n"); // possível erro com malloc (teve bastante)
        return 0;
    }

    Ocorrencia *atual = lista->Primeiro;
    Ocorrencia *anterior = NULL;
    int comparacoes = 0; // para medir com a hash

    while (atual != NULL && atual->item.id < idDoc) // Percorre a lista para encontrar o idDoc ou o ponto de inserção
    {
        comparacoes++;
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL && atual->item.id == idDoc) // Caso 1: incrementa qtde
    {
        comparacoes++; // Comparou e encontrou
        atual->item.qtde++;
        return comparacoes;
    }

    Ocorrencia *novaOcorrencia = (Ocorrencia*)malloc(sizeof(Ocorrencia)); // Caso 2: cria uma nova ocorrencia
    novaOcorrencia->item.id = idDoc;
    novaOcorrencia->item.qtde = 1;
    novaOcorrencia->prox = NULL;

    // Inserção na lista encadeada (mantendo a ordem por idDoc)
    if (anterior == NULL)
    { // Inserir no início da lista (ou lista vazia)
        novaOcorrencia->prox = lista->Primeiro;
        lista->Primeiro = novaOcorrencia;
        if (lista->Ultimo == NULL)
        { // Se a lista estava vazia
            lista->Ultimo = novaOcorrencia;
        }
    }
    else
    { // Inserir no meio ou no final
        novaOcorrencia->prox = atual;
        anterior->prox = novaOcorrencia;
        if (atual == NULL)
        { // Inserir no final
            lista->Ultimo = novaOcorrencia;
        }
    }
    return comparacoes;
}