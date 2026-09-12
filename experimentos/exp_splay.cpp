#include "../include/splay.hpp"
#include "../include/common/time.hpp"
#include "../include/common/dataset_io.hpp"

using namespace std;

static void medir(const string& variacao, int n, const vector<int>& dadosInsercao,
                   const vector<int>& dadosRemocao) {
    SPLAY arvore;
    double t = medir_ms([&]() { for (int v : dadosInsercao) arvore.inserir(v); });
    escreverLinhaCsv("SPLAY", variacao, n, "insercao", t);
    t = medir_ms([&]() { for (int v : dadosInsercao) arvore.buscar(v); });
    escreverLinhaCsv("SPLAY", variacao, n, "busca", t);
    t = medir_ms([&]() { for (int v : dadosRemocao) arvore.remover(v); });
    escreverLinhaCsv("SPLAY", variacao, n, "remocao", t);
}

int main() {
    const string base = "experimentos/datasets/int/";

    // Splay tem garantia AMORTIZADA O(log n) por sequência de operações,
    // mesmo em entrada ordenada -- testamos em todos os tamanhos
    for (int n : TAMANHOS_EXPERIMENTO) {
        cerr << "[SPLAY] n=" << n << "\n";

        auto dadosRemocao = lerInteiros(base + "remocao_" + to_string(n) + ".txt");
        auto dadosRandom = lerInteiros(base + "random_" + to_string(n) + ".txt");
        auto dadosAsc = lerInteiros(base + "sorted_asc_" + to_string(n) + ".txt");
        auto dadosDesc = lerInteiros(base + "sorted_desc_" + to_string(n) + ".txt");

        medir("random", n, dadosRandom, dadosRemocao);
        medir("sorted_asc", n, dadosAsc, dadosRemocao);
        medir("sorted_desc", n, dadosDesc, dadosRemocao);
    }

    return 0;
}
