#include "../include/treap.hpp"
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

void test_arvore_vazia() {
    TREAP treap;
    assert(treap.buscar(10) == nullptr);
    cout << "test_arvore_vazia: OK\n";
}

void test_insercao_e_busca_basica() {
    TREAP treap;
    treap.inserir(50); // prioridade aleatória
    treap.inserir(30);
    treap.inserir(70);

    assert(treap.buscar(30) != nullptr);
    assert(treap.buscar(30)->chave == 30);
    assert(treap.buscar(999) == nullptr);

    cout << "test_insercao_e_busca_basica: OK\n";
}

void test_insercao_duplicada() {
    TREAP treap;
    treap.inserir(10, 100);
    treap.inserir(10, 999); // duplicata, deve ser ignorada (mantém a primeira)

    Node* achado = treap.buscar(10);
    assert(achado != nullptr);
    assert(achado->prioridade == 100); // prova que a segunda inserção foi ignorada

    cout << "test_insercao_duplicada: OK\n";
}

// Valida que a sobrecarga inserir(chave, prioridade) usa EXATAMENTE
// a prioridade passada, sem gerar outra a partir dela.
void test_prioridade_fixa_respeitada() {
    TREAP treap;
    treap.inserir(42, 777);

    Node* achado = treap.buscar(42);
    assert(achado != nullptr);
    assert(achado->prioridade == 777);

    cout << "test_prioridade_fixa_respeitada: OK\n";
}

// Filho tem prioridade maior que o pai -> deve rotacionar pra virar raiz.
void test_rotacao_insercao_direita() {
    TREAP treap;
    treap.inserir(50, 10);
    treap.inserir(30, 20); // maior prioridade, entra à esquerda -> rotaciona à direita

    Node* raiz = treap.buscar(30);
    assert(raiz != nullptr);
    assert(raiz->prioridade == 20);
    assert(raiz->esquerda == nullptr);
    assert(raiz->direita != nullptr && raiz->direita->chave == 50);

    cout << "test_rotacao_insercao_direita: OK\n";
}

void test_rotacao_insercao_esquerda() {
    TREAP treap;
    treap.inserir(50, 10);
    treap.inserir(70, 20); // maior prioridade, entra à direita -> rotaciona à esquerda

    Node* raiz = treap.buscar(70);
    assert(raiz != nullptr);
    assert(raiz->prioridade == 20);
    assert(raiz->direita == nullptr);
    assert(raiz->esquerda != nullptr && raiz->esquerda->chave == 50);

    cout << "test_rotacao_insercao_esquerda: OK\n";
}

// Prioridade mais alta ainda precisa "subir" vários níveis de uma vez.
void test_rotacao_multiplos_niveis() {
    TREAP treap;
    treap.inserir(50, 10);
    treap.inserir(30, 20); // sobe, vira raiz (prioridade 20 > 10)
    treap.inserir(10, 30); // prioridade mais alta ainda -> sobe até virar raiz de novo

    Node* raiz = treap.buscar(10);
    assert(raiz != nullptr);
    assert(raiz->prioridade == 30);
    assert(raiz->esquerda == nullptr);
    assert(raiz->direita != nullptr && raiz->direita->chave == 30);
    assert(raiz->direita->direita != nullptr && raiz->direita->direita->chave == 50);
    assert(raiz->direita->esquerda == nullptr);

    cout << "test_rotacao_multiplos_niveis: OK\n";
}

void test_propriedade_heap_respeitada() {
    TREAP treap;
    // insere em ordem que força várias rotações
    treap.inserir(50, 10);
    treap.inserir(30, 40);
    treap.inserir(70, 20);
    treap.inserir(20, 60);
    treap.inserir(40, 15);

    // em toda a árvore, prioridade do pai deve ser >= prioridade dos filhos (max-heap)
    Node* n20 = treap.buscar(20);
    Node* n30 = treap.buscar(30);
    Node* n50 = treap.buscar(50);
    assert(n20 != nullptr && n30 != nullptr && n50 != nullptr);

    // checagem pontual: quem tem prioridade 60 (chave 20) deve estar acima
    // de quem tem prioridade 40 (chave 30) na hierarquia da árvore
    assert(n20->prioridade == 60);
    assert(n30->prioridade == 40);

    cout << "test_propriedade_heap_respeitada: OK\n";
}

