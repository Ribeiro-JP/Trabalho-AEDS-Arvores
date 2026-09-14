#include "../include/treap.hpp"
#include "../include/common/exportador_grafos.hpp"
#include <iostream>

using namespace std;

int main() {
    auto rotulo = [](Node* n) { return to_string(n->chave) + "\\np=" + to_string(n->prioridade); };
    TREAP arvore;

    // Estado 1: construção com prioridades fixas (pra ser reprodutível),
    // formando uma árvore com prioridades já respeitando a propriedade de heap
    arvore.inserir(50, 80);
    arvore.inserir(30, 60);
    arvore.inserir(70, 40);
    arvore.inserir(20, 30);
    arvore.inserir(40, 50);
    arvore.inserir(60, 20);
    arvore.inserir(80, 10);
    exportarDotBinario(arvore.obterRaiz(), "visualizacao/dot/dot_treap/estado1_inicial.dot", rotulo,
        "TREAP -- Estado inicial (7 insercoes, prioridades fixas)");

    // Estado 2: insere 10 com prioridade muito alta (90) -- sobe vários
    // niveis de uma vez até virar raiz, evidenciando o balanceamento
    // probabilistico guiado por prioridade
    arvore.inserir(10, 90);
    exportarDotBinario(arvore.obterRaiz(), "visualizacao/dot/dot_treap/estado2_subida_prioridade.dot", rotulo,
        "TREAP -- Apos inserir 10 com prioridade 90 (sobe ate a raiz)");

    // Estado 3: remove a raiz atual (tem dois filhos) -- mostra rotação
    // de DESCIDA escolhendo sempre o filho de maior prioridade
    arvore.remover(50); // tem os dois filhos -- forca rotacao de descida de verdade
    exportarDotBinario(arvore.obterRaiz(), "visualizacao/dot/dot_treap/estado3_apos_remocao.dot", rotulo,
        "TREAP -- Apos remover 50 (dois filhos), com rotacao de descida");

    cout << "TREAP: 3 estados gerados\n";
    return 0;
}
