#pragma once

#include <iostream>
#include <string>

struct Node
{
    Node* filhos[26];
    bool fim;
    Node(): fim(false) {
        for(int i=0; i<26; i++){ filhos[i]=nullptr;}
    };
};

class TRIE
{
private:
    Node* raiz;

    Node* inserirR(Node* no,const std::string& chave, size_t indice);
    bool buscarR(Node* no,const std::string& chave, size_t indice);
    Node* removerR(Node* no,const std::string& chave, size_t indice);
    bool contemPrefixoR(Node* no,const std::string& chave, size_t indice);
    void exibirR(Node* no, std::string prefixoAtual);
    void destruirR(Node* no);

public:
    TRIE();
    ~TRIE();
    //detalhe bobo para evitar erros futuros
    TRIE(const TRIE&) = delete;            // impede cópia
    TRIE& operator=(const TRIE&) = delete; // impede atribuição por cópia

    void inserir(const std::string& chave);
    bool buscar(const std::string& chave);
    void remover(const std::string& chave);
    void exibir();
    bool contemPrefixo(const std::string& chave);
};

