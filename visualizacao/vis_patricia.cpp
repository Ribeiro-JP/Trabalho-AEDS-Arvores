#include "../include/patricia.hpp"
#include "../include/common/exportador_grafos.hpp"
#include <iostream>

using namespace std;

int main() {
    auto rotulo = [](Node* n) { return n->prefixo.empty() ? string("(raiz)") : n->prefixo; };
    PATRICIA arvore;

    // Estado 1: "casa" e "carro" divergem na 3a posicao -- primeiro split,
    // criando o bloco comum "ca" com dois ramos comprimidos
    arvore.inserir("casa");
    arvore.inserir("carro");
    exportarDotPrefixo(arvore.obterRaiz(), "visualizacao/dot/dot_patricia/estado1_inicial.dot", rotulo,
        "PATRICIA -- Estado inicial (casa, carro -- primeiro split)");

    // Estado 2: insere "carta", que diverge DENTRO do bloco "rro" -- gera
    // um SEGUNDO split, aninhado dentro do primeiro
    arvore.inserir("carta");
    exportarDotPrefixo(arvore.obterRaiz(), "visualizacao/dot/dot_patricia/estado2_split_aninhado.dot", rotulo,
        "PATRICIA -- Apos inserir 'carta' (split aninhado dentro de 'r')");

    // Estado 3: remove "casa" -- o no 'ca' fica com um unico filho e se
    // COMPACTA com ele, virando 'car' diretamente
    arvore.remover("casa");
    exportarDotPrefixo(arvore.obterRaiz(), "visualizacao/dot/dot_patricia/estado3_apos_compactacao.dot", rotulo,
        "PATRICIA -- Apos remover 'casa' (no 'ca' se compacta em 'car')");

    cout << "PATRICIA: 3 estados gerados\n";
    return 0;
}
