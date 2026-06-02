#ifndef FILA_H
#define FILA_H

typedef struct {

    char nomeUsuario[100];
    int codigoLivro;

} Reserva;

typedef struct NoFila {

    Reserva reserva;
    struct NoFila* proximo;

} NoFila;

typedef struct {

    NoFila* inicio;
    NoFila* fim;

} Fila;

Fila* criarFila();

void enfileirarReserva(
    Fila* fila,
    Reserva reserva
);

Reserva desenfileirarReserva(
    Fila* fila
);

void mostrarFila(
    Fila* fila
);

int filaVazia(
    Fila* fila
);

#endif