#include <stdio.h>
#include <stdlib.h>

void exibirMenu() {
    printf("\n========================================\n");
    printf("   SISTEMA DE GERENCIAMENTO DE BIBLIOTECA \n");
    printf("========================================\n");
    printf("a. Cadastrar novo livro\n");
    printf("b. Buscar livro por codigo\n");
    printf("c. Listar livros em ordem crescente de codigo\n");
    printf("d. Listar livros em pre-ordem\n");
    printf("e. Listar livros em pos-ordem\n");
    printf("f. Realizar emprestimo de livro\n");
    printf("g. Devolver livro\n");
    printf("h. Exibir fila de reservas\n");
    printf("i. Exibir historico de emprestimos\n");
    printf("j. Exibir quantidade de livros cadastrados\n");
    printf("k. Exibir altura da arvore\n");
    printf("s. Sair\n");
    printf("========================================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    /* Tipo char nativo ocupando 1 byte */
    char opcao;

    do {
        exibirMenu();
        
        /* O espaço antes do %c é crucial! Ele ignora quebras de linha (\n) 
           e espaços em branco que ficam no buffer do teclado entre as leituras. */
        scanf(" %c", &opcao);

        switch(opcao) {
            case 'a': case 'A':
                printf("\n--- Cadastrar Novo Livro ---\n");
                // TODO: arvore = inserirLivroArvore(&acervo, criarLivro(...));
                break;
                
            case 'b': case 'B':
                printf("\n--- Buscar Livro ---\n");
                // TODO: buscarLivroArvore(&acervo, codigo)
                break;
                
            case 'c': case 'C':
                printf("\n--- Livros (Em Ordem) ---\n");
                listarLivrosEmOrdem(&acervo);
                break;
                
            case 'd': case 'D':
                printf("\n--- Livros (Pre-Ordem) ---\n");
                listarLivrosPreOrdem(&acervo);
                break;
                
            case 'e': case 'E':
                printf("\n--- Livros (Pos-Ordem) ---\n");
                listarLivrosPosOrdem(&acervo);
                break;
                
            case 'f': case 'F':
                printf("\n--- Realizar Emprestimo ---\n");
                // TODO: Atualizar arvore, historico ou fila
                break;
                
            case 'g': case 'G':
                printf("\n--- Devolver Livro ---\n");
                // TODO: Atualizar arvore e exibir/processar fila
                break;
                
            case 'h': case 'H':
                printf("\n--- Fila de Reservas ---\n");
                exibirReservas(reservas);
                break;
                
            case 'i': case 'I':
                printf("\n--- Historico de Emprestimos ---\n");
                listarEmprestimos(&historico);
                break;
                
            case 'j': case 'J':
                printf("\nQuantidade de livros cadastrados: %d\n", contarLivros(acervo));
                break;
                
            case 'k': case 'K':
                printf("\nAltura da arvore: %d\n", calcularAlturaArvore(&acervo));
                break;
                
            case 's': case 'S':
                printf("\nEncerrando o sistema...\n");
                break;
                
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 's' && opcao != 'S');

    return 0;
}