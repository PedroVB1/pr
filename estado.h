#ifndef ESTADO_H
#define ESTADO_H

#include <vector>

#include "casilla.h"
#include "solucion.h"

class Estado {
public:
    Estado(const std::vector<std::vector<int>> &pistasFilas,
           const std::vector<std::vector<int>> &pistasColumnas);

    const Solucion &getSol() const { return sol_; }

    void avanza(const Casilla &c);
    void retrocede(const Casilla &c);

    std::vector<Casilla> getAlternativas() const;
    bool esFinal() const;

private:
    std::size_t posicionActual_{0};
    const std::vector<std::vector<int>> &pistasFilas_;
    const std::vector<std::vector<int>> &pistasColumnas_;
    Solucion sol_;
};

#endif
