#include <iostream>
#include <vector>

#include "problema.h"

int main() {
    // Ejemplo sencillo 5x5
    std::vector<std::vector<int>> pistasFilas{{1}, {3}, {5}, {3}, {1}};
    std::vector<std::vector<int>> pistasColumnas{{1}, {3}, {5}, {3}, {1}};

    Problema problema(std::move(pistasFilas), std::move(pistasColumnas));

    std::cout << "Resolución voraz (deducciones básicas):\n";
    problema.ejecutarVoraz();
    problema.mejorSolucion().mostrar();

    std::cout << "\nResolución por backtracking:\n";
    problema.ejecutarBacktracking();
    problema.mejorSolucion().mostrar();

    return 0;
}
