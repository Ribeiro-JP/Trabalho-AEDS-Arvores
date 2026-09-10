#include "../include/splay.hpp"
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

void test_arvore_vazia() {
    SPLAY splay;
    assert(splay.buscar(10) == nullptr);
    cout << "test_arvore_vazia: OK\n";
}

// Toda inserção deve trazer o nó recém-inserido para a raiz.
void test_insercao_traz_para_raiz() {
    SPLAY splay;
    splay.inserir(10);
    splay.inserir(20);
    splay.inserir(30);

    Node* raiz = splay.buscar(30);
    assert(raiz != nullptr);
    assert(raiz->chave == 30);
    assert(raiz->esquerda != nullptr && raiz->esquerda->chave == 20);
    assert(raiz->esquerda->esquerda != nullptr && raiz->esquerda->esquerda->chave == 10);
    assert(raiz->direita == nullptr);

    cout << "test_insercao_traz_para_raiz: OK\n";
}

// Busca por uma chave que NÃO está na raiz deve trazê-la pra raiz (zig-zig).
void test_busca_traz_para_raiz() {
    SPLAY splay;
    splay.inserir(50);
    splay.inserir(30);
    splay.inserir(70);
    // depois dessas 3 inserções a raiz é 70; buscar 30 (dois níveis abaixo)
    // deve reorganizar a árvore trazendo 30 pra raiz

    Node* raiz = splay.buscar(30);
    assert(raiz != nullptr);
    assert(raiz->chave == 30);
    assert(raiz->esquerda == nullptr);
    assert(raiz->direita != nullptr && raiz->direita->chave == 50);
    assert(raiz->direita->direita != nullptr && raiz->direita->direita->chave == 70);
    assert(raiz->direita->esquerda == nullptr);

    cout << "test_busca_traz_para_raiz: OK\n";
}

// Caso zig-zig completo (Zag-Zag): busca numa cadeia de 4 níveis pra
// a direita e confirma que a árvore fica "balanceada" após o splay,
// não só que o nó sobe.
void test_zig_zig_completo() {
    SPLAY splay;
    splay.inserir(10);
    splay.inserir(20);
    splay.inserir(30);
    splay.inserir(40);
    // inserções crescentes fazem cada novo nó virar raiz com o antigo à
    // ESQUERDA -- então nesse ponto a árvore é uma cadeia à esquerda:
    // 40 -> esquerda:30 -> esquerda:20 -> esquerda:10 (40 já é raiz)

    // busca o valor mais profundo (10) pra forçar um zig-zig completo
    Node* raiz = splay.buscar(10);
    assert(raiz != nullptr);
    assert(raiz->chave == 10);
    assert(raiz->esquerda == nullptr);
    assert(raiz->direita != nullptr && raiz->direita->chave == 30);
    assert(raiz->direita->esquerda != nullptr && raiz->direita->esquerda->chave == 20);
    assert(raiz->direita->direita != nullptr && raiz->direita->direita->chave == 40);

    cout << "test_zig_zig_completo: OK\n";
}

// Buscar uma chave que NÃO existe ainda assim reorganiza a árvore --
// comportamento característico da Splay, diferente de BST/AVL/Treap.
void test_busca_falha_reorganiza() {
    SPLAY splay;
    splay.inserir(10);
    splay.inserir(20);
    splay.inserir(30);
    splay.inserir(40);
    // cadeia à esquerda: 40 -> esquerda:30 -> esquerda:20 -> esquerda:10

    Node* resultado = splay.buscar(25); // não existe, entre 20 e 30
    assert(resultado == nullptr);

    // mesmo não achando, o último nó visitado no caminho (20) deve ter
    // subido pra raiz -- essa segunda chamada só confirma o estado atual,
    // já que 20 agora está na raiz (não custa reorganização extra real)
    Node* raiz = splay.buscar(20);
    assert(raiz != nullptr && raiz->chave == 20);
    assert(raiz->esquerda != nullptr && raiz->esquerda->chave == 10);
    assert(raiz->direita != nullptr && raiz->direita->chave == 30);
    assert(raiz->direita->direita != nullptr && raiz->direita->direita->chave == 40);
    assert(raiz->direita->esquerda == nullptr);

    cout << "test_busca_falha_reorganiza: OK\n";
}

