#include "CasoDePrueba.h"
#include "CadenaFuncionHash.h"

CasoDePrueba::CasoDePrueba(Puntero<Sistema>(*inicializar)())
{
	this->inicializar = inicializar;
}

Puntero<Sistema> CasoDePrueba::InicializarSistema()
{
	Puntero<Sistema> interfaz = inicializar();
	ignorarOK = false;
	return interfaz;
}

Cadena CasoDePrueba::GetNombre()const
{
	return "Casos de Prueba";
}

void CasoDePrueba::CorrerPruebaConcreta()
{
	IniciarSeccion("Cola de Prioridad Extendida");
	PruebaColaPrioridadExtendida();
	CerrarSeccion();

	Puntero<Prioridad> prioridadA = new PrioridadA();
	Puntero<Prioridad> prioridadB = new PrioridadB();

	IniciarSeccion("Prioridad A");
	PruebaTablero1(prioridadA);
	PruebaTablero2(prioridadA);
	PruebaTablero3(prioridadA);
	PruebaTablero4(prioridadA);
	PruebaTablero5(prioridadA);
	PruebaTablero6(prioridadA);
	CerrarSeccion();

	IniciarSeccion("Prioridad B");
	PruebaTablero1(prioridadB);
	PruebaTablero2(prioridadB);
	PruebaTablero3(prioridadB);
	PruebaTablero4(prioridadB);
	PruebaTablero5(prioridadB);
	PruebaTablero6(prioridadB);
	CerrarSeccion();

}

void CasoDePrueba::Verificar(TipoRetorno obtenido, TipoRetorno esperado, Cadena comentario)
{
	if (!ignorarOK || obtenido != esperado)
		Prueba::Verificar(obtenido, esperado, comentario);
}

template <class T>
void CasoDePrueba::Verificar(const T& obtenido, const T& esperado, Cadena comentario)
{
	Verificar(SonIguales(obtenido, esperado) ? OK : ERROR, OK, comentario.DarFormato(ObtenerTexto(obtenido), ObtenerTexto(esperado)));
}

template <class T>
void CasoDePrueba::VerificarConjuntos(Iterador<T> obtenidos, Iterador<T> esperados, Cadena comentarioEncontrado, Cadena comentarioFalta, Cadena comentarioSobra)
{
	bool verificarCantidad = true;
	nat totalObtenidos = 0;
	T aux;
	obtenidos.Reiniciar();
	esperados.Reiniciar();
	foreach(T obtenido, obtenidos)
	{
		totalObtenidos++;
		if (Pertenece(obtenido, esperados, aux))
			Verificar(OK, OK, comentarioEncontrado.DarFormato(ObtenerTexto(obtenido), ObtenerTexto(obtenido)));
		else
		{
			Verificar(ERROR, OK, comentarioSobra.DarFormato(ObtenerTexto(obtenido)));
			verificarCantidad = false;
		}
	}
	nat totalEsperados = 0;
	obtenidos.Reiniciar();
	esperados.Reiniciar();
	foreach(T esperado, esperados)
	{
		totalEsperados++;
		if (!Pertenece(esperado, obtenidos, aux))
		{
			Verificar(ERROR, OK, comentarioFalta.DarFormato(ObtenerTexto(esperado)));
			verificarCantidad = false;
		}
	}
	if (verificarCantidad && totalObtenidos != totalEsperados)
		Verificar(ERROR, OK, "Se verifica la cantidad de elementos de los conjuntos");
}

template <class T>
void CasoDePrueba::VerificarSecuencias(Iterador<T> obtenidos, Iterador<T> esperados, Cadena comentarioEncontrado, Cadena comentarioFalta, Cadena comentarioSobra)
{
	esperados.Reiniciar();

	foreach(T obtenido, obtenidos)
	{
		if (esperados.HayElemento())
		{
			T esperado = *esperados;
			++esperados;
			Verificar(obtenido, esperado, comentarioEncontrado);
		}
		else
			Verificar(ERROR, OK, comentarioSobra.DarFormato(ObtenerTexto(obtenido)));
	}

	while (esperados.HayElemento())
	{
		T esperado = *esperados;
		++esperados;
		Verificar(ERROR, OK, comentarioFalta.DarFormato(ObtenerTexto(esperado)));
	}
}

