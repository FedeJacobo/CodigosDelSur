#include "PruebasMock.h"

EdificioMock::EdificioMock(nat xI,nat xF, nat h)
{
	xInicial=xI;
	xFinal=xF;
	altura=h;
};

nat EdificioMock::ObtenerXInicial() const
{
	return xInicial;
};

nat EdificioMock::ObtenerXFinal() const
{
	return xFinal;
};

nat EdificioMock::ObtenerAltura() const
{
	return altura;
};

#include "Tira.h"

TiraMock::TiraMock(nat x, nat h)
{
	xInicial=x;
	altura=h;
}

nat TiraMock::ObtenerX() const
{
	return xInicial;
}

nat TiraMock::ObtenerAltura() const
{
	return altura;
}