#include "../include/BST.hpp"
#include <iostream>
#include <cassert>

using namespace std;

void test_arvore_vazia() {
    BST arvore;
    assert(arvore.buscar(10) == nullptr);
    cout << "test_arvore_vazia: OK\n";
}

void test_insercao_e_busca_basica() {
    BST arvore;
    arvore.inserir(50);
    arvore.inserir(30);
    arvore.inserir(70);
    arvore.inserir(20);
    arvore.inserir(40);

    Node* achado = arvore.buscar(30);
    assert(achado != nullptr);
    assert(achado->chave == 30);

    assert(arvore.buscar(999) == nullptr); // não existe

    cout << "test_insercao_e_busca_basica: OK\n";
}

void test_insercao_duplicada() {
    BST arvore;
    arvore.inserir(10);
    arvore.inserir(10); // duplicata: sua implementação ignora

    Node* achado = arvore.buscar(10);
    assert(achado != nullptr);
    assert(achado->chave == 10);
    // não temos como checar diretamente "só existe um nó" sem percorrer,
    // mas o importante aqui é não travar/crashar ao inserir duplicata
    cout << "test_insercao_duplicada: OK\n";
}

void test_remocao_folha() {
    BST arvore;
    arvore.inserir(50);
    arvore.inserir(30);
    arvore.inserir(70);

    arvore.remover(30); // 30 é folha
    assert(arvore.buscar(30) == nullptr);
    assert(arvore.buscar(50) != nullptr); // resto da árvore intacto
    assert(arvore.buscar(70) != nullptr);

    cout << "test_remocao_folha: OK\n";
}

void test_remocao_um_filho() {
    BST arvore;
    arvore.inserir(50);
    arvore.inserir(30);
    arvore.inserir(20); // 30 tem só filho esquerdo (20)

    arvore.remover(30);
    assert(arvore.buscar(30) == nullptr);
    assert(arvore.buscar(20) != nullptr); // 20 deve ter "subido" no lugar de 30
    assert(arvore.buscar(50) != nullptr);

    cout << "test_remocao_um_filho: OK\n";
}

void test_remocao_dois_filhos() {
    BST arvore;
    arvore.inserir(50);
    arvore.inserir(30);
    arvore.inserir(70);
    arvore.inserir(60);
    arvore.inserir(80);
    // 70 tem dois filhos: 60 e 80. Sucessor in-order de 70 é 80... 
    // não, sucessor é o mínimo da subárvore direita: aqui seria 80 mesmo
    // (já que 80 é o único nó à direita de 70 e não tem filho esquerdo)

    arvore.remover(70);
    assert(arvore.buscar(70) == nullptr);
    assert(arvore.buscar(60) != nullptr);
    assert(arvore.buscar(80) != nullptr);
    assert(arvore.buscar(50) != nullptr);
    assert(arvore.buscar(30) != nullptr);

    cout << "test_remocao_dois_filhos: OK\n";
}

void test_remocao_raiz_com_dois_filhos() {
    BST arvore;
    arvore.inserir(50);
    arvore.inserir(30);
    arvore.inserir(70);
    arvore.inserir(60);
    arvore.inserir(80);
    arvore.inserir(65); // sucessor in-order de 50 agora é 60

    arvore.remover(50);
    assert(arvore.buscar(50) == nullptr);
    // a árvore inteira deve continuar acessível a partir da nova raiz
    assert(arvore.buscar(30) != nullptr);
    assert(arvore.buscar(70) != nullptr);
    assert(arvore.buscar(60) != nullptr);
    assert(arvore.buscar(80) != nullptr);
    assert(arvore.buscar(65) != nullptr);

    cout << "test_remocao_raiz_com_dois_filhos: OK\n";
}

void test_remocao_elemento_inexistente() {
    BST arvore;
    arvore.inserir(10);
    arvore.inserir(20);

    arvore.remover(999); // não deve travar nem afetar o resto
    assert(arvore.buscar(10) != nullptr);
    assert(arvore.buscar(20) != nullptr);

    cout << "test_remocao_elemento_inexistente: OK\n";
}

void test_remocao_ate_esvaziar() {
    BST arvore;
    arvore.inserir(10);
    arvore.remover(10);
    assert(arvore.buscar(10) == nullptr);
    // remover de novo numa árvore já vazia não deve travar
    arvore.remover(10);
    cout << "test_remocao_ate_esvaziar: OK\n";
}

int main() {
    test_arvore_vazia();
    test_insercao_e_busca_basica();
    test_insercao_duplicada();
    test_remocao_folha();
    test_remocao_um_filho();
    test_remocao_dois_filhos();
    test_remocao_raiz_com_dois_filhos();
    test_remocao_elemento_inexistente();
    test_remocao_ate_esvaziar();

    cout << "\nTodos os testes da BST passaram!\n";
    return 0;
}

/*
 * Esse codigo de teste foi gerado por agente de IA(Gemini) para facilitar os testes
 * e agilizar o processo de validação do codigo.
 * IMPORTANTE: voltar aqui depois é por conta propria melhorar essa validação, claro
 * se me sobrar tempo, aliais não está sendo testaddo o exibir nessas funções.
 */