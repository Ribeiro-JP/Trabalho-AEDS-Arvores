#include "../include/treap.hpp"
#include "../include/common/time.hpp"
#include "../include/common/dataset_io.hpp"

using namespace std;

static void medir(const string& variacao, int n, const vector<int>& dados) {
    TREAP arvore;
    // usa inserir(chave) -- prioridade genuinamente aleatória, comportamento real
    double t = medir_ms([&]() { for (int v : dados) arvore.inserir(v); });
    escreverLinhaCsv("TREAP", variacao, n, "insercao", t);
    t = medir_ms([&]() { for (int v : dados) arvore.buscar(v); });
    escreverLinhaCsv("TREAP", variacao, n, "busca", t);
    t = medir_ms([&]() { for (int v : dados) arvore.remover(v); });
    escreverLinhaCsv("TREAP", variacao, n, "remocao", t);
}

int main() {
    const string base = "experimentos/datasets/int/";

    // Treap se mantém eficiente independente da ordem de inserção (o
    // balanceamento vem da prioridade aleatória, não da ordem das chaves)
    for (int n : TAMANHOS_EXPERIMENTO) {
        cerr << "[TREAP] n=" << n << "\n";

        auto dadosRandom = lerInteiros(base + "random_" + to_string(n) + ".txt");
        auto dadosAsc = lerInteiros(base + "sorted_asc_" + to_string(n) + ".txt");
        auto dadosDesc = lerInteiros(base + "sorted_desc_" + to_string(n) + ".txt");

        medir("random", n, dadosRandom);
        medir("sorted_asc", n, dadosAsc);
        medir("sorted_desc", n, dadosDesc);
    }

    return 0;
}
