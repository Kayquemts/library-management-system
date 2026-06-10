#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fila.h"

Fila* criarFila()
{
    Fila* fila =
        malloc(sizeof(Fila));

    fila->inicio = NULL;
    fila->fim = NULL;

    return fila;
}

int filaVazia(Fila* fila)
{
    return fila->inicio == NULL;
}

void enfileirarReserva(
    Fila* fila,
    Reserva reserva
)
{
    NoFila* novo =
        malloc(sizeof(NoFila));

    novo->reserva = reserva;
    novo->proximo = NULL;

    if(filaVazia(fila))
    {
        fila->inicio = novo;
        fila->fim = novo;
    }
    else
    {
        fila->fim->proximo = novo;
        fila->fim = novo;
    }
}

Reserva desenfileirarReserva(
    Fila* fila
)
{
    Reserva vazio;

    strcpy(
        vazio.nomeUsuario,
        "NINGUEM"
    );

    vazio.codigoLivro = -1;

    if(filaVazia(fila))
    {
        return vazio;
    }

    NoFila* temp =
        fila->inicio;

    Reserva reserva =
        temp->reserva;

    fila->inicio =
        fila->inicio->proximo;

    if(fila->inicio == NULL)
    {
        fila->fim = NULL;
    }

    free(temp);

    return reserva;
}

void mostrarFila(
    Fila* fila
)
{
    if(filaVazia(fila))
    {
        printf("\nFila vazia!\n");
        return;
    }

    NoFila* atual =
        fila->inicio;

    printf("\n=== FILA DE RESERVAS ===\n");

    while(atual != NULL)
    {
        printf(
            "Usuario: %s | Livro: %d\n",
            atual->reserva.nomeUsuario,
            atual->reserva.codigoLivro
        );

        atual =
            atual->proximo;
    }
}