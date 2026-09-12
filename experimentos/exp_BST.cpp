#include "../include/BST.hpp"
#include "../include/common/time.hpp"
#include "../include/common/dataset_io.hpp"

using namespace std;

// dadosInsercao define a ordem de inserção (varia por cenário: random/
// sorted_asc/sorted_desc); dadosRemocao é SEMPRE uma ordem embaralhada,
// independente da ordem de inserção -- isso evita medir remoção de forma
// artificialmente barata em árvores degeneradas (onde remover na mesma
// ordem da inserção acertaria sempre a raiz/extremo atual, O(1) ali).
static void medir(const string& variacao, int n, const vector<int>& dadosInsercao,
                   const vector<int>& dadosRemocao) {
    BST arvore;
    double t = medir_ms([&]() { for (int v : dadosInsercao) arvore.inserir(v); });
    escreverLinhaCsv("BST", variacao, n, "insercao", t);
    t = medir_ms([&]() { for (int v : dadosInsercao) arvore.buscar(v); });
    escreverLinhaCsv("BST", variacao, n, "busca", t);
    t = medir_ms([&]() { for (int v : dadosRemocao) arvore.remover(v); });
    escreverLinhaCsv("BST", variacao, n, "remocao", t);
}

int main() {
    const string base = "experimentos/datasets/int/";

    for (int n : TAMANHOS_EXPERIMENTO) {
        cerr << "[BST] n=" << n << "\n";
        auto dadosRemocao = lerInteiros(base + "remocao_" + to_string(n) + ".txt");

        auto dadosRandom = lerInteiros(base + "random_" + to_string(n) + ".txt");
        medir("random", n, dadosRandom, dadosRemocao);

        // BST comum não tem autobalanceamento -- entrada já ordenada gera
        // risco real de O(n^2), então limitamos o tamanho testado aqui
        if (n <= LIMITE_PIOR_CASO) {
            auto dadosAsc = lerInteiros(base + "sorted_asc_" + to_string(n) + ".txt");
            auto dadosDesc = lerInteiros(base + "sorted_desc_" + to_string(n) + ".txt");
            medir("sorted_asc", n, dadosAsc, dadosRemocao);
            medir("sorted_desc", n, dadosDesc, dadosRemocao);
        } else {
            cerr << "  pulando sorted_asc/sorted_desc em n=" << n << " (risco de tempo quadratico)\n";
        }
    }

    return 0;
}
