#include "TablaHashc.h"
#ifndef TABLAHASHC_CPP
#define TABLAHASHC_CPP

template  <class C, class V>
TablaHashC<C, V>::TablaHashC(nat cantidadElementos, Puntero<FuncionHash<C>> fHash, const Comparador<C>& comp) {
	hash = Array<Puntero<Tupla<C, V, int>>>(cantidadElementos * 2, NULL);
	this->comp = comp;
	cubetas = cantidadElementos;
	cantElem = 0;
	funcH = fHash;
}

template  <class C, class V>
TablaHashC<C, V>:: ~TablaHashC() {
	for (nat i = 0; i < cubetas; i++)
	{
		hash[i] = NULL;
	}
	cantElem = 0;
}

template  <class C, class V>
void TablaHashC<C, V>::Agregar(const C& c, const V& v) {
	if (EstaLlena())return;
	nat pos = funcH->CodigoDeHash(c) % cubetas;
	if (!hash[pos]) {
		Puntero<Tupla<C, V, int>> ag = new Tupla<C, V, int>(c, v);
		ag->AsignarDato3(1);
		hash[pos] = ag;
		cantElem++;
		return;
	}
	bool dioVuelta = false;
	for (nat i = pos; i < hash.Largo; i++)
	{
		if (hash[pos] && hash[pos]->ObtenerDato3() != 1) {
			if (hash[pos]->ObtenerDato3() == 0) {
				Puntero<Tupla<C, V, int>> ag = new Tupla<C, V, int>(c, v);
				hash[pos] = ag;
				hash[pos]->AsignarDato3(1);
			}
			else {
				hash[pos]->AsignarDato2(v);
				hash[pos]->AsignarDato3(1);
			}
		}

		if (pos == hash.Largo) {
			if (!dioVuelta) {
				pos = -1;
			}
			else return;
		}
		pos++;
	}
	cantElem++;
}

template  <class C, class V>
void TablaHashC<C, V>::Borrar(const C& c) {
	nat pos = funcH->CodigoDeHash(c) % cubetas;
	hash[pos] = nullptr;
	cantElem--;
}

template  <class C, class V>
void TablaHashC<C, V>::BorrarTodos() {
	for (nat i = 0; i < cubetas; i++)
	{
		hash[i] = nullptr;
	}
	cantElem = 0;
}

template  <class C, class V>
bool TablaHashC<C, V>::EstaVacia() const {
	return cantElem == 0;
}

template  <class C, class V>
bool TablaHashC<C, V>::EstaLlena() const {
	return cantElem == cubetas;
}

template  <class C, class V>
bool TablaHashC<C, V>::EstaDefinida(const C& c) const {
	nat pos = funcH->CodigoDeHash(c) % cubetas;
	return hash[pos] != NULL;
}

template  <class C, class V>
const V& TablaHashC<C, V>::Obtener(const C& c) const {
	nat pos = funcH->CodigoDeHash(c) % cubetas;
	return hash[pos]->ObtenerDato2();
}

template  <class C, class V>
nat TablaHashC<C, V>::Largo() const {
	return cantElem;
}

template  <class C, class V>
Iterador<Tupla<C, V>> TablaHashC<C, V>::ObtenerIterador() const {
	Array<Tupla<C, V>> ret = Array<Tupla<C, V>>(cantElem);
	int pos = 0;
	for (nat i = 0; i < cubetas; i++)
	{
		if (hash[i]) {
			Tupla<C, V> ag = Tupla<C, V>(hash[i]->ObtenerDato1(), hash[i]->ObtenerDato2());
			ret[pos] = ag;
			pos++;
		}
	}
	return ret.ObtenerIterador();
}

template  <class C, class V>
Puntero<Tabla<C, V>> TablaHashC<C, V>::Clonar() const {
	Puntero<Tabla<C, V>> ret = new TablaHashC<C, V>(cantElem, funcH, comp);
	for (nat i = 0; i < cubetas; i++)
	{ 
		if (hash[i]) {
			ret->Agregar(hash[i]->ObtenerDato1(), hash[i]->ObtenerDato2());
		}
	}
	return ret;
}
#endif