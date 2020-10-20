#include "Tira.h"

Tira::Tira(nat x, nat h)
{
	xInicial=x;
	altura=h;
}

nat Tira::ObtenerX() const
{
	return xInicial;
}

nat Tira::ObtenerAltura() const
{
	return altura;
}