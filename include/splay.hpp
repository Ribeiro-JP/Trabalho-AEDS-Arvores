#pragma once

struct Node
{
    int chave;
    Node* esquerda;
    Node* direita;
    Node(int valor): chave(valor), esquerda(nullptr), direita(nullptr) {};
};

class SPLAY
{
private:
    Node* raiz;

    Node* inserirR(Node* no, int chave);
    Node* buscarR(Node* no, int chave);
    Node* removerR(Node* no, int chave);
    void exibirOrdemR(Node* no);
    void destruirR(Node* no);
    Node* splay(Node* no, int chave);

    Node* rotacionarEsqR(Node* no);
    Node* rotacionarDirR(Node* no);

public:
    SPLAY();
    ~SPLAY();
    //detalhe bobo para evitar erros futuros
    SPLAY(const SPLAY&) = delete;            // impede cópia
    SPLAY& operator=(const SPLAY&) = delete; // impede atribuição por cópia

    void inserir(int chave);
    Node* buscar(int chave);
    void remover(int chave);
    void exibirOrdem();
    Node* obterRaiz() const { return raiz; }
};

