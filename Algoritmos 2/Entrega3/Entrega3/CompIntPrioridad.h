#ifndef COMPINTPRIORIDAD_H
#define COMPINTPRIORIDAD_H
#include "Comparacion.h"
#include <assert.h>
#include "Puntero.h"

class CompIntPrioridad :public Comparacion<int> {
public:
	CompRetorno Comparar(const int & p1, const int & p2) const
	{
		if (p1 == p2) return IGUALES;
		if (p1 > p2) return MENOR;
		if (p1 < p2) return MAYOR;
		assert(false);
		return DISTINTOS;
	}
};

#endif