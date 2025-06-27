#include <stdio.h>

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
    return 0;
}