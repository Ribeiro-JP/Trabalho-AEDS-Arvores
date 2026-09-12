#pragma once

#include <iostream>
#include <string>

struct Node
{
    std::string prefixo;
    Node* filhos[26];
    bool fim;
    
    Node(const std::string& pref = ""): prefixo(pref), fim(false) {
        for(int i=0; i<26; i++){ filhos[i] = nullptr; }
    };
};

class PATRICIA
{
private:
    Node* raiz;

    Node* inserirR(Node* no, const std::string& chave);
    bool buscarR(Node* no, const std::string& chave);
    Node* removerR(Node* no, const std::string& chave);
    void exibirR(Node* no, std::string prefixoAtual);
    void destruirR(Node* no);

public:
    PATRICIA();
    ~PATRICIA();
    // detalhe bobo para evitar erros futuros
    PATRICIA(const PATRICIA&) = delete;            // impede cópia
    PATRICIA& operator=(const PATRICIA&) = delete; // impede atribuição por cópia

    void inserir(const std::string& chave);
    bool buscar(const std::string& chave);
    void remover(const std::string& chave);
    void exibir();
    Node* obterRaiz() const { return raiz; }
};