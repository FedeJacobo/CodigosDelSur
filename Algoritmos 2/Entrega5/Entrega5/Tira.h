#pragma once

#include "ITira.h"

class Tira : public ITira
{
public:

	Tira(nat xInicial, nat altura);

	nat ObtenerAltura() const;
	nat ObtenerX() const;

private:

	nat xInicial;
	nat altura;
};