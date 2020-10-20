#pragma once

#include "Iteracion.h"
#include "Puntero.h"

template <class T>
class Iterable;

#define foreach(item, iterador)																									\
	for (auto __iterator__ = unwrapIterador(iterador); __iterator__ && __iterator__->HayElemento(); __iterator__->Avanzar())	\
		if (bool __iterated__ = false) {} else for (item = __iterator__->ElementoActual(); !__iterated__; __iterated__ = true)

template <class T>
class Iterador sealed
{
public:
	Iterador(Iteracion<T>* iteracion = nullptr);
	Iterador(const Puntero<Iteracion<T>>& iteracion);
	Iterador(const Puntero<Iterable<T>>& iterable);
	Iterador(const Iterador<T>& iterador);

	const Iterador<T>& operator=(Iteracion<T>* iteracion);
	const Iterador<T>& operator=(const Puntero<Iteracion<T>>& iteracion);
	const Iterador<T>& operator=(const Puntero<Iterable<T>>& iterable);
	const Iterador<T>& operator=(const Iterador<T>& iterador);

	void Reiniciar();
	bool HayElemento() const;
	const T& ElementoActual() const;
	void Avanzar();

	inline Iterador<T>& operator++();
	inline Iterador<T> operator++(int);
	inline const T& operator*() const;
	inline bool operator!() const;
	inline operator bool() const;

	template <class U> operator Iterador<U>() const;

	template <class U, typename Conv>
	Iterador<U> Convert() const;

	Iterador<T> Concat(const Iterador<T>& it) const;

	Iterador<T> Clonar() const;

	Puntero<Iteracion<T>> Unwrap() const;

private:
	Puntero<Iteracion<T>> m_Iteracion;
};

template <class T>
Puntero<Iteracion<T>> unwrapIterador(const Iterador<T>& it)
{
	return it.Unwrap();
}

#include "Iterador.cpp"