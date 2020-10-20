#pragma once

#ifndef COLAPRIORIDADEXTENDIDA_H
#define COLAPRIORIDADEXTENDIDA_H

#include "Iterable.h"
#include "Puntero.h"
#include "Tupla.h"
#include "FuncionHash.h"
#include "Array.h"

typedef unsigned int nat;

template <class T, class P>
class ColaPrioridadExtendida abstract : public Iterable<Tupla<T,P>>
{
public:
	virtual ~ColaPrioridadExtendida() {}

	// PRE: -
	// POS: Inserta el elemento e con prioridad p
	virtual void InsertarConPrioridad(const T& e, const P& p) abstract;

	// PRE: La cola de prioridad no está vacía
	// POS: Retorna el elemento de mayor prioridad en la cola eliminándolo
	virtual T EliminarElementoMayorPrioridad() abstract;

	// PRE: La cola no está vacía
	// POS: Retorna el elemento de mayor prioridad en la cola sin eliminarlo
	virtual const T& ObtenerElementoMayorPrioridad() const abstract;
	
	// PRE: El elemento e pertenece a la cola.
	// POS: Retorna una tupla que contiene al elemento e y su prioridad.
	virtual Tupla<T, P> ObtenerElementoYPrioridad(const  T& e) abstract;

	// PRE: -
	// POS: Retorna el largo de la cola de prioridad
	virtual nat Largo() const abstract;
	
	// PRE: -
	// POS: Retorna true si y solo si el elemento e pertenece a la cola.
	virtual bool Pertenece(const T& e) const abstract;

	// PRE: El elemento e pertenece a la cola.
	// POS: El elemento e tiene una nueva prioridad p.
	virtual void CambiarPrioridad(const T& e, const P& p) abstract;
	
	// PRE: El elemento e pertenece a la cola.
	// POS: El elemento e no pertenece a la cola.
	virtual void EliminarElemento(T& e) abstract;

	// PRE: -
	// POS: Retorna true si y solo si la cola esta vacia
	virtual bool EstaVacia() const abstract;

	// PRE: -
	// POS: Retorna true si y solo si la cola esta llena
	virtual bool EstaLlena() const abstract;

	// PRE: -
	// POS: La cola esta vacía
	virtual void Vaciar() abstract;

	// PRE: -
	// POS: Retorna un clon de la cola que no comparte memoria con ella
	virtual Puntero<ColaPrioridadExtendida<T, P>> Clon() const abstract;
};


#endif