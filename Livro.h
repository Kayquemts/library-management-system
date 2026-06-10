#ifndef LIVRO_H
#define LIVRO_H

typedef struct Livro{
    int codigo ;
    char titulo [100];
    char autor [100];
    int ano ;
    int quantidadeTotal ;
    int quantidadeDisponivel ;
} Livro;

Livro * criarLivro (int codigo, char titulo [], char autor [], int ano , int quantidadeTotal);
void exibirLivro (Livro * livro );
int obterCodigoLivro (Livro * livro );
int obterQuantidadeDisponivel (Livro * livro );
void emprestarExemplar (Livro * livro );
void devolverExemplar (Livro * livro );

#endif