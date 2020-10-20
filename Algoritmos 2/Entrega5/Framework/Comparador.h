#pragma once

#include "Comparacion.h"
#include "Puntero.h"

template <class T>
class Comparador sealed
{
public:
	Comparador(Comparacion<T>* comp = nullptr);
	Comparador(const Puntero<Comparacion<T>>& comp);
	Comparador(const Comparador<T>& comp);

	~Comparador();

	const Comparador<T>& operator=(Comparacion<T>* comp);
	const Comparador<T>& operator=(const Puntero<Comparacion<T>>& comp);
	const Comparador<T>& operator=(const Comparador<T>& comp);

	bool SonIguales(const T& t1, const T& t2) const;
	bool SonDistintos(const T& t1, const T& t2) const;
	bool EsMenor(const T& t1, const T& t2) const;
	bool EsMayor(const T& t1, const T& t2) const;

	CompRetorno Comparar(const T& t1, const T& t2) const;

	Comparador<T> Componer(const Comparador<T>& diferenciador) const;
	Comparador<T> InvertirOrden() const;

	Comparador<T> operator+(const Comparador<T>& diferenciador) const;
	Comparador<T> operator-() const;

	static const Puntero<Comparacion<T>>& Default;

private:
	Puntero<Comparacion<T>> m_Comp;

	static Puntero<Comparacion<T>> s_DefaultComp;
	static unsigned int s_CantComps;

	class ComparacionOperadores : public Comparacion<T>
	{
	public:
		CompRetorno Comparar(const T& t1, const T& t2) const override;
	};

	class ComparacionInversa : public Comparacion<T>
	{
	public:
		CompRetorno Comparar(const T&t1, const T&t2) const override;

		static Puntero<Comparacion<T>> InvertirOrden(Puntero<Comparacion<T>> comp);
	private:
		ComparacionInversa(Puntero<Comparacion<T>> comp);
		Puntero<Comparacion<T>> m_Comp;
	};

	class ComparacionCompuesta : Comparacion<T>
	{
	public:
		ComparacionCompuesta(Puntero<Comparacion<T>> principal, Puntero<Comparacion<T>> diferenciador);
		CompRetorno Comparar(const T&t1, const T&t2) const override;
	private:
		Puntero<Comparacion<T>> m_Principal;
		Puntero<Comparacion<T>> m_Diferenciador;
	};

	static const Puntero<Comparacion<T>>& DefaultComp();
};

#include "Comparador.cpp"
