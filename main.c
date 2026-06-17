#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "livro.h"
#include "arvore.h"
#include "fila.h"
#include "lista.h"

/* ─── protótipos das funções auxiliares do menu ─────────────── */
void exibirMenu();
void cadastrarLivro    (Arvore *acervo);
void buscarLivro       (Arvore *acervo);
void realizarEmprestimo(Arvore *acervo, Fila *filaReservas, Lista *historico);
void realizarDevolucao (Arvore *acervo, Fila *filaReservas, Lista *historico);

/* ─────────────────────────────────────────────────────────────
 *  MAIN
 * ───────────────────────────────────────────────────────────── */
int main() {

    /* Inicializa as três estruturas principais */
    Arvore *acervo       = criarArvore();
    Fila   *filaReservas = criarFila();
    Lista  *historico    = criarLista();

    if (acervo == NULL || filaReservas == NULL || historico == NULL) {
        printf("[ERRO FATAL] Falha ao alocar estruturas principais.\n");
        return 1;
    }

    int opcao;

    do {
        exibirMenu();
        char entrada[50];
        char sobra;

        if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
            if (sscanf(entrada, "%d %c", &opcao, &sobra) != 1) {
                opcao = -1;
            }
        }

        switch (opcao) {

            case 1:
                cadastrarLivro(acervo);
                break;

            case 2:
                buscarLivro(acervo);
                break;

            case 3:
                printf("\n=== LISTAGEM EM ORDEM CRESCENTE ===\n");
                listarLivrosEmOrdem(acervo);
                break;

            case 4:
                printf("\n=== LISTAGEM EM PRE-ORDEM ===\n");
                listarLivrosPreOrdem(acervo);
                break;

            case 5:
                printf("\n=== LISTAGEM EM POS-ORDEM ===\n");
                listarLivrosPosOrdem(acervo);
                break;

            case 6:
                realizarEmprestimo(acervo, filaReservas, historico);
                break;

            case 7:
                realizarDevolucao(acervo, filaReservas, historico);
                break;

            case 8:
                mostrarFila(filaReservas);
                break;

            case 9:
                printf("\n=== HISTORICO DE EMPRESTIMOS ===\n");
                listarEmprestimos(historico);
                break;

            case 10:
                printf("\nQuantidade de livros cadastrados: %d\n",
                       contarLivros(acervo));
                break;

            case 11:
                printf("\nAltura da arvore: %d\n",
                       calcularAlturaArvore(acervo));
                break;

            case 12:
                /* Funcionalidade extra: exibição visual da árvore */
                printarArvoreVisual(acervo);
                break;

            case 0:
                printf("\nEncerrando o sistema. Ate logo!\n");
                break;

            default:
                printf("\n[AVISO] Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    /* Libera a memória antes de encerrar */
    liberarLista(historico);
    /* Fila e árvore: liberação básica das estruturas externas */
    free(filaReservas);
    free(acervo);

    return 0;
}

/* ─────────────────────────────────────────────────────────────
 *  MENU
 * ───────────────────────────────────────────────────────────── */
void exibirMenu() {
    printf("\n========================================\n");
    printf("   SISTEMA DE GERENCIAMENTO DE BIBLIOTECA\n");
    printf("========================================\n");
    printf(" 1. Cadastrar novo livro\n");
    printf(" 2. Buscar livro por codigo\n");
    printf(" 3. Listar livros em ordem crescente\n");
    printf(" 4. Listar livros em pre-ordem\n");
    printf(" 5. Listar livros em pos-ordem\n");
    printf(" 6. Realizar emprestimo\n");
    printf(" 7. Devolver livro\n");
    printf(" 8. Exibir fila de reservas\n");
    printf(" 9. Exibir historico de emprestimos\n");
    printf("10. Exibir quantidade de livros cadastrados\n");
    printf("11. Exibir altura da arvore\n");
    printf("12. [EXTRA] Visualizar estrutura da arvore\n");
    printf(" 0. Sair\n");
    printf("========================================\n");
    printf("Opcao: ");
}

/* ─────────────────────────────────────────────────────────────
 *  CADASTRAR LIVRO
 * ───────────────────────────────────────────────────────────── */
void cadastrarLivro(Arvore *acervo) {
    int  codigo, ano, quantidadeTotal;
    char titulo[100];
    char autor[100];
    char buffer[100];
    char sobra;

    printf("\n--- CADASTRAR NOVO LIVRO ---\n");

    while (1) {
        printf("Codigo       : ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d %c", &codigo, &sobra) == 1) {
                /* Se o código for válido, verifica duplicata */
                if (buscarLivroArvore(acervo, codigo) != NULL) {
                    printf("[ERRO] Ja existe um livro com o codigo %d. Tente outro.\n", codigo);
                    continue; 

                }

                if (codigo <= 0) {
                    printf("[ERRO] O codigo deve ser um numero inteiro positivo. Tente novamente.\n");
                    continue; 
                }

                break;
            }
        }
        printf("[ERRO] Codigo invalido! Digite apenas numeros inteiros.\n");
    }

    printf("Titulo       : ");
    if (fgets(titulo, sizeof(titulo), stdin) != NULL) {
        titulo[strcspn(titulo, "\n")] = '\0';
    }

    printf("Autor        : ");
    if (fgets(autor, sizeof(autor), stdin) != NULL) {
        autor[strcspn(autor, "\n")] = '\0';
    }

    while (1) {
        printf("Ano          : ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d %c", &ano, &sobra) == 1) {
                break; 
            }
        }
        printf("[ERRO] Ano invalido! Digite apenas numeros inteiros.\n");
    }

    while (1) {
        printf("Qtd exemplares: ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d %c", &quantidadeTotal, &sobra) == 1) {
                if (quantidadeTotal > 0) {
                    break;
                } else {
                    printf("[ERRO] A quantidade de exemplares deve ser maior que zero.\n");
                    continue;
                }
            }
        }
        printf("[ERRO] Quantidade invalida! Digite apenas numeros inteiros.\n");
    }

    Livro *novoLivro = criarLivro(codigo, titulo, autor, ano, quantidadeTotal);

    if (novoLivro != NULL) {
        inserirLivroArvore(acervo, novoLivro);
        printf("[SUCESSO] Livro '%s' cadastrado com sucesso!\n", titulo);
    } else {
        printf("[ERRO] Falha de memoria ao criar o livro.\n");
    }
}

