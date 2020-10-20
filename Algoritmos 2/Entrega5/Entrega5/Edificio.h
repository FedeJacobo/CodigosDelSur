#pragma once

#include "IEdificio.h"

class Edificio : public IEdificio
{

public:

	Edificio(nat xI, nat xF, nat h);

	nat ObtenerXInicial() const;
	nat ObtenerXFinal() const;
	nat ObtenerAltura() const;

private:
	nat xInicial;
	nat xFinal;
	nat altura;
};