#include "../include/trie.hpp"
#include "../include/common/exportador_grafos.hpp"
#include <iostream>

using namespace std;

int main() {
    auto rotulo = [](Node* n) { return n->fim ? string("*") : string(""); };
    TRIE arvore;

    // Estado 1: quatro palavras, com "casa" e "carro"/"carta" compartilhando
    // o prefixo "ca", e "bola" totalmente distinta
    for (const string& p : {"casa", "carro", "carta", "bola"}) arvore.inserir(p);
    exportarDotPrefixo(arvore.obterRaiz(), "visualizacao/dot/dot_trie/estado1_inicial.dot", rotulo,
        "TRIE -- Estado inicial (casa, carro, carta, bola)");

    // Estado 2: insere "cartao", aprofundando ainda mais o compartilhamento
    // de prefixo dentro do ramo "car"
    arvore.inserir("cartao");
    exportarDotPrefixo(arvore.obterRaiz(), "visualizacao/dot/dot_trie/estado2_prefixo_aprofundado.dot", rotulo,
        "TRIE -- Apos inserir 'cartao' (aprofunda o ramo compartilhado)");

    // Estado 3: remove "carro" -- "carta"/"cartao" continuam intactas,
    // evidenciando a poda seletiva de nós
    arvore.remover("carro");
    exportarDotPrefixo(arvore.obterRaiz(), "visualizacao/dot/dot_trie/estado3_apos_remocao.dot", rotulo,
        "TRIE -- Apos remover 'carro' (carta/cartao preservadas)");

    cout << "TRIE: 3 estados gerados\n";
    return 0;
}
