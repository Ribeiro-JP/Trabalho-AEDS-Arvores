#include "../include/splay.hpp"
#include <iostream>

using namespace std;

SPLAY::SPLAY() : raiz(nullptr) {}

SPLAY::~SPLAY() {
    destruirR(raiz);
}

void SPLAY::destruirR(Node* no) {
    if (no != nullptr) {
        destruirR(no->esquerda);
        destruirR(no->direita);
        delete no;
    }
}

Node* SPLAY::rotacionarEsqR(Node* no) {
    Node *aux = no->direita;
    no->direita = aux->esquerda;
    aux->esquerda = no;
    return aux;
}

Node* SPLAY::rotacionarDirR(Node* no) {
    Node *aux = no->esquerda;
    no->esquerda = aux->direita;
    aux->direita = no;
    return aux;
}

Node* SPLAY::splay(Node* no, int chave) {
    // Caso base: no é nulo ou a chave está na raiz
    if (no == nullptr || no->chave == chave) {
        return no;
    }

    // A chave está na subárvore esquerda
    if (no->chave > chave) {
        if (no->esquerda == nullptr) return no;

        // Zig-Zig (Esquerda Esquerda)
        if (no->esquerda->chave > chave) {
            no->esquerda->esquerda = splay(no->esquerda->esquerda, chave);
            no = rotacionarDirR(no);
        }
        // Zig-Zag (Esquerda Direita)
        else if (no->esquerda->chave < chave) {
            no->esquerda->direita = splay(no->esquerda->direita, chave);
            if (no->esquerda->direita != nullptr) {
                no->esquerda = rotacionarEsqR(no->esquerda);
            }
        }

        // Executa a segunda rotação para o nó
        return (no->esquerda == nullptr) ? no : rotacionarDirR(no);
    }
    // A chave está na subárvore direita
    else {
        if (no->direita == nullptr) return no;

        // Zag-Zig (Direita Esquerda)
        if (no->direita->chave > chave) {
            no->direita->esquerda = splay(no->direita->esquerda, chave);
            if (no->direita->esquerda != nullptr) {
                no->direita = rotacionarDirR(no->direita);
            }
        }
        // Zag-Zag (Direita Direita)
        else if (no->direita->chave < chave) {
            no->direita->direita = splay(no->direita->direita, chave);
            no = rotacionarEsqR(no);
        }

        // Executa a segunda rotação para o nó
        return (no->direita == nullptr) ? no : rotacionarEsqR(no);
    }
}

Node* SPLAY::inserirR(Node* no, int chave) {
    // Inserção padrão de Árvore Binária de Busca
    if (no == nullptr) return new Node(chave);

    if (chave < no->chave) {
        no->esquerda = inserirR(no->esquerda, chave);
    } else if (chave > no->chave) {
        no->direita = inserirR(no->direita, chave);
    }
    
    return no;
}

void SPLAY::inserir(int chave) {

    raiz = inserirR(raiz, chave);
    raiz = splay(raiz, chave);
}

Node* SPLAY::buscarR(Node* no, int chave) {
    return splay(no, chave);
}

Node* SPLAY::buscar(int chave) {
    raiz = buscarR(raiz, chave);
    if (raiz != nullptr && raiz->chave == chave) {
        return raiz;
    }
    return nullptr;
}

Node* SPLAY::removerR(Node* no, int chave) {
    if (no == nullptr) return nullptr;

    // Primeiro traz a chave para a raiz, se ela existir
    no = splay(no, chave);

    // Se a chave não estiver na árvore, apenas retorna a raiz splayada
    if (no->chave != chave) return no;

    Node* temp;
    
    // Se não tiver filho à esquerda, o filho à direita vira a nova raiz
    if (no->esquerda == nullptr) {
        temp = no;
        no = no->direita;
    } 
    // Se tiver, traz o maior elemento da subárvore esquerda para a raiz
    else {
        temp = no;
        // O maior elemento da subárvore esquerda ficará na raiz da subárvore esquerda
        no = splay(no->esquerda, chave); 
        // Conecta o filho direito antigo à nova raiz
        no->direita = temp->direita;
    }

    delete temp;
    return no;
}

void SPLAY::remover(int chave) {
    raiz = removerR(raiz, chave);
}

void SPLAY::exibirOrdemR(Node* no) {
    if (no != nullptr) {
        exibirOrdemR(no->esquerda);
        cout << no->chave << " ";
        exibirOrdemR(no->direita);
    }
}

void SPLAY::exibirOrdem() {
    exibirOrdemR(raiz);
    cout << endl;
}