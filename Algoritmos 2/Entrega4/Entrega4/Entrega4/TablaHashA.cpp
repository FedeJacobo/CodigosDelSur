#include "TablaHashA.h"
#ifndef TABLAHASHA_CPP
#define TABLAHASHA_CPP

template  <class C, class V>
TablaHashA<C, V>::TablaHashA(nat cantidadElementos, Puntero<FuncionHash<C>> funcionH, const Comparador<C>& comp) {
	hash = Array<Puntero<NodoLista<Tupla<C, V>>>>(cantidadElementos * 2, NULL);
	this->comp = comp;
	cubetas = cantidadElementos;
	cantElem = 0;
	tope = cantidadElementos * 2;
	funcH = funcionH;
}

template  <class C, class V>
TablaHashA<C, V>:: ~TablaHashA() {
	for (nat i = 0; i < cubetas; i++)
	{
		hash[i] = NULL;
	}
	cubetas = cantElem = 0;
}

template  <class C, class V>
void TablaHashA<C, V>::Agregar(const C& c, const V& v) {
	if (!EstaLlena()) {
		nat pos = funcH->CodigoDeHash(c) % cubetas;
		Tupla<C, V> tupla = Tupla<C, V>(c, v);
		if (!hash[pos]) {
			Puntero<NodoLista<Tupla<C, V>>> ag = new NodoLista<Tupla<C, V>>(tupla, NULL, NULL);
			hash[pos] = ag;
		}
		else {
			Puntero<NodoLista<Tupla<C, V>>> ag = new NodoLista<Tupla<C, V>>(tupla, NULL, hash[pos]);
			hash[pos]->ant = ag;
			hash[pos] = ag;
		}
		cantElem++;
	}
}

template  <class C, class V>
void TablaHashA<C, V>::Borrar(const C& c) {
	nat pos = funcH->CodigoDeHash(c) % cubetas;
	Puntero<NodoLista<Tupla<C, V>>> aux = hash[pos];
	if (aux && comp.SonIguales(aux->dato.ObtenerDato1(), c)) {
		hash[pos] = hash[pos]->sig;
		cantElem--;
		return;
	}
	while (aux && aux->sig) {
		if (comp.SonIguales(aux->sig->dato.ObtenerDato1(), c)) {
			aux->sig = aux->sig->sig;
			cantElem--;
			return;
			/*if (aux->ant) {
			aux->ant->sig = aux->sig;
			aux->sig->ant = aux->ant;
			cantElem--;
			return;
			}
			else {
			aux = aux->sig;
			cantElem--;
			hash[pos] = aux;
			return;
			}*/
		}
		aux = aux->sig;
	}
	/*if (aux && comp.SonIguales(aux->dato.ObtenerDato1(), c)) {
	aux = aux->ant;
	}*/
}

template  <class C, class V>
void TablaHashA<C, V>::BorrarTodos() {
	for (nat i = 0; i < cubetas; i++)
	{
		hash[i] = nullptr;
	}
	cubetas = cantElem = 0;
}

template  <class C, class V>
bool TablaHashA<C, V>::EstaVacia() const {
	return cantElem == 0;
}

template  <class C, class V>
bool TablaHashA<C, V>::EstaLlena() const {
	return cantElem == tope;
}

template  <class C, class V>
bool TablaHashA<C, V>::EstaDefinida(const C& c) const {
	nat pos = funcH->CodigoDeHash(c) % cubetas;
	Puntero<NodoLista<Tupla<C, V>>> aux = hash[pos];
	while (aux) {
		if (comp.SonIguales(aux->dato.ObtenerDato1(), c)) return true;
		aux = aux->sig;
	}
	return false;
}

template  <class C, class V>
const V& TablaHashA<C, V>::Obtener(const C& c) const {
	nat pos = funcH->CodigoDeHash(c) % cubetas;
	Puntero<NodoLista<Tupla<C, V>>> aux = hash[pos];
	while (aux) {
		if (comp.SonIguales(aux->dato.ObtenerDato1(), c)) return aux->dato.ObtenerDato2();
		aux = aux->sig;
	}
	return hash[pos]->dato.ObtenerDato2();
}

template  <class C, class V>
nat TablaHashA<C, V>::Largo() const {
	return cantElem;
}

template  <class C, class V>
Iterador<Tupla<C, V>> TablaHashA<C, V>::ObtenerIterador() const {
	Array<Tupla<C, V>> ret = Array<Tupla<C, V>>(cantElem);
	int pos = 0;
	for (nat i = 0; i < hash.Largo; i++)
	{
		if (hash[i] != NULL) {
			Puntero<NodoLista<Tupla<C, V>>> aux = hash[i];
			while (aux) {
				ret[pos] = aux->dato;
				aux = aux->sig;
				pos++;
			}
		}
	}
	return ret.ObtenerIterador();
}

template  <class C, class V>
Puntero<Tabla<C, V>> TablaHashA<C, V>::Clonar() const {
	Puntero<Tabla<C, V>> ret = new TablaHashA<C, V>(cantElem, funcH, comp);
	for (nat i = 0; i < cubetas; i++)
	{
		Puntero<NodoLista<Tupla<C, V>>> aux = hash[i];
		while (aux) {
			ret->Agregar(aux->dato.ObtenerDato1(), aux->dato.ObtenerDato2());
			aux = aux->sig;
		}
	}
	return ret;
}
#endif