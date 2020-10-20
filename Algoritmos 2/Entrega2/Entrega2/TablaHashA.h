#pragma once
#ifndef TABLAHASHA_H
#define TABLAHASHA_H

#include "Tabla.h"

template <class C, class V>
class TablaHashA : public Tabla<C, V>
{
private:
	Array<Puntero<NodoLista<Tupla<C, V>>>> hash;
	nat cubetas;
	nat cantElem;
	nat tope;
	Comparador<C> comp;
	Puntero<FuncionHash<C>> funcH;
public:
	//constructor
	TablaHashA(nat cantidadElementos, Puntero<FuncionHash<C>> funcionH, const Comparador<C>& comp);

	//destructor
	~TablaHashA();

	void Agregar(const C& c, const V& v);

	void Borrar(const C& c);

	void BorrarTodos();

	/* PREDICADOS */

	bool EstaVacia() const;

	bool EstaLlena() const;

	bool EstaDefinida(const C& c) const;

	/* SELECTORAS */

	const V& Obtener(const C& c) const;

	nat Largo() const;

	Iterador<Tupla<C, V>> ObtenerIterador() const;

	Puntero<Tabla<C, V>> Clonar() const;
};

#include "TablaHashA.cpp"
#endif