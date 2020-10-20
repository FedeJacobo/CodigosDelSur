#pragma once

#include "ICiudad.h"

class CiudadMock : public ICiudad
{
	
public:

	CiudadMock(Cadena nombreCiudad, nat numeroCiudad);

	Cadena ObtenerNombre() const;
	nat ObtenerNumero() const;

private:

	Cadena nombre;
	nat numero;

};
