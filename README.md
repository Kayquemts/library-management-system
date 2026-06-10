# Sistema de Gerenciamento de Biblioteca

**Disciplina:** Estrutura de Dados — UECe  
**Professor:** Bonfim Amaro Junior  
**Equipe:** Lyanderson, Lyedson e Kayque

---

## Descrição

Sistema de gerenciamento de acervo bibliotecário desenvolvido em linguagem C, utilizando três estruturas de dados integradas:

- **Árvore Binária de Busca (ABB)** — armazena e organiza os livros por código.
- **Fila (FIFO)** — controla reservas de livros sem exemplares disponíveis.
- **Lista Encadeada** — mantém o histórico completo de empréstimos realizados.

---

## Compilação

```bash
gcc main.c livro.c Arvore.c fila.c lista.c -o biblioteca
```

> **Atenção:** os nomes dos arquivos diferenciam maiúsculas de minúsculas em Linux.  
> Certifique-se de que `Arvore.c` e `Arvore.h` estão com a inicial maiúscula.

---

## Execução

```bash
./biblioteca
```

---

## Estrutura de Arquivos

```
/trabalho_biblioteca
├── main.c       ← Menu principal e integração das estruturas
├── Livro.h      ← Definição do TAD Livro
├── livro.c      ← Implementação do TAD Livro
├── Arvore.h     ← Definição da Árvore Binária de Busca
├── Arvore.c     ← Implementação da ABB
├── fila.h       ← Definição da Fila de Reservas
├── fila.c       ← Implementação da Fila
├── lista.h      ← Definição da Lista de Histórico
├── lista.c      ← Implementação da Lista Encadeada
└── README.md
```

---

## Funcionalidades do Menu

| Opção | Funcionalidade |
|-------|----------------|
| 1 | Cadastrar novo livro |
| 2 | Buscar livro por código |
| 3 | Listar livros em ordem crescente de código |
| 4 | Listar livros em pré-ordem |
| 5 | Listar livros em pós-ordem |
| 6 | Realizar empréstimo |
| 7 | Devolver livro |
| 8 | Exibir fila de reservas |
| 9 | Exibir histórico de empréstimos |
| 10 | Exibir quantidade de livros cadastrados |
| 11 | Exibir altura da árvore |
| 12 | [EXTRA] Visualizar estrutura da árvore |
| 0 | Sair |

---

## O que está implementado hoje

### ✅ TAD Livro (`livro.h` / `livro.c`)
- [x] Estrutura `Livro` com todos os campos obrigatórios
- [x] `criarLivro()` — alocação e inicialização com `strncpy` seguro
- [x] `exibirLivro()` — exibição formatada
- [ ] `obterCodigoLivro()` — **declarada no .h, NÃO implementada no .c**
- [ ] `obterQuantidadeDisponivel()` — **declarada no .h, NÃO implementada no .c**
- [ ] `emprestarExemplar()` — **declarada no .h, NÃO implementada no .c**
- [ ] `devolverExemplar()` — **declarada no .h, NÃO implementada no .c**

### ✅ Árvore Binária de Busca (`Arvore.h` / `Arvore.c`)
- [x] Estruturas `NoArvore` e `Arvore`
- [x] `criarArvore()`
- [x] `inserirLivroArvore()` — com verificação de código duplicado
- [x] `listarLivrosEmOrdem()` — percurso em-ordem
- [x] `listarLivrosPreOrdem()` — percurso pré-ordem
- [x] `listarLivrosPosOrdem()` — percurso pós-ordem
- [x] `printarArvoreVisual()` — extra: visualização lateral da árvore
- [ ] `buscarLivroArvore()` — **declarada no .h, NÃO implementada no .c**
- [ ] `contarLivros()` — **declarada no .h, NÃO implementada no .c**
- [ ] `calcularAlturaArvore()` — **declarada no .h, NÃO implementada no .c**

### ✅ Fila de Reservas (`fila.h` / `fila.c`)
- [x] Estruturas `Reserva`, `NoFila`, `Fila`
- [x] `criarFila()`
- [x] `enfileirarReserva()`
- [x] `desenfileirarReserva()` — com retorno de sentinela em fila vazia
- [x] `filaVazia()`
- [x] `mostrarFila()` _(nome diferente de `exibirReservas` do enunciado — sem impacto funcional)_

### ✅ Lista de Histórico (`lista.h` / `lista.c`)
- [x] Estruturas `Emprestimo`, `NoLista`, `Lista`
- [x] `criarLista()`
- [x] `inserirEmprestimo()` — inserção no início (O(1))
- [x] `listarEmprestimos()`
- [x] `listaVazia()`
- [x] `liberarLista()` — libera toda a memória da lista

### ✅ main.c
- [x] Integração completa das três estruturas
- [x] Menu com todas as 11 opções obrigatórias + 1 extra
- [x] Cadastro com verificação de código duplicado
- [x] Busca por código com feedback de não encontrado
- [x] Empréstimo com redução de estoque e registro no histórico
- [x] Empréstimo com oferta de reserva quando indisponível
- [x] Devolução com atendimento automático do primeiro da fila
- [x] Limpeza básica de memória ao encerrar

---

## O que falta implementar

> As funções abaixo estão **declaradas nos headers** mas sem corpo nos arquivos `.c`.  
> O sistema **não compila** sem elas. Adicione-as nos arquivos indicados:

### Em `livro.c` — 4 funções:

```c
int obterCodigoLivro(Livro *livro);
int obterQuantidadeDisponivel(Livro *livro) ;
void emprestarExemplar(Livro *livro);
void devolverExemplar(Livro *livro);
```

### Em `Arvore.c` — 3 funções:

```c
/* Busca iterativa por código */
Livro *buscarLivroArvore(Arvore *arvore, int codigo);

/* Contagem recursiva de nós */
static int contarNosRecursivo(NoArvore *raiz);

int contarLivros(Arvore *arvore);

/* Altura recursiva da árvore */
static int alturaRecursiva(NoArvore *raiz);

int calcularAlturaArvore(Arvore *arvore);
```

---

## Funcionalidades extras implementadas

- [x] Visualização lateral da estrutura da árvore (`printarArvoreVisual`)
- [x] Atendimento automático da fila de reservas na devolução
- [x] Liberação de memória da lista ao encerrar

## Funcionalidades extras não implementadas (diferenciais do enunciado)

- [ ] Remoção de livro da ABB
- [ ] Salvamento e carregamento de dados em arquivo
- [ ] Busca por título ou autor
- [ ] Listagem de livros indisponíveis
- [ ] Listagem de livros com fila de reserva
- [ ] Liberação completa de memória da árvore e da fila ao encerrar

---

## Limitações conhecidas

- A fila de reservas é única para todos os livros; na devolução, o atendimento automático só ocorre se o **primeiro** da fila estiver esperando exatamente o livro devolvido.
- Não há persistência de dados: ao encerrar o programa, todas as informações são perdidas.
- A memória da árvore e dos nós da fila não é liberada completamente ao sair (apenas a lista é liberada via `liberarLista`).

---

## Exemplos de uso

```
Opcao: 1
Codigo       : 101
Titulo       : Clean Code
Autor        : Lyanderson S. R.
Ano          : 2008
Qtd exemplares: 2
[SUCESSO] Livro 'Clean Code' cadastrado com sucesso!

Opcao: 6
Codigo do livro: 101
Nome do usuario: Kayque
[SUCESSO] Emprestimo realizado!
  Usuario : Kayque
  Livro   : Clean Code (cod. 101)
  Disponiveis restantes: 1
```
