#pragma once

#include "Puntero.h"

template <class T>
class Iteracion abstract
{
public:
	virtual ~Iteracion(){}

	virtual bool HayElemento() const abstract;
	virtual const T& ElementoActual() const abstract;
	virtual void Avanzar() abstract;
	virtual void Reiniciar() abstract;

	virtual Puntero<Iteracion<T>> Clonar() const { return nullptr; }
};