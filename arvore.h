#ifndef ARVORE_H
#define ARVORE_H

#include "livro.h"

typedef struct NoArvore {
    Livro * livro ;
    struct NoArvore * esquerda ;
    struct NoArvore * direita ;
    int altura ;
} NoArvore ;

typedef struct Arvore {
    NoArvore * raiz ;
} Arvore ;



Arvore * criarArvore () ;
void inserirLivroArvore ( Arvore * arvore , Livro * livro ) ;
Livro * buscarLivroArvore ( Arvore * arvore , int codigo ) ;
void listarLivrosEmOrdem ( Arvore * arvore ) ;
void listarLivrosPreOrdem ( Arvore * arvore ) ;
void listarLivrosPosOrdem ( Arvore * arvore ) ;
int contarLivros ( Arvore * arvore ) ;
int calcularAlturaArvore ( Arvore * arvore ) ;
void printarArvoreVisual(Arvore *arvore);

#endif