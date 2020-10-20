#include "Edificio.h"

Edificio::Edificio(nat xI,nat xF, nat h)
{
	xInicial=xI;
	xFinal=xF;
	altura=h;
}

nat Edificio::ObtenerXInicial() const
{
	return xInicial;
}

nat Edificio::ObtenerXFinal() const
{
	return xFinal;
}

nat Edificio::ObtenerAltura() const
{
	return altura;
}