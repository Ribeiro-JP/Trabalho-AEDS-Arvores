#pragma once

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>

// -----------------------------------------------------------------------
// Exportador genérico de árvores binárias (BST, AVL, Treap, Splay, KD-Tree)
// pra formato .dot (Graphviz). NodeT só precisa ter ->esquerda e ->direita.
// O rótulo de cada nó vem de uma função/lambda que você passa, assim cada
// estrutura mostra a informação que faz sentido pra ela (chave simples,
// chave+altura, chave+prioridade, coordenadas x/y etc).
//
// "titulo" vira o texto grande no topo da imagem, pra ela já vir
// autoexplicativa quando colada no relatório.
// -----------------------------------------------------------------------

template <typename NodeT, typename RotuloFn>
void escreverNosBinario(NodeT* no, std::ofstream& out, RotuloFn& rotulo) {
    if (no == nullptr) return;

    out << "  n" << reinterpret_cast<uintptr_t>(no)
        << " [label=\"" << rotulo(no) << "\"];\n";

    if (no->esquerda != nullptr) {
        out << "  n" << reinterpret_cast<uintptr_t>(no)
            << " -> n" << reinterpret_cast<uintptr_t>(no->esquerda) << ";\n";
        escreverNosBinario(no->esquerda, out, rotulo);
    }
    if (no->direita != nullptr) {
        out << "  n" << reinterpret_cast<uintptr_t>(no)
            << " -> n" << reinterpret_cast<uintptr_t>(no->direita) << ";\n";
        escreverNosBinario(no->direita, out, rotulo);
    }
}

template <typename NodeT, typename RotuloFn>
void exportarDotBinario(NodeT* raiz, const std::string& caminho, RotuloFn rotulo,
                         const std::string& titulo = "") {
    std::filesystem::path caminhoPath(caminho);
    if (caminhoPath.has_parent_path()) {
        std::filesystem::create_directories(caminhoPath.parent_path());
    }
    std::ofstream out(caminho);
    out << "digraph Arvore {\n";
    out << "  graph [fontsize=22, fontname=\"Helvetica-Bold\", labelloc=t, "
           "label=\"" << titulo << "\", nodesep=0.4, ranksep=0.6];\n";
    out << "  node [shape=circle, style=filled, fillcolor=\"#cfe8ff\", "
           "fontname=\"Helvetica\", fontsize=16, width=0.9, fixedsize=true];\n";
    out << "  edge [arrowhead=none, penwidth=1.4];\n";
    if (raiz != nullptr) {
        escreverNosBinario(raiz, out, rotulo);
    } else {
        out << "  vazio [label=\"(arvore vazia)\", shape=plaintext];\n";
    }
    out << "}\n";
}

// -----------------------------------------------------------------------
// Exportador genérico de árvores de prefixo (Trie, Patricia) pra .dot.
// NodeT precisa ter ->filhos[26] e ->fim. Cada aresta é rotulada com a
// letra correspondente ao índice do array. O rótulo do nó vem de uma
// função à parte (Trie normalmente deixa vazio; Patricia mostra o
// trecho de prefixo comprimido guardado ali).
// -----------------------------------------------------------------------

template <typename NodeT, typename RotuloFn>
void escreverNosPrefixo(NodeT* no, std::ofstream& out, RotuloFn& rotulo) {
    if (no == nullptr) return;

    out << "  n" << reinterpret_cast<uintptr_t>(no)
        << " [label=\"" << rotulo(no) << "\""
        << ", fillcolor=\"" << (no->fim ? "#ffd27f" : "#cfe8ff") << "\"];\n";

    for (int i = 0; i < 26; i++) {
        if (no->filhos[i] != nullptr) {
            char letra = static_cast<char>('a' + i);
            out << "  n" << reinterpret_cast<uintptr_t>(no)
                << " -> n" << reinterpret_cast<uintptr_t>(no->filhos[i])
                << " [label=\"" << letra << "\", fontsize=16, arrowhead=normal];\n";
            escreverNosPrefixo(no->filhos[i], out, rotulo);
        }
    }
}

template <typename NodeT, typename RotuloFn>
void exportarDotPrefixo(NodeT* raiz, const std::string& caminho, RotuloFn rotulo,
                         const std::string& titulo = "") {
    std::filesystem::path caminhoPath(caminho);
    if (caminhoPath.has_parent_path()) {
        std::filesystem::create_directories(caminhoPath.parent_path());
    }
    std::ofstream out(caminho);
    out << "digraph Arvore {\n";
    out << "  graph [fontsize=22, fontname=\"Helvetica-Bold\", labelloc=t, "
           "label=\"" << titulo << "\", nodesep=0.4, ranksep=0.6];\n";
    out << "  node [shape=circle, style=filled, fontname=\"Helvetica\", "
           "fontsize=15, width=1.0, fixedsize=true];\n";
    if (raiz != nullptr) {
        escreverNosPrefixo(raiz, out, rotulo);
    } else {
        out << "  vazio [label=\"(arvore vazia)\", shape=plaintext];\n";
    }
    out << "}\n";
}