#include <stdio.h>
#include <stdlib.h>
#include "livro.h"
#include <string.h>

Livro * criarLivro (int codigo, char titulo [], char autor [], int ano , int quantidadeTotal) {
    Livro * novoLivro = (Livro *) malloc(sizeof(Livro));
    if (novoLivro != NULL) {
        novoLivro->codigo = codigo;

        strncpy(novoLivro->titulo, titulo, sizeof(novoLivro->titulo) - 1);
        novoLivro->titulo[sizeof(novoLivro->titulo) - 1] = '\0'; // Garantir terminação nula
        
        strncpy(novoLivro->autor, autor, sizeof(novoLivro->autor) - 1);
        novoLivro->autor[sizeof(novoLivro->autor) - 1] = '\0'; // Garantir terminação nula
        
        novoLivro->ano = ano;
        novoLivro->quantidadeTotal = quantidadeTotal;
        novoLivro->quantidadeDisponivel = quantidadeTotal; // Inicialmente, todos os exemplares estão disponíveis
    }
    return novoLivro;
}

void exibirLivro(Livro *livro) {
    if (livro != NULL) {
        printf("ID: %d | Titulo: %s | Autor: %s | Qtd Disp: %d/%d\n", 
               livro->codigo, livro->titulo, livro->autor, 
               livro->quantidadeDisponivel, livro->quantidadeTotal);
    }
}