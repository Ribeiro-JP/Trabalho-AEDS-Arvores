#include "../include/trie.hpp"

#include <cctype>
using namespace std;

TRIE::TRIE() : raiz() {}

TRIE::~TRIE() {
    destruirR(raiz);
}

void TRIE::destruirR(Node* no){
    if (no != nullptr) {
        for(int i=0; i<26; i++){
            destruirR(no->filhos[i]);
        }
        delete no;
    }
}

bool TRIE::buscar(const std::string& chave){
    return buscarR(raiz,chave,0);
}

void TRIE::inserir(const std::string& chave){
    raiz = inserirR(raiz,chave,0);
}

void TRIE::remover(const std::string& chave){
    raiz = removerR(raiz,chave,0);
}

void TRIE::exibir(){
    exibirR(raiz,"");
    cout << endl;
}

bool TRIE::contemPrefixo(const std::string& chave){
    return contemPrefixoR(raiz,chave,0);
}

Node* TRIE::inserirR(Node* no, const std::string& chave, size_t indice) {
    if (no == nullptr) {
        no = new Node();
    }
    
    if (indice == chave.length()) {
        no->fim = true;
        return no;
    }
    
    int charIndex = tolower(chave[indice]) - 'a';
    no->filhos[charIndex] = inserirR(no->filhos[charIndex], chave, indice + 1);
    
    return no;
}

bool TRIE::buscarR(Node* no, const std::string& chave, size_t indice) {
    if (no == nullptr) {
        return false;
    }
    
    if (indice == chave.length()) {
        return no->fim;
    }
    
    int charIndex = tolower(chave[indice]) - 'a';
    return buscarR(no->filhos[charIndex], chave, indice + 1);
}

Node* TRIE::removerR(Node* no, const std::string& chave, size_t indice) {
    if (no == nullptr) {
        return nullptr;
    }
    
    if (indice == chave.length()) {
        no->fim = false;
    } else {
        int charIndex = tolower(chave[indice]) - 'a';
        no->filhos[charIndex] = removerR(no->filhos[charIndex], chave, indice + 1);
    }
    
    if (no->fim) {
        return no;
    }
    
    for (int i = 0; i < 26; i++) {
        if (no->filhos[i] != nullptr) {
            return no;
        }
    }
    
    delete no;
    return nullptr;
}

bool TRIE::contemPrefixoR(Node* no, const std::string& chave, size_t indice) {
    if (no == nullptr) {
        return false;
    }
    
    if (indice == chave.length()) {
        return true;
    }
    
    int charIndex = tolower(chave[indice]) - 'a';
    return contemPrefixoR(no->filhos[charIndex], chave, indice + 1);
}

void TRIE::exibirR(Node* no, std::string prefixoAtual) {
    if (no == nullptr) {
        return;
    }
    
    if (no->fim) {
        cout << prefixoAtual << endl;
    }
    
    for (int i = 0; i < 26; i++) {
        if (no->filhos[i] != nullptr) {
            char letra = 'a' + i;
            exibirR(no->filhos[i], prefixoAtual + letra);
        }
    }
}

