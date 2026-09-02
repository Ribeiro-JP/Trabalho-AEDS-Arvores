#pragma once

struct Node
{
    int chave;
    int altura;
    Node* esquerda;
    Node* direita;
    Node(int valor): chave(valor), altura(0), esquerda(nullptr), direita(nullptr) {};
};

class AVL
{
private:
    Node* raiz;

    Node* inserirR(Node* no, int chave);
    Node* buscarR(Node* no, int chave);
    Node* removerR(Node* no, int chave);
    int obterAltura(Node* no);
    void exibirOrdemR(Node* no);
    void destruirR(Node* no);
    Node* encontrarMinimoR(Node* no);

    Node* rotacionarEsqR(Node* no);
    Node* rotacionarDirR(Node* no);
    Node* rotacionarEsqDirR(Node* no);
    Node* rotacionarDirEsqR(Node* no);


public:
    AVL();
    ~AVL();
    //detalhe bobo para evitar erros futuros
    AVL(const AVL&) = delete;            // impede cópia
    AVL& operator=(const AVL&) = delete; // impede atribuição por cópia

    void inserir(int chave);
    Node* buscar(int chave);
    void remover(int chave);
    void exibirOrdem();
};

