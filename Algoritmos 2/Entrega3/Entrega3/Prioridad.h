#ifndef PRIORIDAD_H
#define PRIORIDAD_H

#include "Tablero.h"

typedef unsigned int nat;
class Tablero;

class Prioridad abstract {
public:
	//Retorna un calculo de prioridad
	virtual nat CalcularPrioridad(const Tablero& t) const abstract;
};

#endif