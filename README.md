# Sistema de Gerenciamento de Biblioteca

**Disciplina:** Estrutura de Dados — UECe  
**Professor:** Bonfim Amaro Junior  
**Equipe:** Lyanderson, Lyedson e Kayque

---

## Descrição

Sistema de gerenciamento de acervo bibliotecário desenvolvido em linguagem C, utilizando três estruturas de dados integradas:

- **Árvore AVL (Árvore Binária de Busca auto-balanceada)** — armazena e organiza os livros por código, garantindo altura mínima em todas as inserções.
- **Fila (FIFO)** — controla reservas de livros sem exemplares disponíveis.
- **Lista Encadeada** — mantém o histórico completo de empréstimos realizados.

---

## Compilação

```bash
gcc main.c livro.c arvore.c fila.c lista.c -o biblioteca
```

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
├── livro.h      ← Definição do TAD Livro
├── livro.c      ← Implementação do TAD Livro
├── arvore.h     ← Definição da Árvore AVL
├── arvore.c     ← Implementação da Árvore AVL
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
| 1  | Cadastrar novo livro |
| 2  | Buscar livro por código |
| 3  | Listar livros em ordem crescente de código |
| 4  | Listar livros em pré-ordem |
| 5  | Listar livros em pós-ordem |
| 6  | Realizar empréstimo |
| 7  | Devolver livro |
| 8  | Exibir fila de reservas |
| 9  | Exibir histórico de empréstimos |
| 10 | Exibir quantidade de livros cadastrados |
| 11 | Exibir altura da árvore |
| 12 | [EXTRA] Visualizar estrutura da árvore |
| 0  | Sair |

---

## Status da Implementação

### ✅ TAD Livro (`livro.h` / `livro.c`)
- [x] Estrutura `Livro` com todos os campos obrigatórios
- [x] `criarLivro()` — alocação e inicialização com `strncpy` seguro
- [x] `exibirLivro()` — exibição formatada
- [x] `obterCodigoLivro()` — retorna o código do livro
- [x] `obterQuantidadeDisponivel()` — retorna a quantidade disponível
- [x] `emprestarExemplar()` — decrementa a quantidade disponível
- [x] `devolverExemplar()` — incrementa a quantidade disponível

### ✅ Árvore AVL (`arvore.h` / `arvore.c`)
- [x] Estruturas `NoArvore` (com campo `altura`) e `Arvore`
- [x] `criarArvore()`
- [x] `inserirLivroArvore()` — inserção com balanceamento AVL automático (rotações LL, LR, RR, RL)
- [x] `buscarLivroArvore()` — busca iterativa O(log n)
- [x] `contarLivros()` — contagem recursiva de nós
- [x] `calcularAlturaArvore()` — leitura O(1) da altura armazenada na raiz
- [x] `listarLivrosEmOrdem()` — percurso em-ordem (ordem crescente de código)
- [x] `listarLivrosPreOrdem()` — percurso pré-ordem
- [x] `listarLivrosPosOrdem()` — percurso pós-ordem
- [x] `printarArvoreVisual()` — [EXTRA] visualização lateral da árvore no terminal

### ✅ Fila de Reservas (`fila.h` / `fila.c`)
- [x] Estruturas `Reserva`, `NoFila`, `Fila`
- [x] `criarFila()`
- [x] `enfileirarReserva()` — insere no fim (política FIFO)
- [x] `desenfileirarReserva()` — remove do início, retorna sentinela se vazia
- [x] `filaVazia()`
- [x] `mostrarFila()` — exibe todos os usuários na fila com seus livros

### ✅ Lista de Histórico (`lista.h` / `lista.c`)
- [x] Estruturas `Emprestimo`, `NoLista`, `Lista`
- [x] `criarLista()`
- [x] `inserirEmprestimo()` — inserção no início O(1)
- [x] `listarEmprestimos()` — exibe usuário, código e título de cada empréstimo
- [x] `listaVazia()`
- [x] `liberarLista()` — libera toda a memória da lista

### ✅ main.c
- [x] Integração completa das três estruturas
- [x] Menu com todas as 11 opções obrigatórias + 1 extra
- [x] Cadastro com verificação de código duplicado
- [x] Busca por código com feedback de não encontrado
- [x] Empréstimo com redução de estoque e registro automático no histórico
- [x] Empréstimo com oferta de entrada na fila quando indisponível
- [x] Devolução com atendimento automático do primeiro da fila (se for do mesmo livro)
- [x] Liberação de memória da lista ao encerrar

---

## Funcionalidades extras implementadas

- [x] **Balanceamento AVL** — a árvore se rebalanceia a cada inserção via rotações simples e duplas, mantendo altura O(log n)
- [x] **Visualização lateral da árvore** — opção 12 exibe a estrutura da AVL deitada no terminal
- [x] **Atendimento automático da fila na devolução** — ao devolver um livro, o sistema verifica se o primeiro da fila espera aquele título e já realiza o empréstimo automaticamente

## Funcionalidades extras não implementadas

- [ ] Remoção de livro da árvore AVL
- [ ] Salvamento e carregamento de dados em arquivo
- [ ] Busca por título ou autor
- [ ] Listagem de livros indisponíveis
- [ ] Listagem de livros com fila de reserva ativa
- [ ] Liberação completa de memória da árvore e dos nós da fila ao encerrar

---

## Limitações conhecidas

- A fila de reservas é única para todos os livros; na devolução, o atendimento automático só ocorre se o **primeiro** da fila estiver aguardando exatamente o livro devolvido.
- Não há persistência de dados: ao encerrar o programa, todas as informações são perdidas.
- A memória dos nós da árvore AVL e dos nós da fila não é liberada ao encerrar (apenas a lista é liberada via `liberarLista`).

---

## Exemplos de uso

```
Opcao: 1
Codigo        : 101
Titulo        : Clean Code
Autor         : Robert C. Martin
Ano           : 2008
Qtd exemplares: 2
[SUCESSO] Livro 'Clean Code' cadastrado com sucesso!

Opcao: 6
Codigo do livro: 101
Nome do usuario: Kayque
[SUCESSO] Emprestimo realizado!
  Usuario : Kayque
  Livro   : Clean Code (cod. 101)
  Disponiveis restantes: 1

Opcao: 6
Codigo do livro: 101
Nome do usuario: Lyanderson
[SUCESSO] Emprestimo realizado!
  Usuario : Lyanderson
  Livro   : Clean Code (cod. 101)
  Disponiveis restantes: 0

Opcao: 6
Codigo do livro: 101
Nome do usuario: Lyedson
[AVISO] Nao ha exemplares disponiveis para 'Clean Code'.
Deseja entrar na fila de reservas?
  1 - Sim
  2 - Nao
Opcao: 1
[INFO] Lyedson entrou na fila de reservas para 'Clean Code'.

Opcao: 7
Codigo do livro: 101
[SUCESSO] Devolucao registrada para 'Clean Code'.
  Disponiveis agora: 1/2
[INFO] Exemplar automaticamente reservado para 'Lyedson' (primeiro da fila).
  Disponiveis agora: 0/2
```