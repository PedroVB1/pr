#ifndef CASILLA_H
#define CASILLA_H

#include <cstddef>
#include <string>

// Representa una casilla individual de un nonograma
class Casilla {
public:
    enum class EstadoCasilla { Desconocida, Llena, Vacia };

    Casilla() = default;
    Casilla(std::size_t f, std::size_t c, EstadoCasilla e);

    std::size_t fila() const { return fila_; }
    std::size_t columna() const { return columna_; }
    EstadoCasilla estado() const { return estado_; }
    std::string estadoComoTexto() const;

    bool operator==(const Casilla &otro) const;

private:
    std::size_t fila_{};
    std::size_t columna_{};
    EstadoCasilla estado_{EstadoCasilla::Desconocida};
};

#endif
