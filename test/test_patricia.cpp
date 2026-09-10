#include "../include/patricia.hpp"
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

void test_arvore_vazia() {
    PATRICIA patricia;
    assert(patricia.buscar("casa") == false);
    cout << "test_arvore_vazia: OK\n";
}

void test_insercao_e_busca_basica() {
    PATRICIA patricia;
    patricia.inserir("casa");
    patricia.inserir("bola");

    assert(patricia.buscar("casa") == true);
    assert(patricia.buscar("bola") == true);
    assert(patricia.buscar("bolo") == false);
    assert(patricia.buscar("cas") == false);

    cout << "test_insercao_e_busca_basica: OK\n";
}

void test_insercao_duplicada() {
    PATRICIA patricia;
    patricia.inserir("teste");
    patricia.inserir("teste"); // duplicata, não deve quebrar nada

    assert(patricia.buscar("teste") == true);
    cout << "test_insercao_duplicada: OK\n";
}

// Caso central da Patricia: uma nova chave diverge NO MEIO de um bloco
// já comprimido, forçando o split em "car" (raiz do split) + "ro" + "tao".
void test_split_no_meio_do_prefixo() {
    PATRICIA patricia;
    patricia.inserir("carro");
    patricia.inserir("cartao"); // diverge na posição 3 ('r' vs 't')

    assert(patricia.buscar("carro") == true);
    assert(patricia.buscar("cartao") == true);
    assert(patricia.buscar("car") == false); // "car" nunca foi inserida como palavra

    cout << "test_split_no_meio_do_prefixo: OK\n";
}

// Chave é um PREFIXO ESTRITO de um bloco já existente (mais curta que ele).
void test_chave_mais_curta_que_bloco_existente() {
    PATRICIA patricia;
    patricia.inserir("carro"); // vira um único bloco "carro"
    patricia.inserir("car");   // mais curta -- deve quebrar "carro" em "car" + "ro"

    assert(patricia.buscar("car") == true);
    assert(patricia.buscar("carro") == true);
    assert(patricia.buscar("ca") == false);

    cout << "test_chave_mais_curta_que_bloco_existente: OK\n";
}

// Chave é uma EXTENSÃO de um bloco existente (mais longa que ele).
void test_chave_mais_longa_que_bloco_existente() {
    PATRICIA patricia;
    patricia.inserir("sol");
    patricia.inserir("solar"); // estende o bloco "sol" com um novo filho "ar"

    assert(patricia.buscar("sol") == true);
    assert(patricia.buscar("solar") == true);
    assert(patricia.buscar("so") == false);

    cout << "test_chave_mais_longa_que_bloco_existente: OK\n";
}

void test_prefixo_compartilhado_multiplo() {
    PATRICIA patricia;
    patricia.inserir("carro");
    patricia.inserir("carta");
    patricia.inserir("carne");

    assert(patricia.buscar("carro") == true);
    assert(patricia.buscar("carta") == true);
    assert(patricia.buscar("carne") == true);
    assert(patricia.buscar("car") == false);

    cout << "test_prefixo_compartilhado_multiplo: OK\n";
}

void test_remocao_palavra_simples() {
    PATRICIA patricia;
    patricia.inserir("casa");

    patricia.remover("casa");
    assert(patricia.buscar("casa") == false);

    cout << "test_remocao_palavra_simples: OK\n";
}

// Remove "sol", que é prefixo de "solar" -- "solar" precisa continuar
// intacta, e o nó restante deve se compactar (sol + ar -> solar).
void test_remocao_preserva_prefixo_de_outra_palavra() {
    PATRICIA patricia;
    patricia.inserir("sol");
    patricia.inserir("solar");

    patricia.remover("sol");

    assert(patricia.buscar("sol") == false);
    assert(patricia.buscar("solar") == true);

    cout << "test_remocao_preserva_prefixo_de_outra_palavra: OK\n";
}

// Remove "carro" (que forçou split com "carta") -- "carta" precisa
// continuar intacta, e o split deve se desfazer via compactação.
void test_remocao_nao_afeta_outra_palavra_com_prefixo_comum() {
    PATRICIA patricia;
    patricia.inserir("carro");
    patricia.inserir("carta");

    patricia.remover("carro");

    assert(patricia.buscar("carro") == false);
    assert(patricia.buscar("carta") == true);

    cout << "test_remocao_nao_afeta_outra_palavra_com_prefixo_comum: OK\n";
}

void test_remocao_elemento_inexistente() {
    PATRICIA patricia;
    patricia.inserir("bola");

    patricia.remover("gato"); // não existe, não deve travar nem afetar nada
    assert(patricia.buscar("bola") == true);

    cout << "test_remocao_elemento_inexistente: OK\n";
}

void test_remocao_ate_esvaziar() {
    PATRICIA patricia;
    patricia.inserir("oi");
    patricia.remover("oi");

    assert(patricia.buscar("oi") == false);
    patricia.remover("oi"); // remover de árvore já vazia não deve travar

    cout << "test_remocao_ate_esvaziar: OK\n";
}

// A ordem de exibição segue o índice do array filhos[26] em cada nível
// (a..z), então mesmo com blocos comprimidos a saída sai alfabética.
void test_exibir() {
    PATRICIA patricia;
    patricia.inserir("casa");
    patricia.inserir("carro");
    patricia.inserir("bola");

    ostringstream buffer;
    streambuf* cout_original = cout.rdbuf(buffer.rdbuf());
    patricia.exibir();
    cout.rdbuf(cout_original);

    // PATRICIA::exibir() não imprime um endl extra no final -- a saída
    // termina no \n da última palavra
    string esperado = "bola\ncarro\ncasa\n";
    assert(buffer.str() == esperado);

    cout << "test_exibir: OK\n";
}

void test_exibir_vazia() {
    PATRICIA patricia;

    ostringstream buffer;
    streambuf* cout_original = cout.rdbuf(buffer.rdbuf());
    patricia.exibir();
    cout.rdbuf(cout_original);

    assert(buffer.str() == ""); // nenhuma palavra, e sem endl extra -> buffer vazio mesmo
    cout << "test_exibir_vazia: OK\n";
}

int main() {
    test_arvore_vazia();
    test_insercao_e_busca_basica();
    test_insercao_duplicada();
    test_split_no_meio_do_prefixo();
    test_chave_mais_curta_que_bloco_existente();
    test_chave_mais_longa_que_bloco_existente();
    test_prefixo_compartilhado_multiplo();

    test_remocao_palavra_simples();
    test_remocao_preserva_prefixo_de_outra_palavra();
    test_remocao_nao_afeta_outra_palavra_com_prefixo_comum();
    test_remocao_elemento_inexistente();
    test_remocao_ate_esvaziar();

    test_exibir();
    test_exibir_vazia();

    cout << "\nTodos os testes da Patricia passaram!\n";
    return 0;
}