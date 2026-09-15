<div align="center">

![C++](https://img.shields.io/badge/C++-17-00599C?style=flat\&logo=cplusplus)
![Python](https://img.shields.io/badge/Python-3-3776AB?style=flat\&logo=python)
![Make](https://img.shields.io/badge/Build-Make-brightgreen?style=flat\&logo=gnu)

# Trabalho de Estruturas em Árvores

**Trabalho acadêmico voltado ao estudo, implementação, visualização e análise experimental de estruturas de dados em árvores.**

</div>

---

## O que é este projeto?

Este repositório contém a implementação e avaliação de diferentes **estruturas de dados baseadas em árvores**, desenvolvidas em C++17.

O projeto reúne implementações, testes automatizados, experimentos de desempenho, geração de conjuntos de dados e ferramentas para visualização das estruturas.

---

## Estruturas Implementadas

| Estrutura    | Explicação                                                                                          |
| ------------ | --------------------------------------------------------------------------------------------------- |
| **BST**      | Árvore de busca que organiza os valores menores à esquerda e maiores à direita.                     |
| **AVL**      | Árvore de busca que se mantém balanceada através de rotações.                                       |
| **Trie**     | Árvore que organiza palavras através de seus prefixos.                                              |
| **Patricia** | Trie compactada que reduz caminhos desnecessários entre os nós.                                     |
| **Splay**    | Árvore que reorganiza seus elementos após acessos, trazendo o elemento acessado para perto da raiz. |
| **Treap**    | Combina uma árvore de busca com um heap usando prioridades.                                         |
| **KD-Tree**  | Organiza pontos no espaço para facilitar buscas espaciais.                                          |

A **BST** e a **AVL** são utilizadas como estruturas de referência para comparação com as demais implementações.

---

## Estrutura do Projeto

```text
.
├── include/                  # Arquivos de cabeçalho das estruturas
│   ├── AVL.hpp
│   ├── BST.hpp
│   ├── kdtree.hpp
│   ├── patricia.hpp
│   ├── splay.hpp
│   ├── treap.hpp
│   └── trie.hpp
│
├── src/                      # Implementações das estruturas
│   ├── AVL.cpp
│   ├── BST.cpp
│   ├── kdtree.cpp
│   ├── patricia.cpp
│   ├── splay.cpp
│   ├── treap.cpp
│   └── trie.cpp
│
├── test/                     # Testes das estruturas
│   ├── test_AVL.cpp
│   ├── test_BST.cpp
│   ├── test_kdtree.cpp
│   ├── test_patricia.cpp
│   ├── test_splay.cpp
│   ├── test_treap.cpp
│   └── test_trie.cpp
│
├── experimentos/             # Experimentos e análise de desempenho
│   ├── exp_AVL.cpp
│   ├── exp_BST.cpp
│   ├── exp_kdtree.cpp
│   ├── exp_patricia.cpp
│   ├── exp_splay.cpp
│   ├── exp_treap.cpp
│   ├── exp_trie.cpp
│   ├── gerar_datasets.py
│   └── gerar_graficos.py
│
├── visualizacao/             # Programas para geração das visualizações
│   ├── vis_AVL.cpp
│   ├── vis_BST.cpp
│   ├── vis_kdtree.cpp
│   ├── vis_patricia.cpp
│   ├── vis_splay.cpp
│   ├── vis_treap.cpp
│   ├── vis_trie.cpp
│   └── rendered/             # Imagens geradas
│
└── Makefile                  # Automação do projeto
```

---

## Compilação, Execução e Testes

O projeto utiliza um `Makefile` para facilitar a compilação, execução dos testes, experimentos e geração das visualizações.

### Pré-requisitos

Certifique-se de possuir o compilador C++, o Make, o Python 3 e o Graphviz instalados:

```bash
sudo apt update
sudo apt install build-essential python3 graphviz
```

Para verificar as instalações:

```bash
g++ --version
make --version
python3 --version
dot -V
```

### Comandos Disponíveis

| Comando             | Função                                      |
| ------------------- | ------------------------------------------- |
| `make`              | Compila o projeto                           |
| `make test`         | Executa os testes das estruturas            |
| `make datasets`     | Gera os conjuntos de dados dos experimentos |
| `make experimentos` | Executa os experimentos de desempenho       |
| `make graficos`     | Gera os gráficos dos resultados             |
| `make visualizacao` | Gera as representações visuais das árvores  |
| `make clean`        | Remove os arquivos gerados                  |

### Fluxo recomendado

Para executar o projeto completo, recomenda-se seguir esta ordem:

```bash
make
```

Primeiro, compile o projeto.

```bash
make test
```

Em seguida, execute os testes para verificar o funcionamento das estruturas.

```bash
make datasets
```

Gere os conjuntos de dados utilizados nos experimentos.

```bash
make experimentos
```

Execute os experimentos de desempenho utilizando os datasets gerados.

```bash
make graficos
```

Gere os gráficos a partir dos resultados obtidos.

```bash
make visualizacao
```

Por fim, gere as representações visuais das estruturas.

Caso seja necessário realizar uma nova compilação do projeto, os arquivos gerados podem ser removidos com:

```bash
make clean
```

---

## Tecnologias Utilizadas

* **C++17** — implementação das estruturas de dados, testes e experimentos;
* **Python 3** — geração dos conjuntos de dados e gráficos;
* **Make** — automação da compilação e execução das tarefas;
* **Graphviz** — geração das representações visuais das árvores.
