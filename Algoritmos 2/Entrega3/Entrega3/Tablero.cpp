#ifndef TABLERO_CPP
#define TABLERO_CPP

#include "Tablero.h"

Tablero::Tablero(Matriz<int> bloques, Puntero<Prioridad> p)
{
	tablero = bloques;
	p = p;
	cantMov = 0;
}
	
nat Tablero::CalcularPrioridad() const
{
	return p->CalcularPrioridad(*this);
}
		
bool Tablero::operator==(const Tablero& t ) const
{
	for (nat i = 0; i < tablero.Largo; i++)
	{
		for (nat j = 0; j < tablero.Largo; j++)
		{
			if (t.tablero.Largo <= i || t.tablero.Ancho <= j || tablero[i][j] != t.tablero[i][j])return false;
		}
	}
	return true;
}
	

Iterador<Tablero> Tablero::Vecinos()
{
	Array<Tablero> ret = Array<Tablero>(4);
	for (nat i = 0; i < tablero.Largo; i++)
	{
		for (nat j = 0; j < tablero.Largo; j++)
		{
			nat cont = 0;
			if (tablero[i][j] == 0) {
				if (esPosValida(i + 1)) {
					Matriz<int> mat = Matriz<int>(tablero.Largo);
					for (nat i = 0; i < tablero.Largo; i++)
					{
						for (nat j = 0; j < tablero.Ancho; j++)
						{
							int valor =
								mat[i][j] = tablero[i][j];
						}
					}
					Tablero t = Tablero(swap(i, j, i + 1, j, mat), p);
					t.cantMov = cantMov + 1;
					cont++;
					ret[cont] = t;
				}
				if (esPosValida(i - 1))
				{
					Matriz<int> mat = Matriz<int>(tablero.Largo);
					for (nat i = 0; i < tablero.Largo; i++)
					{
						for (nat j = 0; j < tablero.Ancho; j++)
						{
							int valor =
								mat[i][j] = tablero[i][j];
						}
					}
					Tablero t = Tablero(swap(i, j, i - 1, j, mat), p);
					t.cantMov = cantMov + 1;
					cont++;
					ret[cont] = t;
				}
				if (esPosValida(j + 1))
				{
					Matriz<int> mat = Matriz<int>(tablero.Largo);
					for (nat i = 0; i < tablero.Largo; i++)
					{
						for (nat j = 0; j < tablero.Ancho; j++)
						{
							int valor =
								mat[i][j] = tablero[i][j];
						}
					}
					Tablero t = Tablero(swap(i, j, i, j + 1, mat), p);
					t.cantMov = cantMov + 1;
					cont++;
					ret[cont] = t;
				}
				if (esPosValida(j - 1))
				{
					Matriz<int> mat = Matriz<int>(tablero.Largo);
					for (nat i = 0; i < tablero.Largo; i++)
					{
						for (nat j = 0; j < tablero.Ancho; j++)
						{
							int valor =
								mat[i][j] = tablero[i][j];
						}
					}
					Tablero t = Tablero(swap(i, j, i, j - 1, mat), p);
					t.cantMov = cantMov + 1;
					cont++;
					ret[cont] = t;
				}
				return new ArrayIteracion<Tablero>(ret, cont);
			}
		}
	}
	return ret.ObtenerIterador();
}
	

Matriz<int> Tablero::ObtenerTablero() const
{
	return tablero;
}

Cadena Tablero::Imprimir() const
{
	Cadena ret = "";
	for (nat i = 0; i < tablero.Largo; i++)
	{
		for (nat j = 0; j < tablero.Largo; j++)
		{
			ret += tablero[i][j] + "";
		}
		ret += "\n";
	}
	return "";
}

int Tablero::CantidadDeMovimientos() const {
	return cantMov;
}

bool Tablero::esPosValida(const nat pos) const {
	return pos >= 0 && pos < tablero.Largo;
}

Matriz<int> Tablero::swap(int iniX, int iniY, int finX, int finY, Matriz<int> ret) const{
	
	int aux = ret[iniX][iniY];
	ret[iniX][iniY] = ret[finX][finY];
	ret[finX][finY] = aux;
	return ret;
}

#endif