void test_insercao_duplicada() {
    SPLAY splay;
    splay.inserir(10);
    splay.inserir(10); // duplicata, sua inserirR ignora (não cria segundo nó)

    Node* achado = splay.buscar(10);
    assert(achado != nullptr);
    assert(achado->chave == 10);

    cout << "test_insercao_duplicada: OK\n";
}

void test_remocao_folha() {
    SPLAY splay;
    splay.inserir(50);
    splay.inserir(30);
    splay.inserir(70);

    splay.remover(30);
    assert(splay.buscar(30) == nullptr);
    assert(splay.buscar(50) != nullptr);
    assert(splay.buscar(70) != nullptr);

    cout << "test_remocao_folha: OK\n";
}

// Remove a raiz atual (que tem dois filhos) e confirma que a árvore
// continua correta -- sem depender da forma exata resultante, só de
// que os valores certos continuam (ou não) acessíveis, em ordem.
void test_remocao_raiz_com_dois_filhos() {
    SPLAY splay;
    splay.inserir(20);
    splay.inserir(10);
    splay.inserir(30); // raiz atual = 30, com esquerda=20(esquerda=10)

    Node* raizAntes = splay.buscar(30);
    assert(raizAntes != nullptr); // confirma que 30 é mesmo a raiz atual antes de remover

    splay.remover(30);
    assert(splay.buscar(30) == nullptr);
    assert(splay.buscar(10) != nullptr);
    assert(splay.buscar(20) != nullptr);

    cout << "test_remocao_raiz_com_dois_filhos: OK\n";
}

void test_remocao_elemento_inexistente() {
    SPLAY splay;
    splay.inserir(10);
    splay.inserir(20);

    splay.remover(999);
    assert(splay.buscar(10) != nullptr);
    assert(splay.buscar(20) != nullptr);

    cout << "test_remocao_elemento_inexistente: OK\n";
}

void test_remocao_ate_esvaziar() {
    SPLAY splay;
    splay.inserir(10);
    splay.remover(10);
    assert(splay.buscar(10) == nullptr);
    splay.remover(10); // remover de árvore vazia não deve travar
    cout << "test_remocao_ate_esvaziar: OK\n";
}

// exibirOrdem é in-order, então sempre sai ordenado por chave,
// independente de como o splay reorganizou a árvore por baixo.
void test_exibir_ordem() {
    SPLAY splay;
    splay.inserir(50);
    splay.inserir(30);
    splay.inserir(70);
    splay.inserir(20);
    splay.inserir(40);

    ostringstream buffer;
    streambuf* cout_original = cout.rdbuf(buffer.rdbuf());
    splay.exibirOrdem();
    cout.rdbuf(cout_original);

    string esperado = "20 30 40 50 70 \n";
    assert(buffer.str() == esperado);

    cout << "test_exibir_ordem: OK\n";
}

void test_exibir_ordem_vazia() {
    SPLAY splay;

    ostringstream buffer;
    streambuf* cout_original = cout.rdbuf(buffer.rdbuf());
    splay.exibirOrdem();
    cout.rdbuf(cout_original);

    assert(buffer.str() == "\n");
    cout << "test_exibir_ordem_vazia: OK\n";
}

int main() {
    test_arvore_vazia();
    test_insercao_traz_para_raiz();
    test_busca_traz_para_raiz();
    test_zig_zig_completo();
    test_busca_falha_reorganiza();
    test_insercao_duplicada();

    test_remocao_folha();
    test_remocao_raiz_com_dois_filhos();
    test_remocao_elemento_inexistente();
    test_remocao_ate_esvaziar();

    test_exibir_ordem();
    test_exibir_ordem_vazia();

    cout << "\nTodos os testes da Splay passaram!\n";
    return 0;
}