#ifndef NODOLISTA_H
#define NODOLISTA_H

#include <iostream>
#include <assert.h>
#include <Puntero.h>

template <class U>
class NodoLista {
public:
	U dato;
	Puntero<NodoLista<U>> ant;
	Puntero<NodoLista<U>> sig;

	NodoLista(const U &e, Puntero<NodoLista<U>>a, Puntero<NodoLista<U>>s) : dato(e), ant(a), sig(s) {}
	virtual ~NodoLista() {}
private:
	NodoLista(const NodoLista<U> &n) : dato(n.dato), ant(n.ant), sig(n.sig) {}

	NodoLista<U> &operator=(const NodoLista<U> &n) { assert(false); return *this; }
};
#endif