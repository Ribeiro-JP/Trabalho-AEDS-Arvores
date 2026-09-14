#include "../include/BST.hpp"
#include "../include/common/exportador_grafos.hpp"
#include <iostream>

using namespace std;

int main() {
    auto rotulo = [](Node* n) { return to_string(n->chave); };
    BST arvore;

    // Estado 1: mesmo conjunto de dados usado no demo da AVL -- de
    // propósito, pra permitir comparação direta entre as duas no relatório
    for (int v : {50, 30, 70, 20, 40, 60, 80}) arvore.inserir(v);
    exportarDotBinario(arvore.obterRaiz(), "visualizacao/dot/dot_BST/estado1_inicial.dot", rotulo,
        "BST -- Estado inicial (7 insercoes)");

    // Estado 2: mesmas 3 inserções adicionais que, na AVL, disparariam
    // rotação -- aqui NADA acontece, e a subarvore esquerda vira uma
    // corrente. Contraste direto com a AVL na mesma situação.
    arvore.inserir(10);
    arvore.inserir(5);
    arvore.inserir(3);
    exportarDotBinario(arvore.obterRaiz(), "visualizacao/dot/dot_BST/estado2_sem_rebalanceamento.dot", rotulo,
        "BST -- Apos inserir 10, 5, 3 (sem rebalanceamento, forma corrente)");

    // Estado 3: remove a raiz (dois filhos) -- mostra substituição pelo
    // sucessor in-order, sem nenhum ajuste de balanceamento depois
    arvore.remover(50);
    exportarDotBinario(arvore.obterRaiz(), "visualizacao/dot/dot_BST/estado3_apos_remocao.dot", rotulo,
        "BST -- Apos remover a raiz (50)");

    cout << "BST: 3 estados gerados\n";
    return 0;
}
