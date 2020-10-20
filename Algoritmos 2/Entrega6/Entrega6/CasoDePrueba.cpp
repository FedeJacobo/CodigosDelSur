#include "CasoDePrueba.h"

CasoDePrueba::CasoDePrueba(Puntero<ISistema>(*inicializar)())
{
	this->inicializar = inicializar;
}

Puntero<ISistema> CasoDePrueba::InicializarSistema()
{
	Puntero<ISistema> interfaz = inicializar();
	ignorarOK = false;
	return interfaz;
}

Cadena CasoDePrueba::GetNombre()const
{
	return "Casos de Prueba";
}

void CasoDePrueba::CorrerPruebaConcreta()
{
	PruebaLaberinto();
	PruebaViajero();
	PruebaDegustacion();

	PruebaViajero2();
	PruebaProteccionAnimales();
	PruebaQuickSort();
	PruebaCaminoCaballo();
	PruebaOptimizarGranja();
	PruebaInscribirMaterias();
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
bool CasoDePrueba::SonIguales(const Tupla<int, int>& obtenido, const Tupla<int, int>& esperado) const
{
	return (obtenido.ObtenerDato1() == esperado.ObtenerDato1() && obtenido.ObtenerDato2() == esperado.ObtenerDato2());
}
bool CasoDePrueba::SonIguales(const Tupla<nat, nat>& obtenido, const Tupla<nat, nat>& esperado) const
{
	return (obtenido.ObtenerDato1() == esperado.ObtenerDato1() && obtenido.ObtenerDato2() == esperado.ObtenerDato2());
}
bool CasoDePrueba::SonIguales(const Tupla<Cadena, bool>& obtenido, const Tupla<Cadena, bool>& esperado) const
{
	return (obtenido.ObtenerDato1() == esperado.ObtenerDato1() && obtenido.ObtenerDato2() == esperado.ObtenerDato2());
}
bool CasoDePrueba::SonIguales(const nat& obtenido, const nat& esperado) const
{
	return (obtenido == esperado);
}

bool CasoDePrueba::SonIguales(const Puntero<ICiudad>& obtenido, const Puntero<ICiudad>& esperado) const
{
	return obtenido->ObtenerNombre() == esperado->ObtenerNombre() && obtenido->ObtenerNumero() == esperado->ObtenerNumero();
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
Cadena CasoDePrueba::ObtenerTexto(const Tupla<int, int>& t) const
{
	Cadena sep = ",";
	Cadena retorno = ObtenerTexto(t.ObtenerDato1()) + sep + ObtenerTexto(t.ObtenerDato2());
	return retorno;
}
Cadena CasoDePrueba::ObtenerTexto(const Tupla<nat, nat>& t) const
{
	Cadena sep = ",";
	Cadena retorno = ObtenerTexto(t.ObtenerDato1()) + sep + ObtenerTexto(t.ObtenerDato2());
	return retorno;
}
Cadena CasoDePrueba::ObtenerTexto(const Tupla<Cadena, bool>& materia) const
{
	Cadena turno = " - nocturo";
	if (materia.Dato2)
	{
		turno = " - matutino";
	}
	return materia.Dato1 + turno;
}
Cadena CasoDePrueba::ObtenerTexto(const Puntero<ICiudad>& t) const
{
	return t->ObtenerNombre();
}

Cadena CasoDePrueba::ObtenerTexto(nat n) const
{
	char textoE[10];
	_itoa_s(n, textoE, 10);

	Cadena nueva = "{0}";
	return nueva.DarFormato(textoE);

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

template <class T>
bool CasoDePrueba::Pertenece(const T& dato, Iterador<T> iterador, T& encontrado) const
{
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

void CasoDePrueba::VerificarCaminos(const Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>>& obtenido, const Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>>& esperado)
{
	if (obtenido.Dato1 == OK && esperado.Dato1 == OK)
	{
		IniciarSeccion("Caminos Caballo", esperado.Dato1);
		VerificarConjuntos(obtenido.Dato2, esperado.Dato2, "Se obtuvo correctamente {0}", "Falta el Camino {0}", "No se esperaba el camino {0}");
		CerrarSeccion();
	}
	else
		Verificar(obtenido.Dato1, esperado.Dato1, "Caminos Caballo");
}
void CasoDePrueba::VerificarViajero2(const Tupla<TipoRetorno, Iterador<nat>>& obtenido, const Tupla<TipoRetorno, Iterador<nat>>& esperado)
{
	if (obtenido.Dato1 == OK && esperado.Dato1 == OK)
	{
		IniciarSeccion("Viajero 2", esperado.Dato1);
		VerificarSecuencias(obtenido.Dato2, esperado.Dato2, "Se obtuvo ciudad {0}", "Falta ciudad {0}", "No se esperaba ciudad {0}");
		CerrarSeccion();
	}
	else
		Verificar(obtenido.Dato1, esperado.Dato1, "Viajero 2");
}
void CasoDePrueba::VerificarGranja(const Array<Tupla<nat, nat, nat>>& semillas, const Tupla<TipoRetorno, Array<nat>>& esperado, const Tupla<TipoRetorno, Array<nat>>& obtenido, nat maxdinero, nat maxtierra, nat maxagua)
{
	if (obtenido.Dato1 == OK && esperado.Dato1 == OK)
	{
		IniciarSeccion("", esperado.Dato1);
		if (esperado.Dato2.Largo != obtenido.Dato2.Largo)
		{
			Verificar(ERROR, OK, "Se verifica el largo del retorno.");
		}
		else
		{
			//Tupla costo, agua, ganancia
			int sumaEsperada = 0;
			int sumaObtenida = 0;
			nat costo = 0;
			nat agua = 0;
			nat area = 0;

			for (nat i = 0; i < semillas.Largo; i++)
			{
				sumaEsperada += semillas[i].Dato3 * esperado.Dato2[i];
				nat cantS = obtenido.Dato2[i];
				sumaObtenida += semillas[i].Dato3 * cantS;

				area += cantS;
				agua += semillas[i].Dato2 * cantS;
				costo += semillas[i].Dato1 * cantS;
			}
			Verificar(sumaObtenida, sumaEsperada, "Se esperaba una ganancia total de '{1}' y se obtuvo '{0}'");
			Cadena maxError = "Se esperaba '{0}' maximo '{1}' y se obtuvo '{2}'";
			if (area > area)
			{
				Verificar(ERROR, OK, maxError.DarFormato("area", ObtenerTexto(maxtierra), ObtenerTexto(area)));
			}
			if (agua > maxagua)
			{
				Verificar(ERROR, OK, maxError.DarFormato("agua", ObtenerTexto(maxagua), ObtenerTexto(agua)));
			}
			if (costo > maxdinero)
			{
				Verificar(ERROR, OK, maxError.DarFormato("dinero", ObtenerTexto(maxdinero), ObtenerTexto(costo)));
			}
		}
		CerrarSeccion();
	}
	else
		Verificar(obtenido.Dato1, esperado.Dato1, "Proteccion de animales");
}
void CasoDePrueba::VerificarProteccionAnimales(const Array<Accion>& acciones, const Tupla<TipoRetorno, Array<nat>>& esperado, const Tupla<TipoRetorno, Array<nat>>& obtenido, nat maxVeterinarios, nat maxVehiculos, nat maxDinero, nat maxVacunas, nat maxVoluntarios)
{
	if (obtenido.Dato1 == OK && esperado.Dato1 == OK)
	{
		IniciarSeccion("", esperado.Dato1);
		if (esperado.Dato2.Largo != obtenido.Dato2.Largo)
		{
			Verificar(ERROR, OK, "Se verifica el largo del retorno.");
		}
		else
		{
			int sumaEsperada = 0;
			int sumaObtenida = 0;
			nat veterinarios = 0;
			nat vehiculos = 0;
			nat dinero = 0;
			nat vacunas = 0;
			nat voluntarios = 0;

			for (nat i = 0; i < acciones.Largo; i++)
			{
				sumaEsperada += acciones[i].impacto * esperado.Dato2[i];
				nat obtenidoCant = obtenido.Dato2[i];
				sumaObtenida += acciones[i].impacto * obtenidoCant;
				veterinarios += acciones[i].veterinarios * obtenidoCant;
				vehiculos += acciones[i].vehiculos * obtenidoCant;
				dinero += acciones[i].dinero * obtenidoCant;
				vacunas += acciones[i].vacunas * obtenidoCant;
				voluntarios += acciones[i].voluntarios * obtenidoCant;
			}
			Verificar(sumaObtenida, sumaEsperada, "Se esperaba un impacto total de '{1}' y se obtuvo '{0}'");

			Cadena maxError = "Se esperaba '{0}' maximo '{1}' y se obtuvo '{2}'";
			if (veterinarios > maxVeterinarios)
			{
				Verificar(ERROR, OK, maxError.DarFormato("Veterinarios", ObtenerTexto(maxVeterinarios), ObtenerTexto(veterinarios)));
			}
			if (vehiculos > maxVehiculos)
			{
				Verificar(ERROR, OK, maxError.DarFormato("vehiculos", ObtenerTexto(maxVehiculos), ObtenerTexto(vehiculos)));
			}
			if (dinero > maxDinero)
			{
				Verificar(ERROR, OK, maxError.DarFormato("dinero", ObtenerTexto(maxDinero), ObtenerTexto(dinero)));
			}
			if (vacunas > maxVacunas)
			{
				Verificar(ERROR, OK, maxError.DarFormato("vacunas", ObtenerTexto(maxVacunas), ObtenerTexto(vacunas)));
			}
			if (voluntarios > maxVoluntarios)
			{
				Verificar(ERROR, OK, maxError.DarFormato("voluntarios", ObtenerTexto(maxVoluntarios), ObtenerTexto(voluntarios)));
			}
		}
		CerrarSeccion();
	}
	else
		Verificar(obtenido.Dato1, esperado.Dato1, "Proteccion de animales");
}

void CasoDePrueba::VerificarMaterias(const Tupla<TipoRetorno, Iterador<Tupla<Cadena, bool>>>& obtenido, const Tupla<TipoRetorno, Iterador<Tupla<Cadena, bool>>>& esperado)
{
	if (obtenido.Dato1 == OK && esperado.Dato1 == OK)
	{
		IniciarSeccion("Materias", esperado.Dato1);
		VerificarConjuntos(obtenido.Dato2, esperado.Dato2, "Se obtuvo la materia '{0}'", "Falta la materia '{0}'", "No se esperaba la materia '{0}'");
		CerrarSeccion();
	}
	else
		Verificar(obtenido.Dato1, esperado.Dato1, "Materias");
}

void CasoDePrueba::PruebaLaberinto()
{
	IniciarSeccion("Laberinto");
	Puntero<ISistema> interfaz = InicializarSistema();

	Matriz<nat> laberinto = Matriz<nat>(14,9);
	for ( nat i = 0; i < laberinto.Largo; i++)
	{
		for (nat j = 0; j < laberinto.Ancho; j++)
		{
			laberinto[i][j] = 0;
		}
	}
	laberinto[3][1] = 1;
	laberinto[3][2] = 1;
	laberinto[3][3] = 1;
	laberinto[4][1] = 1;
	laberinto[5][1] = 1;
	laberinto[6][1] = 1;
	laberinto[7][1] = 1;
	laberinto[8][1] = 1;
	laberinto[9][1] = 1;
	laberinto[10][1] = 1;
	laberinto[4][3] = 1;
	laberinto[5][3] = 1;
	laberinto[6][3] = 1;
	laberinto[7][3] = 1;
	laberinto[8][3] = 1;
	laberinto[9][3] = 1;
	laberinto[10][3] = 1;
	laberinto[10][2] = 1;
	laberinto[10][4] = 1;
	laberinto[10][5] = 1;
	laberinto[10][6] = 1;
	laberinto[2][3] = 1;
	laberinto[1][3] = 1;
	laberinto[1][4] = 1;
	laberinto[1][5] = 1;
	laberinto[1][6] = 1;
	laberinto[0][6] = 1;
	laberinto[0][7] = 1;
	laberinto[0][8] = 1;
	laberinto[1][8] = 1;
	laberinto[2][8] = 1;
	laberinto[3][8] = 1;
	laberinto[4][8] = 1;
	laberinto[4][7] = 1;
	laberinto[4][6] = 1;
	laberinto[5][6] = 1;
	laberinto[6][6] = 1;
	laberinto[6][5] = 1;
	laberinto[6][4] = 1;
	laberinto[7][7] = 1;
	laberinto[7][8] = 1;
	laberinto[8][7] = 1;
	laberinto[8][8] = 1;

	Array<Tupla<nat,nat>> resultado = Array<Tupla<nat,nat>>(13);
	resultado[0] = Tupla<nat,nat>(3,1);
	resultado[1] = Tupla<nat,nat>(4,1);
	resultado[2] = Tupla<nat,nat>(5,1);
	resultado[3] = Tupla<nat,nat>(6,1);
	resultado[4] = Tupla<nat,nat>(7,1);
	resultado[5] = Tupla<nat,nat>(8,1);
	resultado[6] = Tupla<nat,nat>(9,1);
	resultado[7] = Tupla<nat,nat>(10,1);
	resultado[8] = Tupla<nat,nat>(10,2);
	resultado[9] = Tupla<nat,nat>(10,3);
	resultado[10] = Tupla<nat,nat>(10,4);
	resultado[11] = Tupla<nat,nat>(10,5);
	resultado[12] = Tupla<nat,nat>(10,6);

	Iterador<Tupla<nat,nat>> esperado = resultado.ObtenerIterador();
	Iterador<Tupla<nat,nat>> obtenido = interfaz->Laberinto(Tupla<nat,nat>(3,1),Tupla<nat,nat>(10,6),laberinto);
	VerificarSecuencias(obtenido, esperado,"Se encontró el camino {0} y se esperaba el {1}","Falta el camino {0}","No se esperaba pasar por el camino {0}");

	resultado = Array<Tupla<nat,nat>>(11);
	resultado[0] = Tupla<nat,nat>(3,1);
	resultado[1] = Tupla<nat,nat>(3,2);
	resultado[2] = Tupla<nat,nat>(3,3);
	resultado[3] = Tupla<nat,nat>(4,3);
	resultado[4] = Tupla<nat,nat>(5,3);
	resultado[5] = Tupla<nat,nat>(6,3);
	resultado[6] = Tupla<nat,nat>(6,4);
	resultado[7] = Tupla<nat,nat>(6,5);
	resultado[8] = Tupla<nat,nat>(6,6);
	resultado[9] = Tupla<nat,nat>(5,6);
	resultado[10] = Tupla<nat,nat>(4,6);

	esperado = resultado.ObtenerIterador();
	obtenido = interfaz->Laberinto(Tupla<nat,nat>(3,1),Tupla<nat,nat>(4,6),laberinto);
	VerificarSecuencias(obtenido, esperado,"Se encontró el camino {0} y se esperaba el {1}","Falta el camino {0}","No se esperaba pasar por el camino {0}");

	esperado = NULL;
	obtenido = interfaz->Laberinto(Tupla<nat,nat>(3,1),Tupla<nat,nat>(7,8),laberinto);
	VerificarSecuencias(obtenido, esperado,"Se encontró el camino {0} y se esperaba el {1}","Falta el camino {0}","No se esperaba pasar por el camino {0}");
}

void CasoDePrueba::PruebaViajero()
{
	IniciarSeccion("Viajero");
	Puntero<ISistema> interfaz = InicializarSistema();

	Array<Puntero<ICiudad>> ciudadesDelMapa = Array<Puntero<ICiudad>>(5);
	ciudadesDelMapa[0] = new CiudadMock("Artigas",0);
	ciudadesDelMapa[1] = new CiudadMock("Paysandu",1);
	ciudadesDelMapa[2] = new CiudadMock("Montevideo",2);
	ciudadesDelMapa[3] = new CiudadMock("Salto",3);
	ciudadesDelMapa[4] = new CiudadMock("Punta del Este",4);

	Matriz<nat> mapa = Matriz<nat>(5,5);
	for ( nat i = 0; i < mapa.Largo; i++)
	{
		for (nat j = 0; j < mapa.Ancho; j++)
		{
			mapa[i][j] = 0;
		}
	}

	mapa[0][1] = 20;
	mapa[0][2] = 40;
	mapa[1][2] = 100;
	mapa[2][3] = 190;
	mapa[2][4] = 100;
	mapa[3][0] = 30;
	mapa[4][3] = 50;

	Array<Puntero<ICiudad>> ciudadesPasar = Array<Puntero<ICiudad>>(2); 
	ciudadesPasar[0] = ciudadesDelMapa[0];
	ciudadesPasar[1] = ciudadesDelMapa[3];

	Array<Iterador<Puntero<ICiudad>>> resultados = Array<Iterador<Puntero<ICiudad>>>(1);
	Array<Puntero<ICiudad>> resultado = Array<Puntero<ICiudad>>(4);
	resultado[0] = ciudadesDelMapa[2];
	resultado[1] = ciudadesDelMapa[4];
	resultado[2] = ciudadesDelMapa[3];
	resultado[3] = ciudadesDelMapa[0];

	resultados[0] = resultado.ObtenerIterador();
	
	Iterador<Iterador<Puntero<ICiudad>>> esperado = resultados.ObtenerIterador();
	Iterador<Iterador<Puntero<ICiudad>>> obtenido = interfaz->Viajero(ciudadesDelMapa,mapa,ciudadesDelMapa[2],ciudadesPasar.ObtenerIterador(),255);
	
	VerificarConjuntos(obtenido, esperado,"Se encontró el itinerario {0} y se esperaba el itinerario {1}","Falta el itinerario {0}","No se esperaba encontrar el itinerario {0}");
	
	ciudadesDelMapa = Array<Puntero<ICiudad>>(8);
	ciudadesDelMapa[0] = new CiudadMock("Artigas",0);
	ciudadesDelMapa[1] = new CiudadMock("Paysandu",1);
	ciudadesDelMapa[2] = new CiudadMock("Montevideo",2);
	ciudadesDelMapa[3] = new CiudadMock("Salto",3);
	ciudadesDelMapa[4] = new CiudadMock("Punta del Este",4);
	ciudadesDelMapa[5] = new CiudadMock("Rocha",5);
	ciudadesDelMapa[6] = new CiudadMock("Canelones",6);
	ciudadesDelMapa[7] = new CiudadMock("Fray Bentos",7);

	mapa = Matriz<nat>(8,8);
	for ( nat i = 0; i < mapa.Largo; i++)
	{
		for (nat j = 0; j < mapa.Ancho; j++)
		{
			mapa[i][j] = 0;
		}
	}

	mapa[0][1] = 30;
	mapa[0][4] = 40;
	mapa[0][5] = 35;
	mapa[0][6] = 70;
	mapa[1][5] = 45;
	mapa[1][6] = 20;
	mapa[2][0] = 50;
	mapa[2][3] = 60;
	mapa[3][0] = 20;
	mapa[4][2] = 10;
	mapa[4][3] = 40;
	mapa[4][7] = 30;
	mapa[5][6] = 15;
	mapa[6][4] = 55;
	mapa[7][0] = 90;

	ciudadesPasar = Array<Puntero<ICiudad>>(2); 
	ciudadesPasar[0] = ciudadesDelMapa[0];
	ciudadesPasar[1] = ciudadesDelMapa[6];

	resultados = Array<Iterador<Puntero<ICiudad>>>(4);
	
	Array<Puntero<ICiudad>> resultado1 = Array<Puntero<ICiudad>>(5);
	resultado1[0] = ciudadesDelMapa[4];
	resultado1[1] = ciudadesDelMapa[3];
	resultado1[2] = ciudadesDelMapa[0];
	resultado1[3] = ciudadesDelMapa[5];
	resultado1[4] = ciudadesDelMapa[6];

	Array<Puntero<ICiudad>> resultado2 = Array<Puntero<ICiudad>>(5);
	resultado2[0] = ciudadesDelMapa[4];
	resultado2[1] = ciudadesDelMapa[3];
	resultado2[2] = ciudadesDelMapa[0];
	resultado2[3] = ciudadesDelMapa[1];
	resultado2[4] = ciudadesDelMapa[6];

	Array<Puntero<ICiudad>> resultado3 = Array<Puntero<ICiudad>>(5);
	resultado3[0] = ciudadesDelMapa[4];
	resultado3[1] = ciudadesDelMapa[2];
	resultado3[2] = ciudadesDelMapa[0];
	resultado3[3] = ciudadesDelMapa[5];
	resultado3[4] = ciudadesDelMapa[6];

	Array<Puntero<ICiudad>> resultado4 = Array<Puntero<ICiudad>>(5);
	resultado4[0] = ciudadesDelMapa[4];
	resultado4[1] = ciudadesDelMapa[2];
	resultado4[2] = ciudadesDelMapa[0];
	resultado4[3] = ciudadesDelMapa[1];
	resultado4[4] = ciudadesDelMapa[6];

	resultados[0] = resultado1.ObtenerIterador();
	resultados[1] = resultado2.ObtenerIterador();
	resultados[2] = resultado3.ObtenerIterador();
	resultados[3] = resultado4.ObtenerIterador();
	
	esperado = resultados.ObtenerIterador();
	obtenido = interfaz->Viajero(ciudadesDelMapa,mapa,ciudadesDelMapa[4],ciudadesPasar.ObtenerIterador(),230);
	
	VerificarConjuntos(obtenido, esperado,"Se encontró el itinerario {0} y se esperaba el itinerario {1}","Falta el itinerario {0}","No se esperaba encontrar el itinerario {0}");

	ciudadesDelMapa = Array<Puntero<ICiudad>>(6);
	ciudadesDelMapa[0] = new CiudadMock("Artigas",0);
	ciudadesDelMapa[1] = new CiudadMock("Paysandu",1);
	ciudadesDelMapa[2] = new CiudadMock("Montevideo",2);
	ciudadesDelMapa[3] = new CiudadMock("Salto",3);
	ciudadesDelMapa[4] = new CiudadMock("Punta del Este",4);
	ciudadesDelMapa[5] = new CiudadMock("Rocha",5);

	mapa = Matriz<nat>(6,6);
	for ( nat i = 0; i < mapa.Largo; i++)
	{
		for (nat j = 0; j < mapa.Ancho; j++)
		{
			mapa[i][j] = 0;
		}
	}

	mapa[0][4] = 80;
	mapa[1][2] = 10;
	mapa[2][0] = 40;
	mapa[2][5] = 70;
	mapa[2][3] = 50;
	mapa[3][5] = 20;
	mapa[4][5] = 10;
	mapa[5][2] = 10;
	mapa[5][1] = 20;

	ciudadesPasar = Array<Puntero<ICiudad>>(2); 
	ciudadesPasar[0] = ciudadesDelMapa[2];
	ciudadesPasar[1] = ciudadesDelMapa[5];

	resultados = Array<Iterador<Puntero<ICiudad>>>(1);
	resultado = Array<Puntero<ICiudad>>(3);
	resultado[0] = ciudadesDelMapa[1];
	resultado[1] = ciudadesDelMapa[2];
	resultado[2] = ciudadesDelMapa[5];

	resultados[0] = resultado.ObtenerIterador();
	
	esperado = resultados.ObtenerIterador();
	obtenido = interfaz->Viajero(ciudadesDelMapa,mapa,ciudadesDelMapa[1],ciudadesPasar.ObtenerIterador(),100);
	
	VerificarConjuntos(obtenido, esperado,"Se encontró el itinerario {0} y se esperaba el itinerario {1}","Falta el itinerario {0}","No se esperaba encontrar el itinerario {0}");
	
}


void CasoDePrueba::PruebaDegustacion()
{
	IniciarSeccion("Degustacion");
	Puntero<ISistema> interfaz = InicializarSistema();

	Producto p1(100, 50, 0, 2, 3);
	Producto p2(150, 30, 10, 10, 4);
	Producto p3(170, 150, 25, 3, 5);
	Producto p4(90, 10, 50, 15, 1);
	Producto p5(50, 18, 5, 3, 2);
	Producto p6(80, 10, 1, 4, 2);
	Producto p7(800, 1000, 10, 5, 5);
	Producto p8(5, 250, 0, 3, 2);
	Array<Producto> ps1(6);
	ps1[0] = p1;
	ps1[1] = p2;
	ps1[2] = p3;
	ps1[3] = p4;
	ps1[4] = p5;
	ps1[5] = p6;
	
	//Prueba 1
	Array<nat> obtenido = interfaz->Degustacion(ps1, 5000, 1900, 300);

	int valorMochila = 0;
	for(nat i = 0; i < obtenido.Largo; i ++)
	{
		valorMochila += ps1[i].preferencia * obtenido[i];
	}

	Verificar(valorMochila, 54, "Se obtuvo una suma de preferencias de valor {0} y se esperaba de valor {1}");

	//Prueba 2
	obtenido = interfaz->Degustacion(ps1, 3000, 4000, 3500);

	valorMochila = 0;
	for(nat i = 0; i < obtenido.Largo; i ++)
	{
		valorMochila += ps1[i].preferencia * obtenido[i];
	}

	Verificar(valorMochila, 89, "Se obtuvo una suma de preferencias de valor {0} y se esperaba de valor {1}");

	Array<Producto> ps2(8);
	ps2[0] = p1;
	ps2[1] = p2;
	ps2[2] = p3;
	ps2[3] = p4;
	ps2[4] = p5;
	ps2[5] = p6;
	ps2[6] = p7;
	ps2[7] = p8;

	//Prueba 3
	Array<nat> obtenido2 = interfaz->Degustacion(ps2, 9000, 8000, 5000);

	valorMochila = 0;
	for(nat i = 0; i < obtenido2.Largo; i ++)
	{
		valorMochila += ps2[i].preferencia * obtenido2[i];
	}

	Verificar(valorMochila, 120, "Se obtuvo una suma de preferencias de valor {0} y se esperaba de valor {1}");
}

void CasoDePrueba::PruebaCaminoCaballo()
{
	IniciarSeccion("Ejercicio Camino Caballo");
	Puntero<ISistema> interfaz = InicializarSistema();
	Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>> obtenido;
	Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>> esperado;
	Array<Tupla<int, int>> pasar;
	Array<Tupla<int, int>> noPasar;

	Array<Iterador<Tupla<int, int>>> mejoresCaminos;
	Array<Tupla<int, int>> camino;

	pasar = Array<Tupla<int, int>>(1);
	pasar[0] = Tupla<int, int>(1, 2);

	noPasar = Array<Tupla<int, int>>(2);
	noPasar[0] = Tupla<int, int>(2, 2);
	noPasar[1] = Tupla<int, int>(2, 1);

	obtenido = interfaz->CaminoCaballo(Tupla<int, int>(0, 0), Tupla<int, int>(1, 2), 1, 10, pasar.ObtenerIterador(), noPasar.ObtenerIterador(), 5);
	camino = Array<Tupla<int, int>>(2);
	camino[0] = Tupla<int, int>(0, 0);
	camino[1] = Tupla<int, int>(1, 2);

	mejoresCaminos = Array<Iterador<Tupla<int, int>>>(1);
	mejoresCaminos[0] = camino.ObtenerIterador();

	esperado = Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>>(OK, mejoresCaminos.ObtenerIterador());

	VerificarCaminos(obtenido, esperado);
	
	pasar = Array<Tupla<int, int>>(4);
	pasar[0] = Tupla<int, int>(1, 0);
	pasar[1] = Tupla<int, int>(1, 5);
	pasar[2] = Tupla<int, int>(5, 5);
	pasar[3] = Tupla<int, int>(1, 4);

	noPasar = Array<Tupla<int, int>>(4);
	noPasar[0] = Tupla<int, int>(0, 0);
	noPasar[1] = Tupla<int, int>(1, 1);
	noPasar[2] = Tupla<int, int>(3, 3);
	noPasar[3] = Tupla<int, int>(4, 2);

	obtenido = interfaz->CaminoCaballo(Tupla<int, int>(3, 1), Tupla<int, int>(3, 5), 2, 6, pasar.ObtenerIterador(), noPasar.ObtenerIterador(), 5);

	mejoresCaminos = Array<Iterador<Tupla<int, int>>>(2);

	camino = Array<Tupla<int, int>>(5);
	camino[0] = Tupla<int, int>(3, 1);
	camino[1] = Tupla<int, int>(1, 0);
	camino[2] = Tupla<int, int>(0, 2);
	camino[3] = Tupla<int, int>(1, 4);
	camino[4] = Tupla<int, int>(3, 5);
	mejoresCaminos[0] = camino.ObtenerIterador();

	camino = Array<Tupla<int, int>>(5);
	camino[0] = Tupla<int, int>(3, 1);
	camino[1] = Tupla<int, int>(1, 0);
	camino[2] = Tupla<int, int>(2, 2);
	camino[3] = Tupla<int, int>(1, 4);
	camino[4] = Tupla<int, int>(3, 5);
	mejoresCaminos[1] = camino.ObtenerIterador();

	esperado = Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>>(OK, mejoresCaminos.ObtenerIterador());

	VerificarCaminos(obtenido, esperado);
	CerrarSeccion();
}

void CasoDePrueba::PruebaOptimizarGranja()
{
	IniciarSeccion("Ejercicio Optimizar Granja");
	Puntero<ISistema> interfaz = InicializarSistema();

	Tupla<TipoRetorno, Array<nat>> esperado;
	Tupla<TipoRetorno, Array<nat>> obtenido;
	Array<nat> cantEsperado(5);

	esperado = Tupla<TipoRetorno, Array<nat>>(OK, cantEsperado);
	//Tupla costo, agua, ganancia
	Array<Tupla<nat, nat, nat>> semillas(5);
	semillas[0] = Tupla<nat, nat, nat>(10, 10, 10);
	semillas[1] = Tupla<nat, nat, nat>(10000, 10, 100000);
	semillas[2] = Tupla<nat, nat, nat>(100, 10, 70);
	semillas[3] = Tupla<nat, nat, nat>(10, 15, 9);
	semillas[4] = Tupla<nat, nat, nat>(30, 7, 35);

	//OptimizarGranja(Array<Tupla<nat, nat, nat>>& semillas, nat dinero, nat tierra, nat agua)
	obtenido = interfaz->OptimizarGranja(semillas, 1, 1, 1);
	VerificarGranja(semillas, esperado, obtenido, 1, 1, 1);

	obtenido = interfaz->OptimizarGranja(semillas, 40, 3, 10);
	cantEsperado[4] = 1;
	VerificarGranja(semillas, esperado, obtenido, 40, 3, 10);

	obtenido = interfaz->OptimizarGranja(semillas, 500, 3, 500);
	cantEsperado[4] = 0;
	cantEsperado[2] = 3;
	VerificarGranja(semillas, esperado, obtenido, 500, 3, 500);

	obtenido = interfaz->OptimizarGranja(semillas, 81, 5, 100);
	cantEsperado[0] = 2;
	cantEsperado[2] = 0;
	cantEsperado[4] = 2;
	VerificarGranja(semillas, esperado, obtenido, 100, 5, 100);
	
	obtenido = interfaz->OptimizarGranja(semillas, 499, 5, 210);
	cantEsperado[0] = 0;
	cantEsperado[2] = 4;
	cantEsperado[4] = 1;
	VerificarGranja(semillas, esperado, obtenido, 499, 10, 210);

	CerrarSeccion();
}

void CasoDePrueba::PruebaInscribirMaterias()
{
	IniciarSeccion("Ejercicio Inscribir Materias");
	Puntero<ISistema> interfaz = InicializarSistema();
	Tupla<TipoRetorno, Iterador<Tupla<Cadena, bool>>> obtenido;
	Tupla<TipoRetorno, Iterador<Tupla<Cadena, bool>>> esperado;
	Array<Tupla<Cadena, nat, nat>> matutino;
	Array<Tupla<Cadena, nat, nat>> nocturno;
	Array<Tupla<Cadena, bool>> materias;

	matutino = Array<Tupla<Cadena, nat, nat>>(2);
	matutino[0] = Tupla<Cadena, nat, nat>("Algoritmos", 1000, 7);
	matutino[1] = Tupla<Cadena, nat, nat>("Matematica", 10, 6);

	nocturno = Array<Tupla<Cadena, nat, nat>>(1);
	nocturno[0] = Tupla<Cadena, nat, nat>("Algoritmos", 1000, 7);

	//InscribirMaterias(Iterador<Tupla<Cadena, nat, nat>> matutino, Iterador<Tupla<Cadena, nat, nat>> nocturno, nat horasM, nat horasN)
	obtenido = interfaz->InscribirMaterias(matutino.ObtenerIterador(), nocturno.ObtenerIterador(), 8, 8);
	
	materias = Array<Tupla<Cadena, bool>>(2);
	materias[0] = Tupla<Cadena, bool>("Algoritmos", false);
	materias[1] = Tupla<Cadena, bool>("Matematica", true);
	esperado = Tupla<TipoRetorno, Iterador<Tupla<Cadena, bool>>>(OK, materias.ObtenerIterador());

	VerificarMaterias(obtenido, esperado);	
	CerrarSeccion();
}

void CasoDePrueba::PruebaViajero2()
{
	IniciarSeccion("Ejercicio Viajero2");
	Puntero<ISistema> interfaz = InicializarSistema();
	Tupla<TipoRetorno, Iterador<nat>> obtenido;
	//Tupla representa <costo, distancia, tiempo>
	Tupla<nat, nat, nat> NoHayConexion(0, 0, 0);
	Tupla<nat, nat, nat> Conexion1(1, 1, 1);
	Array<nat> CiudadesPasar;
	Array<nat> CiudadesNoPasar;

	Tupla<TipoRetorno, Iterador<nat>> esperado;
	Array<nat> ciudadesEsperadas;
	Matriz<Tupla<nat, nat, nat>> relacionesCiudades;


	// Prueba 1
	CiudadesPasar = Array<nat>(3);
	CiudadesPasar[0] = 5;
	CiudadesPasar[1] = 0;
	CiudadesPasar[2] = 3;

	CiudadesNoPasar = Array<nat>(1);
	CiudadesNoPasar[0] = 2;

	relacionesCiudades = Matriz<Tupla<nat, nat, nat>>(6);

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			relacionesCiudades[i][j] = NoHayConexion;
		}
	}
	for (int i = 0; i < 6; i++)
	{
		//Conexiones ultra baratas... que no se pueden usar porque la ciudad es prohibida
		relacionesCiudades[i][2] = Conexion1;
		relacionesCiudades[2][i] = Conexion1;
	}

	relacionesCiudades[5][4] = Conexion1;
	relacionesCiudades[4][0] = Conexion1;
	relacionesCiudades[5][0] = Tupla<nat, nat, nat>(1000, 70, 15);

	relacionesCiudades[0][1] = Tupla<nat, nat, nat>(10, 70, 15);
	relacionesCiudades[1][3] = Tupla<nat, nat, nat>(10, 30, 15);
	relacionesCiudades[0][3] = Tupla<nat, nat, nat>(20, 100, 10);

	obtenido = interfaz->Viajero2(relacionesCiudades, CiudadesPasar.ObtenerIterador(), CiudadesNoPasar.ObtenerIterador());

	ciudadesEsperadas = Array<nat>(4);
	ciudadesEsperadas[0] = 5;
	ciudadesEsperadas[1] = 4;
	ciudadesEsperadas[2] = 0;
	ciudadesEsperadas[3] = 3;

	esperado = Tupla<TipoRetorno, Iterador<nat>>(OK, ciudadesEsperadas.ObtenerIterador());

	VerificarViajero2(obtenido, esperado);

	// Prueba 2
	CiudadesPasar = Array<nat>(3);
	CiudadesPasar[0] = 3;
	CiudadesPasar[1] = 5;
	CiudadesPasar[2] = 10;

	CiudadesNoPasar = Array<nat>(3);
	CiudadesNoPasar[0] = 12;
	CiudadesNoPasar[1] = 4;
	CiudadesNoPasar[2] = 11;

	relacionesCiudades = Matriz<Tupla<nat, nat, nat>>(13);
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			relacionesCiudades[i][j] = NoHayConexion;
		}
	}
	for (int i = 0; i < 13; i++)
	{
		//Conexiones ultra baratas... que no se pueden usar porque la ciudad es prohibida
		relacionesCiudades[i][11] = Conexion1;
		relacionesCiudades[11][i] = Conexion1;
	}

	relacionesCiudades[1][12] = Conexion1;
	relacionesCiudades[3][12] = Conexion1;
	relacionesCiudades[5][12] = Conexion1;
	relacionesCiudades[10][12] = Conexion1;
	relacionesCiudades[12][5] = Conexion1;
	relacionesCiudades[12][10] = Conexion1;

	relacionesCiudades[0][5] = Tupla<nat, nat, nat>(20, 20, 20);
	relacionesCiudades[5][0] = Tupla<nat, nat, nat>(10, 10, 10);
	relacionesCiudades[6][0] = Tupla<nat, nat, nat>(30, 30, 30);
	relacionesCiudades[0][10] = Tupla<nat, nat, nat>(1000, 1000, 1000);
	relacionesCiudades[3][1] = Tupla<nat, nat, nat>(2, 2, 10);
	relacionesCiudades[1][4] = Tupla<nat, nat, nat>(3, 3, 10);
	relacionesCiudades[1][9] = Tupla<nat, nat, nat>(4, 3, 10);
	relacionesCiudades[3][2] = Tupla<nat, nat, nat>(40, 40, 40);
	relacionesCiudades[4][2] = Tupla<nat, nat, nat>(3, 3, 10);
	relacionesCiudades[2][5] = Tupla<nat, nat, nat>(20, 20, 10);
	relacionesCiudades[2][6] = Tupla<nat, nat, nat>(20, 30, 30);
	relacionesCiudades[6][2] = Tupla<nat, nat, nat>(20, 30, 30);
	relacionesCiudades[3][6] = Tupla<nat, nat, nat>(20, 120, 120);
	relacionesCiudades[5][6] = Tupla<nat, nat, nat>(15, 30, 70);
	relacionesCiudades[6][7] = Tupla<nat, nat, nat>(15, 13, 7);
	relacionesCiudades[7][8] = Tupla<nat, nat, nat>(20, 30, 20);
	relacionesCiudades[8][10] = Tupla<nat, nat, nat>(30, 20, 30);
	relacionesCiudades[7][9] = Tupla<nat, nat, nat>(30, 20, 30);
	relacionesCiudades[9][10] = Tupla<nat, nat, nat>(20, 30, 200);
	relacionesCiudades[9][7] = Tupla<nat, nat, nat>(15, 13, 7);
	relacionesCiudades[7][10] = Tupla<nat, nat, nat>(50, 50, 50);

	obtenido = interfaz->Viajero2(relacionesCiudades, CiudadesPasar.ObtenerIterador(), CiudadesNoPasar.ObtenerIterador());

	ciudadesEsperadas = Array<nat>(7);
	ciudadesEsperadas[0] = 3;
	ciudadesEsperadas[1] = 6;
	ciudadesEsperadas[2] = 2;
	ciudadesEsperadas[3] = 5;
	ciudadesEsperadas[4] = 6;
	ciudadesEsperadas[5] = 7;
	ciudadesEsperadas[6] = 10;

	esperado = Tupla<TipoRetorno, Iterador<nat>>(OK, ciudadesEsperadas.ObtenerIterador());

	VerificarViajero2(obtenido, esperado);

	CerrarSeccion();
}

