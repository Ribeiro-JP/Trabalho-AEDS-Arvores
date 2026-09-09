#pragma once

struct Node
{
    int chave;
    int prioridade;
    Node* esquerda;
    Node* direita;
    Node(int valor,int valor_prioridade): chave(valor), prioridade(valor_prioridade), esquerda(nullptr), direita(nullptr) {};
};

class TREAP
{
private:
    Node* raiz;

    int gerarPrioridade();
    Node* inserirR(Node* no, int chave, int prioridade);
    Node* buscarR(Node* no, int chave);
    Node* removerR(Node* no, int chave);
    void exibirOrdemR(Node* no);
    void destruirR(Node* no);

    Node* rotacionarEsqR(Node* no);
    Node* rotacionarDirR(Node* no);

public:
    TREAP();
    ~TREAP();
    //detalhe bobo para evitar erros futuros
    TREAP(const TREAP&) = delete;            // impede cópia
    TREAP& operator=(const TREAP&) = delete; // impede atribuição por cópia

    void inserir(int chave);//inserir com prioridade realmente aleatoria
    void inserir(int chave, int prioridade);//inserir para testes, a prioridade pode ser "definida"
    Node* buscar(int chave);
    void remover(int chave);
    void exibirOrdem();
};

/*
 * Nesse caso aqui aqui das duas inserções, o inserir com apenas int chave como
 * entrada, realmente gera prioridades para heap fora do controle do usuario
 * enquanto isso a que tem int prioridade permite que vc insira uma valor
 * para o rand e que assim possa repetir os mesmos testes varias vezes.
 * 
*/
