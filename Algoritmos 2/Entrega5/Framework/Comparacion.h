#pragma once

enum CompRetorno
{
	IGUALES,
	MENOR,
	MAYOR,
	DISTINTOS
};

template <class T>
class Comparacion abstract
{
public:
	virtual ~Comparacion() {}
	virtual CompRetorno Comparar(const T& t1, const T& t2) const abstract;
};