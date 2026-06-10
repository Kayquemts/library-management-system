#include <stdio.h>
#include <stdlib.h>
#include "Livro.h"
#include "Arvore.h"

// Declaração das funções auxiliares de interface (para manter o main limpo)
void exibirMenu();
void cadastrarLivro(Arvore *acervo);

int main() {
    Arvore *acervo = criarArvore();
    if(acervo == NULL) {
        fprintf(stderr, "Erro ao criar a arvore de livros.\n");
        return EXIT_FAILURE;
    }
    
    char opcao;
    do {
        exibirMenu();
        scanf(" %c", &opcao);

        switch(opcao) {
            case 'a': case 'A':
                cadastrarLivro(acervo);
                break;
                
            case 'b': case 'B':
                printf("\n--- Buscar Livro ---\n");
                // TODO: buscarLivroArvore(&acervo, codigo)
                break;
                
            case 'c': case 'C':
                printf("\n--- Livros (Em Ordem) ---\n");
                listarLivrosEmOrdem(acervo);
                break;
                
            case 'd': case 'D':
                printf("\n--- Livros (Pre-Ordem) ---\n");
                listarLivrosPreOrdem(acervo);
                break;
                
            case 'e': case 'E':
                printf("\n--- Livros (Pos-Ordem) ---\n");
                listarLivrosPosOrdem(acervo);
                break;
                
            case 'f': case 'F':
                printarArvoreVisual(acervo);
                break;
                
            case 'j': case 'J':
                // printf("\nQuantidade de livros cadastrados: %d\n", contarLivros(acervo));
                break;
                
            case 'k': case 'K':
                // printf("\nAltura da arvore: %d\n", calcularAlturaArvore(&acervo));
                break;
                
            case 's': case 'S':
                printf("\nEncerrando o sistema...\n");
                break;
                
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 's' && opcao != 'S');

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