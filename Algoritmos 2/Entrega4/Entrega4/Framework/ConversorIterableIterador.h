#pragma once

#include "Conversor.h"
#include "Iterable.h"

template <class T>
class ConversorIterableIterador : public Conversor<Puntero<Iterable<T>>, Iterador<T>>
{
public:
	virtual ~ConversorIterableIterador(){}
protected:
	Iterador<T> Convertir(const Puntero<Iterable<T>>& iterable) const override;
};

template <class T>
Iterador<T> ConversorIterableIterador<T>::Convertir(Puntero<Iterable<T>> const& iterable) const
{
	return iterable->ObtenerIterador();
}