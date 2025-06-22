#include <stdio.h>

#include "entrada.h"

int main() {
    int i;
    ListaArquivos entrada;
    entrada = leitura_arq("entrada.txt");
    ler_pocs(&entrada);
    ImprimeIndiceInvertido();
    return 0;
}