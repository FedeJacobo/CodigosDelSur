#ifndef SISTEMA_H
#define SISTEMA_H

#include "Cadena.h"
#include "Puntero.h"
#include "Tupla.h"
#include "NodoArbol.h"
#include "NodoLista.h"
#include "Array.h"
#include "Tabla.h"
#include "FuncionHash.h"
#include "TablaHashA.h"
#include "TablaHashC.h"
#include "CadenaFuncionHash.h"


#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Sistema
{
private:
	Cadena nombreDicc;
	Puntero<Tabla<Cadena, Cadena>> tabla = NULL;

	//PRE: -
	//POS: carga los datos del diccionario en la tabla
	void CargarDiccionario();

	//PRE: -
	//POS: transforma una cadena en un char
	char* cadenaToChar(Cadena cadena) const;

	//PRE: -
	//POS: ordena la cadena de acuerdo al codigo ascii
	Cadena ordenarCadena(const Cadena& c);

	//PRE: -
	//POS: ordena un array utilizando el metodo swap
	void Ordenar(Array<Cadena>& elementos, const Comparador<Cadena>& comp);

	//PRE: -
	//POS: normaliza la cadena eliminando mayusculas y tildes
	void inicializarCadena(Cadena &cadena);
public:
	Sistema(const Cadena& nombreArchivoDiccionario);
	~Sistema();

	// Ejercicio 1: Anagramas, TablaHash abierta y cerrada
	Array<Cadena> Anagramas(const Cadena& c);
	
	template <class C, class V>
	Puntero<Tabla<C, V>> CrearTablaHashAbierto(nat cantidadElementos, Puntero<FuncionHash<C>> funcH, const Comparador<C>& comp);
	
	template <class C, class V>
	Puntero<Tabla<C, V>> CrearTablaHashCerrado(nat cantidadElementos, Puntero<FuncionHash<C>> funcH, const Comparador<C>& comp);

	// Ejercicio 2: AVL
	template <class T>
	bool EsAVL(Puntero<NodoArbol<T>> raiz, const Comparador<T>& comp);

private:
	//Atributos necesarios para cumplir con las operaciones.

};


#include "SistemaTemplates.cpp"

#endif
