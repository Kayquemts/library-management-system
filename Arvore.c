#include <stdio.h>
#include <stdlib.h>
#include "Livro.h"
#include "Arvore.h"

Arvore * criarArvore () {
    Arvore * novaArvore = (Arvore *) malloc(sizeof(Arvore));
    if (novaArvore != NULL) {
        novaArvore->raiz = NULL;
    }
    return novaArvore;
}

static NoArvore* criarNoArvore(Livro* livro) {
    NoArvore* novoNo = (NoArvore*) malloc(sizeof(NoArvore));
    if (novoNo != NULL) {
        novoNo->livro = livro;
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;
    }
    return novoNo;
}

static NoArvore* inserirNoRecursivo(NoArvore* raiz, Livro* livro) {
    if (raiz == NULL) {
        return criarNoArvore(livro);
    }

    // Comparação ultra rápida usando o código inteiro do livro
    if (livro->codigo < raiz->livro->codigo) {
        raiz->esquerda = inserirNoRecursivo(raiz->esquerda, livro);
    }else if (livro->codigo > raiz->livro->codigo) {
        raiz->direita = inserirNoRecursivo(raiz->direita, livro);
    }else {
        printf("\n[ERRO] O codigo %d ja pertence a outro livro!\n", livro->codigo);
        free(livro); 
    }

    return raiz;
}

void inserirLivroArvore(Arvore * arvore, Livro * livro) {
    if (arvore == NULL || livro == NULL) return;
    arvore->raiz = inserirNoRecursivo(arvore->raiz, livro);
}


// =================================================================
// 1. PERCURSO EM-ORDEM (Esquerda -> Raiz -> Direita)
// =================================================================
static void emOrdemRecursivo(NoArvore *raiz) {
    if (raiz != NULL) {
        emOrdemRecursivo(raiz->esquerda);  // 1. Vai tudo para a esquerda
        exibirLivro(raiz->livro);          // 2. Visita a raiz (printa o livro)
        emOrdemRecursivo(raiz->direita);   // 3. Vai para a direita
    }
}

void listarLivrosEmOrdem(Arvore *arvore) {
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("\n[AVISO] O acervo esta vazio.\n");
        return;
    }
    emOrdemRecursivo(arvore->raiz);
}


// =================================================================
// 2. PERCURSO PRÉ-ORDEM (Raiz -> Esquerda -> Direita)
// =================================================================
static void preOrdemRecursivo(NoArvore *raiz) {
    if (raiz != NULL) {
        exibirLivro(raiz->livro);          // 1. Visita a raiz primeiro
        preOrdemRecursivo(raiz->esquerda); // 2. Vai para a esquerda
        preOrdemRecursivo(raiz->direita);  // 3. Vai para a direita
    }
}

void listarLivrosPreOrdem(Arvore *arvore) {
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("\n[AVISO] O acervo esta vazio.\n");
        return;
    }
    preOrdemRecursivo(arvore->raiz);
}


// =================================================================
// 3. PERCURSO PÓS-ORDEM (Esquerda -> Direita -> Raiz)
// =================================================================
static void posOrdemRecursivo(NoArvore *raiz) {
    if (raiz != NULL) {
        posOrdemRecursivo(raiz->esquerda); // 1. Vai para a esquerda
        posOrdemRecursivo(raiz->direita);  // 2. Vai para a direita
        exibirLivro(raiz->livro);          // 3. Visita a raiz por ultimo
    }
}

void listarLivrosPosOrdem(Arvore *arvore) {
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("\n[AVISO] O acervo esta vazio.\n");
        return;
    }
    posOrdemRecursivo(arvore->raiz);
}


// =================================================================
// BONUS: FUNÇÃO DE PRINT VISUAL 
// =================================================================
static void exibirEstruturaArvore(NoArvore *raiz, int espaco) {
    if (raiz == NULL) return;

    // Aumenta a distância entre os níveis (4 espaços por nível)
    espaco += 5;

    // Processa a subárvore direita primeiro (ela fica no topo do terminal)
    exibirEstruturaArvore(raiz->direita, espaco);

    // Printa o nó atual após aplicar os espaços necessários
    printf("\n");
    for (int i = 5; i < espaco; i++) {
        printf(" ");
    }
    // Mostra apenas o código do livro para ficar visualmente limpo
    printf("[%d]\n", raiz->livro->codigo);

    // Processa a subárvore esquerda (fica na parte de baixo do terminal)
    exibirEstruturaArvore(raiz->esquerda, espaco);
}

// Você pode chamar essa função no seu menu para fins de teste/debug seu
void printarArvoreVisual(Arvore *arvore) {
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("Arvore vazia.\n");
        return;
    }
    printf("\n--- ESTRUTURA DA ARVORE (Deitada) ---\n");
    exibirEstruturaArvore(arvore->raiz, 0);
    printf("-------------------------------------\n");
}