#pragma once

#include "Iteracion.h"
#include "Puntero.h"

template <class T>
class ConcatIteracion : public Iteracion<T>
{
public:
	ConcatIteracion(Puntero<Iteracion<T>> parte1, Puntero<Iteracion<T>> parte2);

	void Reiniciar() override;
	bool HayElemento() const override;
	const T& ElementoActual() const override;
	void Avanzar() override;

	Puntero<Iteracion<T>> Clonar() const override;

private:
	Puntero<Iteracion<T>> m_Parte1;
	Puntero<Iteracion<T>> m_Parte2;
	bool m_PrimeraParte;
};

#include "ConcatIteracion.cpp"