/* ─────────────────────────────────────────────────────────────
 *  BUSCAR LIVRO
 * ───────────────────────────────────────────────────────────── */
void buscarLivro(Arvore *acervo) {
    int codigo;
    char buffer[100];
    char sobra;
    Livro *encontrado = NULL;

    printf("\n--- BUSCAR LIVRO ---\n");

    while (1) {
        printf("Codigo do livro (ou 0 para cancelar): ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            
            if (sscanf(buffer, "%d %c", &codigo, &sobra) == 1) {
                
                if (codigo == 0) {
                    printf("[INFO] Busca cancelada.\n");
                    return;
                }

                encontrado = buscarLivroArvore(acervo, codigo);
                
                if (encontrado != NULL) {
                    break; 
                } else {
                    printf("[AVISO] Livro com codigo %d nao encontrado. Tente outro.\n", codigo);
                    continue; 
                }
            }
        }
        printf("[ERRO] Codigo invalido! Digite apenas numeros inteiros.\n");
    }

    printf("\n[ENCONTRADO]\n");
    exibirLivro(encontrado);
}

/* ─────────────────────────────────────────────────────────────
 *  REALIZAR EMPRESTIMO
 * ───────────────────────────────────────────────────────────── */
void realizarEmprestimo(Arvore *acervo, Fila *filaReservas, Lista *historico) {
    int  codigo;
    char nomeUsuario[100];
    char buffer[100];
    char sobra;
    Livro *livro = NULL;

    printf("\n--- REALIZAR EMPRESTIMO ---\n");

    while (1) {
        printf("Codigo do livro: ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d %c", &codigo, &sobra) == 1) {
                
                livro = buscarLivroArvore(acervo, codigo);
                if (livro != NULL) {
                    break; 
                } else {
                    printf("[ERRO] Livro com codigo %d nao encontrado no acervo. Tente novamente.\n", codigo);
                    continue;
                }
            }
        }
        printf("[ERRO] Codigo invalido! Digite apenas numeros inteiros.\n");
    }

    printf("Nome do usuario: ");
    if (fgets(nomeUsuario, sizeof(nomeUsuario), stdin) != NULL) {
        nomeUsuario[strcspn(nomeUsuario, "\n")] = '\0';
    }

    /* ── Caso 1: há exemplares disponíveis ── */
    if (obterQuantidadeDisponivel(livro) > 0) {

        emprestarExemplar(livro);

        /* Registra no histórico */
        Emprestimo emp;
        strncpy(emp.nomeUsuario, nomeUsuario, 99);
        emp.nomeUsuario[99] = '\0';
        emp.codigoLivro = obterCodigoLivro(livro);
        strncpy(emp.tituloLivro, livro->titulo, 99);
        emp.tituloLivro[99] = '\0';

        inserirEmprestimo(historico, emp);

        printf("[SUCESSO] Emprestimo realizado!\n");
        printf("  Usuario : %s\n", nomeUsuario);
        printf("  Livro   : %s (cod. %d)\n", livro->titulo, livro->codigo);
        printf("  Disponiveis restantes: %d\n", obterQuantidadeDisponivel(livro));

    /* ── Caso 2: sem exemplares disponíveis → oferecer reserva ── */
    } else {
        printf("\n[AVISO] Nao ha exemplares disponiveis para '%s'.\n", livro->titulo);

        int resposta;
        do {
            printf("Deseja entrar na fila de reservas?\n");
            printf("  1 - Sim\n");
            printf("  2 - Nao\n");
            printf("Opcao: ");
            if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d %c", &resposta, &sobra) != 1) {
                resposta = -1;
            }
        } while (resposta != 1 && resposta != 2);

        if (resposta == 1) {
            Reserva reserva;
            strncpy(reserva.nomeUsuario, nomeUsuario, 99);
            reserva.nomeUsuario[99] = '\0';
            reserva.codigoLivro = obterCodigoLivro(livro);

            enfileirarReserva(filaReservas, reserva);
            printf("[INFO] %s entrou na fila de reservas para '%s'.\n",
                   nomeUsuario, livro->titulo);
        } else {
            printf("[INFO] Operacao cancelada.\n");
        }
    }
}

