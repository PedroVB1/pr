#include "casilla.h"

Casilla::Casilla(std::size_t f, std::size_t c, EstadoCasilla e)
    : fila_(f), columna_(c), estado_(e) {}

std::string Casilla::estadoComoTexto() const {
    switch (estado_) {
    case EstadoCasilla::Llena:
        return "Llena";
    case EstadoCasilla::Vacia:
        return "Vacía";
    default:
        return "Desconocida";
    }
}

bool Casilla::operator==(const Casilla &otro) const {
    return fila_ == otro.fila_ && columna_ == otro.columna_ && estado_ == otro.estado_;
}
