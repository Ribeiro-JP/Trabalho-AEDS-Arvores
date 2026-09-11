#include "../include/trie.hpp"
#include "../include/common/time.hpp"
#include "../include/common/dataset_io.hpp"

using namespace std;

static void medir(const string& variacao, int n, const vector<string>& dados) {
    TRIE arvore;
    double t = medir_ms([&]() { for (const auto& v : dados) arvore.inserir(v); });
    escreverLinhaCsv("TRIE", variacao, n, "insercao", t);
    t = medir_ms([&]() { for (const auto& v : dados) arvore.buscar(v); });
    escreverLinhaCsv("TRIE", variacao, n, "busca", t);
    t = medir_ms([&]() { for (const auto& v : dados) arvore.remover(v); });
    escreverLinhaCsv("TRIE", variacao, n, "remocao", t);
}

int main() {
    const string base = "experimentos/datasets/string/";
    vector<string> variacoes = {"random", "alta_densidade", "baixa_densidade"};

    for (int n : TAMANHOS_EXPERIMENTO) {
        cerr << "[TRIE] n=" << n << "\n";
        for (const auto& variacao : variacoes) {
            auto dados = lerStrings(base + variacao + "_" + to_string(n) + ".txt");
            medir(variacao, n, dados);
        }
    }

    return 0;
}
