#ifndef LIVRO_H
#define LIVRO_H

typedef struct {

    int codigo;
    char titulo[100];
    int quantidadeDisponivel;

} Livro;

void exibirLivro(Livro* livro);

#endif