/* ─────────────────────────────────────────────────────────────
 *  REALIZAR DEVOLUCAO
 * ───────────────────────────────────────────────────────────── */
void realizarDevolucao(Arvore *acervo, Fila *filaReservas, Lista *historico) {
    int codigo;
    char buffer[100];
    char sobra;
    Livro *livro = NULL;

    printf("\n--- DEVOLVER LIVRO ---\n");

    while (1) {
        printf("Codigo do livro: ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d %c", &codigo, &sobra) == 1) {
                
                livro = buscarLivroArvore(acervo, codigo);
                if (livro != NULL) {
                    break; 
                } else {
                    printf("[ERRO] Livro com codigo %d nao encontrado no acervo. Tente novamente.\n", codigo);
                    continue;
                }
            }
        }
        printf("[ERRO] Codigo invalido! Digite apenas numeros inteiros.\n");
    }

    devolverExemplar(livro);
    printf("[SUCESSO] Devolucao registrada para '%s'.\n", livro->titulo);
    printf("  Disponiveis agora: %d/%d\n",
           obterQuantidadeDisponivel(livro), livro->quantidadeTotal);

    if (!filaVazia(filaReservas)) {

        /* Verifica se o primeiro da fila está esperando por este livro */
        NoFila *primeiro = filaReservas->inicio;

        if (primeiro->reserva.codigoLivro == codigo) {

            Reserva proximo = desenfileirarReserva(filaReservas);
            emprestarExemplar(livro); /* reserva o exemplar recém-devolvido */

            /* Registra o empréstimo automático no histórico */
            Emprestimo emp;
            strncpy(emp.nomeUsuario, proximo.nomeUsuario, 99);
            emp.nomeUsuario[99] = '\0';
            emp.codigoLivro = obterCodigoLivro(livro);
            strncpy(emp.tituloLivro, livro->titulo, 99);
            emp.tituloLivro[99] = '\0';

            inserirEmprestimo(historico, emp);

            printf("[INFO] Exemplar automaticamente reservado para '%s' (primeiro da fila).\n",
                   proximo.nomeUsuario);
            printf("  Disponiveis agora: %d/%d\n",
                   obterQuantidadeDisponivel(livro), livro->quantidadeTotal);

        } else {
            /* Há fila, mas o primeiro espera outro livro */
            printf("[INFO] Ha usuarios na fila de reservas. Use a opcao 8 para visualizar.\n");
        }
    }
}