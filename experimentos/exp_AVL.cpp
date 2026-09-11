#include "../include/AVL.hpp"
#include "../include/common/time.hpp"
#include "../include/common/dataset_io.hpp"

using namespace std;

static void medir(const string& variacao, int n, const vector<int>& dados) {
    AVL arvore;
    double t = medir_ms([&]() { for (int v : dados) arvore.inserir(v); });
    escreverLinhaCsv("AVL", variacao, n, "insercao", t);
    t = medir_ms([&]() { for (int v : dados) arvore.buscar(v); });
    escreverLinhaCsv("AVL", variacao, n, "busca", t);
    t = medir_ms([&]() { for (int v : dados) arvore.remover(v); });
    escreverLinhaCsv("AVL", variacao, n, "remocao", t);
}

int main() {
    const string base = "experimentos/datasets/int/";

    // AVL se mantém O(log n) garantido independente da ordem de inserção,
    // então testamos TODAS as variações em TODOS os tamanhos, sem exceção
    for (int n : TAMANHOS_EXPERIMENTO) {
        cerr << "[AVL] n=" << n << "\n";

        auto dadosRandom = lerInteiros(base + "random_" + to_string(n) + ".txt");
        auto dadosAsc = lerInteiros(base + "sorted_asc_" + to_string(n) + ".txt");
        auto dadosDesc = lerInteiros(base + "sorted_desc_" + to_string(n) + ".txt");

        medir("random", n, dadosRandom);
        medir("sorted_asc", n, dadosAsc);
        medir("sorted_desc", n, dadosDesc);
    }

    return 0;
}