void CasoDePrueba::PruebaProteccionAnimales()
{
	IniciarSeccion("Ejercicio Protección Animales");
	Puntero<ISistema> interfaz = InicializarSistema();

	Tupla<TipoRetorno, Array<nat>> esperado;
	Tupla<TipoRetorno, Array<nat>> obtenido;
	Array<nat> cantEsperado(10);
	esperado = Tupla<TipoRetorno, Array<nat>>(OK, cantEsperado);

	Array<Accion> acciones(10);

	acciones[0] = Accion(10, 10, 10, 10, 10, 10);
	acciones[1] = Accion(100000, 100000, 100000, 100000, 100000, INT_MAX); //nunca se puede usar
	acciones[2] = Accion(13, 13, 13, 13, 13, 13);
	acciones[3] = Accion(10, 20, 15, 100, 10, 300);
	acciones[4] = Accion(20, 30, 10, 10, 50, 100);
	acciones[5] = Accion(100, 10, 70, 50, 15, 10);
	acciones[6] = Accion(10, 20, 15, 100, 10, 1);
	acciones[7] = Accion(100, 100, 100, 100, 100, 101);
	acciones[8] = Accion(100, 100, 200, 100, 100, 105);
	acciones[9] = Accion(10, 10, 10, 10, 10, 9);

	//ProteccionAnimales(acciones, maxVeterinarios, maxVehiculos, maxDinero, maxVacunas, maxVoluntarios)

	//No puede realizar ninguna accion
	obtenido = interfaz->ProteccionAnimales(acciones, 1, 1, 1, 1, 1);
	VerificarProteccionAnimales(acciones, esperado, obtenido, 1, 1, 1, 1, 1);

	obtenido = interfaz->ProteccionAnimales(acciones, 10, 10, 10, 10, 10);
	cantEsperado[0] = 1;
	VerificarProteccionAnimales(acciones, esperado, obtenido, 10, 10, 10, 10, 10);

	obtenido = interfaz->ProteccionAnimales(acciones, 110, 110, 110, 110, 110);
	cantEsperado[0] = 0;
	cantEsperado[3] = 1;
	cantEsperado[4] = 1;
	VerificarProteccionAnimales(acciones, esperado, obtenido, 110, 110, 110, 110, 110);

	obtenido = interfaz->ProteccionAnimales(acciones, 110, 110, 110, 99, 110);
	cantEsperado[0] = 1;
	cantEsperado[3] = 0;
	cantEsperado[4] = 2;
	VerificarProteccionAnimales(acciones, esperado, obtenido, 110, 110, 110, 99, 110);

	obtenido = interfaz->ProteccionAnimales(acciones, 110, 110, 110, 299, 110);
	cantEsperado[0] = 4;
	cantEsperado[3] = 2;
	cantEsperado[4] = 1;
	VerificarProteccionAnimales(acciones, esperado, obtenido, 110, 110, 110, 299, 110);

	obtenido = interfaz->ProteccionAnimales(acciones, 113, 113, 113, 299, 113);
	cantEsperado[0] = 3;
	cantEsperado[2] = 1;
	cantEsperado[3] = 2;
	cantEsperado[4] = 1;
	VerificarProteccionAnimales(acciones, esperado, obtenido, 113, 113, 113, 299, 113);

	CerrarSeccion();
}

