#include "../include/splay.hpp"
#include "../include/common/exportador_grafos.hpp"
#include <iostream>

using namespace std;

int main() {
    auto rotulo = [](Node* n) { return to_string(n->chave); };
    SPLAY arvore;

    // Estado 1: insercoes em ordem crescente -- cada insercao traz o novo
    // no pra raiz (comportamento caracteristico da Splay), formando uma
    // corrente a esquerda
    for (int v : {10, 20, 30, 40, 50}) arvore.inserir(v);
    exportarDotBinario(arvore.obterRaiz(), "visualizacao/dot/dot_splay/estado1_inicial.dot", rotulo,
        "SPLAY -- Estado inicial (insercoes 10..50 em ordem)");

    // Estado 2: busca pelo elemento mais profundo (10, o mais antigo) --
    // forca um zig-zig completo, reorganizando toda a arvore de uma vez
    arvore.buscar(10);
    exportarDotBinario(arvore.obterRaiz(), "visualizacao/dot/dot_splay/estado2_apos_busca.dot", rotulo,
        "SPLAY -- Apos buscar 10 (zig-zig completo, reorganiza tudo)");

    // Estado 3: remove a raiz atual -- mostra o mecanismo de remocao
    // (splay da chave removida, depois junta as duas subarvores)
    arvore.remover(10);
    exportarDotBinario(arvore.obterRaiz(), "visualizacao/dot/dot_splay/estado3_apos_remocao.dot", rotulo,
        "SPLAY -- Apos remover 10 (nova raiz assume o lugar)");

    cout << "SPLAY: 3 estados gerados\n";
    return 0;
}
