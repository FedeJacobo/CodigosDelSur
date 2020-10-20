#ifndef SISTEMATEMPLATES_CPP
#define SISTEMATEMPLATES_CPP

#include "Sistema.h"

template <class V, class A>
Tupla<TipoRetorno, Puntero<Grafo<V, A>>> Sistema::CrearGrafo(nat maxVertices, Puntero<FuncionHash<V>> funcionHash, const Comparador<V>& comp)
{
	Puntero<Grafo<V, A>> ret = new GrafoImp<V, A>(maxVertices, funcionHash, comp);
	return Tupla<TipoRetorno, Puntero<Grafo<V, A>>>(OK, ret);
}


#endif