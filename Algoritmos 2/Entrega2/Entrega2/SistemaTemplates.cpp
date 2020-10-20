#ifndef SISTEMATEMPLATES_CPP
#define SISTEMATEMPLATES_CPP

#include "Sistema.h"

template <class C, class V>
Puntero<Tabla<C, V>> Sistema::CrearTablaHashAbierto(nat cantidadElementos, Puntero<FuncionHash<C>> funcH, const Comparador<C>& comp)
{
	return new TablaHashA<C, V>(cantidadElementos, funcH, comp);
}

template <class C, class V>
Puntero<Tabla<C, V>> Sistema::CrearTablaHashCerrado(nat cantidadElementos, Puntero<FuncionHash<C>> funcH, const Comparador<C>& comp)
{
	return new TablaHashC<C, V>(cantidadElementos, funcH, comp);;
}

template <class T>
bool Sistema::EsAVL(Puntero<NodoArbol<T>> raiz, const Comparador<T>& comp)
{
	return estaOrdenado(raiz, comp) && estaBalanceado(raiz, comp);
}

template <class T>
bool Sistema::estaBalanceado(Puntero<NodoArbol<T>> raiz, const Comparador<T>& comp) {
	if (!raiz) return true;
	int aI = altura(raiz->izq, comp);
	int aD = altura(raiz->der, comp);
	int dif = (comp.EsMayor(aD, aI) || comp.SonIguales(aD, aI)) ? aD - aI : aI - aD;
	return dif <= 1 && estaBalanceado(raiz->izq, comp) && estaBalanceado(raiz->der, comp);
}

template <class T>
int Sistema::altura(Puntero<NodoArbol<T>> raiz, const Comparador<T>& comp) {
	if (!raiz) return 0;
	int aI = altura(raiz->izq, comp);
	int aD = altura(raiz->der, comp);
	int max = (comp.EsMayor(aI, aD) || comp.SonIguales(aI, aD)) ? aI : aD;
	return 1 + max;
}

template <class T>
bool Sistema::estaOrdenado(Puntero<NodoArbol<T>> raiz, const Comparador<T>& comp) {
	if (!raiz)return true;
	Puntero<NodoLista<T>> lista = nullptr;
	arbolALista(raiz, lista);
	while (lista && lista->sig) {
		if (comp.EsMayor(lista->dato, lista->sig->dato))return false;
		lista = lista->sig;
	}
	return true;
}

template <class T>
void Sistema::arbolALista(Puntero<NodoArbol<T>> raiz, Puntero<NodoLista<T>>& arbol) {
	if (!raiz)return;
	arbolALista(raiz->izq, arbol);
	agregarFin(raiz->dato, arbol);
	arbolALista(raiz->der, arbol);
}

template <class T>
void Sistema::agregarFin(T& t, Puntero<NodoLista<T>> &lista) {
	if (!lista) {
		lista = new NodoLista<T>(t, NULL, NULL);
		return;
	}
	agregarFin(t, lista->sig);
}
#endif