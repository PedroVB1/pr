#ifndef PROBLEMA_H
#define PROBLEMA_H

#include <vector>

#include "estado.h"

class Problema {
public:
    Problema(std::vector<std::vector<int>> pistasFilas,
             std::vector<std::vector<int>> pistasColumnas);

    void ejecutarBacktracking();
    void ejecutarVoraz();
    void actualizaMejorSolucion(const Estado &e);

    const Solucion &mejorSolucion() const { return mejorSolucion_; }

private:
    void bt(Estado &estado);
    void aplicarDeduccionesBasicas(Solucion &sol) const;

    std::vector<std::vector<int>> pistasFilas_;
    std::vector<std::vector<int>> pistasColumnas_;
    Solucion mejorSolucion_;
};

#endif
