#include "../include/trie.hpp"
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

void test_arvore_vazia() {
    TRIE trie;
    assert(trie.buscar("casa") == false);
    assert(trie.contemPrefixo("c") == false);
    cout << "test_arvore_vazia: OK\n";
}

void test_insercao_e_busca_basica() {
    TRIE trie;
    trie.inserir("casa");
    trie.inserir("carro");

    assert(trie.buscar("casa") == true);
    assert(trie.buscar("carro") == true);
    assert(trie.buscar("caro") == false);  // não foi inserida
    assert(trie.buscar("car") == false);   // prefixo, mas não é palavra completa

    cout << "test_insercao_e_busca_basica: OK\n";
}

void test_insercao_duplicada() {
    TRIE trie;
    trie.inserir("teste");
    trie.inserir("teste"); // duplicata, não deve quebrar nada

    assert(trie.buscar("teste") == true);
    cout << "test_insercao_duplicada: OK\n";
}

void test_prefixo_compartilhado() {
    TRIE trie;
    trie.inserir("carro");
    trie.inserir("carta");
    trie.inserir("carne");

    // "car" é prefixo comum às três, mas não é palavra por si só
    assert(trie.contemPrefixo("car") == true);
    assert(trie.buscar("car") == false);

    assert(trie.buscar("carro") == true);
    assert(trie.buscar("carta") == true);
    assert(trie.buscar("carne") == true);

    cout << "test_prefixo_compartilhado: OK\n";
}

void test_contem_prefixo_inexistente() {
    TRIE trie;
    trie.inserir("bola");

    assert(trie.contemPrefixo("bo") == true);
    assert(trie.contemPrefixo("bol") == true);
    assert(trie.contemPrefixo("bola") == true); // palavra completa também conta como prefixo dela mesma
    assert(trie.contemPrefixo("z") == false);
    assert(trie.contemPrefixo("bolax") == false); // passa do fim da palavra existente

    cout << "test_contem_prefixo_inexistente: OK\n";
}

void test_palavra_prefixo_de_outra() {
    TRIE trie;
    // "sol" é prefixo de "solo", que por sua vez é prefixo de "solar"
    trie.inserir("sol");
    trie.inserir("solo");
    trie.inserir("solar");

    assert(trie.buscar("sol") == true);
    assert(trie.buscar("solo") == true);
    assert(trie.buscar("solar") == true);
    assert(trie.buscar("so") == false); // prefixo comum, não é palavra

    cout << "test_palavra_prefixo_de_outra: OK\n";
}

void test_remocao_palavra_simples() {
    TRIE trie;
    trie.inserir("casa");
    trie.remover("casa");

    assert(trie.buscar("casa") == false);
    assert(trie.contemPrefixo("cas") == false); // ramo inteiro deve ter sido podado

    cout << "test_remocao_palavra_simples: OK\n";
}

void test_remocao_preserva_prefixo_de_outra_palavra() {
    TRIE trie;
    // "sol" é prefixo de "solar" -- remover "sol" NÃO pode afetar "solar"
    trie.inserir("sol");
    trie.inserir("solar");

    trie.remover("sol");

    assert(trie.buscar("sol") == false);   // "sol" não é mais palavra válida
    assert(trie.buscar("solar") == true);  // mas "solar" continua existindo
    assert(trie.contemPrefixo("sol") == true); // o caminho ainda existe, por causa de "solar"

    cout << "test_remocao_preserva_prefixo_de_outra_palavra: OK\n";
}

void test_remocao_nao_afeta_outra_palavra_com_prefixo_comum() {
    TRIE trie;
    trie.inserir("carro");
    trie.inserir("carta");

    trie.remover("carro");

    assert(trie.buscar("carro") == false);
    assert(trie.buscar("carta") == true); // "carta" não deve ser afetada
    assert(trie.contemPrefixo("car") == true); // ainda existe por causa de "carta"

    cout << "test_remocao_nao_afeta_outra_palavra_com_prefixo_comum: OK\n";
}

void test_remocao_palavra_inexistente() {
    TRIE trie;
    trie.inserir("bola");

    trie.remover("gato"); // não existe, não deve travar nem afetar nada
    assert(trie.buscar("bola") == true);

    cout << "test_remocao_palavra_inexistente: OK\n";
}

void test_remocao_ate_esvaziar() {
    TRIE trie;
    trie.inserir("oi");
    trie.remover("oi");

    assert(trie.buscar("oi") == false);
    trie.remover("oi"); // remover de trie já vazia não deve travar

    cout << "test_remocao_ate_esvaziar: OK\n";
}

void test_exibir() {
    TRIE trie;
    trie.inserir("casa");
    trie.inserir("carro");
    trie.inserir("bola");

    ostringstream buffer;
    streambuf* cout_original = cout.rdbuf(buffer.rdbuf());
    trie.exibir();
    cout.rdbuf(cout_original);

    // a ordem de exibição segue o índice do array filhos[26] (a..z),
    // então sai em ordem alfabética naturalmente
    string esperado = "bola\ncarro\ncasa\n\n";
    assert(buffer.str() == esperado);

    cout << "test_exibir: OK\n";
}

void test_exibir_vazia() {
    TRIE trie;

    ostringstream buffer;
    streambuf* cout_original = cout.rdbuf(buffer.rdbuf());
    trie.exibir();
    cout.rdbuf(cout_original);

    assert(buffer.str() == "\n"); // nenhuma palavra, só o endl final
    cout << "test_exibir_vazia: OK\n";
}

int main() {
    test_arvore_vazia();
    test_insercao_e_busca_basica();
    test_insercao_duplicada();
    test_prefixo_compartilhado();
    test_contem_prefixo_inexistente();
    test_palavra_prefixo_de_outra();

    test_remocao_palavra_simples();
    test_remocao_preserva_prefixo_de_outra_palavra();
    test_remocao_nao_afeta_outra_palavra_com_prefixo_comum();
    test_remocao_palavra_inexistente();
    test_remocao_ate_esvaziar();

    test_exibir();
    test_exibir_vazia();

    cout << "\nTodos os testes da Trie passaram!\n";
    return 0;
}