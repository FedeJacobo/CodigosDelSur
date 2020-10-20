#ifndef COMPARADOR_CPP
#define COMPARADOR_CPP

#include "Comparador.h"

template <class T>
Comparador<T>::Comparador(Comparacion<T>* comp)
{
	if (!comp)
		m_Comp = DefaultComp();
	else
		m_Comp = comp;
	s_CantComps++;
}

template <class T>
Comparador<T>::Comparador(const Puntero<Comparacion<T>>& comp)
{
	if (!comp)
		m_Comp = DefaultComp();
	else
		m_Comp = comp;
	s_CantComps++;
}

template <class T>
Comparador<T>::Comparador(const Comparador<T>& comp)
{
	assert(comp.m_Comp != nullptr);
	m_Comp = comp.m_Comp;
	s_CantComps++;
}

template <class T>
Comparador<T>::~Comparador()
{
	s_CantComps--;
	if (s_CantComps == 0)
		s_DefaultComp = nullptr;
}

template <class T>
const Comparador<T>& Comparador<T>::operator=(Comparacion<T>* comp)
{
	if (!comp)
		m_Comp = DefaultComp();
	else
		m_Comp = comp;
	return *this;
}

template <class T>
const Comparador<T>& Comparador<T>::operator=(const Puntero<Comparacion<T>>& comp)
{
	if (!comp)
		m_Comp = DefaultComp();
	else
		m_Comp = comp;
	return *this;
}

template <class T>
const Comparador<T>& Comparador<T>::operator=(const Comparador<T>& comp)
{
	assert(comp.m_Comp != nullptr);
	m_Comp = comp.m_Comp;
	return *this;
}

template <class T>
bool Comparador<T>::SonIguales(const T& t1, const T& t2) const
{
	return Comparar(t1, t2) == IGUALES;
}

template <class T>
bool Comparador<T>::SonDistintos(const T& t1, const T& t2) const
{
	// Se define que los elementos son distintos, si el
	// resultado de la comparaci�n no da IGUALES,
	// por lo tanto SonDistintos devuelve true si el comparar
	// devuelve MENOR, MAYOR o DISTINTOS
	return Comparar(t1, t2) != IGUALES;
}

template <class T>
bool Comparador<T>::EsMenor(const T& t1, const T& t2) const
{
	return Comparar(t1, t2) == MENOR;
}

template <class T>
CompRetorno Comparador<T>::Comparar(const T& t1, const T& t2) const
{
	return m_Comp->Comparar(t1, t2);
}

template <class T>
Comparador<T> Comparador<T>::Componer(const Comparador<T>& diferenciador) const
{
	return new ComparacionCompuesta(m_Comp, diferenciador.m_Comp);
}

template <class T>
Comparador<T> Comparador<T>::InvertirOrden() const
{
	return ComparacionInversa::InvertirOrden(m_Comp);
}

template <class T>
Comparador<T> Comparador<T>::operator+(const Comparador<T>& diferenciador) const
{
	return Componer(diferenciador);
}

template <class T>
Comparador<T> Comparador<T>::operator-() const
{
	return InvertirOrden();
}

template <class T>
bool Comparador<T>::EsMayor(const T& t1, const T& t2) const
{
	return Comparar(t1, t2) == MAYOR;
}

// VS 2015 no soporta operador __if_exists sobre tipos de datos fundamentales
// Se crea la clase SeparadorTipo con dos implementaciones (una para <T, true> y la otra para <T, false>)
// para separar el caso de que se este comparando un tipo fundamental de un clase/struct
template<typename T, bool = true>
struct SeparadorTipo
{
	// Este comparar es llamado cuando la condición "isFundamental" da verdadero
	CompRetorno Comparar(const T& t1, const T& t2) const
	{
		if (t1 == t2)
			return IGUALES;
		
		if (t1 < t2)
			return MENOR;
		
		if (t1 > t2)
			return MAYOR;		

		return DISTINTOS;
	}
};
template<typename T>
struct SeparadorTipo<T, false>
{
	// Este comparar es llamado cuando la condición "isFundamental" da falso
	CompRetorno Comparar(const T& t1, const T& t2) const
	{
		// Si la clase evaluada "T" tiene definidos los operadores entonces los usa
		__if_exists(T::operator==)
		{
			if (t1 == t2)
				return IGUALES;
		}
		__if_exists(T::operator<)
		{
			if (t1 < t2)
				return MENOR;
		}
		__if_exists(T::operator>)
		{
			if (t1 > t2)
				return MAYOR;
		}

		return DISTINTOS;
	}
};

template <class T>
CompRetorno Comparador<T>::ComparacionOperadores::Comparar(const T& t1, const T& t2) const
{
	// Se instancia la clase "SeparadorTipo" correspondiente, dependiendo del retorno de is_fundamental
	// a esa instancia se le llama al Comparar
	return SeparadorTipo<T, std::is_fundamental<T>::value>().Comparar(t1, t2);
}
template <class T>
Comparador<T>::ComparacionInversa::ComparacionInversa(Puntero<Comparacion<T>> comp)
{
	assert(comp != nullptr);
	m_Comp = comp;
}

template <class T>
Puntero<Comparacion<T>> Comparador<T>::ComparacionInversa::InvertirOrden(Puntero<Comparacion<T>> comp)
{
	if (comp.Is<ComparacionInversa>())
	{
		Puntero<ComparacionInversa> compInv = comp;
		return compInv->m_Comp;
	}
	else
		return new ComparacionInversa(comp);
}

template <class T>
CompRetorno Comparador<T>::ComparacionInversa::Comparar(const T& t1, const T& t2) const
{
	return m_Comp->Comparar(t2, t1);
}

template <class T>
Comparador<T>::ComparacionCompuesta::ComparacionCompuesta(Puntero<Comparacion<T>> principal, Puntero<Comparacion<T>> diferenciador)
{
	m_Principal = principal;
	m_Diferenciador = diferenciador;
}

template <class T>
CompRetorno Comparador<T>::ComparacionCompuesta::Comparar(const T& t1, const T& t2) const
{
	CompRetorno ret = m_Principal->Comparar(t1, t2);
	if (ret == IGUALES)
		ret = m_Diferenciador->Comparar(t1, t2);
	return ret;
}

template <class T>
const Puntero<Comparacion<T>>& Comparador<T>::DefaultComp()
{
	if (!s_DefaultComp)
		s_DefaultComp = new ComparacionOperadores();
	return s_DefaultComp;
}

template <class T>
const Puntero<Comparacion<T>>& Comparador<T>::Default = nullptr;

template <class T>
Puntero<Comparacion<T>> Comparador<T>::s_DefaultComp = nullptr;

template <class T>
unsigned int Comparador<T>::s_CantComps = 0;

#endif