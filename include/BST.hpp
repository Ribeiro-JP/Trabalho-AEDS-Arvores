#pragma once

struct Node
{
    int chave;
    Node* esquerda;
    Node* direita;
    Node(int valor): chave(valor), esquerda(nullptr), direita(nullptr) {};
};
/*
 * Essa é a estrutura base que vou usar no trabalho inteiro
 * acho melhor detalhar um pouco oque estou fazendo pois estou um
 * pouco esquecido de como se coda em c++,
 * aqui em cima eu tenho uma struct que resume um no simples, direita,
 * esquerda, chave é o construtor do no que gera ele com o valor já
 * sendo a chave e os dois ponteiros vazios.
 */

class BST
{
private:
    Node* raiz;

    Node* inserirR(Node* no, int chave);
    Node* buscarR(Node* no, int chave);
    Node* removerR(Node* no, int chave);
    void exibirOrdemR(Node* no);
    void destruirR(Node* no);
    Node* encontrarMinimoR(Node* no);

    /*
     * Esses aqui são os metodos privados, mais especificamnete, esses com R no
     * final são metodos recursivos, em resumo oque rola e o seguinte, no public
     * você vai ter somente a chamada e no private vai ser onde as coisas realmente
     * funcionam, agora uma leve explicação dessas duas ultimas funções que podem
     * parecer um pouco diferentes, a "destruirR" e um auxiliar que ser para a gente
     * apagar a arvoré porque já que a gente vai usar ponteiro do jeito raiz, é bom
     * termos esse cuidado, e o "encontrarMinimoR" vai nos ajudar na remoção no processo
     * em que removemos um no com dois filhos e temos que caminhar de forma pegar o
     * ultimo filho e trocar no lugar do pai, é isso, a frente a gente só vai ter as
     * publicas.
     */


public:
    BST();
    ~BST();
    //detalhe bobo para evitar erros futuros
    BST(const BST&) = delete;            // impede cópia
    BST& operator=(const BST&) = delete; // impede atribuição por cópia

    void inserir(int chave);
    Node* buscar(int chave);
    void remover(int chave);
    void exibirOrdem();
    Node* obterRaiz() const { return raiz; }
};

