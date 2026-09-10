#include "../include/kdtree.hpp"
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

void test_arvore_vazia() {
    KDTREE kd;
    assert(kd.buscar(10, 10) == nullptr);
    cout << "test_arvore_vazia: OK\n";
}

void test_insercao_e_busca_basica() {
    KDTREE kd;
    kd.inserir(50, 50);
    kd.inserir(30, 70);
    kd.inserir(70, 20);

    assert(kd.buscar(30, 70) != nullptr);
    assert(kd.buscar(70, 20) != nullptr);
    assert(kd.buscar(999, 999) == nullptr);
    assert(kd.buscar(30, 20) == nullptr); // x existe, y existe, mas não como esse PONTO

    cout << "test_insercao_e_busca_basica: OK\n";
}

void test_insercao_duplicada() {
    KDTREE kd;
    kd.inserir(10, 10);
    kd.inserir(10, 10); // ponto duplicado, ignorado

    assert(kd.buscar(10, 10) != nullptr);
    cout << "test_insercao_duplicada: OK\n";
}

// Confirma que o eixo de comparação alterna por profundidade: no nível 1,
// a decisão passa a ser pelo Y, não mais pelo X.
void test_alternancia_de_eixo() {
    KDTREE kd;
    kd.inserir(50, 50); // raiz, nível 0 -> compara x
    kd.inserir(30, 70); // x=30 < 50 -> esquerda, nível 1
    kd.inserir(70, 20); // x=70 >= 50 -> direita, nível 1
    kd.inserir(40, 80); // x=40 < 50 -> esquerda até (30,70); ali nível 1 compara y: 80 >= 70 -> direita
    kd.inserir(10, 60); // x=10 < 50 -> esquerda até (30,70); ali nível 1 compara y: 60 < 70 -> esquerda

    Node* filhoEsquerdo = kd.buscar(30, 70);
    assert(filhoEsquerdo != nullptr);
    assert(filhoEsquerdo->esquerda != nullptr && filhoEsquerdo->esquerda->x == 10 && filhoEsquerdo->esquerda->y == 60);
    assert(filhoEsquerdo->direita != nullptr && filhoEsquerdo->direita->x == 40 && filhoEsquerdo->direita->y == 80);

    cout << "test_alternancia_de_eixo: OK\n";
}

void test_remocao_folha() {
    KDTREE kd;
    kd.inserir(50, 50);
    kd.inserir(30, 70);
    kd.inserir(70, 20);

    kd.remover(30, 70);
    assert(kd.buscar(30, 70) == nullptr);
    assert(kd.buscar(50, 50) != nullptr);
    assert(kd.buscar(70, 20) != nullptr);

    cout << "test_remocao_folha: OK\n";
}

// Remove um nó que tem filho À DIREITA -- o sucessor vem do mínimo
// (no eixo certo) da subárvore direita.
void test_remocao_com_filho_direito() {
    KDTREE kd;
    kd.inserir(50, 50);
    kd.inserir(70, 20); // nível 1, eixo y
    kd.inserir(90, 30); // desce até (70,20); nível 1 compara y: 30 >= 20 -> direita

    kd.remover(70, 20);

    assert(kd.buscar(70, 20) == nullptr);
    Node* substituto = kd.buscar(90, 30);
    assert(substituto != nullptr); // o ponto que era filho direito assumiu o lugar
    assert(substituto->esquerda == nullptr && substituto->direita == nullptr); // virou folha

    cout << "test_remocao_com_filho_direito: OK\n";
}

// Remove um nó que só tem filho À ESQUERDA -- precisa usar o mínimo da
// esquerda e reconectar do lado direito (convenção clássica da KD-Tree).
void test_remocao_com_apenas_filho_esquerdo() {
    KDTREE kd;
    kd.inserir(50, 50);
    kd.inserir(70, 20); // nível 1, eixo y
    kd.inserir(80, 10); // desce até (70,20); nível 1 compara y: 10 < 20 -> esquerda

    kd.remover(70, 20);

    assert(kd.buscar(70, 20) == nullptr);
    Node* substituto = kd.buscar(80, 10);
    assert(substituto != nullptr); // o ponto que era filho esquerdo assumiu o lugar
    assert(substituto->esquerda == nullptr && substituto->direita == nullptr); // virou folha

    cout << "test_remocao_com_apenas_filho_esquerdo: OK\n";
}

void test_remocao_elemento_inexistente() {
    KDTREE kd;
    kd.inserir(10, 10);
    kd.inserir(20, 20);

    kd.remover(999, 999); // não existe, não deve travar nem afetar nada
    assert(kd.buscar(10, 10) != nullptr);
    assert(kd.buscar(20, 20) != nullptr);

    cout << "test_remocao_elemento_inexistente: OK\n";
}

void test_remocao_ate_esvaziar() {
    KDTREE kd;
    kd.inserir(5, 5);
    kd.remover(5, 5);
    assert(kd.buscar(5, 5) == nullptr);
    kd.remover(5, 5); // remover de árvore vazia não deve travar
    cout << "test_remocao_ate_esvaziar: OK\n";
}

// exibir() percorre em pré-ordem (nó, depois esquerda, depois direita).
void test_exibir() {
    KDTREE kd;
    kd.inserir(50, 50);
    kd.inserir(30, 70);
    kd.inserir(70, 20);

    ostringstream buffer;
    streambuf* cout_original = cout.rdbuf(buffer.rdbuf());
    kd.exibir();
    cout.rdbuf(cout_original);

    string esperado = "(50, 50) (30, 70) (70, 20) \n";
    assert(buffer.str() == esperado);

    cout << "test_exibir: OK\n";
}

void test_exibir_vazia() {
    KDTREE kd;

    ostringstream buffer;
    streambuf* cout_original = cout.rdbuf(buffer.rdbuf());
    kd.exibir();
    cout.rdbuf(cout_original);

    assert(buffer.str() == "\n");
    cout << "test_exibir_vazia: OK\n";
}

int main() {
    test_arvore_vazia();
    test_insercao_e_busca_basica();
    test_insercao_duplicada();
    test_alternancia_de_eixo();

    test_remocao_folha();
    test_remocao_com_filho_direito();
    test_remocao_com_apenas_filho_esquerdo();
    test_remocao_elemento_inexistente();
    test_remocao_ate_esvaziar();

    test_exibir();
    test_exibir_vazia();

    cout << "\nTodos os testes da KD-Tree passaram!\n";
    return 0;
}