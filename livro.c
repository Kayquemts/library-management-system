#include <stdio.h>
#include "livro.h"

void exibirLivro(Livro* livro)
{
    printf("\n=== LIVRO ===\n");

    printf("Codigo: %d\n",
           livro->codigo);

    printf("Titulo: %s\n",
           livro->titulo);

    printf("Disponiveis: %d\n",
           livro->quantidadeDisponivel);
}