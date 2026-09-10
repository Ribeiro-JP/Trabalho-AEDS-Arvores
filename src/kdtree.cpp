#include "../include/kdtree.hpp"
#include <iostream>

using namespace std;

KDTREE::KDTREE() : raiz(nullptr) {}

KDTREE::~KDTREE() {
    destruirR(raiz);
}

void KDTREE::destruirR(Node* no) {
    if (no != nullptr) {
        destruirR(no->esquerda);
        destruirR(no->direita);
        delete no;
    }
}

// eixo 0 = compara por x, eixo 1 = compara por y
// o eixo usado em cada nível é definido pela profundidade (profundidade % 2)

Node* KDTREE::inserirR(Node* no, int x, int y, int profundidade) {
    if (no == nullptr) {
        return new Node(x, y);
    }

    if (no->x == x && no->y == y) {
        return no; // ponto duplicado, ignora
    }

    int eixo = profundidade % 2;
    int valorNovo = (eixo == 0) ? x : y;
    int valorAtual = (eixo == 0) ? no->x : no->y;

    if (valorNovo < valorAtual) {
        no->esquerda = inserirR(no->esquerda, x, y, profundidade + 1);
    } else {
        no->direita = inserirR(no->direita, x, y, profundidade + 1);
    }

    return no;
}

void KDTREE::inserir(int x, int y) {
    raiz = inserirR(raiz, x, y, 0);
}

Node* KDTREE::buscarR(Node* no, int x, int y, int profundidade) {
    if (no == nullptr) {
        return nullptr;
    }

    if (no->x == x && no->y == y) {
        return no;
    }

    int eixo = profundidade % 2;
    int valorBusca = (eixo == 0) ? x : y;
    int valorAtual = (eixo == 0) ? no->x : no->y;

    if (valorBusca < valorAtual) {
        return buscarR(no->esquerda, x, y, profundidade + 1);
    } else {
        return buscarR(no->direita, x, y, profundidade + 1);
    }
}

Node* KDTREE::buscar(int x, int y) {
    return buscarR(raiz, x, y, 0);
}

// Encontra o nó de MENOR valor no eixo 'eixoAlvo' dentro da subárvore de 'no'.
// Isso NÃO é uma busca de mínimo comum: como o critério de comparação alterna
// por nível, o mínimo pode estar tanto na esquerda quanto na direita quando o
// eixo do nível atual não é o eixo que estamos procurando.
Node* KDTREE::encontrarMinimoR(Node* no, int eixoAlvo, int profundidade) {
    if (no == nullptr) {
        return nullptr;
    }

    int eixoAtual = profundidade % 2;

    if (eixoAtual == eixoAlvo) {
        // este nível decide exatamente pelo eixo que procuramos -> o mínimo
        // só pode estar na subárvore esquerda (ou ser o próprio nó)
        if (no->esquerda == nullptr) {
            return no;
        }
        return encontrarMinimoR(no->esquerda, eixoAlvo, profundidade + 1);
    }

    // este nível não decide pelo eixo que procuramos -> o mínimo pode estar
    // em qualquer uma das duas subárvores, precisa comparar os candidatos
    Node* minEsq = encontrarMinimoR(no->esquerda, eixoAlvo, profundidade + 1);
    Node* minDir = encontrarMinimoR(no->direita, eixoAlvo, profundidade + 1);
    Node* minimo = no;

    auto valor = [eixoAlvo](Node* n) { return (eixoAlvo == 0) ? n->x : n->y; };

    if (minEsq != nullptr && valor(minEsq) < valor(minimo)) {
        minimo = minEsq;
    }
    if (minDir != nullptr && valor(minDir) < valor(minimo)) {
        minimo = minDir;
    }

    return minimo;
}

Node* KDTREE::removerR(Node* no, int x, int y, int profundidade) {
    if (no == nullptr) {
        return nullptr;
    }

    int eixo = profundidade % 2;

    if (no->x == x && no->y == y) {
        // achou o ponto a remover
        if (no->direita != nullptr) {
            // substitui pelo mínimo (no eixo deste nível) da subárvore direita
            Node* sucessor = encontrarMinimoR(no->direita, eixo, profundidade + 1);
            no->x = sucessor->x;
            no->y = sucessor->y;
            no->direita = removerR(no->direita, sucessor->x, sucessor->y, profundidade + 1);
        } else if (no->esquerda != nullptr) {
            // sem filho direito: usa o mínimo da esquerda, e move a
            // subárvore inteira pra direita (convenção clássica da KD-Tree,
            // já que ela não permite comparação direta de "sucessor" à esquerda)
            Node* sucessor = encontrarMinimoR(no->esquerda, eixo, profundidade + 1);
            no->x = sucessor->x;
            no->y = sucessor->y;
            no->direita = removerR(no->esquerda, sucessor->x, sucessor->y, profundidade + 1);
            no->esquerda = nullptr;
        } else {
            // folha
            delete no;
            return nullptr;
        }
        return no;
    }

    int valorBusca = (eixo == 0) ? x : y;
    int valorAtual = (eixo == 0) ? no->x : no->y;

    if (valorBusca < valorAtual) {
        no->esquerda = removerR(no->esquerda, x, y, profundidade + 1);
    } else {
        no->direita = removerR(no->direita, x, y, profundidade + 1);
    }

    return no;
}

void KDTREE::remover(int x, int y) {
    raiz = removerR(raiz, x, y, 0);
}

void KDTREE::exibirR(Node* no, int profundidade) {
    if (no != nullptr) {
        cout << "(" << no->x << ", " << no->y << ") ";
        exibirR(no->esquerda, profundidade + 1);
        exibirR(no->direita, profundidade + 1);
    }
}

void KDTREE::exibir() {
    exibirR(raiz, 0);
    cout << endl;
}