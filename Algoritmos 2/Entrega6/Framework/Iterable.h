#pragma once

#include "Iterador.h"

template <class T>
class Iterable abstract
{
public:
	virtual ~Iterable(){}

	// Retorna un nuevo iterador sobre la estructura
	// Postcondición: El iterador se encuentra reiniciado
	virtual Iterador<T> ObtenerIterador() const abstract;
};

template <class T>
Puntero<Iteracion<T>> unwrapIterador(const Iterable<T>& it)
{
	return it.ObtenerIterador().Unwrap();
}

template <class PtrIterable>
auto unwrapIterador(PtrIterable it) -> decltype(it->ObtenerIterador().Unwrap())
{
	return it->ObtenerIterador().Unwrap();
}