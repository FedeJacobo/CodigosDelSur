#ifndef SOLUCION_CPP
#define SOLUCION_CPP

#include "Sistema.h"

Sistema::Sistema()
{
	prioriA = PrioridadA();
}

void Sistema::EstablecerTableroInicial(Tablero inicial)
{
	tablero = inicial;
	tableroAnt = Tablero();
	Matriz<int> solucionado = Matriz<int>(tablero.ObtenerTablero().Largo);
	int cont = 1;
	for (nat i = 0; i < solucionado.Largo; i++)
	{
		for (nat j = 0; j < solucionado.Largo; j++)
		{
			solucionado[i][j] = cont++;
		}
	}
	solucionado[tablero.ObtenerTablero().Largo - 1][tablero.ObtenerTablero().Largo - 1] = 0;
	estadoFinal = Tablero(solucionado, 0);
}

bool Sistema::TieneSolucion()
{
	Matriz<int> t = tablero.ObtenerTablero();
	int cont = 0;
	Array <int> arr = Array<int>(t.Largo * t.Ancho - 1);
	int pos = 0;
	for (nat i = 0; i < t.Largo; i++)
	{
		for (nat j = 0; j < t.Largo; j++)
		{
			if (t[i][j] != 0) {
				arr[pos] = t[i][j];
				pos++;
			}
		}
	}
	for (nat i = 0; i < arr.Largo; i++)
	{
		for (nat j = i + 1; j < arr.Largo; j++)
		{
			if (arr[i] < arr[j]) cont++;
		}
	}
	return cont % 2 == 0;
}
	
int Sistema::Movimientos()
{
	Tablero original = tablero;
	if (!TieneSolucion()) return -1;
	Iterador<Tablero> aux = Solucionar();
	int ret = 0;
	while (aux.HayElemento())
	{
		ret++;
		aux.Avanzar();
	}
	tablero = original;
	tableroAnt = Tablero();
	return ret;
}

Iterador<Tablero> Sistema::Solucionar()
{ 
	Array<Tablero> ret = Array<Tablero>(100);
	if (!TieneSolucion()) return ret.ObtenerIterador();
	Comparador<Tablero> compT = new CompTablero();
	Comparador<int> compI = new CompIntPrioridad();
	Puntero<ColaPrioridadExtendida<Tablero, int>> cola = new ColaPrioridadExtendidaHeap<Tablero, int>(compT, compI, Puntero<FHashTablero>());
	cola->InsertarConPrioridad(tablero, prioriA.CalcularPrioridad(tablero));
	nat cont = 0;
	while (!cola->EstaVacia() && !(cola->ObtenerElementoMayorPrioridad() == estadoFinal)) {
		Tablero aux = tablero;
		tablero = cola->EliminarElementoMayorPrioridad();
		if (TieneSolucion() && cont < ret.Largo) {
			ret[cont] = tablero;
			Iterador<Tablero> vecinos = tablero.Vecinos();
			while (vecinos.HayElemento())
			{
				if (!(vecinos.ElementoActual() == tableroAnt)) {
					cola->InsertarConPrioridad(vecinos.ElementoActual(), prioriA.CalcularPrioridad(vecinos.ElementoActual()));
				}
				vecinos.Avanzar();
			}
			tableroAnt = aux;
			cont++;
		}
	}
	if(cont < ret.Largo)
	ret[cont] = estadoFinal;
	else ret[cont - 1] = estadoFinal;
	Array<Tablero> retorno = Array<Tablero>(cont);
	for (nat i = 0; i < cont; i++)
	{
		retorno[i] = ret[i];
	}
	return retorno.ObtenerIterador();
}


#endif