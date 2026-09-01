#include "../include/BST.hpp"
#include <iostream>

using namespace std;

Node::Node(int valor) : chave(valor) , esquerda(nullptr), direita(nullptr) {}

BST::BST() : raiz(nullptr) {}

BST::~BST() {
    destruirR(raiz);
}

void BST::destruirR(Node* no){
    if (no != nullptr) {
        destruirR(no->esquerda);
        destruirR(no->direita);
        delete no;
    }
}

void BST::inserir(int chave){
    raiz = inserirR(raiz,chave);
}

Node* BST::inserirR(Node* no, int chave){
    if (no == nullptr){
        return new Node(chave);
    }

    if (chave < no->chave) {
        no->esquerda = inserirR(no->esquerda,chave);
    } 
    else if (chave > no->chave) {
        no->direita = inserirR(no->direita,chave);
    }

    return no;
}

Node* BST::buscar(int chave){
    return buscarR(raiz,chave);
}

Node* BST::buscarR(Node* no, int chave){
    if (no == nullptr || no->chave == chave) {
        return no;
    }

    if (chave < no->chave) {
        return buscarR(no->esquerda, chave);
    }

    return buscarR(no->direita, chave);
}

void BST::remover(int chave) {
    raiz = removerR(raiz, chave);
}

Node* BST::removerR(Node* no, int chave){
    if(no == nullptr){
        return nullptr;
    }

    if (chave < no->chave) {
        no->esquerda = removerR(no->esquerda,chave);
    } 
    else if (chave > no->chave) {
        no->direita = removerR(no->direita,chave);
    }

    else{

        if (no->esquerda == nullptr && no->direita == nullptr) {
            delete no;
            return nullptr;
        }

        if (no->esquerda == nullptr) {
            Node* filhoDireito = no->direita;
            delete no;
            return filhoDireito;
        } else if (no->direita == nullptr) {
            Node* filhoEsquerdo = no->esquerda;
            delete no;
            return filhoEsquerdo;
        }

        Node* sucessor = encontrarMinimoR(no->direita);
        no->chave = sucessor->chave;
        no->direita = removerR(no->direita, sucessor->chave);
    }

    return no;
}

Node* BST::encontrarMinimoR(Node* no){
    while (no && no->esquerda != nullptr) {
        no = no->esquerda;
    }
    return no;
}

void BST::exibirOrdem() {
    exibirOrdemR(raiz);
    cout << endl;
}

void BST::exibirOrdemR(Node* no) {
    if (no != nullptr) {
        exibirOrdemR(no->esquerda);
        cout << no->chave << " ";
        exibirOrdemR(no->direita);
    }
}

