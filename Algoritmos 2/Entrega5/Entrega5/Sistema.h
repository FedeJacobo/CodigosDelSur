#ifndef SISTEMA_H
#define SISTEMA_H

#include "ISistema.h"
#include "Tira.h"

class Sistema : public ISistema
{
public:
	Sistema();
	//EJ 1
	void TransponerMatriz(Matriz<nat> matriz);
	//pre: -
	//pos: transpone la matriz
	void TransponerMatrizAux(Matriz<nat> &matriz, nat desdex, nat desdey, nat n);
	//pre: -
	//pos: intercambia los sectores de la matriz acotados por las variables recibidas
	void Swap(nat x1, nat y1, nat x2, nat y2, nat largo, Matriz<nat>&mat);
	//pre: -
	//pos: muestra la matriz en la consola
	void imprimir(Matriz<nat> matriz);
	//EJ 2
	Array<Puntero<ITira>> CalcularSiluetaDeLaCiudad(Array<Puntero<IEdificio>> ciudad);
	//pre: -
	//pos: realiza el calculo de la silueta de la ciudad
	Array<Puntero<ITira>> CalcularSiluetaDeLaCiudadAux(Array<Tupla<Puntero<ITira>, Puntero<ITira>>> ciudad, nat izq, nat der);
	//pre: -
	//pos: devuelve la silueta intercalando sus divisiones (siluetaIzq y siluetaDer)
	Array<Puntero<ITira>> Intercalar(Array<Puntero<ITira>> siluetaIzq, Array<Puntero<ITira>> siluetaDer);
	//pre: -
	//pos: agrega una tira con los datos pasados por parametros a ret
	void Agregar(Array<Puntero<ITira>>& ret, nat x, nat h, nat & hAnt, nat &cant);
	//pre: -
	//pos:
	Array<Puntero<ITira>> Filtrar(Array<Puntero<ITira>> a, nat cant);
	//EJ 3
	nat CalcularCoeficienteBinomial(nat n, nat k);
	};

#endif
