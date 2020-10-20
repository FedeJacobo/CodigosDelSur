#ifndef SISTEMATEMPLATES_CPP
#define SISTEMATEMPLATES_CPP

#include "Sistema.h"

template <class T, class P>
Puntero<ColaPrioridadExtendida<T, P>> Sistema::CrearColaPrioridadExtendida(const Comparador<T>& compElementos, const Comparador<P>& compPrioridades, Puntero<FuncionHash<T>> fHashElementos) {
	return new ColaPrioridadExtendidaHeap<T, P>(compElementos, compPrioridades, fHashElementos);
}

#endif