#ifndef LISTA_H
#define LISTA_H

typedef struct Emprestimo {
    char nomeUsuario[100];
    int codigoLivro;
    char tituloLivro[100];
} Emprestimo;

typedef struct NoLista {
    Emprestimo emprestimo;
    struct NoLista *proximo;
} NoLista;

typedef struct Lista {
    NoLista *inicio;
} Lista;

Lista *criarLista(); //ok
void inserirEmprestimo(Lista *lista, Emprestimo emprestimo);//ok
void listarEmprestimos(Lista *lista);//ok
int listaVazia(Lista *lista); //ok 
void liberarLista(Lista *lista); //ok

#endif