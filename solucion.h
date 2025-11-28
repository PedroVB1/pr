#ifndef SOLUCION_H
#define SOLUCION_H

#include <cstddef>
#include <string>
#include <vector>

#include "casilla.h"

class Solucion {
public:
    Solucion() = default;
    Solucion(std::size_t filas, std::size_t columnas);

    void add(const Casilla &c);
    void remove(const Casilla &c);

    bool esCompatible(const Casilla &c, const std::vector<std::vector<int>> &pistasFilas,
                      const std::vector<std::vector<int>> &pistasColumnas) const;
    bool esConsistenteFinal(const std::vector<std::vector<int>> &pistasFilas,
                            const std::vector<std::vector<int>> &pistasColumnas) const;

    std::size_t filas() const { return filas_; }
    std::size_t columnas() const { return columnas_; }
    const std::vector<std::vector<char>> &tablero() const { return tablero_; }

    void mostrar() const;

private:
    bool lineaCompatible(const std::vector<char> &linea, const std::vector<int> &pistas,
                         bool final) const;

    std::vector<std::vector<char>> tablero_;
    std::size_t filas_{};
    std::size_t columnas_{};
};

#endif
