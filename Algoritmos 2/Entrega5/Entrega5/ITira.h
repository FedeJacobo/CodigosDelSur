#ifndef ITIRA_H
#define ITIRA_H

typedef unsigned int nat;

class ITira abstract
{
public:
	virtual ~ITira(){}

	//PRE: -
	//POS: Devuelve la coordenada en X inicial de la tira
	virtual nat ObtenerX() const abstract;

	//PRE: -
	//POS: Devuelve la altura de la tira
	virtual nat ObtenerAltura() const abstract;
};



#endif