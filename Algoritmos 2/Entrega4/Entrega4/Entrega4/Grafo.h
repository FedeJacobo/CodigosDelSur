#ifndef GRAFO_H
#define GRAFO_H

#include "Iterable.h"
#include "FuncionHash.h"
#include "FuncionCosto.h"
#include "Tupla.h"
#include "Array.h"
#include "Matriz.h"
#include "Tabla.h"
#include "TablaHashA.h"
#include "IntFuncionHash.h"
#include "Comparador.h"
#include "Nodo.h"

enum TipoConexo 
{
	NO_CONEXO, DEBILMENTE_CONEXO, FUERTEMENTE_CONEXO
};

typedef unsigned int nat;

template <class V, class A>
class Grafo abstract 
{
public:
	virtual ~Grafo() {}
	
	// CONSTRUCTORAS
	
	// PRE: No existe el vertice v en el grafo 
	// POS: Agrega el vertice v al grafo
	virtual void AgregarVertice(const V& v) abstract;

	// PRE: Existe el vertice v en el grafo
	// POS: El vertice v no pertenece al grafo. Las aristas incidentes y adyacentes a v tampoco pertenecen al grafo.
	virtual void BorrarVertice(const V& v) abstract;

	// PRE: No existe un arco entre v1 y v2 en el grafo
	// POS: Agrega el arco 'arco' entre los vertices v1 y v2 al grafo
	virtual void AgregarArco(const V& v1, const V& v2, const A& arco) abstract;

	// PRE: Existe el arco entre v1 y v2 en el grafo
	// POS: El arco 'arco' entre los vertices v1 y v2 no pertenece al grafo
	virtual void BorrarArco(const V& v1, const V& v2) abstract;

	// SELECTORAS y PREDICADOS

	// PRE: -
	// POS: Retorna un iterador de vertices del grafo
	virtual Iterador<V> Vertices() const abstract;

	// PRE: -
	// POS: Dado un vertice v devuelve un iterador con los vertices adyacentes a v
	virtual Iterador<V> Adyacentes(const V& v) const abstract;

	// PRE: -
	// POS: Dado un vertice v devuelve un iterador con los vertices incidentes 
	//		(vertices de los cuales v es adyacente)
	virtual Iterador<V> Incidentes(const V& v) const abstract;

	// PRE: Existe un arco entre los vertices v1 y v2
	// POS: Retorna el arco entre v1 y v2
	virtual const A& ObtenerArco(const V& v1, const V& v2) const abstract;

	// PRE: -
	// POS: Retorna la cantidad de vertices del grafo
	virtual nat CantidadVertices() const abstract;

	// PRE: -
	// POS: Retorna la cantidad de arcos del grafo
	virtual nat CantidadArcos() const abstract;

	// PRE: El vertice v pertenece al grafo
	// POS: Retorna la cantidad de vertices adyacentes a v
	virtual nat CantidadAdyacentes(const V& v) const abstract;

	// PRE: El vertice v pertenece al grafo
	// POS: Retorna la cantidad de vertices incidentes a v
	virtual nat CantidadIncidentes(const V& v) const abstract;
	
	// PRE: -
	// POS: Retorna true sii el vertice v pertenece al grafo
	virtual bool ExisteVertice(const V& v) const abstract;

	// PRE: -
	// POS: Retorna true sii existe un arco entre los vertices v1 y v2
	virtual bool ExisteArco(const V& v1, const V& v2) const abstract;

	// PRE: -
	// POS: Retorna true sii el grafo esta lleno
	virtual bool EstaLleno() const abstract;

	// PRE: -
	// POS: Retorna true sii el grafo esta vacio
	virtual bool EstaVacio() const abstract;

	// PRE: -
	// POS: Retorna true sii existe un camino desde el vertice vD hacia el vertice vO
	virtual bool HayCamino(const V& vO, const V& vD) const abstract;

	// PRE: -
	// POS: Retorna true sii el grafo es conexo
	virtual	TipoConexo EsConexo() const abstract;

	// PRE: -
	// POS: Retorna un iterador de vertices ordenados de acuerdo al orden topologico del grafo
	virtual	Iterador<V> OrdenTopologico() const abstract;

	// PRE: -
	// POS: Retorna un iterador de Tupla<V,V> representando las aristas 
	//		pertenecientes al árbol de cubrimiento minimo de acuerdo a 
	//		la funcion de costo 'costo'
	virtual Iterador<Tupla<V, V>> ArbolCubrimientoMinimo(const FuncionCosto<V, A>& costo = FuncionCosto<V, A>::Default) const abstract;
	
	// PRE: -
	// POS: Retorna un Iterador con las componentes conexas	del grafo subyacente (no dirigido).
	//		Una componente conexa se representará como un Iterador de los vértices que
	//		pertenecen a dicha componente.
	virtual Iterador<Iterador<V>> ComponentesConexas() const abstract;
};

#endif