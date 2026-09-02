#include "../include/AVL.hpp"
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

void test_arvore_vazia() {
    AVL arvore;
    assert(arvore.buscar(10) == nullptr);
    cout << "test_arvore_vazia: OK\n";
}

void test_insercao_e_busca_basica() {
    AVL arvore;
    arvore.inserir(50);
    arvore.inserir(30);
    arvore.inserir(70);
    arvore.inserir(20);
    arvore.inserir(40);

    Node* achado = arvore.buscar(30);
    assert(achado != nullptr);
    assert(achado->chave == 30);
    assert(arvore.buscar(999) == nullptr);

    cout << "test_insercao_e_busca_basica: OK\n";
}

void test_insercao_duplicada() {
    AVL arvore;
    arvore.inserir(10);
    arvore.inserir(10);

    Node* achado = arvore.buscar(10);
    assert(achado != nullptr);
    assert(achado->chave == 10);
    cout << "test_insercao_duplicada: OK\n";
}

// Nos 4 testes de rotação de inserção abaixo, o resultado esperado é
// sempre o mesmo formato: raiz = 20, esquerda = 10, direita = 30,
// todos com altura correta (0 nas folhas, 1 na raiz).
void test_rotacao_insercao_LL() {
    AVL arvore; // pende esquerda, filho esquerdo também pende esquerda -> rotação simples
    arvore.inserir(30);
    arvore.inserir(20);
    arvore.inserir(10);

    Node* raiz = arvore.buscar(20);
    assert(raiz != nullptr);
    assert(raiz->altura == 1);
    assert(raiz->esquerda != nullptr && raiz->esquerda->chave == 10);
    assert(raiz->direita != nullptr && raiz->direita->chave == 30);
    assert(raiz->esquerda->altura == 0);
    assert(raiz->direita->altura == 0);

    cout << "test_rotacao_insercao_LL: OK\n";
}

void test_rotacao_insercao_RR() {
    AVL arvore; // pende direita, filho direito também pende direita -> rotação simples
    arvore.inserir(10);
    arvore.inserir(20);
    arvore.inserir(30);

    Node* raiz = arvore.buscar(20);
    assert(raiz != nullptr);
    assert(raiz->altura == 1);
    assert(raiz->esquerda != nullptr && raiz->esquerda->chave == 10);
    assert(raiz->direita != nullptr && raiz->direita->chave == 30);

    cout << "test_rotacao_insercao_RR: OK\n";
}

void test_rotacao_insercao_LR() {
    AVL arvore; // pende esquerda, filho esquerdo pende direita -> rotação dupla
    arvore.inserir(30);
    arvore.inserir(10);
    arvore.inserir(20);

    Node* raiz = arvore.buscar(20);
    assert(raiz != nullptr);
    assert(raiz->altura == 1);
    assert(raiz->esquerda != nullptr && raiz->esquerda->chave == 10);
    assert(raiz->direita != nullptr && raiz->direita->chave == 30);

    cout << "test_rotacao_insercao_LR: OK\n";
}

void test_rotacao_insercao_RL() {
    AVL arvore; // pende direita, filho direito pende esquerda -> rotação dupla
    arvore.inserir(10);
    arvore.inserir(30);
    arvore.inserir(20);

    Node* raiz = arvore.buscar(20);
    assert(raiz != nullptr);
    assert(raiz->altura == 1);
    assert(raiz->esquerda != nullptr && raiz->esquerda->chave == 10);
    assert(raiz->direita != nullptr && raiz->direita->chave == 30);

    cout << "test_rotacao_insercao_RL: OK\n";
}

void test_remocao_folha() {
    AVL arvore;
    arvore.inserir(50);
    arvore.inserir(30);
    arvore.inserir(70);

    arvore.remover(30);
    assert(arvore.buscar(30) == nullptr);
    assert(arvore.buscar(50) != nullptr);
    assert(arvore.buscar(70) != nullptr);

    cout << "test_remocao_folha: OK\n";
}

void test_remocao_um_filho() {
    AVL arvore;
    arvore.inserir(50);
    arvore.inserir(30);
    arvore.inserir(20);

    arvore.remover(30);
    assert(arvore.buscar(30) == nullptr);
    assert(arvore.buscar(20) != nullptr);
    assert(arvore.buscar(50) != nullptr);

    cout << "test_remocao_um_filho: OK\n";
}

void test_remocao_dois_filhos() {
    AVL arvore;
    arvore.inserir(50);
    arvore.inserir(30);
    arvore.inserir(70);
    arvore.inserir(60);
    arvore.inserir(80);

    arvore.remover(70);
    assert(arvore.buscar(70) == nullptr);
    assert(arvore.buscar(60) != nullptr);
    assert(arvore.buscar(80) != nullptr);

    cout << "test_remocao_dois_filhos: OK\n";
}

