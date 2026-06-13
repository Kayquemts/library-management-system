#include <stdio.h>
#include <stdlib.h>
#include "livro.h"
#include "arvore.h"

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
        novoNo->altura = 0; // novo no e sempre uma folha (altura 0)
    }
    return novoNo;
}

// =================================================================
// FUNCOES AUXILIARES DE BALANCEAMENTO (AVL)
// =================================================================

// Retorna a altura de um no (-1 se for NULL, seguindo a mesma
// convencao usada em calcularAlturaArvore)
static int alturaNo(NoArvore *no) {
    if (no == NULL) return -1;
    return no->altura;
}

// Atualiza a altura de um no com base nos filhos
static void atualizarAltura(NoArvore *no) {
    int e = alturaNo(no->esquerda);
    int d = alturaNo(no->direita);
    no->altura = 1 + (e > d ? e : d);
}

// Fator de balanceamento = altura(esquerda) - altura(direita)
static int fatorBalanceamento(NoArvore *no) {
    if (no == NULL) return 0;
    return alturaNo(no->esquerda) - alturaNo(no->direita);
}

// Rotacao simples para a direita
//        y                x
//       / \              / \
//      x   T3   ===>    T1  y
//     / \                   / \
//    T1 T2                T2  T3
static NoArvore* rotacaoDireita(NoArvore *y) {
    NoArvore *x  = y->esquerda;
    NoArvore *t2 = x->direita;

    x->direita = y;
    y->esquerda = t2;

    atualizarAltura(y);
    atualizarAltura(x);

    return x; // nova raiz da subarvore
}

// Rotacao simples para a esquerda
//      x                    y
//     / \                  / \
//    T1  y     ===>       x  T3
//       / \               / \
//      T2 T3             T1 T2
static NoArvore* rotacaoEsquerda(NoArvore *x) {
    NoArvore *y  = x->direita;
    NoArvore *t2 = y->esquerda;

    y->esquerda = x;
    x->direita  = t2;

    atualizarAltura(x);
    atualizarAltura(y);

    return y; // nova raiz da subarvore
}

// Aplica as rotacoes necessarias (se houver) para balancear o no
static NoArvore* balancear(NoArvore *no) {
    if (no == NULL) return NULL;

    atualizarAltura(no);
    int fb = fatorBalanceamento(no);

    // Caso Esquerda-Esquerda
    if (fb > 1 && fatorBalanceamento(no->esquerda) >= 0) {
        return rotacaoDireita(no);
    }

    // Caso Esquerda-Direita
    if (fb > 1 && fatorBalanceamento(no->esquerda) < 0) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Caso Direita-Direita
    if (fb < -1 && fatorBalanceamento(no->direita) <= 0) {
        return rotacaoEsquerda(no);
    }

    // Caso Direita-Esquerda
    if (fb < -1 && fatorBalanceamento(no->direita) > 0) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    // Ja esta balanceado
    return no;
}

// =================================================================
// INSERCAO (com balanceamento automatico apos cada insercao)
// =================================================================
static NoArvore* inserirNoRecursivo(NoArvore* raiz, Livro* livro) {
    if (raiz == NULL) {
        return criarNoArvore(livro);
    }

    // Comparação ultra rápida usando o código inteiro do livro
    if (livro->codigo < raiz->livro->codigo) {
        raiz->esquerda = inserirNoRecursivo(raiz->esquerda, livro);
    } else if (livro->codigo > raiz->livro->codigo) {
        raiz->direita = inserirNoRecursivo(raiz->direita, livro);
    } else {
        printf("\n[ERRO] O codigo %d ja pertence a outro livro!\n", livro->codigo);
        free(livro);
        return raiz; // nada foi alterado, nao precisa rebalancear este ramo
    }

    // Apos inserir, rebalanceia o caminho de volta a raiz
    return balancear(raiz);
}

void inserirLivroArvore(Arvore * arvore, Livro * livro) {
    if (arvore == NULL || livro == NULL) return;
    arvore->raiz = inserirNoRecursivo(arvore->raiz, livro);
}


// =================================================================
// BUSCA POR CODIGO (iterativa)
// =================================================================
Livro * buscarLivroArvore(Arvore * arvore, int codigo) {
    if (arvore == NULL) return NULL;

    NoArvore *atual = arvore->raiz;

    while (atual != NULL) {
        if (codigo == atual->livro->codigo) {
            return atual->livro;
        } else if (codigo < atual->livro->codigo) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }

    return NULL; // nao encontrado
}


// =================================================================
// CONTAGEM DE LIVROS (numero total de nos da arvore)
// =================================================================
static int contarNosRecursivo(NoArvore *raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNosRecursivo(raiz->esquerda) + contarNosRecursivo(raiz->direita);
}

int contarLivros(Arvore * arvore) {
    if (arvore == NULL) return 0;
    return contarNosRecursivo(arvore->raiz);
}


// =================================================================
// ALTURA DA ARVORE
// =================================================================
// Como ja mantemos a altura em cada no atualizada pelo AVL,
// basta consultar a altura armazenada na raiz. Arvore vazia = -1,
// folha unica = 0 (mesma convencao usada no balanceamento).
int calcularAlturaArvore(Arvore * arvore) {
    if (arvore == NULL || arvore->raiz == NULL) return -1;
    return arvore->raiz->altura;
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

int obterCodigoLivro (Livro * livro ){
    if (livro == NULL) return -1;
    return livro->codigo;
}

int obterQuantidadeDisponivel (Livro * livro ){
    if (livro == NULL) return -1;
    return livro->quantidadeDisponivel;
}

void emprestarExemplar (Livro * livro ){
    if (livro != NULL && livro->quantidadeDisponivel > 0)
        livro->quantidadeDisponivel--;
}
void devolverExemplar (Livro * livro ){
    if (livro != NULL && livro->quantidadeDisponivel < livro->quantidadeTotal)
        livro->quantidadeDisponivel++;
}