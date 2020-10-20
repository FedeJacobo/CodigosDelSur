#ifndef PRIORIDAD_A_CPP
#define PRIORIDAD_A_CPP

#include "PrioridadA.h"


nat PrioridadA::CalcularPrioridad(const Tablero& t) const 
{
	Matriz<int> solucionado = Matriz<int>(t.ObtenerTablero().Largo);
	int cont = 1;
	for (nat i = 0; i < solucionado.Largo; i++)
	{
		for (nat j = 0; j < solucionado.Largo; j++)
		{
			solucionado[i][j] = cont++;
		}
	}
	solucionado[t.ObtenerTablero().Largo - 1][t.ObtenerTablero().Largo - 1] = 0;
	int ret = 0;
	Matriz<int> tablero = t.ObtenerTablero();
	for (nat i = 0; i < solucionado.Largo; i++)
	{
		for (nat j = 0; j < solucionado.Largo; j++)
		{
			if (solucionado[i][j] != tablero[i][j]) ret++;
		}
	}
	return ret + t.CantidadDeMovimientos();
}



#endif