void test_remocao_elemento_inexistente() {
    AVL arvore;
    arvore.inserir(10);
    arvore.inserir(20);

    arvore.remover(999);
    assert(arvore.buscar(10) != nullptr);
    assert(arvore.buscar(20) != nullptr);

    cout << "test_remocao_elemento_inexistente: OK\n";
}

void test_remocao_ate_esvaziar() {
    AVL arvore;
    arvore.inserir(10);
    arvore.remover(10);
    assert(arvore.buscar(10) == nullptr);
    arvore.remover(10); // remover de árvore vazia não deve travar
    cout << "test_remocao_ate_esvaziar: OK\n";
}

// Este é o teste que valida especificamente a correção que fizemos:
// remove um nó de forma que o desbalanceamento resultante não tem
// nenhuma relação com o valor removido -- só o fbEsquerda/fbDireita
// calculado a partir da estrutura resolve certo.
void test_remocao_com_rotacao_pende_esquerda() {
    AVL arvore;
    // árvore: 20 -> esquerda(10 -> esquerda(5), direita(15)), direita(30)
    arvore.inserir(20);
    arvore.inserir(10);
    arvore.inserir(30);
    arvore.inserir(5);
    arvore.inserir(15);

    arvore.remover(30); // remove o único nó da direita -> desbalanceia pra esquerda

    // esperado após rotação simples (LL): raiz vira 10, esquerda=5, direita=20(com esquerda=15)
    Node* raiz = arvore.buscar(10);
    assert(raiz != nullptr);
    assert(raiz->altura == 2);
    assert(raiz->esquerda != nullptr && raiz->esquerda->chave == 5);
    assert(raiz->direita != nullptr && raiz->direita->chave == 20);
    assert(raiz->direita->esquerda != nullptr && raiz->direita->esquerda->chave == 15);
    assert(raiz->direita->direita == nullptr);

    cout << "test_remocao_com_rotacao_pende_esquerda: OK\n";
}

void test_remocao_com_rotacao_pende_direita() {
    AVL arvore;
    // árvore: 20 -> esquerda(10), direita(30 -> esquerda(25), direita(35))
    arvore.inserir(20);
    arvore.inserir(10);
    arvore.inserir(30);
    arvore.inserir(25);
    arvore.inserir(35);

    arvore.remover(10); // remove o único nó da esquerda -> desbalanceia pra direita

    // esperado após rotação simples (RR): raiz vira 30, esquerda=20(com direita=25), direita=35
    Node* raiz = arvore.buscar(30);
    assert(raiz != nullptr);
    assert(raiz->altura == 2);
    assert(raiz->esquerda != nullptr && raiz->esquerda->chave == 20);
    assert(raiz->direita != nullptr && raiz->direita->chave == 35);
    assert(raiz->esquerda->direita != nullptr && raiz->esquerda->direita->chave == 25);
    assert(raiz->esquerda->esquerda == nullptr);

    cout << "test_remocao_com_rotacao_pende_direita: OK\n";
}

void test_exibir_ordem() {
    AVL arvore;
    arvore.inserir(50);
    arvore.inserir(30);
    arvore.inserir(70);
    arvore.inserir(20);
    arvore.inserir(40);

    ostringstream buffer;
    streambuf* cout_original = cout.rdbuf(buffer.rdbuf());
    arvore.exibirOrdem();
    cout.rdbuf(cout_original);

    string esperado = "20 30 40 50 70 \n";
    assert(buffer.str() == esperado);
    cout << "test_exibir_ordem: OK\n";
}

void test_exibir_ordem_vazia() {
    AVL arvore;

    ostringstream buffer;
    streambuf* cout_original = cout.rdbuf(buffer.rdbuf());
    arvore.exibirOrdem();
    cout.rdbuf(cout_original);

    assert(buffer.str() == "\n");
    cout << "test_exibir_ordem_vazia: OK\n";
}

int main() {
    test_arvore_vazia();
    test_insercao_e_busca_basica();
    test_insercao_duplicada();

    test_rotacao_insercao_LL();
    test_rotacao_insercao_RR();
    test_rotacao_insercao_LR();
    test_rotacao_insercao_RL();

    test_remocao_folha();
    test_remocao_um_filho();
    test_remocao_dois_filhos();
    test_remocao_elemento_inexistente();
    test_remocao_ate_esvaziar();

    test_remocao_com_rotacao_pende_esquerda();
    test_remocao_com_rotacao_pende_direita();

    test_exibir_ordem();
    test_exibir_ordem_vazia();

    cout << "\nTodos os testes da AVL passaram!\n";
    return 0;
}