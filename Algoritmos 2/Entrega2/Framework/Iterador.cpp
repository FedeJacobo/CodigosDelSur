#ifndef ITERADOR_CPP
#define ITERADOR_CPP

#include "Iterador.h"
#include "ConversorCast.h"
#include "ConvertIteracion.h"
#include "ConcatIteracion.h"

template <class T>
Iterador<T>::Iterador(Iteracion<T>* iteracion)
	: m_Iteracion(iteracion)
{
	Reiniciar();
}

template <class T>
Iterador<T>::Iterador(const Puntero<Iteracion<T>>& iteracion)
	: m_Iteracion(iteracion)
{
	Reiniciar();
}

template <class T>
Iterador<T>::Iterador(const Puntero<Iterable<T>>& iterable)
	: m_Iteracion(iterable ? iterable->ObtenerIterador().m_Iteracion : nullptr)
{
}

template <class T>
Iterador<T>::Iterador(const Iterador<T>& iterador)
	: m_Iteracion(iterador.m_Iteracion)
{
}

template <class T>
const Iterador<T>& Iterador<T>::operator=(Iteracion<T>* iteracion)
{
	m_Iteracion = iteracion;
	Reiniciar();
	return *this;
}

template <class T>
const Iterador<T>& Iterador<T>::operator=(const Puntero<Iteracion<T>>& iteracion)
{
	m_Iteracion = iteracion;
	Reiniciar();
	return *this;
}

template <class T>
const Iterador<T>& Iterador<T>::operator=(const Puntero<Iterable<T>>& iterable)
{
	m_Iteracion = iterable ? iterable->ObtenerIterador().m_Iteracion : nullptr;
	Reiniciar();
	return *this;
}

template <class T>
const Iterador<T>& Iterador<T>::operator=(const Iterador<T>& iterador)
{
	m_Iteracion = iterador.m_Iteracion;
	return *this;
}

template <class T>
void Iterador<T>::Reiniciar()
{
	if (m_Iteracion)
		m_Iteracion->Reiniciar();
}

template <class T>
bool Iterador<T>::HayElemento() const
{
	return m_Iteracion && m_Iteracion->HayElemento();
}

template <class T>
const T& Iterador<T>::ElementoActual() const
{
	assert(HayElemento());
	return m_Iteracion->ElementoActual();
}

template <class T>
void Iterador<T>::Avanzar()
{
	assert(HayElemento());
	m_Iteracion->Avanzar();
}

template <class T>
Iterador<T>& Iterador<T>::operator++()
{
	Avanzar();
	return *this;
}

template <class T>
Iterador<T> Iterador<T>::operator++(int)
{
	Iterador<T> copia = Clonar();
	Avanzar();
	return copia;
}

template <class T>
const T& Iterador<T>::operator*() const
{
	return ElementoActual();
}

template <class T>
bool Iterador<T>::operator!() const
{
	return !HayElemento();
}

template <class T>
Iterador<T>::operator bool() const
{
	return HayElemento();
}

template <class T>
template <class U> Iterador<T>::operator Iterador<U>() const
{
	return Convert<U, ConversorCast<T, U>>();
}

template <class T>
template <class U, typename Conv>
Iterador<U> Iterador<T>::Convert() const
{
	return m_Iteracion ? new ConvertIteracion<T, U, Conv>(m_Iteracion) : nullptr;
}

template <class T>
Iterador<T> Iterador<T>::Concat(const Iterador<T>& it) const
{
	return m_Iteracion ? it.m_Iteracion ? new ConcatIteracion<T>(m_Iteracion, it.m_Iteracion) : m_Iteracion : it.m_Iteracion;
}

template <class T>
Iterador<T> Iterador<T>::Clonar() const
{
	if (m_Iteracion)
	{
		Iterador<T> it;
		it.m_Iteracion = m_Iteracion->Clonar();
		return it;
	}
	else
		return nullptr;
}

template <class T>
Puntero<Iteracion<T>> Iterador<T>::Unwrap() const
{
	auto it = m_Iteracion;
	if (it)
		it->Reiniciar();
	return it;
}

#endif