#include "solucion.h"

#include <algorithm>
#include <iostream>

namespace {
constexpr char LLENA = '#';
constexpr char VACIA = '.';
constexpr char DESCONOCIDA = '?';
}

Solucion::Solucion(std::size_t filas, std::size_t columnas)
    : tablero_(filas, std::vector<char>(columnas, DESCONOCIDA)), filas_(filas),
      columnas_(columnas) {}

void Solucion::add(const Casilla &c) {
    tablero_[c.fila()][c.columna()] =
        c.estado() == Casilla::EstadoCasilla::Llena ? LLENA : VACIA;
}

void Solucion::remove(const Casilla &c) { tablero_[c.fila()][c.columna()] = DESCONOCIDA; }

bool Solucion::lineaCompatible(const std::vector<char> &linea, const std::vector<int> &pistas,
                               bool final) const {
    std::vector<int> grupos;
    int conteo = 0;
    for (char celda : linea) {
        if (celda == LLENA) {
            ++conteo;
        } else {
            if (conteo > 0) {
                grupos.push_back(conteo);
                conteo = 0;
            }
        }
    }
    if (conteo > 0)
        grupos.push_back(conteo);

    if (!final) {
        // En parcial, los grupos no pueden exceder las pistas ni su tamaño
        if (grupos.size() > pistas.size())
            return false;
        for (std::size_t i = 0; i < grupos.size(); ++i) {
            if (grupos[i] > pistas[i])
                return false;
        }
        // Si hay casillas desconocidas, permitir que el último grupo sea incompleto
        if (!pistas.empty() && grupos.size() == pistas.size() && conteo == 0) {
            // Si ya no quedan incógnitas, debe coincidir
            bool hayDesconocidas = std::any_of(linea.begin(), linea.end(), [](char c) {
                return c == DESCONOCIDA;
            });
            if (!hayDesconocidas && grupos != pistas)
                return false;
        }
        return true;
    }

    return grupos == pistas;
}

bool Solucion::esCompatible(const Casilla &c, const std::vector<std::vector<int>> &pistasFilas,
                            const std::vector<std::vector<int>> &pistasColumnas) const {
    std::vector<std::vector<char>> copia = tablero_;
    copia[c.fila()][c.columna()] =
        c.estado() == Casilla::EstadoCasilla::Llena ? LLENA : VACIA;

    const auto &fila = copia[c.fila()];
    std::vector<char> columna(columnas_);
    for (std::size_t f = 0; f < filas_; ++f) {
        columna[f] = copia[f][c.columna()];
    }

    bool filaFinal = std::none_of(fila.begin(), fila.end(), [](char celda) {
        return celda == DESCONOCIDA;
    });
    bool colFinal = std::none_of(columna.begin(), columna.end(), [](char celda) {
        return celda == DESCONOCIDA;
    });

    return lineaCompatible(fila, pistasFilas[c.fila()], filaFinal) &&
           lineaCompatible(columna, pistasColumnas[c.columna()], colFinal);
}

bool Solucion::esConsistenteFinal(const std::vector<std::vector<int>> &pistasFilas,
                                  const std::vector<std::vector<int>> &pistasColumnas) const {
    for (std::size_t f = 0; f < filas_; ++f) {
        if (!lineaCompatible(tablero_[f], pistasFilas[f], true))
            return false;
    }
    for (std::size_t c = 0; c < columnas_; ++c) {
        std::vector<char> columna(filas_);
        for (std::size_t f = 0; f < filas_; ++f) {
            columna[f] = tablero_[f][c];
        }
        if (!lineaCompatible(columna, pistasColumnas[c], true))
            return false;
    }
    return true;
}

void Solucion::mostrar() const {
    for (const auto &fila : tablero_) {
        for (char celda : fila) {
            std::cout << celda << ' ';
        }
        std::cout << '\n';
    }
}
