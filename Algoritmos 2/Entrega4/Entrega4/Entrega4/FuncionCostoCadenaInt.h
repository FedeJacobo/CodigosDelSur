#pragma once

#include "FuncionCosto.h"
#include "Cadena.h"

class FuncionCostoCadenaInt : public FuncionCosto<Cadena, int>
{
protected:
	virtual nat Evaluar(const Cadena& v1, const Cadena& v2, const int& arco) const override
	{
		return (nat) arco;
	}
};
