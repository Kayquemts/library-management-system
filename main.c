#include <stdio.h>
#include <string.h>

#include "livro.h"
#include "fila.h"

int main()
{
    Livro livro;

    livro.codigo = 10;

    strcpy(
        livro.titulo,
        "Clean Code"
    );

    livro.quantidadeDisponivel = 1;

    Fila* fila =
        criarFila();

    int opcao;

    do
    {
        printf("\n");
        printf("1 - Mostrar livro\n");
        printf("2 - Solicitar emprestimo\n");
        printf("3 - Devolver livro\n");
        printf("4 - Mostrar fila\n");
        printf("0 - Sair\n");

        printf("Opcao: ");
        scanf("%d", &opcao);

        getchar();

        switch(opcao)
        {
            case 1:

                exibirLivro(&livro);

                break;

            case 2:
            {
                char nome[100];

                printf(
                    "Nome do usuario: "
                );

                fgets(
                    nome,
                    sizeof(nome),
                    stdin
                );

                nome[
                    strcspn(
                        nome,
                        "\n"
                    )
                ] = '\0';

                if(
                    livro.quantidadeDisponivel > 0
                )
                {
                    livro.quantidadeDisponivel--;

                    printf(
                        "\nLivro emprestado para %s\n",
                        nome
                    );
                }
                else
                {
                    int resposta;

                    printf(
                        "\nSem exemplares disponiveis.\n"
                    );

                    do
                    {
                        printf(
                            "\nDeseja entrar na fila de espera?\n"
                        );

                        printf(
                            "1 - Sim\n"
                        );

                        printf(
                            "2 - Nao\n"
                        );

                        printf(
                            "Opcao: "
                        );

                        scanf(
                            "%d",
                            &resposta
                        );

                    } while(
                        resposta != 1 &&
                        resposta != 2
                    );

                    if(resposta == 1)
                    {
                        Reserva reserva;

                        strcpy(
                            reserva.nomeUsuario,
                            nome
                        );

                        reserva.codigoLivro =
                            livro.codigo;

                        enfileirarReserva(
                            fila,
                            reserva
                        );

                        printf(
                            "\n%s entrou na fila.\n",
                            nome
                        );
                    }
                    else
                    {
                        printf(
                            "\nOperacao cancelada.\n"
                        );
                    }
                }

                break;
            }

            case 3:
            {
                livro.quantidadeDisponivel++;

                printf(
                    "\nLivro devolvido.\n"
                );

                if(
                    !filaVazia(fila)
                )
                {
                    Reserva proximo =
                        desenfileirarReserva(
                            fila
                        );

                    printf(
                        "\nPrimeiro da fila: %s\n",
                        proximo.nomeUsuario
                    );

                    printf(
                        "Livro reservado para ele.\n"
                    );

                    livro.quantidadeDisponivel--;
                }

                break;
            }

            case 4:

                mostrarFila(fila);

                break;

            case 0:

                printf(
                    "\nEncerrando...\n"
                );

                break;

            default:

                printf(
                    "\nOpcao invalida.\n"
                );
        }

    } while(opcao != 0);

    return 0;
}