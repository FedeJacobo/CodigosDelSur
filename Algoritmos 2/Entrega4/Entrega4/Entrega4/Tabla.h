#ifndef TABLA_H
#define TABLA_H

#include "Iterable.h"
#include "Puntero.h"
#include "Array.h"
#include "NodoLista.h"
#include "Tupla.h"
#include "FuncionHash.h"
#include "Comparador.h"


typedef unsigned int nat;

template <class C, class V>
class Tabla abstract : public Iterable<Tupla<C, V>>
{
public:

	virtual ~Tabla() { }

	/* CONSTRUCTORAS */

	//PRE: T(c) no está definida y la tabla no está llena
	//POS: Define T(c) = v
	virtual void Agregar(const C& c, const V& v) abstract;

	//PRE: T(c) está definida
	//POS: Borra la asociación ligada a 'c'
	virtual void Borrar(const C& c) abstract;

	//PRE: - 
	//POS: Borra todas las asociaciones
	virtual void BorrarTodos() abstract;

	/* PREDICADOS */

	//PRE: - 
	//POS: Retorna true si está vacía, false sino.
	virtual bool EstaVacia() const abstract;

	//PRE: - 
	//POS: Retorna true si está llena, false sino.
	virtual bool EstaLlena() const abstract;

	//PRE: - 
	//POS: Retorna true si T(c) está definida, es decir, si la clave c está definida. False sino.
	virtual bool EstaDefinida(const C& c) const abstract;

	/* SELECTORAS */

	//PRE: T(c) está definida
	//POS: Retorna 'v', tal que T(c) = v
	virtual const V& Obtener(const C& c) const abstract;

	//PRE: -
	//POS: Retorna el largo de la tabla
	virtual nat Largo() const abstract;

	//PRE: -
	//POS: Devuelve un clon de la tabla, no comparten memoria
	virtual Puntero<Tabla<C, V>> Clonar() const abstract;
};

#endif