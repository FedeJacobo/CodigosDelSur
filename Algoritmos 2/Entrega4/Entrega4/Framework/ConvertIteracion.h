#pragma once

#include "Iteracion.h"
#include "Puntero.h"

template <class T, class U, typename Conv>
class ConvertIteracion : public Iteracion<U>
{
public:
	ConvertIteracion(Puntero<Iteracion<T>> toConvert);

	void Reiniciar() override;
	bool HayElemento() const override;
	const U& ElementoActual() const override;
	void Avanzar() override;

	Puntero<Iteracion<U>> Clonar() const override;

private:
	Puntero<Iteracion<T>> m_ToConvert;
	mutable U m_Actual;
};

#include "ConvertIteracion.cpp"
