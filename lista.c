#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Lista *criarLista() {
    Lista *lista = (Lista *) malloc(sizeof(Lista));

     if (lista == NULL) {
        printf("Erro: memoria insuficiente!\n");
        return 0;
    }

    lista->inicio = NULL;

    return lista;
}

int listaVazia(Lista *lista) {
    if (lista == NULL || lista->inicio == NULL) {
        return 1;
        printf("A lista está vazia");
    }
    return 0;
}

void inserirEmprestimo(Lista *lista, Emprestimo emprestimo) {

    NoLista *novoNo = (NoLista *) malloc(sizeof(NoLista));

    if (novoNo == NULL) {
        printf("Erro: memoria insuficiente!\n");
        return;
    }

    novoNo->emprestimo = emprestimo;

    novoNo->proximo = lista->inicio;

    lista->inicio = novoNo;
}

void listarEmprestimos(Lista *lista) {

    if (lista == NULL || lista->inicio == NULL) {
        printf("Historico vazio.\n");
        return;
    }

    NoLista *aux = lista->inicio;

    while (aux != NULL) {

        printf("Usuario: %s\n",
               aux->emprestimo.nomeUsuario);

        printf("Codigo do livro: %d\n",
               aux->emprestimo.codigoLivro);

        printf("Titulo: %s\n",
               aux->emprestimo.tituloLivro);

        printf("-------------------------\n");

        aux = aux->proximo;
    }
}




void liberarLista(Lista *lista) {
    if (lista == NULL) {
        return;
    }

    NoLista *atual = lista->inicio;
    NoLista *proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    free(lista);
}