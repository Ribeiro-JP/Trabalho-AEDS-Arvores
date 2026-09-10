#pragma once

struct Node
{
    int x, y;
    Node* esquerda;
    Node* direita;
    Node(int x_valor, int y_valor): x(x_valor), y(y_valor), esquerda(nullptr), direita(nullptr) {}
};

class KDTREE
{
private:
    Node* raiz;

    Node* inserirR(Node* no, int x, int y, int profundidade);
    Node* buscarR(Node* no, int x, int y, int profundidade);
    Node* removerR(Node* no, int x, int y, int profundidade);
    Node* encontrarMinimoR(Node* no, int eixoAlvo, int profundidade);
    void exibirR(Node* no, int profundidade);
    void destruirR(Node* no);

public:
    KDTREE();
    ~KDTREE();
    //detalhe bobo para evitar erros futuros
    KDTREE(const KDTREE&) = delete;            // impede cópia
    KDTREE& operator=(const KDTREE&) = delete; // impede atribuição por cópia

    void inserir(int x, int y);
    Node* buscar(int x, int y);
    void remover(int x, int y);
    void exibir();
};