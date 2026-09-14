#include "../include/AVL.hpp"
#include "../include/common/exportador_grafos.hpp"
#include <iostream>

using namespace std;

int main() {
    auto rotulo = [](Node* n) { return to_string(n->chave) + "\\nh=" + to_string(n->altura); };
    AVL arvore;

    // Estado 1: construção de uma árvore com formato orgânico (sem
    // nenhuma rotação ainda ter sido necessária)
    for (int v : {50, 30, 70, 20, 40, 60, 80}) arvore.inserir(v);
    exportarDotBinario(arvore.obterRaiz(), "visualizacao/dot/dot_AVL/estado1_inicial.dot", rotulo,
        "AVL -- Estado inicial (7 insercoes)");

    // Estado 2: inserir 10 e depois 5 aprofunda a subarvore esquerda de 20
    // além do limite -- dispara uma rotação simples (LL) exatamente ali
    arvore.inserir(10);
    arvore.inserir(5);
    exportarDotBinario(arvore.obterRaiz(), "visualizacao/dot/dot_AVL/estado2_apos_rotacao.dot", rotulo,
        "AVL -- Apos inserir 10 e 5 (rotacao LL no no 20)");

    // Estado 3: remove a raiz (tem dois filhos) -- mostra substituicao
    // pelo sucessor in-order e o rebalanceamento que segue
    arvore.remover(50);
    exportarDotBinario(arvore.obterRaiz(), "visualizacao/dot/dot_AVL/estado3_apos_remocao.dot", rotulo,
        "AVL -- Apos remover a raiz (50), com rebalanceamento");

    cout << "AVL: 3 estados gerados\n";
    return 0;
}
