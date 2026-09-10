#include "../include/patricia.hpp"
#include <cctype>

using namespace std;

PATRICIA::PATRICIA() {
    raiz = new Node(""); // A raiz na Patricia geralmente inicia com prefixo vazio
}

PATRICIA::~PATRICIA() {
    destruirR(raiz);
}

void PATRICIA::destruirR(Node* no) {
    if (no != nullptr) {
        for (int i = 0; i < 26; i++) {
            destruirR(no->filhos[i]);
        }
        delete no;
    }
}

Node* PATRICIA::inserirR(Node* no, const std::string& chave) {
    if (no == nullptr) {
        Node* novo = new Node(chave);
        novo->fim = true;
        return novo;
    }

    int len_chave = chave.length();
    int len_pref = no->prefixo.length();
    int i = 0;

    // Encontra o tamanho do prefixo em comum
    while (i < len_chave && i < len_pref && chave[i] == no->prefixo[i]) {
        i++;
    }

    // Caso 1: A chave tem o prefixo do nó inteiro (ou é um match exato)
    if (i == len_pref) {
        if (i == len_chave) {
            no->fim = true; // A chave já existe ou é igual ao prefixo
        } else {
            // A chave é maior, precisamos descer para os filhos
            std::string sufixo = chave.substr(i);
            int letra = tolower(sufixo[0]) - 'a';
            if (letra >= 0 && letra < 26) {
                no->filhos[letra] = inserirR(no->filhos[letra], sufixo);
            }
        }
    } 
    // Caso 2: O prefixo do nó precisa ser "quebrado" (split)
    else {
        // Cria um novo nó para a parte do prefixo que foi quebrada
        Node* splitNode = new Node(no->prefixo.substr(i));
        splitNode->fim = no->fim;
        for (int k = 0; k < 26; k++) {
            splitNode->filhos[k] = no->filhos[k];
            no->filhos[k] = nullptr;
        }

        // Ajusta o nó atual
        no->prefixo = no->prefixo.substr(0, i);
        no->fim = false; // Só será verdadeiro se a chave terminar exatamente aqui

        // Conecta o nó quebrado ao nó atual
        int letraSplit = tolower(splitNode->prefixo[0]) - 'a';
        no->filhos[letraSplit] = splitNode;

        // Se sobrou algo na chave sendo inserida, cria um novo nó para o sufixo dela
        if (i == len_chave) {
            no->fim = true;
        } else {
            std::string sufixoChave = chave.substr(i);
            int letraNova = tolower(sufixoChave[0]) - 'a';
            Node* novoNo = new Node(sufixoChave);
            novoNo->fim = true;
            no->filhos[letraNova] = novoNo;
        }
    }
    return no;
}

void PATRICIA::inserir(const std::string& chave) {
    // Como a raiz inicia vazia, tratamos como ponto de partida da recursão
    raiz = inserirR(raiz, chave);
}

bool PATRICIA::buscarR(Node* no, const std::string& chave) {
    if (no == nullptr) return false;

    int len_chave = chave.length();
    int len_pref = no->prefixo.length();
    int i = 0;

    while (i < len_chave && i < len_pref && chave[i] == no->prefixo[i]) {
        i++;
    }

    if (i == len_pref) {
        if (i == len_chave) {
            return no->fim;
        } else {
            std::string sufixo = chave.substr(i);
            int letra = tolower(sufixo[0]) - 'a';
            if (letra >= 0 && letra < 26) {
                return buscarR(no->filhos[letra], sufixo);
            }
        }
    }
    
    return false;
}

bool PATRICIA::buscar(const std::string& chave) {
    return buscarR(raiz, chave);
}

Node* PATRICIA::removerR(Node* no, const std::string& chave) {
    if (no == nullptr) return nullptr;

    int len_chave = chave.length();
    int len_pref = no->prefixo.length();
    int i = 0;

    while (i < len_chave && i < len_pref && chave[i] == no->prefixo[i]) {
        i++;
    }

    // Se encontramos o caminho
    if (i == len_pref) {
        if (i == len_chave) {
            no->fim = false; // Desmarca o final da palavra
        } else {
            std::string sufixo = chave.substr(i);
            int letra = tolower(sufixo[0]) - 'a';
            if (letra >= 0 && letra < 26) {
                no->filhos[letra] = removerR(no->filhos[letra], sufixo);
            }
        }
    }

    // Fase de compactação pós-remoção
    if (no == raiz) return no; // Não deleta nem compacta a raiz para manter a estrutura inicial

    int qtdFilhos = 0;
    int unicoFilhoIdx = -1;
    for (int k = 0; k < 26; k++) {
        if (no->filhos[k] != nullptr) {
            qtdFilhos++;
            unicoFilhoIdx = k;
        }
    }

    if (!no->fim) {
        if (qtdFilhos == 0) {
            delete no;
            return nullptr;
        } 
        else if (qtdFilhos == 1) { // Compacta o nó com o seu único filho
            Node* filho = no->filhos[unicoFilhoIdx];
            no->prefixo += filho->prefixo;
            no->fim = filho->fim;
            for (int k = 0; k < 26; k++) {
                no->filhos[k] = filho->filhos[k];
            }
            delete filho; // Libera o nó filho que foi mesclado
        }
    }

    return no;
}

void PATRICIA::remover(const std::string& chave) {
    raiz = removerR(raiz, chave);
}

void PATRICIA::exibirR(Node* no, std::string prefixoAtual) {
    if (no == nullptr) return;

    prefixoAtual += no->prefixo;

    if (no->fim) {
        cout << prefixoAtual << endl;
    }

    for (int i = 0; i < 26; i++) {
        if (no->filhos[i] != nullptr) {
            exibirR(no->filhos[i], prefixoAtual);
        }
    }
}

void PATRICIA::exibir() {
    exibirR(raiz, "");
}