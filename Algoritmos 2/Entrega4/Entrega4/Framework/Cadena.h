#pragma once

#include "Array.h"

#include <iostream>
using namespace std;

#define MAX_CADENA 256

class Cadena
{
	friend ostream& operator<<(ostream& out, const Cadena& c);
	friend istream& operator>>(istream& in, Cadena& c);

public:
	Cadena(const char* cadena = nullptr);
	Cadena(const Cadena& c);

	char operator[](nat index) const;

	__declspec(property(get = ObtenerLargo)) nat Largo;
	nat ObtenerLargo() const;

	bool operator==(const Cadena& c) const;
	bool operator!=(const Cadena& c) const;
	bool operator<(const Cadena& c) const;
	bool operator>(const Cadena& c) const;
	bool operator<=(const Cadena& c) const;
	bool operator>=(const Cadena& c) const;

	Cadena& operator=(const Cadena& c);
	Cadena operator+(const Cadena& c) const;
	Cadena& operator+=(const Cadena& c);

	/*/ Ajusta la Cadena al ser impresa
	 *  Si el parámetro largo es menor que el largo de la cadena, se
	 *  imprimen la cantidad de caracteres indicados por el parámetro
	 *  Si el parámetro largo es mayor que el largo de la cadena, se
	 *  imprime la cadena completa, y se rellena la salida con espacios
	/*/
	Cadena operator^(nat largo) const;

	Cadena SubCadena(nat desde) const;
	Cadena SubCadena(nat desde, nat largo) const;

	Cadena LTrim() const;
	Cadena RTrim() const;
	Cadena Trim() const;

	Cadena DarFormato(const Cadena& c0) const;
	Cadena DarFormato(const Cadena& c0, const Cadena& c1) const;
	Cadena DarFormato(const Cadena& c0, const Cadena& c1, const Cadena& c2) const;
	Cadena DarFormato(const Cadena& c0, const Cadena& c1, const Cadena& c2, const Cadena& c3) const;

	Cadena Reemplazar(const Cadena& vieja, const Cadena& nueva) const;

private:
	static Array<char> s_ArrayVacio;

	Cadena(const Array<char>& string, nat desde, nat largo);

	Array<char> string;
	nat ini;
	nat largo;

	nat ajustar;
};
