#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// Tamanhos usados nos experimentos -- PRECISA bater com TAMANHOS em
// experimentos/gerar_datasets.py
inline const std::vector<int> TAMANHOS_EXPERIMENTO = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000};

// Acima desse tamanho, pulamos variações de PIOR CASO em estruturas sem
// autobalanceamento (BST comum, KD-Tree) -- entrada já ordenada nelas pode
// custar O(n^2), o que em 100k levaria minutos/horas.
inline const int LIMITE_PIOR_CASO = 10000;

inline std::vector<int> lerInteiros(const std::string& caminho) {
    std::vector<int> valores;
    std::ifstream arquivo(caminho);
    int v;
    while (arquivo >> v) valores.push_back(v);
    return valores;
}

inline std::vector<std::string> lerStrings(const std::string& caminho) {
    std::vector<std::string> valores;
    std::ifstream arquivo(caminho);
    std::string v;
    while (arquivo >> v) valores.push_back(v);
    return valores;
}

inline std::vector<std::pair<int, int>> lerPontos(const std::string& caminho) {
    std::vector<std::pair<int, int>> valores;
    std::ifstream arquivo(caminho);
    int x, y;
    while (arquivo >> x >> y) valores.push_back({x, y});
    return valores;
}

// Imprime uma linha de CSV em stdout (o Makefile redireciona/concatena
// a saída de cada executável em experimentos/resultados.csv)
inline void escreverLinhaCsv(const std::string& estrutura, const std::string& variacao, int tamanho,
                              const std::string& operacao, double tempoMs) {
    std::cout << estrutura << "," << variacao << "," << tamanho << "," << operacao << "," << tempoMs << "\n";
}
