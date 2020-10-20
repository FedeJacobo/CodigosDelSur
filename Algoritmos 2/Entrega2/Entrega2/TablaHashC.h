#pragma once
#ifndef TABLAHASHC_H
#define TABLAHASHC_H

#include "Tabla.h"

template <class C, class V>
class TablaHashC : public Tabla<C, V>
{
private:
	Array<Puntero<Tupla<C, V, int>>> hash; // 0-libre  1-ocupado  2-de baja
	nat cantElem;
	nat cubetas;
	Puntero<FuncionHash<C>> funcH;
	Comparador<C> comp;
public:
	//constructor
	TablaHashC(nat cantidadElementos, Puntero<FuncionHash<C>> fHash, const Comparador<C>& comp);

	//destructor
	~TablaHashC();

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

#include "TablaHashC.cpp"
#endif