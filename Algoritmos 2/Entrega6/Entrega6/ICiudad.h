#ifndef ICIUDAD_H
#define ICIUDAD_H

#include "Cadena.h"

typedef unsigned int nat;

class ICiudad abstract
{
public:
	virtual ~ICiudad(){}

	//PRE: -
	//POS: Devuelve la el nombre de la Ciudad
	virtual Cadena ObtenerNombre() const abstract;

	//PRE: -
	//POS: Devuelve el número interno de esa ciudad en el mapa
	virtual nat ObtenerNumero() const abstract;
};

#endif