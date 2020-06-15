#pragma once

#include <random>
#include <ostream>
using namespace std;

class Nodo {
public:
    // Representa un nodo de la red de computadores sobre la cual se aplica la simulación
    // de dispersión de virus.

    /* TIPO PÚBLICO DE ESTADOS DE VÉRTICES */
    enum E { // representa el tipo de estados de la red de infección
        S, // representa un vértice susceptible de infección
        I, // representa un vértice infectado
        R, // representa un vértice resistente
    };

    Nodo();
    Nodo(const Nodo& orig);
    virtual ~Nodo();

    // EFE: retorna el valor del estado del nodo.
    E obtEstado() const;

    // MOD: *this.
    // EFE: cambia el estado del nodo a ne.
    void modEstado(E ne);

    // EFE: permite que n sea consumido por el flujo s mediante el operator<<.
    // NOTA: es una función externa a la clase que por hacer acceso
    //       a los atributos privados del nodo se debe declarar como friend.
    friend ostream& operator<<(ostream& s, const Nodo& n);

    // EFE: modifica *this con los valores de n.
    Nodo operator=(const Nodo& n);

private:
    E estado; // representa el estado del nodo
};

Nodo::Nodo() : estado(S) {
}

Nodo::Nodo(const Nodo& orig) : estado(orig.estado) {
}

Nodo::~Nodo() {
}

Nodo::E Nodo::obtEstado() const {
    return estado;
}

void Nodo::modEstado(E ne) {
    estado = ne;
}

ostream& operator<<(ostream& s, const Nodo& n) {

    if (n.estado == 0) {
        s << "S";
    }
    else if (n.estado == 1) {
        s << "I";
    }
    else if (n.estado == 2) {
        s << "R";
    }

    return s;
}

Nodo Nodo::operator=(const Nodo& n) {

    estado = n.estado;
    return *this;
}


