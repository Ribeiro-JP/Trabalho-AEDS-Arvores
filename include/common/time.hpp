#pragma once

#include <chrono>

// Mede o tempo de execução (em milissegundos) de qualquer função/lambda
// passada como argumento. Uso:
//
//   double tempo = medir_ms([&]() {
//       // código a ser cronometrado
//   });
//
template <typename Func>
double medir_ms(Func&& func) {
    auto inicio = std::chrono::high_resolution_clock::now();
    func();
    auto fim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracao = fim - inicio;
    return duracao.count();
}
