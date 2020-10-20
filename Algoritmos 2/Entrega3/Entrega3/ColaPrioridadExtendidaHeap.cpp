#pragma once

#ifndef COLAPRIORIDADEXTENDIDAHEAP_CPP
#define COLAPRIORIDADEXTENDIDAHEAP_CPP
#include "ColaPrioridadExtendidaHeap.h"

template <class T, class P>
ColaPrioridadExtendidaHeap<T, P>::ColaPrioridadExtendidaHeap(const Comparador<T>& compElementos, const Comparador<P>& compPrioridades, Puntero<FuncionHash<T>> fHashElementos) {
	cola = Array<Puntero<Tupla<T, P>>>(100);
	cantElem = 0;
	fHash = fHashElementos;
	compE = compElementos;
	compP = compPrioridades;
}

template <class T, class P>
void ColaPrioridadExtendidaHeap<T, P>::InsertarConPrioridad(const T& e, const P& p) {
	if (EstaLlena()) AgrandarArray();
	Puntero<Tupla<T, P>> ag = new Tupla<T, P>(e, p);
	cola[cantElem + 1] = ag;
	cantElem++;
	Flotar(cantElem);
}

template <class T, class P>
T ColaPrioridadExtendidaHeap<T, P>::EliminarElementoMayorPrioridad() {
	T aux = cola[1]->ObtenerDato1();
	cola[1] = cola[cantElem];
	cola[cantElem] = nullptr;
	cantElem--;
	Hundir(1);
	return aux;
}

template <class T, class P>
const T& ColaPrioridadExtendidaHeap<T, P>::ObtenerElementoMayorPrioridad() const {
	return cola[1]->ObtenerDato1();
}

template <class T, class P>
Tupla<T, P> ColaPrioridadExtendidaHeap<T, P>::ObtenerElementoYPrioridad(const  T& e) {
	for (nat i = 1; i <= cantElem; i++)
	{
		if (compE.SonIguales(e, cola[i]->ObtenerDato1())) {
			return Tupla<T, P>(cola[i]->ObtenerDato1(), cola[i]->ObtenerDato2());
		}
	}
	return Tupla<T, P>();
}

template <class T, class P>
nat ColaPrioridadExtendidaHeap<T, P>::Largo() const {
	return cantElem;
}

template <class T, class P>
bool ColaPrioridadExtendidaHeap<T, P>::Pertenece(const T& e) const {
	for (nat i = 1; i <= cantElem; i++)
	{
		if (compE.SonIguales(e, cola[i]->ObtenerDato1())) return true;
	}
	return false;
}

template <class T, class P>
void ColaPrioridadExtendidaHeap<T, P>::CambiarPrioridad(const T& e, const P& p) {
	for (nat i = 1; i <= cantElem; i++)
	{
		if (compE.SonIguales(e, cola[i]->ObtenerDato1())) {
			if (compP.EsMayor(p, cola[i]->ObtenerDato2())) {
				cola[i]->AsignarDato2(p);
				Flotar(i);
			}
			else {
				cola[i]->AsignarDato2(p);
				Hundir(i);
			}
		}
	}
}

template <class T, class P>
void ColaPrioridadExtendidaHeap<T, P>::EliminarElemento(T& e) {
	for (nat i = 1; i <= cantElem; i++) {
		if (compE.SonIguales(e, cola[i]->ObtenerDato1())) {
			cola[i] = cola[cantElem];
			cola[cantElem] = nullptr;
			cantElem--;
			Flotar(i);
			Hundir(i);
		}
	}
}

template <class T, class P>
bool ColaPrioridadExtendidaHeap<T, P>::EstaVacia() const {
	return cantElem == 0;
}

template <class T, class P>
bool ColaPrioridadExtendidaHeap<T, P>::EstaLlena() const {
	return cantElem + 1== cola.Largo;
}

template <class T, class P>
void ColaPrioridadExtendidaHeap<T, P>::Vaciar() {
	for (nat i = 1; i <= cantElem; i++)
	{
		cola[i] = nullptr;
	}
	cantElem = 0;
}

template <class T, class P>
Iterador<Tupla<T, P>> ColaPrioridadExtendidaHeap<T, P>::ObtenerIterador() const{
	Array<Tupla<T, P>> ret = Array<Tupla<T, P>>(cantElem);
	for (nat i = 0; i < cantElem; i++)
	{
		ret[i] = Tupla<T, P>(cola[i + 1]->ObtenerDato1(), cola[i + 1]->ObtenerDato2());
	}
	return ret.ObtenerIterador();
}

template <class T, class P>
Puntero<ColaPrioridadExtendida<T, P>> ColaPrioridadExtendidaHeap<T, P>::Clon() const {
	Puntero<ColaPrioridadExtendida<T, P>> ret = new ColaPrioridadExtendidaHeap<T, P>(compE, compP, fHash);
	for (nat i = 0; i < cantElem; i++)
	{
		ret->InsertarConPrioridad(cola[i]->ObtenerDato1(), cola[i]->ObtenerDato2());
	}
	return ret;
}

template <class T, class P>
void ColaPrioridadExtendidaHeap<T, P>::Flotar(nat pos) {
	while (cola [pos] && cola[pos/2] && pos != 1 && compP.EsMenor(cola[pos / 2]->ObtenerDato2(), cola[pos]->ObtenerDato2())) {
		nat padre = pos / 2;
		Puntero<Tupla<T, P>> aux = new Tupla<T, P> (cola[padre]->ObtenerDato1(), cola[padre]->ObtenerDato2());
		cola[padre] = cola[pos];
		cola[pos] = aux;
		pos = padre;
	}
}

template <class T, class P>
void ColaPrioridadExtendidaHeap<T, P>::Hundir(nat pos) {
	nat  hijoI = (2 * pos) + 1;
	nat hijoD = hijoI + 1;
	nat hijoAComp = hijoI;
	if (hijoI < cantElem) {
		if (cola[hijoD] && cola[hijoI] && hijoD < cantElem && compP.EsMayor(cola[hijoD]->ObtenerDato2(), cola[hijoI]->ObtenerDato2())) {
			hijoAComp = hijoD;
		}
		if (cola[hijoD] && cola[hijoI] && !compP.EsMayor(cola[hijoD]->ObtenerDato2(), cola[hijoAComp]->ObtenerDato2())) {
			Puntero<Tupla<T, P>> aux = new Tupla<T, P>(cola[pos]->ObtenerDato1(), cola[pos]->ObtenerDato2());
			cola[pos] = cola[hijoAComp];
			cola[hijoAComp] = aux;
			Hundir(hijoAComp);
		}
	}
}

template <class T, class P>
void ColaPrioridadExtendidaHeap<T, P>::AgrandarArray() {
	Array<Puntero<Tupla<T, P>>> nuevo = Array<Puntero<Tupla<T, P>>>(cola.Largo * 2);
	for (nat i = 0; i < cola.Largo; i++)
	{
		nuevo [i]= cola[i];
	}
	cola = nuevo;
}


#endif