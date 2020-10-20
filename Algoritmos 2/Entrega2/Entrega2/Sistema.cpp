#ifndef SISTEMA_CPP
#define SISTEMA_CPP

#include "Sistema.h"

Sistema::Sistema(const Cadena& nombreArchivoDiccionario)
{	
	this->nombreDicc = nombreArchivoDiccionario + ".txt";
	if (!tabla) {
		tabla = new TablaHashA <Cadena, Cadena>(10000, new CadenaFuncionHash(), Comparador <Cadena>());
		CargarDiccionario();
	}
}
Sistema::~Sistema()
{
	
}

// Ejercicio 1: Anagramas
Array<Cadena> Sistema::Anagramas(const Cadena & c) {
	Cadena cad = c;
	inicializarCadena(cad);
	Array<Cadena> ret = Array<Cadena>(100);
	nat cont = 0;
	Puntero<Tabla<Cadena, Cadena>> clon = tabla->Clonar();
	Cadena clave = ordenarCadena(cad);
	while (clon->EstaDefinida(clave)) {
		ret[cont] = clon->Obtener(clave);
		clon->Borrar(clave);
		cont++;
	}
	Array<Cadena> retorno = Array<Cadena>(cont);
	for (nat i = 0; i < cont; i++)
	{
		retorno[i] = ret[i];
	}
	clon = NULL;
	return retorno;
}

void Sistema::CargarDiccionario() {
	char* rutaDiccionario = cadenaToChar(nombreDicc);
	ifstream entrada;
	//entrada.open(rutaDiccionario);
	entrada.open("../../diccionario.txt");
	if (!entrada) {
		cout << "no se abrio el archivo";
	}
	Cadena cadenaLinea;
	while (!entrada.eof()) {
		entrada >> cadenaLinea;
		if (cadenaLinea != "") {
			Cadena clave = ordenarCadena(cadenaLinea);
			tabla->Agregar(clave, cadenaLinea);
		}
	}
	entrada.close();
	delete rutaDiccionario;
}

char* Sistema::cadenaToChar(Cadena cadena) const {
	char* cadenaChar = new char[cadena.Largo + 1];
	for (unsigned int i = 0; i < cadena.Largo; i++) {
		cadenaChar[i] = cadena[i];
	}
	cadenaChar[cadena.Largo] = '\0';
	return cadenaChar;
}

Cadena Sistema::ordenarCadena(const Cadena& c) {
	Cadena ret = "";
	Array<Cadena> ordenar = Array<Cadena>(c.Largo);
	for (unsigned int i = 0; i < c.Largo; i++) {
		ordenar[i] = c.SubCadena(i, 1);
	}
	Ordenar(ordenar, Comparador<Cadena>());
	for (unsigned int i = 0; i < c.Largo; i++) {
		ret += ordenar[i];
	}
	return ret;
}

void Sistema::Ordenar(Array<Cadena>& elementos, const Comparador<Cadena>& comp)
{
	if (elementos.Largo == 0) return;
	for (nat i = 0; i<(elementos.Largo - 1); i++) {
		for (nat j = i + 1; j<elementos.Largo; j++) {
			if (comp.EsMayor(elementos[i], elementos[j])) {
				Cadena aux = elementos[i];
				elementos[i] = elementos[j];
				elementos[j] = aux;
			}
		}
	}
}

void Sistema::inicializarCadena(Cadena &cadena) {
	string aux = "";
	for (nat i = 0; i < cadena.Largo; i++)
	{
		if (cadena[i] >= 65 && cadena[i] <= 90) {
			aux += cadena[i] + 32;
		}
		else {
			aux += cadena[i];
		}
	}
	Cadena ret = Cadena(aux.c_str());
	cadena = ret;
}
#endif