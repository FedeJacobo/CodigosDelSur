#ifndef ARRAYITERACION_CPP
#define ARRAYITERACION_CPP

#include "ArrayIteracion.h"
#include "Array.h"

template <class T>
ArrayIteracion<T>::ArrayIteracion(const Array<T>& iterable)
: m_Iterable(iterable)
{
	m_Inicio = 0;
	m_Largo = iterable.Largo;
}

template <class T>
ArrayIteracion<T>::ArrayIteracion(const Array<T>& iterable, nat largo)
: m_Iterable(iterable)
{
	assert(largo <= iterable.Largo);
	m_Inicio = 0;
	m_Largo = largo;
}

template <class T>
ArrayIteracion<T>::ArrayIteracion(const Array<T>& iterable, nat inicio, nat largo)
: m_Iterable(iterable)
{
	assert(inicio + largo <= iterable.Largo);
	m_Inicio = inicio;
	m_Largo = largo;
}

template <class T>
ArrayIteracion<T>::ArrayIteracion(const Array<T>& iterable, nat inicio, nat largo, nat posicion)
: m_Iterable(iterable)
{
	assert(inicio + largo <= iterable.Largo);
	assert(posicion >= inicio && posicion <= inicio + largo);
	m_Inicio = inicio;
	m_Largo = largo;
	m_Posicion = posicion;
}

template <class T>
void ArrayIteracion<T>::Reiniciar()
{
	m_Posicion = m_Inicio;
}

template <class T>
bool ArrayIteracion<T>::HayElemento() const
{
	return m_Posicion < m_Inicio + m_Largo;
}

template <class T>
const T& ArrayIteracion<T>::ElementoActual() const
{
	return m_Iterable[m_Posicion];
}

template <class T>
void ArrayIteracion<T>::Avanzar()
{
	m_Posicion++;
}

template <class T>
Puntero<Iteracion<T>> ArrayIteracion<T>::Clonar() const
{
	return new ArrayIteracion<T>(m_Iterable, m_Inicio, m_Largo, m_Posicion);
}

#endif