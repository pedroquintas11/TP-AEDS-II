#include <stdio.h>

#include "entrada.h"

int main() {
    int i;
    ListaArquivos entrada;
    entrada = leitura_arq("entrada.txt");
    ler_pocs(&entrada);
    for (i=0; i<total_p; i++) {
        printf("(%s %d %d) ", v[i].nome, v[i].id, v[i].qtde);
    }
    return 0;
}