void CasoDePrueba::VerificarSolucionTablero(Matriz<int> inicial, Iterador<Tablero> sol)
{
	ignorarOK = false;
	sol.Reiniciar();

	if (!sol.HayElemento()) 
	{
		Verificar(ERROR, OK, "La solución retornada es vacía.");
		return;
	}

	if (!this->SonIguales(inicial, sol.ElementoActual().ObtenerTablero()))
	{
		Verificar(ERROR, OK, "El tablero inicial no coincide.");
		return;
	}
	Matriz<int> tab1 = sol.ElementoActual().ObtenerTablero();
	Matriz<int> tab2 = sol.ElementoActual().ObtenerTablero();
	while(sol.HayElemento())
	{
		tab1 = sol.ElementoActual().ObtenerTablero();
		sol.Avanzar();
		if (!sol.HayElemento()) break;
		tab2 = sol.ElementoActual().ObtenerTablero();
	
		if (!this->SonVecinos(tab1, tab2)) {
			Verificar(ERROR, OK, "Se hace un movimiento inválido en el tablero.");
			return;
		}
		tab1 = tab2;
	}

	Matriz<int> bloques = Matriz<int>(3);
	bloques[0][0] = 1;
	bloques[0][1] = 2;
	bloques[0][2] = 3;

	bloques[1][0] = 4;
	bloques[1][1] = 5;
	bloques[1][2] = 6;

	bloques[2][0] = 7;
	bloques[2][1] = 8;
	bloques[2][2] = 0;

	if (this->SonIguales(bloques, tab1))
	{
		Verificar(OK, OK, "La solución proporcionada es correcta.");
	}
	else {
		Verificar(ERROR, OK, "El tablero final no se corresponde con una solución.");
	}
}

bool CasoDePrueba::SonIguales(const Cadena& obtenidos, const Cadena& esperados) const
{
	return obtenidos == esperados;
}
template <class T>
bool CasoDePrueba::SonIguales(Iterador<T> obtenidos, Iterador<T> esperados) const
{
	obtenidos.Reiniciar();
	esperados.Reiniciar();
	while (obtenidos.HayElemento() && esperados.HayElemento())
	{
		if (!SonIguales(*obtenidos, *esperados))
			return false;
		++obtenidos;
		++esperados;
	}

	return esperados.HayElemento() == obtenidos.HayElemento();
}

template <class T>
Cadena CasoDePrueba::ObtenerTexto(Iterador<T> it) const
{
	Cadena sepVacio = "";
	Cadena sepGuion = "-";
	Cadena sep = sepVacio;
	Cadena retorno = sepVacio;
	foreach(auto t, it)
	{
		retorno += sep + ObtenerTexto(t);
		sep = sepGuion;
	}
	return retorno;
}

Cadena CasoDePrueba::ObtenerTexto(const Tupla<nat, nat>& t) const
{
	Cadena ret = " {0} - {1} ";
	return ret.DarFormato(ObtenerTexto(t.Dato1), ObtenerTexto(t.Dato2));
}

Cadena CasoDePrueba::ObtenerTexto(const Tupla<Cadena, nat>& t) const
{
	Cadena ret = " {0} - {1} ";
	return ret.DarFormato(ObtenerTexto(t.Dato1), ObtenerTexto(t.Dato2));
}

Cadena CasoDePrueba::ObtenerTexto(Cadena n) const
{
	return n;
}
Cadena CasoDePrueba::ObtenerTexto(Puntero<Tablero> tablero) const
{
	if (tablero != nullptr)
	{
		return tablero->Imprimir();
	}
	return "Tablero vacio";
}

Cadena CasoDePrueba::ObtenerTexto(nat n) const
{
	switch (n)
	{
	case 0:
		return "0";
	case 1:
		return "1";
	case 2:
		return "2";
	case 3:
		return "3";
	case 4:
		return "4";
	case 5:
		return "5";
	case 6:
		return "6";
	case 7:
		return "7";
	case 8:
		return "8";
	case 9:
		return "9";
	default:
		Cadena ret = "";
		while (n != 0)
		{
			ret = ObtenerTexto(n % 10) + ret;
			n /= 10;
		}
		return ret;
	}
}

bool CasoDePrueba::SonIguales(const Tupla<Cadena, nat>& obtenido, const Tupla<Cadena, nat>& esperado) const
{
	return (obtenido.Dato1 == esperado.Dato1 && obtenido.Dato2 == esperado.Dato2);
}

