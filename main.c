#include <stdio.h>
#include <string.h>

#include "entrada.h"
#include "hash.h"

int main() {
    Inicializahash(Tabela);
    GeraPesos(p);

    ListaArquivos entrada;
    entrada = leitura_arq("entrada.txt");
    ler_pocs(&entrada);
    Imprime(Tabela);
    ImprimeIndiceInvertido();
    ImprimeOrdenadohash(Tabela);

    char termo_busca[200];
    printf("\nDigite os termos para a busca: ");
    if (fgets(termo_busca, sizeof(termo_busca), stdin)) {
        termo_busca[strcspn(termo_busca, "\n")] = '\0';
        buscar_por_relevancia_hash(termo_busca, &entrada, Tabela, p);
    }
    return 0;
}