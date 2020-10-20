#pragma once
#ifndef FHASHTABLERO_H
#define FHASHTABLERO_H
#include "FuncionHash.h"
#include "Tablero.h"
#include "Puntero.h"
//CREE ESTA CLASE PARA QUE NO SE CAIGA, NO USO LA FHASH AÚN, ES PARA IMPLEMENTAR LA COLAHEAP CON LA TABLA DE HASH PERO NO ARRANQUE CON ESO Y NO SE CAMBIA ESTO
class FHashTablero : public FuncionHash<Tablero>
{
public:
	nat CodigoDeHash(const Tablero& t) const {
		return -1;
	}
};
#endif 