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

    // TODO: Liberar a memória da árvore antes de fechar
    free(acervo);
    return 0;
}

// Imprime as opções textuais na tela
void exibirMenu() {
    printf("\n========================================\n");
    printf("   SISTEMA DE GERENCIAMENTO DE BIBLIOTECA \n");
    printf("========================================\n");
    printf("a. Cadastrar novo livro\n");
    printf("b. Buscar livro por codigo\n");
    printf("c. Listar livros em ordem crescente de codigo\n");
    printf("d. Listar livros em pre-ordem\n");
    printf("e. Listar livros em pos-ordem\n");
    printf("f. Mostrar Arvore\n");
    printf("j. Exibir quantidade de livros cadastrados\n");
    printf("k. Exibir altura da arvore\n");
    printf("s. Sair\n");
    printf("========================================\n");
    printf("Escolha uma opcao: ");
}

// Função responsável por interagir com o usuário e alimentar a árvore
void cadastrarLivro(Arvore *acervo) {
    int codigo, ano, quantidadeTotal;
    char titulo[100];
    char autor[100];

    printf("\n--- Cadastrar Novo Livro ---\n");

    printf("Digite o codigo do livro: ");
    scanf("%d", &codigo);

    /* O " %[^\n]" resolve o problema do buffer:
       O espaço inicial ignora o \n deixado pelo scanf anterior.
       O [^\n] faz ler a frase inteira com espaços até você apertar ENTER. */
    printf("Digite o titulo do livro: ");
    scanf(" %[^\n]", titulo);
    
    printf("Digite o nome do autor do livro: ");
    scanf(" %[^\n]", autor);

    printf("Digite o ano de publicacao do livro: ");
    scanf("%d", &ano);

    printf("Digite a quantidade total de exemplares: ");
    scanf("%d", &quantidadeTotal);

    /* Envia os dados para o TAD criar a estrutura na memória.
       Repare que passamos 5 parâmetros conforme exigido no PDF [cite: 57, 223-229]. */
    Livro *novoLivro = criarLivro(codigo, titulo, autor, ano, quantidadeTotal);

    if (novoLivro != NULL) {
        inserirLivroArvore(acervo, novoLivro);
        printf("\n[SUCESSO] Livro '%s' cadastrado com sucesso!\n", titulo);
    } else {
        printf("\n[ERRO] Falha crítica de memória ao gerar a entidade do livro.\n");
    }
}