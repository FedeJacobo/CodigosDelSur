#ifndef IEDIFICIO_H
#define IEDIFICIO_H

typedef unsigned int nat;

class IEdificio abstract
{
public:
	virtual ~IEdificio(){}

	//PRE: -
	//POS: Devuelve la coordenada en X inicial del Edificio
	virtual nat ObtenerXInicial() const abstract;

	//PRE: -
	//POS: Devuelve la coordenada en X final del Edificio
	virtual nat ObtenerXFinal() const abstract;

	//PRE: -
	//POS: Devuelve la altura del Edificio
	virtual nat ObtenerAltura() const abstract;
};

#endif