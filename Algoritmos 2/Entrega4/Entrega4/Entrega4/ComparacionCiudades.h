#pragma once
#ifndef COMPARACIONCIUDADES_H
#define COMPARACIONCIUDADES_H
#include "Comparacion.h"
#include "Sistema.h"

class ComparacionCiudades : public Comparacion<NodoArco> {
public:
	virtual ~ComparacionCiudades() {}
	CompRetorno Comparar(const NodoArco& t1, const NodoArco& t2) const {
		nat paradas1 = t1.nroParadas;
		nat vertices1 = t1.vertices;

		nat paradas2 = t2.nroParadas;
		nat vertices2 = t2.vertices;

		if (vertices1 == vertices2 && paradas1 == paradas2) {
			return IGUALES;
		}
		else if (vertices1 > vertices2) {
			return MAYOR;
		}
		else if (vertices1 < vertices2) {
			return MENOR;
		}
		else {
			if (paradas1 > paradas2) {
				return MAYOR;
			}
			else if (paradas1 < paradas2) {
				return MENOR;
			}
		}
		return DISTINTOS;
	}
};

#endif