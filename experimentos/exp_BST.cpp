#include "../include/BST.hpp"
#include "../include/common/time.hpp"
#include "../include/common/dataset_io.hpp"

using namespace std;

static void medir(const string& variacao, int n, const vector<int>& dados) {
    BST arvore;
    double t = medir_ms([&]() { for (int v : dados) arvore.inserir(v); });
    escreverLinhaCsv("BST", variacao, n, "insercao", t);
    t = medir_ms([&]() { for (int v : dados) arvore.buscar(v); });
    escreverLinhaCsv("BST", variacao, n, "busca", t);
    t = medir_ms([&]() { for (int v : dados) arvore.remover(v); });
    escreverLinhaCsv("BST", variacao, n, "remocao", t);
}

int main() {
    const string base = "experimentos/datasets/int/";

    for (int n : TAMANHOS_EXPERIMENTO) {
        cerr << "[BST] n=" << n << "\n";

        auto dadosRandom = lerInteiros(base + "random_" + to_string(n) + ".txt");
        medir("random", n, dadosRandom);

        // BST comum não tem autobalanceamento -- entrada já ordenada gera
        // risco real de O(n^2), então limitamos o tamanho testado aqui
        if (n <= LIMITE_PIOR_CASO) {
            auto dadosAsc = lerInteiros(base + "sorted_asc_" + to_string(n) + ".txt");
            auto dadosDesc = lerInteiros(base + "sorted_desc_" + to_string(n) + ".txt");
            medir("sorted_asc", n, dadosAsc);
            medir("sorted_desc", n, dadosDesc);
        } else {
            cerr << "  pulando sorted_asc/sorted_desc em n=" << n << " (risco de tempo quadratico)\n";
        }
    }

    return 0;
}
