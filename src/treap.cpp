#include "../include/treap.hpp"
#include <iostream>
#include <random>

//LEMBRANDO QUE O HEAP USADO E O MAX-HEAP

using namespace std;

TREAP::TREAP() : raiz(nullptr) {}

TREAP::~TREAP() {
    destruirR(raiz);
}

void TREAP::destruirR(Node* no) {
    if (no != nullptr) {
        destruirR(no->esquerda);
        destruirR(no->direita);
        delete no;
    }
}

Node* TREAP::rotacionarEsqR(Node* no) {
    Node *aux = no->direita;
    no->direita = aux->esquerda;
    aux->esquerda = no;
    return aux;
}

Node* TREAP::rotacionarDirR(Node* no) {
    Node *aux = no->esquerda;
    no->esquerda = aux->direita;
    aux->direita = no;
    return aux;
}

Node* TREAP::buscarR(Node* no, int chave) {
    if (no == nullptr || no->chave == chave) {
        return no;
    }

    if (chave < no->chave) {
        return buscarR(no->esquerda, chave);
    }

    return buscarR(no->direita, chave);
}

Node* TREAP::buscar(int chave) {
    return buscarR(raiz, chave);
}

Node* TREAP::removerR(Node* no, int chave) {
    if (no == nullptr) {
        return nullptr;
    }

    if (chave < no->chave) {
        no->esquerda = removerR(no->esquerda, chave);
    } else if (chave > no->chave) {
        no->direita = removerR(no->direita, chave);
    } else {
        if (no->esquerda == nullptr && no->direita == nullptr) {
            delete no;
            return nullptr;
        } 
        else if (no->esquerda != nullptr && no->direita != nullptr) {
            if (no->esquerda->prioridade > no->direita->prioridade) {
                no = rotacionarDirR(no);
                no->direita = removerR(no->direita, chave);
            } else {
                no = rotacionarEsqR(no);
                no->esquerda = removerR(no->esquerda, chave);
            }
        } 
        else {
            Node* filho = (no->esquerda != nullptr) ? no->esquerda : no->direita;
            delete no;
            return filho;
        }
    }
    
    return no;
}

void TREAP::remover(int chave) {
    raiz = removerR(raiz, chave);
}

void TREAP::exibirOrdemR(Node* no) {
    if (no != nullptr) {
        exibirOrdemR(no->esquerda);
        cout << "[Chave: " << no->chave << " | Prioridade: " << no->prioridade << "] ";
        exibirOrdemR(no->direita);
    }
}

void TREAP::exibirOrdem() {
    exibirOrdemR(raiz);
    cout << endl;
}

int TREAP::gerarPrioridade() {
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1000000); // Intervalo de prioridades
    
    return dist(gen);
}

Node* TREAP::inserirR(Node* no, int chave, int prioridade_gerada) {
    if (no == nullptr) {
        return new Node(chave, prioridade_gerada);
    }

    if (chave < no->chave) {
        no->esquerda = inserirR(no->esquerda, chave, prioridade_gerada);

        if (no->esquerda->prioridade > no->prioridade) {
            no = rotacionarDirR(no);
        }
    } else if (chave > no->chave) {
        no->direita = inserirR(no->direita, chave, prioridade_gerada);

        if (no->direita->prioridade > no->prioridade) {
            no = rotacionarEsqR(no);
        }
    } else {
        return no; 
    }
    
    return no;
}

void TREAP::inserir(int chave) {

    raiz = inserirR(raiz, chave, gerarPrioridade());
}

void TREAP::inserir(int chave, int prioridade) {
    raiz = inserirR(raiz, chave, prioridade);
}