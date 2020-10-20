#ifndef COMPTABLERO_H
#define COMPTABLERO_H
#include "Comparacion.h"
#include <assert.h>
#include "Puntero.h"
#include "Tablero.h"
class CompTablero :public Comparacion<Tablero> {
public:
	CompRetorno Comparar(const Tablero & p1, const Tablero & p2) const
	{
		if (p1 == p2) return IGUALES;
		if (!(p1 == p2)) return DISTINTOS;
		assert(false);
		return MENOR;
		return MAYOR;

	}
};

#endif