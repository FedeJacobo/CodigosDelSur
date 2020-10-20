#pragma once
#ifndef COMPARACIONCOSTO_H
#define COMPARACIONCOSTO_H
#include "Comparacion.h"
#include "Sistema.h"

class ComparacionCosto : public Comparacion<NodoArco> {
	typedef unsigned int nat;
public:
	//virtual ~ComparacionCosto() {}
	CompRetorno Comparar(const NodoArco& t1, const NodoArco& t2) const {
		nat costo1 = t1.costo;
		nat tiempo1 = t1.tiempo;
		nat vertices1 = t1.vertices;

		nat costo2 = t2.costo;
		nat tiempo2 = t2.tiempo;
		nat vertices2 = t2.vertices;

		if (costo1 == costo2 && tiempo1 == tiempo2 && vertices1 == vertices2) {
			return IGUALES;
		}
		else if (costo1 > costo2) {
			return MAYOR;
		}
		else if (costo1 < costo2) {
			return MENOR;
		}
		else {
			if (tiempo1 > tiempo2) {
				return MAYOR;
			}
			else if (tiempo1 < tiempo2) {
				return MENOR;
			}
			else {
				if (vertices1 > vertices2) {
					return MAYOR;
				}
				else {
					return MENOR;
				}
			}
		}
		return DISTINTOS;
	}
};

#endif