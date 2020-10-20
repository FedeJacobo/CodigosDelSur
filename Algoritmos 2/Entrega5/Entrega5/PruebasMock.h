#pragma once

#include "IEdificio.h"
#include "ITira.h"

class EdificioMock : public IEdificio
{
	
public:

	EdificioMock(nat xI, nat xF, nat h);

	nat ObtenerXInicial() const;
	nat ObtenerXFinal() const;
	nat ObtenerAltura() const;

private:

	nat xInicial;
	nat xFinal;
	nat altura;

};

class TiraMock : public ITira
{
public:

	TiraMock(nat xInicial, nat altura);

	nat ObtenerAltura() const;
	nat ObtenerX() const;

private:

	nat xInicial;
	nat altura;
};