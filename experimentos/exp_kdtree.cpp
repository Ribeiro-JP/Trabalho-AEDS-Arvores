#include "../include/kdtree.hpp"
#include "../include/common/time.hpp"
#include "../include/common/dataset_io.hpp"

using namespace std;

static void medir(const string& variacao, int n, const vector<pair<int, int>>& dados) {
    KDTREE arvore;
    double t = medir_ms([&]() { for (auto& p : dados) arvore.inserir(p.first, p.second); });
    escreverLinhaCsv("KDTREE", variacao, n, "insercao", t);
    t = medir_ms([&]() { for (auto& p : dados) arvore.buscar(p.first, p.second); });
    escreverLinhaCsv("KDTREE", variacao, n, "busca", t);
    t = medir_ms([&]() { for (auto& p : dados) arvore.remover(p.first, p.second); });
    escreverLinhaCsv("KDTREE", variacao, n, "remocao", t);
}

int main() {
    const string base = "experimentos/datasets/coord/";

    for (int n : TAMANHOS_EXPERIMENTO) {
        cerr << "[KDTREE] n=" << n << "\n";

        auto dadosRandom = lerPontos(base + "random_" + to_string(n) + ".txt");
        auto dadosCluster = lerPontos(base + "cluster_" + to_string(n) + ".txt");
        medir("random", n, dadosRandom);
        medir("cluster", n, dadosCluster);

        // sem autobalanceamento -- pontos ordenados por x são um risco real
        // de degradação quadrática, então limitamos o tamanho testado aqui
        if (n <= LIMITE_PIOR_CASO) {
            auto dadosSortedX = lerPontos(base + "sorted_x_" + to_string(n) + ".txt");
            medir("sorted_x", n, dadosSortedX);
        } else {
            cerr << "  pulando sorted_x em n=" << n << " (risco de tempo quadratico)\n";
        }
    }

    return 0;
}
