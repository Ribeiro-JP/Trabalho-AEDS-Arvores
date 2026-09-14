#include "../include/kdtree.hpp"
#include "../include/common/exportador_grafos.hpp"
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    auto rotulo = [](Node* n) { return "(" + to_string(n->x) + "," + to_string(n->y) + ")"; };
    KDTREE arvore;

    // Estado 1: sete pontos inseridos alternando o eixo de comparacao a
    // cada nivel (x no nivel 0, y no nivel 1, x no nivel 2...)
    vector<pair<int,int>> pontos = {{50,50}, {30,70}, {70,20}, {20,80}, {40,60}, {80,10}, {60,30}};
    for (auto& p : pontos) arvore.inserir(p.first, p.second);
    exportarDotBinario(arvore.obterRaiz(), "visualizacao/dot/dot_kdtree/estado1_inicial.dot", rotulo,
        "KD-TREE -- Estado inicial (7 pontos, eixos alternados)");

    // Estado 2: insere um ponto que desce ate o nivel mais profundo da
    // arvore, evidenciando a alternancia x/y/x/y ao longo do caminho
    arvore.inserir(35, 65);
    exportarDotBinario(arvore.obterRaiz(), "visualizacao/dot/dot_kdtree/estado2_insercao_profunda.dot", rotulo,
        "KD-TREE -- Apos inserir (35,65) (desce por varios niveis)");

    // Estado 3: remove um no com dois filhos -- mostra a substituicao pelo
    // minimo no eixo correto da subarvore direita
    arvore.remover(30, 70);
    exportarDotBinario(arvore.obterRaiz(), "visualizacao/dot/dot_kdtree/estado3_apos_remocao.dot", rotulo,
        "KD-TREE -- Apos remover (30,70), com substituicao no eixo certo");

    cout << "KDTREE: 3 estados gerados\n";
    return 0;
}
