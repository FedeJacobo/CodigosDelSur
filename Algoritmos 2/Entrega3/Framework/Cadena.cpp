#include "Cadena.h"

ostream& operator<<(ostream& out, const Cadena& c)
{
	nat largo = c.Largo;
	if (c.ajustar > 0 && c.ajustar < largo)
		largo = c.ajustar;

	for (nat i = 0; i < largo; i++)
		out << c[i];

	for (nat i = largo; i < c.ajustar; i++)
		out << ' ';

	return out;
}

istream& operator>>(istream& in, Cadena& c)
{
	char aux[MAX_CADENA];
	in >> aux;
	c = Cadena(aux);
	return in;
}

Cadena::Cadena(const char* cadena)
{
	ini = 0;
	largo = 0;
	ajustar = 0;
	if (cadena != nullptr)
	{
		while (cadena[largo] != '\0')
			largo++;
	}
	if (largo == 0)
		*this = Cadena(s_ArrayVacio, 0, 0);
	else
	{
		string = Array<char>(largo + 1);
		for (nat i = 0; i < largo; i++)
			string[i] = cadena[i];
		string[largo] = '\0';
	}
}

Cadena::Cadena(const Cadena& c)
{
	*this = c;
	ajustar = c.ajustar;
}

Cadena::Cadena(const Array<char>& string, nat desde, nat largo)
{
	assert(desde + largo < string.Largo);
	if (largo > 0)
	{
		ini = desde;
		this->largo = largo;
		this->string = string;
	}
	else
	{
		ini = 0;
		this->largo = 0;
		this->string = string.Largo == 1 ? string : s_ArrayVacio;
	}
	ajustar = 0;
}

char Cadena::operator[](nat index) const
{
	assert(index < largo);
	return string[ini + index];
}

nat Cadena::ObtenerLargo() const
{
	return largo;
}

bool Cadena::operator==(const Cadena& c) const
{
	if (largo == c.Largo)
	{
		nat i;
		for (i = 0; i < largo && (*this)[i] == c[i]; i++);
		return i == largo;
	}
	return false;
}

bool Cadena::operator!=(const Cadena& c) const
{
	return !(*this == c);
}

bool Cadena::operator<(const Cadena& c) const
{
	nat largoMin = Largo < c.Largo ? Largo : c.Largo;
	for (nat i = 0; i < largoMin; i++)
		if ((*this)[i] < c[i])
			return true;
		else if ((*this)[i] > c[i])
			return false;
	return Largo < c.Largo;
}

bool Cadena::operator>(const Cadena& c) const
{
	nat largoMin = Largo < c.Largo ? Largo : c.Largo;
	for (nat i = 0; i < largoMin; i++)
		if ((*this)[i] > c[i])
			return true;
		else if ((*this)[i] < c[i])
			return false;
	return Largo > c.Largo;
}

bool Cadena::operator<=(const Cadena& c) const
{
	return (*this == c) || (*this < c);
}

bool Cadena::operator>=(const Cadena& c) const
{
	return (*this == c) || (*this > c);
}

Cadena& Cadena::operator=(const Cadena& c)
{
	if (&c != this)
	{
		string = c.string;
		ini = c.ini;
		largo = c.largo;
	}
	return *this;
}

Cadena Cadena::operator+(const Cadena& c) const
{
	if (c.Largo == 0)
		return *this;
	if (Largo == 0)
		return c;
	Array<char> concated = Array<char>(Largo + c.Largo + 1);
	Array<char>::Copiar(string, ini, Largo, concated);
	Array<char>::Copiar(c.string, c.ini, c.Largo, concated, Largo);
	return Cadena(concated, 0, concated.Largo - 1);
}

Cadena& Cadena::operator+=(const Cadena& c)
{
	nat ajustar = this->ajustar;
	*this = *this + c;
	this->ajustar = ajustar;
	return *this;
}

Cadena Cadena::operator^(nat largo) const
{
	Cadena cad = Cadena(string, ini, Largo);
	cad.ajustar = largo;
	return cad;
}

Cadena Cadena::SubCadena(nat desde) const
{
	return SubCadena(desde, Largo - desde);
}

Cadena Cadena::SubCadena(nat desde, nat largo) const
{
	return Cadena(string, ini + desde, largo);
}

Cadena Cadena::LTrim() const
{
	nat posIni = 0;
	while (posIni < Largo && (*this)[posIni] == ' ')
		posIni++;
	return SubCadena(posIni);
}

Cadena Cadena::RTrim() const
{
	nat posFin = Largo - 1;
	while (posFin >= 0 && (*this)[posFin] == ' ')
		posFin--;
	return SubCadena(0, posFin + 1);
}

Cadena Cadena::Trim() const
{
	return LTrim().RTrim();
}

Cadena Cadena::DarFormato(const Cadena& c0) const
{
	Cadena c = "";
	return DarFormato(c0, c, c, c);
}

Cadena Cadena::DarFormato(const Cadena& c0, const Cadena& c1) const
{
	Cadena c = "";
	return DarFormato(c0, c1, c, c);
}

Cadena Cadena::DarFormato(const Cadena& c0, const Cadena& c1, const Cadena& c2) const
{
	Cadena c = "";
	return DarFormato(c0, c1, c2, c);
}

#include "Tupla.h"
int BuscarPos(const Cadena& origen, const Cadena& buscar);
int BuscarPos(const Cadena& origen, const Cadena& buscar, nat desde);
void CopiarFormateado(const Array<char> string, nat ini, Array<char> formateado, nat& lastPosC, nat& lastPosF, nat pos, const Array<char> cad_string, nat cad_ini, nat cad_largo, nat largoViejo);
void OrdenarPos(Tupla<int, Cadena>& t1, Tupla<int, Cadena>& t2);

