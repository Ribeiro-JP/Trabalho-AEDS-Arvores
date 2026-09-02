#include "../include/AVL.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

AVL::AVL() : raiz(nullptr) {}

AVL::~AVL() {
    destruirR(raiz);
}

void AVL::destruirR(Node* no){
    if (no != nullptr) {
        destruirR(no->esquerda);
        destruirR(no->direita);
        delete no;
    }
}

Node* AVL::buscar(int chave){
    return buscarR(raiz,chave);
}

Node* AVL::buscarR(Node* no, int chave){
    if (no == nullptr || no->chave == chave) {
        return no;
    }

    if (chave < no->chave) {
        return buscarR(no->esquerda, chave);
    }

    return buscarR(no->direita, chave);
}

Node* AVL::encontrarMinimoR(Node* no){
    while (no && no->esquerda != nullptr) {
        no = no->esquerda;
    }
    return no;
}

void AVL::exibirOrdem() {
    exibirOrdemR(raiz);
    cout << endl;
}

void AVL::exibirOrdemR(Node* no) {
    if (no != nullptr) {
        exibirOrdemR(no->esquerda);
        cout << no->chave << " ";
        exibirOrdemR(no->direita);
    }
}

int AVL::obterAltura(Node* no){
    return (no == nullptr) ? -1 : no->altura;
}

void AVL::inserir(int chave){
    raiz = inserirR(raiz,chave);
}

Node* AVL::inserirR(Node* no, int chave){
    if (no == nullptr){
        return new Node(chave);
    }

    if (chave < no->chave) {
        no->esquerda = inserirR(no->esquerda,chave);
    } 
    else if (chave > no->chave) {
        no->direita = inserirR(no->direita,chave);
    } else{
        return no;
    }

    no->altura = 1 + max(obterAltura(no->direita),obterAltura(no->esquerda));

    int fator_balanceamento = obterAltura(no->direita) - obterAltura(no->esquerda);

    if(fator_balanceamento > 1){ 
        return (chave > no->direita->chave) ? rotacionarEsqR(no) : rotacionarDirEsqR(no);
    }
    if(fator_balanceamento < -1){
        return (chave < no->esquerda->chave) ? rotacionarDirR(no) : rotacionarEsqDirR(no);
    }

    return no;

}

Node* AVL::rotacionarEsqR(Node* no){
    Node *aux = no->direita;
    no->direita = aux->esquerda;
    aux->esquerda = no;
    no->altura = 1 + max(obterAltura(no->direita),obterAltura(no->esquerda));
    aux->altura = 1 + max(obterAltura(aux->direita),no->altura);
    return aux;
}

Node* AVL::rotacionarDirR(Node* no){
    Node *aux = no->esquerda;
    no->esquerda = aux->direita;
    aux->direita = no;
    no->altura = 1 + max(obterAltura(no->direita),obterAltura(no->esquerda));
    aux->altura = 1 + max(obterAltura(aux->esquerda),no->altura);
    return aux;   
}

Node* AVL::rotacionarEsqDirR(Node* no) {
    no->esquerda = rotacionarEsqR(no->esquerda);
    return rotacionarDirR(no);
}

Node* AVL::rotacionarDirEsqR(Node* no) {
    no->direita = rotacionarDirR(no->direita);
    return rotacionarEsqR(no);
}

void AVL::remover(int chave) {
    raiz = removerR(raiz, chave);
}

Node* AVL::removerR(Node* no, int chave){
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

    no->altura = 1 + max(obterAltura(no->direita),obterAltura(no->esquerda));

    int fator_balanceamento = obterAltura(no->direita) - obterAltura(no->esquerda);

    if(fator_balanceamento > 1){ 
        int fbDireita = obterAltura(no->direita->direita) - obterAltura(no->direita->esquerda);
        return (fbDireita >= 0) ? rotacionarEsqR(no) : rotacionarDirEsqR(no);
    }
    if(fator_balanceamento < -1){
        int fbEsquerda = obterAltura(no->esquerda->esquerda) - obterAltura(no->esquerda->direita);
        return (fbEsquerda <= 0) ? rotacionarDirR(no) : rotacionarEsqDirR(no);
    }

    return no;
}