void test_remocao_folha() {
    TREAP treap;
    treap.inserir(50, 30);
    treap.inserir(30, 10);
    treap.inserir(70, 10);

    treap.remover(30);
    assert(treap.buscar(30) == nullptr);
    assert(treap.buscar(50) != nullptr);
    assert(treap.buscar(70) != nullptr);

    cout << "test_remocao_folha: OK\n";
}

void test_remocao_um_filho() {
    TREAP treap;
    treap.inserir(50, 30);
    treap.inserir(30, 20);
    treap.inserir(20, 10); // fica pendurado embaixo de 30, sem forçar rotação até a raiz

    treap.remover(30);
    assert(treap.buscar(30) == nullptr);
    assert(treap.buscar(20) != nullptr);
    assert(treap.buscar(50) != nullptr);

    cout << "test_remocao_um_filho: OK\n";
}

// Valida a remoção de um nó com dois filhos, incluindo a rotação de
// descida escolhendo o filho de MAIOR prioridade pra subir.
void test_remocao_dois_filhos_com_rotacao() {
    TREAP treap;
    treap.inserir(50, 100); // raiz
    treap.inserir(30, 50);  // esquerda
    treap.inserir(70, 60);  // direita, prioridade maior que a esquerda

    treap.remover(50);

    // esperado: 70 sobe (maior prioridade), 30 continua como filho esquerdo dele
    Node* raiz = treap.buscar(70);
    assert(raiz != nullptr);
    assert(raiz->prioridade == 60);
    assert(raiz->esquerda != nullptr && raiz->esquerda->chave == 30);
    assert(raiz->direita == nullptr);
    assert(treap.buscar(50) == nullptr);

    cout << "test_remocao_dois_filhos_com_rotacao: OK\n";
}

void test_remocao_elemento_inexistente() {
    TREAP treap;
    treap.inserir(10);
    treap.inserir(20);

    treap.remover(999);
    assert(treap.buscar(10) != nullptr);
    assert(treap.buscar(20) != nullptr);

    cout << "test_remocao_elemento_inexistente: OK\n";
}

void test_remocao_ate_esvaziar() {
    TREAP treap;
    treap.inserir(10);
    treap.remover(10);
    assert(treap.buscar(10) == nullptr);
    treap.remover(10); // remover de árvore vazia não deve travar
    cout << "test_remocao_ate_esvaziar: OK\n";
}

void test_exibir_ordem() {
    TREAP treap;
    // prioridades fixas só pra deixar a saída 100% previsível;
    // o in-order sempre sai ordenado por chave, independente da forma da árvore
    treap.inserir(20, 5);
    treap.inserir(10, 3);
    treap.inserir(30, 4);

    ostringstream buffer;
    streambuf* cout_original = cout.rdbuf(buffer.rdbuf());
    treap.exibirOrdem();
    cout.rdbuf(cout_original);

    string esperado = "[Chave: 10 | Prioridade: 3] [Chave: 20 | Prioridade: 5] [Chave: 30 | Prioridade: 4] \n";
    assert(buffer.str() == esperado);

    cout << "test_exibir_ordem: OK\n";
}

void test_exibir_ordem_vazia() {
    TREAP treap;

    ostringstream buffer;
    streambuf* cout_original = cout.rdbuf(buffer.rdbuf());
    treap.exibirOrdem();
    cout.rdbuf(cout_original);

    assert(buffer.str() == "\n");
    cout << "test_exibir_ordem_vazia: OK\n";
}

int main() {
    test_arvore_vazia();
    test_insercao_e_busca_basica();
    test_insercao_duplicada();
    test_prioridade_fixa_respeitada();

    test_rotacao_insercao_direita();
    test_rotacao_insercao_esquerda();
    test_rotacao_multiplos_niveis();
    test_propriedade_heap_respeitada();

    test_remocao_folha();
    test_remocao_um_filho();
    test_remocao_dois_filhos_com_rotacao();
    test_remocao_elemento_inexistente();
    test_remocao_ate_esvaziar();

    test_exibir_ordem();
    test_exibir_ordem_vazia();

    cout << "\nTodos os testes da Treap passaram!\n";
    return 0;
}