Cadena Cadena::DarFormato(const Cadena& c0, const Cadena& c1, const Cadena& c2, const Cadena& c3) const
{
	Tupla<int, Cadena> t0 (BuscarPos(*this, "{0}"), c0);
	Tupla<int, Cadena> t1 (BuscarPos(*this, "{1}"), c1);
	Tupla<int, Cadena> t2 (BuscarPos(*this, "{2}"), c2);
	Tupla<int, Cadena> t3 (BuscarPos(*this, "{3}"), c3);

	OrdenarPos(t0, t1);
	OrdenarPos(t0, t2);
	OrdenarPos(t0, t3);
	OrdenarPos(t1, t2);
	OrdenarPos(t1, t3);
	OrdenarPos(t2, t3);

	if (t3.Dato1 == -1)
		return *this;

	nat largoF = largo;
	if (t0.Dato1 != -1)
		largoF += (t0.Dato2.largo - 3);
	if (t1.Dato1 != -1)
		largoF += (t1.Dato2.largo - 3);
	if (t2.Dato1 != -1)
		largoF += (t2.Dato2.largo - 3);
	if (t3.Dato1 != -1)
		largoF += (t3.Dato2.largo - 3);

	Array<char> formateado = Array<char>(largoF + 1);
	nat lastPosC = ini;
	nat lastPosF = 0;
	CopiarFormateado(string, ini, formateado, lastPosC, lastPosF, t0.Dato1, t0.Dato2.string, t0.Dato2.ini, t0.Dato2.largo, 3);
	CopiarFormateado(string, ini, formateado, lastPosC, lastPosF, t1.Dato1, t1.Dato2.string, t1.Dato2.ini, t1.Dato2.largo, 3);
	CopiarFormateado(string, ini, formateado, lastPosC, lastPosF, t2.Dato1, t2.Dato2.string, t2.Dato2.ini, t2.Dato2.largo, 3);
	CopiarFormateado(string, ini, formateado, lastPosC, lastPosF, t3.Dato1, t3.Dato2.string, t3.Dato2.ini, t3.Dato2.largo, 3);
	Cadena t4 = SubCadena(t3.Dato1 + 3);
	CopiarFormateado(string, ini, formateado, lastPosC, lastPosF, lastPosC, t4.string, t4.ini, t4.largo, 3);
	formateado[largoF] = '\0';
	return Cadena(formateado, 0, largoF);
}

Cadena Cadena::Reemplazar(const Cadena& vieja, const Cadena& nueva) const
{
	assert(vieja.Largo > 0);
	if (vieja.Largo > Largo)
		return *this;

	nat cantOcurrencias = 0;
	int pos = BuscarPos(*this, vieja);
	while (pos != -1)
	{
		cantOcurrencias++;
		pos = BuscarPos(*this, vieja, pos + vieja.Largo);
	}
	if (cantOcurrencias == 0)
		return *this;

	int difLargo = nueva.Largo;
	difLargo -= vieja.Largo;
	nat largoR = Largo + cantOcurrencias * difLargo;
	Array<char> reemplazado = Array<char>(largoR + 1);
	nat lastPosC = ini;
	nat lastPosR = 0;
	pos = BuscarPos(*this, vieja);
	nat ultimaPos = 0;
	while (pos != -1)
	{
		CopiarFormateado(string, ini, reemplazado, lastPosC, lastPosR, pos, nueva.string, nueva.ini, nueva.largo, vieja.Largo);
		ultimaPos = pos;
		pos = BuscarPos(*this, vieja, pos + vieja.Largo);
	}
	Cadena tmp = SubCadena(ultimaPos + vieja.Largo);
	CopiarFormateado(string, ini, reemplazado, lastPosC, lastPosR, lastPosC, tmp.string, tmp.ini, tmp.largo, vieja.Largo);
	reemplazado[largoR] = '\0';
	return Cadena(reemplazado, 0, largoR);
}

int BuscarPos(const Cadena& origen, const Cadena& buscar)
{
	return BuscarPos(origen, buscar, 0);
}

int BuscarPos(const Cadena& origen, const Cadena& buscar, nat desde)
{
	for (nat pos = desde; pos <= origen.Largo - buscar.Largo; pos++)
	{
		if (origen.SubCadena(pos, buscar.Largo) == buscar)
			return pos;
	}
	return -1;
}

void OrdenarPos(Tupla<int, Cadena>& t1, Tupla<int, Cadena>& t2)
{
	if (t2.Dato1 < t1.Dato1)
	{
		auto aux = t1;
		t1 = t2;
		t2 = aux;
	}
}

void CopiarFormateado(const Array<char> string, nat ini, Array<char> formateado, nat& lastPosC, nat& lastPosF, nat pos, const Array<char> cad_string, nat cad_ini, nat cad_largo, nat largoViejo)
{
	if (pos != -1)
	{
		nat largoTramo = pos + ini - lastPosC;
		Array<char>::Copiar(string, lastPosC, largoTramo, formateado, lastPosF);
		lastPosC = pos + ini + largoViejo;
		lastPosF += largoTramo;
		Array<char>::Copiar(cad_string, cad_ini, cad_largo, formateado, lastPosF);
		lastPosF += cad_largo;
	}
}

Array<char> CrearArrayVacio()
{
	Array<char> vacio = Array<char>(1);
	vacio[0] = '\0';
	return vacio;
}

Array<char> Cadena::s_ArrayVacio = CrearArrayVacio();