bool CasoDePrueba::SonIguales(const Tupla<nat, nat>& obtenido, const Tupla<nat, nat>& esperado) const
{
	return (obtenido.Dato1 == esperado.Dato1 && obtenido.Dato2 == esperado.Dato2) ||
		(obtenido.Dato2 == esperado.Dato1 && obtenido.Dato1 == esperado.Dato2);
}

bool CasoDePrueba::SonIguales(const bool obtenido, const bool esperado) const
{
	return obtenido == esperado;
}

bool CasoDePrueba::SonIguales(const Puntero<Tablero> obtenido, const Puntero<Tablero> esperado) const
{
	return obtenido == esperado;
}

bool CasoDePrueba::SonIguales(const int obtenido, const int esperado) const
{
	return obtenido == esperado;
}

bool CasoDePrueba::SonIguales(const Matriz<int>& obtenido, const Matriz<int>& esperado) const
{
	if (obtenido.Ancho != esperado.Ancho || obtenido.Largo != esperado.Largo)
		return false;
	for(nat i = 0; i < obtenido.Largo; i++)
	{
		for (nat j = 0; j < esperado.Ancho; j++) {
			if (obtenido[i][j] != esperado[i][j])
				return false;
		}
	}

	return true;
}

bool CasoDePrueba::SonVecinos(const Matriz<int>& obtenido, const Matriz<int>& esperado) const
{
	if (obtenido.Largo != esperado.Largo || obtenido.Ancho != esperado.Ancho)
		return false;

	int cantDif = 0;
	Array<Tupla<int, int>> difs(2);
	for (nat i = 0; i < obtenido.Largo; i++) 
	{
		for (nat j = 0; j < obtenido.Ancho; j++)
		{
			if (obtenido[i][j] != esperado[i][j]) 
			{
				if (obtenido[i][j] == 0 || esperado[i][j] == 0)
				{
					if (cantDif >= 2)
					{
						return false;
					}
					else {
						difs[cantDif] = Tupla<int, int>(i, j);
						cantDif++;
					}
				}
				else {
					return false;
				}
			}
		}
	}
	return cantDif == 2 && abs(difs[0].ObtenerDato1() - difs[1].ObtenerDato1())+ abs(difs[0].ObtenerDato2() - difs[1].ObtenerDato2()) == 1;
}

template <class T>
bool CasoDePrueba::Pertenece(const T& dato, Iterador<T> iterador, T& encontrado) const
{
	iterador.Reiniciar();
	foreach(T dato2, iterador)
	{
		if (SonIguales(dato, dato2))
		{
			encontrado = dato2;
			return true;
		}
	}
	return false;
}

void CasoDePrueba::PruebaTablero1(Puntero<Prioridad> prioridad)
{
	IniciarSeccion("Pruebas Tablero 1");
	Puntero<Sistema> interfaz = InicializarSistema();

	Matriz<int> bloques = Matriz<int>(3);
	bloques[0][0] = 1;
	bloques[0][1] = 2;
	bloques[0][2] = 3;

	bloques[1][0] = 4;
	bloques[1][1] = 5;
	bloques[1][2] = 6;

	bloques[2][0] = 0;
	bloques[2][1] = 7;
	bloques[2][2] = 8;

	Tablero* tablero1 = new Tablero(bloques, prioridad);

	interfaz->EstablecerTableroInicial(*tablero1);
	
	if (interfaz->TieneSolucion())
	{
		Verificar(OK, OK, "El tablero tiene solucion");
	}
	else 
	{
		Verificar(ERROR, OK, "El tablero tiene solucion");
	}

	Verificar(interfaz->Movimientos(), 2, "Se obtuvo {0} y se esperaba {1} movimientos");

	this->VerificarSolucionTablero(bloques, interfaz->Solucionar());
	
	delete tablero1;
	CerrarSeccion();
}

void CasoDePrueba::PruebaTablero2(Puntero<Prioridad> prioridad)
{
	IniciarSeccion("Pruebas Tablero 2");
	Puntero<Sistema> interfaz = InicializarSistema();

	Matriz<int> bloques = Matriz<int>(3);
	bloques[0][0] = 1;
	bloques[0][1] = 2;
	bloques[0][2] = 3;

	bloques[1][0] = 4;
	bloques[1][1] = 6;
	bloques[1][2] = 0;

	bloques[2][0] = 7;
	bloques[2][1] = 5;
	bloques[2][2] = 8;

	Tablero* tablero1 = new Tablero(bloques, prioridad);

	interfaz->EstablecerTableroInicial(*tablero1);

	if (interfaz->TieneSolucion())
	{
		Verificar(OK, OK, "El tablero tiene solucion");
	}
	else
	{
		Verificar(ERROR, OK, "El tablero tiene solucion");
	}

	Verificar(interfaz->Movimientos(), 3, "Se obtuvo {0} y se esperaba {1} movimientos");

	this->VerificarSolucionTablero(bloques, interfaz->Solucionar());

	delete tablero1;
	CerrarSeccion();
}

