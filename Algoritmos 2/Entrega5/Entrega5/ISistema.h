#ifndef ISISTEMA_H
#define ISISTEMA_H

#include "Cadena.h"
#include "Iterador.h"
#include "Puntero.h"
#include "TipoRetorno.h"
#include "Tupla.h"
#include "Matriz.h"
#include "IEdificio.h"
#include "ITira.h"

class ISistema abstract
{
public:
	virtual ~ISistema(){}

	//PRE: la matriz es de dimensiones n x n, donde n es una potencia de 2
	//POS: se calcula la traspuesta de la matriz
	virtual void TransponerMatriz(Matriz<nat> matriz) abstract;

	//PRE: -
	//POS: se calcula la silueta del conjunto de edificios
	virtual Array<Puntero<ITira>> CalcularSiluetaDeLaCiudad(Array<Puntero<IEdificio>> ciudad) abstract;

	//PRE: -
	//POS: se calculan las formas posibles de tomar k elementos de n
	virtual nat CalcularCoeficienteBinomial(nat n, nat k) abstract;
};

#endif
