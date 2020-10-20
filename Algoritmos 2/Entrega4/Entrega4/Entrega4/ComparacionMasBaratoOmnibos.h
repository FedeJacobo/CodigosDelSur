#pragma once
#ifndef COMPARACIONMASBARATOOMNIBUS_H
#define COMPARACIONMASBARATOOMNIBUS_H
#include "Comparacion.h"
#include "sistema.h"

class ComparacionMasBaratoOmnibus : public Comparacion<NodoArco> {
public:
	virtual ~ComparacionMasBaratoOmnibus() {}
	CompRetorno Comparar(const NodoArco& t1, const NodoArco& t2) const {
		nat costo1 = t1.costo;
		nat cantO1 = t1.cantO;
		
		nat costo2 = t2.costo;
		nat cantO2 = t2.cantO;

		if (costo1 == costo2 && cantO1 == cantO2) {
			return IGUALES;
		}
		else if (costo1 > costo2) {
			return MAYOR;
		}
		else if (costo1 < costo2) {
			return MENOR;
		}
		else {
			if (cantO1 > cantO2) {
				return MAYOR;
			}
			else if (cantO1 < cantO2) {
				return MENOR;
			}
		}
		return DISTINTOS;
	}
};

#endif