void CasoDePrueba::PruebaTablero3(Puntero<Prioridad> prioridad)
{
	IniciarSeccion("Pruebas Tablero 3");
	Puntero<Sistema> interfaz = InicializarSistema();

	Matriz<int> bloques = Matriz<int>(3);
	bloques[0][0] = 4;
	bloques[0][1] = 1;
	bloques[0][2] = 2;

	bloques[1][0] = 0;
	bloques[1][1] = 5;
	bloques[1][2] = 3;

	bloques[2][0] = 7;
	bloques[2][1] = 8;
	bloques[2][2] = 6;

	Tablero* tablero1 = new Tablero(bloques, prioridad);

	interfaz->EstablecerTableroInicial(*tablero1);

	if (interfaz->TieneSolucion())
	{
		Verificar(OK, OK, "El tablero tiene solucion");
	}
	else
	{
		Verificar(ERROR, OK, "El tablero tiene solucion");
	}

	Verificar(interfaz->Movimientos(), 5, "Se obtuvo {0} y se esperaba {1} movimientos");

	this->VerificarSolucionTablero(bloques, interfaz->Solucionar());

	delete tablero1;
	CerrarSeccion();
}

void CasoDePrueba::PruebaTablero4(Puntero<Prioridad> prioridad)
{
	IniciarSeccion("Pruebas Tablero 4");
	Puntero<Sistema> interfaz = InicializarSistema();

	Matriz<int> bloques = Matriz<int>(3);
	bloques[0][0] = 4;
	bloques[0][1] = 1;
	bloques[0][2] = 2;

	bloques[1][0] = 7;
	bloques[1][1] = 6;
	bloques[1][2] = 3;

	bloques[2][0] = 0;
	bloques[2][1] = 5;
	bloques[2][2] = 8;
	
	Tablero* tablero1 = new Tablero(bloques, prioridad);

	interfaz->EstablecerTableroInicial(*tablero1);

	if (interfaz->TieneSolucion())
	{
		Verificar(OK, OK, "El tablero tiene solucion");
	}
	else
	{
		Verificar(ERROR, OK, "El tablero tiene solucion");
	}

	Verificar(interfaz->Movimientos(), 8, "Se obtuvo {0} y se esperaba {1} movimientos");

	this->VerificarSolucionTablero(bloques, interfaz->Solucionar());

	delete tablero1;
	CerrarSeccion();
}

void CasoDePrueba::PruebaTablero5(Puntero<Prioridad> prioridad)
{
	IniciarSeccion("Pruebas Tablero 5");
	Puntero<Sistema> interfaz = InicializarSistema();

	Matriz<int> bloques = Matriz<int>(3);
	bloques[0][0] = 4;
	bloques[0][1] = 1;
	bloques[0][2] = 2;

	bloques[1][0] = 7;
	bloques[1][1] = 6;
	bloques[1][2] = 3;

	bloques[2][0] = 5;
	bloques[2][1] = 8;
	bloques[2][2] = 0;
	
	Tablero* tablero1 = new Tablero(bloques, prioridad);

	interfaz->EstablecerTableroInicial(*tablero1);

	if (interfaz->TieneSolucion())
	{
		Verificar(OK, OK, "El tablero tiene solucion");
	}
	else
	{
		Verificar(ERROR, OK, "El tablero tiene solucion");
	}

	Verificar(interfaz->Movimientos(), 10, "Se obtuvo {0} y se esperaba {1} movimientos");

	this->VerificarSolucionTablero(bloques, interfaz->Solucionar());

	delete tablero1;
	CerrarSeccion();
}

