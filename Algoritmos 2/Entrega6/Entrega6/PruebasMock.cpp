#include "PruebasMock.h"

CiudadMock::CiudadMock(Cadena nombreCiudad, nat numeroCiudad)
{
	nombre = nombreCiudad;
	numero = numeroCiudad;
};

Cadena CiudadMock::ObtenerNombre() const
{
	return nombre;
};

nat CiudadMock::ObtenerNumero() const
{
	return numero;
};
