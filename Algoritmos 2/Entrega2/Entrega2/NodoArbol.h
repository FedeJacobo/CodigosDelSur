#ifndef NODOARBOL_H
#define NODOARBOL_H

#include "Puntero.h"

template<class T>
class NodoArbol
{
	public:
		T dato;
		Puntero<NodoArbol<T>> izq;
		Puntero<NodoArbol<T>> der;
};

#endif