#include "estado.h"

#include <algorithm>

Estado::Estado(const std::vector<std::vector<int>> &pistasFilas,
               const std::vector<std::vector<int>> &pistasColumnas)
    : pistasFilas_(pistasFilas), pistasColumnas_(pistasColumnas),
      sol_(pistasFilas.size(), pistasColumnas.size()) {}

void Estado::avanza(const Casilla &c) {
    sol_.add(c);
    ++posicionActual_;
}

void Estado::retrocede(const Casilla &c) {
    sol_.remove(c);
    if (posicionActual_ > 0)
        --posicionActual_;
}

std::vector<Casilla> Estado::getAlternativas() const {
    std::vector<Casilla> alternativas;
    std::size_t fila = posicionActual_ / sol_.columnas();
    std::size_t columna = posicionActual_ % sol_.columnas();

    Casilla llena(fila, columna, Casilla::EstadoCasilla::Llena);
    Casilla vacia(fila, columna, Casilla::EstadoCasilla::Vacia);

    if (sol_.esCompatible(llena, pistasFilas_, pistasColumnas_))
        alternativas.push_back(llena);
    if (sol_.esCompatible(vacia, pistasFilas_, pistasColumnas_))
        alternativas.push_back(vacia);

    return alternativas;
}

bool Estado::esFinal() const {
    if (posicionActual_ < sol_.filas() * sol_.columnas())
        return false;
    return sol_.esConsistenteFinal(pistasFilas_, pistasColumnas_);
}