void CasoDePrueba::PruebaQuickSort()
{
	IniciarSeccion("Ejercicio QuickSort");
	Puntero<ISistema> interfaz = InicializarSistema();
	Array<nat> elementos;
	Array<nat> esperado;
	Array<nat> obtenido;

	elementos = Array<nat>(7);
	elementos[0] = 1;
	elementos[1] = 7;
	elementos[2] = 13;
	elementos[3] = 17;
	elementos[4] = 23;
	elementos[5] = 27;
	elementos[6] = 31;

	esperado = Array<nat>(7);
	Array<nat>::Copiar(elementos, esperado);

	obtenido = interfaz->QuickSort(elementos);
	VerificarSecuencias(obtenido.ObtenerIterador(), esperado.ObtenerIterador(), "Se obtuvo elemento '{0}'", "Falta elemento '{0}'", "No se esperaba elemento '{0}'");

	elementos = Array<nat>(7);
	elementos[0] = 77;
	elementos[1] = 70;
	elementos[2] = 37;
	elementos[3] = 34;
	elementos[4] = 25;
	elementos[5] = 16;
	elementos[6] = 7;

	esperado = Array<nat>(7);
	esperado[6] = 77;
	esperado[5] = 70;
	esperado[4] = 37;
	esperado[3] = 34;
	esperado[2] = 25;
	esperado[1] = 16;
	esperado[0] = 7;

	obtenido = interfaz->QuickSort(elementos);
	VerificarSecuencias(obtenido.ObtenerIterador(), esperado.ObtenerIterador(), "Se obtuvo elemento '{0}'", "Falta elemento '{0}'", "No se esperaba elemento '{0}'");

	elementos = Array<nat>(7);
	elementos[0] = 77;
	elementos[1] = 1;
	elementos[2] = 37;
	elementos[3] = 34;
	elementos[4] = 80;
	elementos[5] = 16;
	elementos[6] = 7;

	esperado = Array<nat>(7);
	esperado[0] = 1;
	esperado[1] = 7;
	esperado[2] = 16;
	esperado[3] = 34;
	esperado[4] = 37;
	esperado[5] = 77;
	esperado[6] = 80;

	obtenido = interfaz->QuickSort(elementos);
	VerificarSecuencias(obtenido.ObtenerIterador(), esperado.ObtenerIterador(), "Se obtuvo elemento '{0}'", "Falta elemento '{0}'", "No se esperaba elemento '{0}'");

	elementos = Array<nat>(1);
	elementos[0] = 111;
	esperado = Array<nat>(1);
	esperado[0] = 111;

	obtenido = interfaz->QuickSort(elementos);
	VerificarSecuencias(obtenido.ObtenerIterador(), esperado.ObtenerIterador(), "Se obtuvo elemento '{0}'", "Falta elemento '{0}'", "No se esperaba elemento '{0}'");

	CerrarSeccion();
}