void CasoDePrueba::PruebaTablero6(Puntero<Prioridad> prioridad)
{
	IniciarSeccion("Pruebas Tablero 6");
	Puntero<Sistema> interfaz = InicializarSistema();

	Matriz<int> bloques = Matriz<int>(3);
	bloques[0][0] = 4;
	bloques[0][1] = 6;
	bloques[0][2] = 7;

	bloques[1][0] = 5;
	bloques[1][1] = 8;
	bloques[1][2] = 0;

	bloques[2][0] = 2;
	bloques[2][1] = 3;
	bloques[2][2] = 1;

	Tablero* tablero1 = new Tablero(bloques, prioridad);

	interfaz->EstablecerTableroInicial(*tablero1);

	if (interfaz->TieneSolucion())
	{
		Verificar(ERROR, OK, "El tablero no tiene solucion");
	}
	else
	{
		Verificar(OK, OK, "El tablero no tiene solucion");
	}

	delete tablero1;
	CerrarSeccion();	
}

void CasoDePrueba::PruebaColaPrioridadExtendida()
{	
	Puntero<Sistema> interfaz = InicializarSistema();
	Puntero<ColaPrioridadExtendida<Cadena, nat>> cola = interfaz->CrearColaPrioridadExtendida<Cadena,nat>(Comparador<Cadena>::Default, Comparador<nat>::Default, new CadenaFuncionHash());
	
	Verificar(cola != NULL, true, "La cola no debe ser nula.");
	if (cola != NULL) {
		Verificar(cola->EstaLlena(), false, "La cola no está llena.");
		Verificar(cola->EstaVacia(), true, "La cola está vacía.");

		Cadena elemento1 = "elemento1";
		nat prioridad1 = 1;

		cola->InsertarConPrioridad(elemento1,1);
		Verificar(cola->Largo() == 1, true, "El largo de la cola es 1.");
		Verificar(cola->EstaVacia(), false, "La cola no está vacía.");
		Verificar(cola->Pertenece(elemento1), true, "elemento1 pertenece a la cola.");
		Verificar(cola->ObtenerElementoMayorPrioridad(), elemento1, "El elemento de mayor prioridad es elemento1.");

		Tupla<Cadena, nat> t1 = Tupla<Cadena, nat>(elemento1, 1);
		Tupla<Cadena, nat> obtenido = cola->ObtenerElementoYPrioridad(elemento1);
		Verificar(obtenido, t1, "elemento1 tiene prioridad 1");

		cola->EliminarElementoMayorPrioridad();
		Verificar(cola->Largo() == 0, true, "El largo de la cola es 0.");
		Verificar(cola->EstaVacia(), true, "La cola está vacía.");
		
	
		nat cant = 8;
		Array<Tupla<Cadena, nat>> elementos = Array<Tupla<Cadena, nat>>(cant);
		elementos[0] = Tupla<Cadena, nat>("elemento0", 0);
		elementos[1] = Tupla<Cadena, nat>("elemento1", 1);
		elementos[2] = Tupla<Cadena, nat>("elemento2", 2);
		elementos[3] = Tupla<Cadena, nat>("elemento3", 3);
		elementos[4] = Tupla<Cadena, nat>("elemento4", 4);
		elementos[5] = Tupla<Cadena, nat>("elemento5", 5);
		elementos[6] = Tupla<Cadena, nat>("elemento6", 6);
		elementos[7] = Tupla<Cadena, nat>("elemento7", 7);

		foreach(auto tupla, elementos.ObtenerIterador())
		{
			cola->InsertarConPrioridad(tupla.Dato1, tupla.Dato2);
		}

		Verificar(cola->Largo() == elementos.Largo, true, "El largo de la cola es 8.");

		foreach(auto tupla, elementos.ObtenerIterador())
		{
			Verificar(cola->Pertenece(tupla.Dato1), true, Cadena("{0} esta definida.").DarFormato(tupla.Dato1));
			Verificar(cola->ObtenerElementoYPrioridad(tupla.Dato1), tupla, Cadena("La prioridad del elemento: {0} es {1}").DarFormato(tupla.Dato1,tupla.Dato2+""));//
		}

		VerificarConjuntos(cola->ObtenerIterador(), elementos.ObtenerIterador(), "Se obtuvo {0} correctamente", "Se esperaba {0}", "No se esperaba {0}");//

		elementos = Array<Tupla<Cadena, nat>>(0);
		cola->Vaciar();
		Verificar(cola->EstaVacia(), true, "La cola está vacía.");
		Verificar(cola->Largo() == 0, true, "El largo de la cola es 0.");
		VerificarConjuntos(cola->ObtenerIterador(), elementos.ObtenerIterador(), "Se obtuvo {0} correctamente", "Se esperaba {0}", "No se esperaba {0}");//
	}
}
