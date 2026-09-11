#include "../include/patricia.hpp"
#include "../include/common/time.hpp"
#include "../include/common/dataset_io.hpp"

using namespace std;

static void medir(const string& variacao, int n, const vector<string>& dados) {
    PATRICIA arvore;
    double t = medir_ms([&]() { for (const auto& v : dados) arvore.inserir(v); });
    escreverLinhaCsv("PATRICIA", variacao, n, "insercao", t);
    t = medir_ms([&]() { for (const auto& v : dados) arvore.buscar(v); });
    escreverLinhaCsv("PATRICIA", variacao, n, "busca", t);
    t = medir_ms([&]() { for (const auto& v : dados) arvore.remover(v); });
    escreverLinhaCsv("PATRICIA", variacao, n, "remocao", t);
}

int main() {
    const string base = "experimentos/datasets/string/";
    vector<string> variacoes = {"random", "alta_densidade", "baixa_densidade"};

    for (int n : TAMANHOS_EXPERIMENTO) {
        cerr << "[PATRICIA] n=" << n << "\n";
        for (const auto& variacao : variacoes) {
            auto dados = lerStrings(base + variacao + "_" + to_string(n) + ".txt");
            medir(variacao, n, dados);
        }
    }

    return 0;
}
