#pragma once
#ifndef COMPARACIONOMNIBUS_H
#define COMPARACIONOMNIBUS_H
#include "Comparacion.h"
#include "Sistema.h"

class ComparacionOmnibus : public Comparacion<NodoArco> {
public:
	virtual ~ComparacionOmnibus() {}
	CompRetorno Comparar(const NodoArco& t1, const NodoArco& t2) const {
		nat cantO1 = t1.cantO;
		nat tiempo1 = t1.tiempo;

		nat cantO2 = t2.cantO;
		nat tiempo2 = t2.tiempo;

		if (cantO1 == cantO2 && tiempo1 == tiempo2) {
			return IGUALES;
		}
		else if (cantO1 > cantO2) {
			return MAYOR; // PUEDE SER AL REVEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEZZZZZZZZZZZZZZZZZZZZZZ
		}
		else if (cantO1 < cantO2) {
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