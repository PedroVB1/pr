#include "problema.h"

#include <algorithm>
#include <iostream>

Problema::Problema(std::vector<std::vector<int>> pistasFilas,
                   std::vector<std::vector<int>> pistasColumnas)
    : pistasFilas_(std::move(pistasFilas)), pistasColumnas_(std::move(pistasColumnas)),
      mejorSolucion_(pistasFilas_.size(), pistasColumnas_.size()) {}

void Problema::ejecutarBacktracking() {
    Estado estado(pistasFilas_, pistasColumnas_);
    bt(estado);
}

void Problema::bt(Estado &estado) {
    if (estado.esFinal()) {
        actualizaMejorSolucion(estado);
        return;
    }

    for (const auto &c : estado.getAlternativas()) {
        estado.avanza(c);
        bt(estado);
        estado.retrocede(c);
    }
}

void Problema::aplicarDeduccionesBasicas(Solucion &sol) const {
    // Estrategia voraz: para cada fila/columna, marcar casillas que sean comunes
    for (std::size_t f = 0; f < pistasFilas_.size(); ++f) {
        const auto &pistas = pistasFilas_[f];
        int total = 0;
        for (int pista : pistas)
            total += pista;
        int solapamiento = total + static_cast<int>(pistas.size()) - 1 - static_cast<int>(pistasColumnas_.size());
        if (solapamiento > 0) {
            int inicio = 0;
            for (int pista : pistas) {
                int margen = pistasColumnas_.size() - pista - inicio;
                int fijoDesde = inicio + std::max(0, pista - margen);
                int fijoHasta = inicio + pista - 1 - std::max(0, pista - margen);
                for (int c = fijoDesde; c <= fijoHasta; ++c) {
                    sol.add(Casilla(f, c, Casilla::EstadoCasilla::Llena));
                }
                inicio += pista + 1;
            }
        }
    }

    for (std::size_t c = 0; c < pistasColumnas_.size(); ++c) {
        const auto &pistas = pistasColumnas_[c];
        int total = 0;
        for (int pista : pistas)
            total += pista;
        int solapamiento = total + static_cast<int>(pistas.size()) - 1 - static_cast<int>(pistasFilas_.size());
        if (solapamiento > 0) {
            int inicio = 0;
            for (int pista : pistas) {
                int margen = pistasFilas_.size() - pista - inicio;
                int fijoDesde = inicio + std::max(0, pista - margen);
                int fijoHasta = inicio + pista - 1 - std::max(0, pista - margen);
                for (int f = fijoDesde; f <= fijoHasta; ++f) {
                    sol.add(Casilla(f, c, Casilla::EstadoCasilla::Llena));
                }
                inicio += pista + 1;
            }
        }
    }
}

void Problema::ejecutarVoraz() {
    Solucion sol(pistasFilas_.size(), pistasColumnas_.size());
    aplicarDeduccionesBasicas(sol);
    mejorSolucion_ = sol;
}

void Problema::actualizaMejorSolucion(const Estado &e) { mejorSolucion_ = e.getSol(); }
