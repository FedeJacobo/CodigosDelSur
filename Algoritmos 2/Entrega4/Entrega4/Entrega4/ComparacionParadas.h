#pragma once
#ifndef COMPARACIONPARADAS_H
#define COMPARACIONPARADAS_H
#include "Comparacion.h"
#include "sistema.h"

class ComparacionParadas : public Comparacion<NodoArco> {
public:
	virtual ~ComparacionParadas() {}
	CompRetorno Comparar(const NodoArco& t1, const NodoArco& t2) const {
		nat paradas1 = t1.nroParadas;
		nat costo1 = t1.costo;

		nat paradas2 = t2.nroParadas;
		nat costo2 = t2.costo;

		if (costo1 == costo2 && paradas1 == paradas2) {
			return IGUALES;
		}
		else if (paradas1 > paradas2) {
			return MAYOR;
		}
		else if (paradas1 < paradas2) {
			return MENOR;
		}
		else {
			if (costo1 > costo2) {
				return MAYOR;
			}
			else if (costo1 < costo2) {
				return MENOR;
			}
		}
		return DISTINTOS;
	}
};

#endif