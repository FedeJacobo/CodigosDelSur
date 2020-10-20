#ifndef PRIORIDAD_B_H
#define PRIORIDAD_B_H

#include "Tablero.h"
#include "Prioridad.h"

typedef unsigned int nat;

class PrioridadB : public Prioridad {
public:
	PrioridadB() {};

	//Retorna la suma de distancias de los bloques a su posicion final. 
	nat CalcularPrioridad(const Tablero& t) const;
};

#endif