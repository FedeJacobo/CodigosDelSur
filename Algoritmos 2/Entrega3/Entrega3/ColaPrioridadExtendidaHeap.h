#pragma once

#ifndef COLAPRIORIDADEXTENDIDAHEAP_H
#define COLAPRIORIDADEXTENDIDAHEAP_H
#include "ColaPrioridadExtendida.h"

template <class T, class P>
class ColaPrioridadExtendidaHeap: public ColaPrioridadExtendida<T, P>
{
private:
	Array<Puntero<Tupla<T, P>>> cola;
	nat cantElem;
	Puntero<FuncionHash<T>> fHash;
	Comparador<T> compE;
	Comparador<P> compP;

	void Flotar(nat pos);
	void Hundir(nat pos);
	void AgrandarArray();
public:

	ColaPrioridadExtendidaHeap(const Comparador<T>& compElementos, const Comparador<P>& compPrioridades, Puntero<FuncionHash<T>> fHashElementos);

	~ColaPrioridadExtendidaHeap() {}

	void InsertarConPrioridad(const T& e, const P& p);

	T EliminarElementoMayorPrioridad();

	const T& ObtenerElementoMayorPrioridad() const;

	Tupla<T, P> ObtenerElementoYPrioridad(const  T& e);

	nat Largo() const;

	bool Pertenece(const T& e) const;

	void CambiarPrioridad(const T& e, const P& p);

	void EliminarElemento(T& e);

	bool EstaVacia() const;

	bool EstaLlena() const;

	void Vaciar();

	Iterador<Tupla<T, P>> ObtenerIterador() const;

	Puntero<ColaPrioridadExtendida<T, P>> Clon() const;
};

#include "ColaPrioridadExtendidaHeap.cpp"
#endif