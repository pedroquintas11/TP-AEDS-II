#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <ctype.h>

#include "hash.h"
#include "entrada.h"

TipoDicionario Tabela;
TipoPesos p;
TipoApontador i;

void FLVaziahash(TipoLista *Lista)
{ 
  Lista->Primeiro = (TipoCelula *)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
}  

short Vaziahash(TipoLista Lista)
{ 
  return (Lista.Primeiro == Lista.Ultimo); 
}
void InsHash(TipoItem x, TipoLista *Lista)
{ 
  Lista->Ultimo->Prox = (TipoCelula *)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Ultimo->Prox;
  Lista->Ultimo->Item = x;
  Lista->Ultimo->Prox = NULL;
} 

void GeraPesos(TipoPesos p)
{ 
  int i, j;
  struct timeval semente;
  gettimeofday(&semente, NULL); 
  srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
  for (i = 0; i < N; i++)
    for (j = 0; j < TAMALFABETO; j++)
      p[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
}

TipoIndice h(Palavras palavra, TipoPesos p)
{ 
  int i;
  unsigned int Soma = 0; 
  int comp = strlen(palavra);
  for (i = 0; i < comp; i++)
    Soma += p[i][(unsigned int)palavra[i]];
  return (Soma % M);
}

void Inicializahash(TipoDicionario T)
{ 
  int i;
  for (i = 0; i < M; i++) FLVaziahash(&T[i]);
}

TipoApontador PesquisaHash(Palavras Ch, TipoPesos p, TipoDicionario T)
{ 
  TipoIndice i;
  TipoApontador Ap;
  i = h(Ch, p);
  if (Vaziahash(T[i])){
    return NULL;
  }
  
  Ap = T[i].Primeiro->Prox;
  while (Ap != NULL) {
    if (strcmp(Ch, Ap->Item.palavra) == 0) {
        return Ap; 
    }
    Ap = Ap->Prox;
  }
  return NULL;
}

void InsereHash(const char *palavra, int idDoc, TipoPesos p, TipoDicionario T){
  TipoApontador Posicao;
    Posicao = PesquisaHash((char*)palavra, p, T);
    if (Posicao != NULL) { 
        insereOuAtualizaOcorrencia(Posicao->Item.Ocorrencia, idDoc);
    } else { // Palavra nova, precisa ser inserida
        TipoItem novoItem;
        strcpy(novoItem.palavra, palavra);
        // Aloca e inicializa a lista de ocorrências para a nova palavra
        novoItem.Ocorrencia = (ListaOcorrencias*)malloc(sizeof(ListaOcorrencias));
        FLOVazia(novoItem.Ocorrencia);
        // Insere a primeira ocorrência (id do documento)
        insereOuAtualizaOcorrencia(novoItem.Ocorrencia, idDoc);
        // Insere o novo item (palavra + lista de ocorrências) na hash
        InsHash(novoItem, &T[h(novoItem.palavra, p)]);
    }
}


void Imp(TipoLista Lista)
{ 
  TipoApontador Aux;
  Aux = Lista.Primeiro->Prox;
  while (Aux != NULL) 
    { printf("%.*s ", N, Aux->Item.palavra);
      Aux = Aux->Prox;
    }
}

void Imprime(TipoDicionario Tabela)
{ 
  int i;
  for (i = 0; i < M; i++) 
    { printf("%d: ", i);
      if (!Vaziahash(Tabela[i]))
      Imp(Tabela[i]);
      putchar('\n');
    }
} 

int Compara (const void *a, const void *b)
{
  const TipoItem *itemA = (const TipoItem *)a;
  const TipoItem *itemB = (const TipoItem *)b;
  return strncmp(itemA->palavra, itemB->palavra, N);
}

void ImprimeOrdenadohash(TipoDicionario Tabela) 
{
    int i;
    TipoApontador Aux;
    int totalDeItens = 0;

    for (i = 0; i < M; i++) {
        if (!Vaziahash(Tabela[i])) {
            Aux = Tabela[i].Primeiro->Prox;
            while (Aux != NULL) {
                totalDeItens++;
                Aux = Aux->Prox;
            }
        }
    }
    if (totalDeItens == 0) {
        printf("A tabela está vazia.\n");
        return;
    }
    TipoItem *todosOsItens = malloc(totalDeItens * sizeof(TipoItem));
    if (todosOsItens == NULL) {
        printf("Falha ao alocar memoria para ordenacao.\n");
        return;
    }
    int k = 0; 
    for (i = 0; i < M; i++) {
        if (!Vaziahash(Tabela[i])) {
            Aux = Tabela[i].Primeiro->Prox;
            while (Aux != NULL) {
                todosOsItens[k] = Aux->Item;
                k++;
                Aux = Aux->Prox;
            }
        }
    }
    qsort(todosOsItens, totalDeItens, sizeof(TipoItem), Compara);
    printf("--- Indice Invertido (Hash) ---\n");
    for (i = 0; i < totalDeItens; i++) {
        printf("%s -> ", todosOsItens[i].palavra);
        if (todosOsItens[i].Ocorrencia != NULL) {
            Ocorrencia *atual = todosOsItens[i].Ocorrencia->Primeiro;
            while (atual != NULL) {
                printf("<%d, %d> ", atual->item.id, atual->item.qtde);
                atual = atual->prox;
            }
        }
        printf("\n");
    }
    printf("----------------------------------\n");
    free(todosOsItens);
}
 
