#pragma once
#ifndef COMPARACIONAVION_H
#define COMPARACIONAVION_H
#include "Comparacion.h"
#include "Sistema.h"

class ComparacionAvion : public Comparacion<NodoArco> {
public:
	virtual ~ComparacionAvion() {}
	CompRetorno Comparar(const NodoArco& t1, const NodoArco& t2) const {
		nat cantA1 = t1.cantA;
		nat tiempo1 = t1.tiempo;

		nat cantA2 = t2.cantA;
		nat tiempo2 = t2.tiempo;

		if (cantA1 == cantA2 && tiempo1 == tiempo2) {
			return IGUALES;
		}
		else if (cantA1 > cantA2) {
			return MAYOR; // PUEDE SER AL REVEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEZZZZZZZZZZZZZZZZZZZZZZ
		}
		else if (cantA1 < cantA2) {
			return MENOR;
		}
		else {
			if (tiempo1 > tiempo2) {
				return MAYOR;
			}
			else if (tiempo1 < tiempo2) {
				return MENOR;
			}
		}
		return DISTINTOS;
	}
};

#endif