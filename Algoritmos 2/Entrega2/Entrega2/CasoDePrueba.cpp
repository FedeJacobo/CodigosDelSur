#include "CasoDePrueba.h"

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
	PruebaTablas();
	PruebaAnagramas();
	PruebaEsAVL();
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

Cadena CasoDePrueba::ObtenerTexto(const Tupla<Cadena, Cadena>& t) const
{
	Cadena ret = " {0} - {1} ";
	return ret.DarFormato(t.Dato1, t.Dato2);
}
Cadena CasoDePrueba::ObtenerTexto(const Tupla<nat, nat>& t) const
{
	Cadena ret = " {0} - {1} ";
	return ret.DarFormato(ObtenerTexto(t.Dato1), ObtenerTexto(t.Dato2));
}
Cadena CasoDePrueba::ObtenerTexto(Cadena n) const
{
	return n;
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

bool CasoDePrueba::SonIguales(const Tupla<nat, nat>& obtenido, const Tupla<nat, nat>& esperado) const
{
	return (obtenido.Dato1 == esperado.Dato1 && obtenido.Dato2 == esperado.Dato2) ||
		(obtenido.Dato2 == esperado.Dato1 && obtenido.Dato1 == esperado.Dato2);
}

bool CasoDePrueba::SonIguales(const Tupla<Cadena, Cadena>& obtenido, const Tupla<Cadena, Cadena>& esperado) const
{
	return (obtenido.Dato1 == esperado.Dato1 && obtenido.Dato2 == esperado.Dato2) ||
		(obtenido.Dato2 == esperado.Dato1 && obtenido.Dato1 == esperado.Dato2);
}

bool CasoDePrueba::SonIguales(const bool obtenido, const bool esperado) const
{
	return obtenido == esperado;
}

bool CasoDePrueba::SonIguales(const int obtenido, const int esperado) const
{
	return obtenido == esperado;
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

void CasoDePrueba::PruebaTablas()
{
	IniciarSeccion("Pruebas Tablas Hash");
	Puntero<Sistema> interfaz = InicializarSistema();

	nat cantidadElementosInicial = 10;
	PruebaTabla(interfaz->CrearTablaHashAbierto<Cadena, Cadena>(cantidadElementosInicial, new CadenaFuncionHash(), Comparador<Cadena>::Default), "Prueba Tabla Hash Abierto");
	PruebaTabla(interfaz->CrearTablaHashCerrado<Cadena, Cadena>(cantidadElementosInicial, new CadenaFuncionHash(), Comparador<Cadena>::Default), "Prueba Tabla Hash Cerrado");
	
	CerrarSeccion();
}


void CasoDePrueba::PruebaTabla(Puntero<Tabla<Cadena, Cadena>> hash, Cadena nombreSeccion)
{
	IniciarSeccion(nombreSeccion);
	Verificar(hash != NULL, true, "La tabla no debe ser nula.");
	if (hash != NULL) {
		Verificar(hash->EstaLlena(), false, "La tabla no está llena.");
		Verificar(hash->EstaVacia(), true, "La tabla está vacía.");

		Cadena clave1 = "clave1";
		Cadena valor1 = "value1";
		
		hash->Agregar(clave1, valor1);
		Verificar(hash->Largo() == 1, true, "El largo de la tabla es 1.");
		Verificar(hash->EstaVacia(), false, "La tabla no está vacía.");
		Verificar(hash->EstaDefinida(clave1), true, "clave1 está definida en la tabla.");
		Verificar(hash->Obtener(clave1), valor1, "El valor asociado a clave1 es value1.");
		
		hash->Borrar(clave1);
		Verificar(hash->Largo() == 0, true, "El largo de la tabla es 0.");
		Verificar(hash->EstaVacia(), true, "La tabla está vacía.");
		Verificar(hash->EstaDefinida(clave1), false, "clave1 no está definida en la tabla.");
		
		nat cant = 8;
		Array<Tupla<Cadena, Cadena>> elementos = Array<Tupla<Cadena, Cadena>>(cant);
		elementos[0] = Tupla<Cadena, Cadena>("clave0", "valor0");
		elementos[1] = Tupla<Cadena, Cadena>("clave1", "valor1");
		elementos[2] = Tupla<Cadena, Cadena>("clave2", "valor2");
		elementos[3] = Tupla<Cadena, Cadena>("clave3", "valor3");
		elementos[4] = Tupla<Cadena, Cadena>("clave4", "valor4");
		elementos[5] = Tupla<Cadena, Cadena>("clave5", "valor5");
		elementos[6] = Tupla<Cadena, Cadena>("clave6", "valor6");
		elementos[7] = Tupla<Cadena, Cadena>("clave7", "valor7");

		foreach(auto tupla, elementos.ObtenerIterador())
		{
			hash->Agregar(tupla.Dato1, tupla.Dato2);
		}

		Verificar(hash->Largo() == elementos.Largo, true, "El largo de la tabla es 8.");

		foreach(auto tupla, elementos.ObtenerIterador())
		{
			Verificar(hash->EstaDefinida(tupla.Dato1), true, Cadena("{0} esta definida.").DarFormato(tupla.Dato1));
			Verificar(hash->Obtener(tupla.Dato1), tupla.Dato2, Cadena("El valor asociado a {0} es {1}").DarFormato(tupla.Dato1, tupla.Dato2));
		}

		VerificarConjuntos(hash->ObtenerIterador(), elementos.ObtenerIterador(), "Se obtuvo {0} correctamente", "Se esperaba {0}", "No se esperaba {0}");
		
		elementos = Array<Tupla<Cadena, Cadena>>(0);
		hash->BorrarTodos();
		Verificar(hash->EstaVacia(), true, "La tabla está vacía.");
		Verificar(hash->Largo() == 0, true, "El largo de la tabla es 0.");
		VerificarConjuntos(hash->ObtenerIterador(), elementos.ObtenerIterador(), "Se obtuvo {0} correctamente", "Se esperaba {0}", "No se esperaba {0}");
	}

	CerrarSeccion();
}

void CasoDePrueba::PruebaAnagramas()
{
	IniciarSeccion("Pruebas Anagramas");
	Puntero<Sistema> interfaz = InicializarSistema();

	Array<Cadena> anagramas;
	Array<Cadena> obtenidos;

//+ Prueba 1
	anagramas = Array<Cadena>(2);
	anagramas[0] = "algoritmo";
	anagramas[1] = "logaritmo";

	obtenidos = interfaz->Anagramas("algoritmo");

	IniciarSeccion("Anagramas de algoritmos");
	VerificarConjuntos(obtenidos.ObtenerIterador(), anagramas.ObtenerIterador(), "Se obtuvo {0} y se esperaba {1}", "Se esperaba {0}", "No se esperaba {0}");
	CerrarSeccion();
//- Prueba 1


//+ Prueba 2
	anagramas = Array<Cadena>(5);
	anagramas[0] = "roma";
	anagramas[1] = "amor";
	anagramas[2] = "mora";
	anagramas[3] = "maro";
	anagramas[4] = "ramo";
	
	obtenidos = interfaz->Anagramas("Roma");
	
	IniciarSeccion("Anagramas de Roma");	
	VerificarConjuntos(obtenidos.ObtenerIterador(), anagramas.ObtenerIterador(), "Se obtuvo {0} correctamente", "Se esperaba {0}", "No se esperaba {0}");
	CerrarSeccion();
//- Prueba 2

//+ Prueba 3
	obtenidos = interfaz->Anagramas("rmoa");

	IniciarSeccion("Anagramas de rmoa");
	VerificarConjuntos(obtenidos.ObtenerIterador(), anagramas.ObtenerIterador(), "Se obtuvo {0} correctamente", "Se esperaba {0}", "No se esperaba {0}");
	CerrarSeccion();
//- Prueba 3

//+ Prueba 4: Palabra más anagramas
	anagramas = Array<Cadena>(9);
	anagramas[0] = "trapo";
	anagramas[1] = "rapto";
	anagramas[2] = "porta";
	anagramas[3] = "potra";
	anagramas[4] = "tropa";
	anagramas[5] = "optar";
	anagramas[6] = "parto";
	anagramas[7] = "potar";
	anagramas[8] = "topar";
	obtenidos = interfaz->Anagramas("trapo");

	IniciarSeccion("Anagramas de trapo");
	VerificarConjuntos(obtenidos.ObtenerIterador(), anagramas.ObtenerIterador(), "Se obtuvo {0} correctamente", "Se esperaba {0}", "No se esperaba {0}");
	CerrarSeccion();
//- Prueba 4

//+ Prueba 5
	anagramas = Array<Cadena>(1);
	anagramas[0] = "logos";
	obtenidos = interfaz->Anagramas("logos");

	IniciarSeccion("Anagramas de logos");
	VerificarConjuntos(obtenidos.ObtenerIterador(), anagramas.ObtenerIterador(), "Se obtuvo {0} correctamente", "Se esperaba {0}", "No se esperaba {0}");
	CerrarSeccion();
//- Prueba 5

	obtenidos = interfaz->Anagramas("loosg");

	IniciarSeccion("Anagramas de loosg");
	VerificarConjuntos(obtenidos.ObtenerIterador(), anagramas.ObtenerIterador(), "Se obtuvo {0} correctamente", "Se esperaba {0}", "No se esperaba {0}");
	CerrarSeccion();
//- Prueba 5

//+ Prueba 6
	anagramas = Array<Cadena>(3);
	anagramas[0] = "paleto";
	anagramas[1] = "pelota";
	anagramas[2] = "palote";
	obtenidos = interfaz->Anagramas("pelota");

	IniciarSeccion("Anagramas de pelota");
	VerificarConjuntos(obtenidos.ObtenerIterador(), anagramas.ObtenerIterador(), "Se obtuvo {0} correctamente", "Se esperaba {0}", "No se esperaba {0}");
	CerrarSeccion();
//- Prueba 6

//+ Prueba 7
	anagramas = Array<Cadena>(5);
	anagramas[0] = "estor";
	anagramas[1] = "estro";
	anagramas[2] = "resto";
	anagramas[3] = "terso";
	anagramas[4] = "toser";
	obtenidos = interfaz->Anagramas("resto");

	IniciarSeccion("Anagramas de resto");
	VerificarConjuntos(obtenidos.ObtenerIterador(), anagramas.ObtenerIterador(), "Se obtuvo {0} correctamente", "Se esperaba {0}", "No se esperaba {0}");
	CerrarSeccion();
//- Prueba 7

//+ Prueba 8
	anagramas = Array<Cadena>(8);
	anagramas[0] = "arrate";
	anagramas[1] = "artera";
	anagramas[2] = "atraer";
	anagramas[3] = "errata";
	anagramas[4] = "etarra";
	anagramas[5] = "ratear";
	anagramas[6] = "ratera";
	anagramas[7] = "reatar";
	obtenidos = interfaz->Anagramas("atraer");

	IniciarSeccion("Anagramas de atraer");
	VerificarConjuntos(obtenidos.ObtenerIterador(), anagramas.ObtenerIterador(), "Se obtuvo {0} correctamente", "Se esperaba {0}", "No se esperaba {0}");
	CerrarSeccion();
//- Prueba 8	
		
//+ Prueba 9
	anagramas = Array<Cadena>(7);
	anagramas[0] = "acerbo";
	anagramas[1] = "barceo";
	anagramas[2] = "bocear";
	anagramas[3] = "bocera";
	anagramas[4] = "braceo";
	anagramas[5] = "cabero";
	anagramas[6] = "cabreo";
	obtenidos = interfaz->Anagramas("acerbo");

	IniciarSeccion("Anagramas de acerbo");
	VerificarConjuntos(obtenidos.ObtenerIterador(), anagramas.ObtenerIterador(), "Se obtuvo {0} correctamente", "Se esperaba {0}", "No se esperaba {0}");
	CerrarSeccion();
//- Prueba 9

//+ Prueba 10
	anagramas = Array<Cadena>(1);
	anagramas[0] = "universidad";
	obtenidos = interfaz->Anagramas("universidad");

	IniciarSeccion("Anagramas de universidad");
	VerificarConjuntos(obtenidos.ObtenerIterador(), anagramas.ObtenerIterador(), "Se obtuvo {0} correctamente", "Se esperaba {0}", "No se esperaba {0}");
	CerrarSeccion();
//- Prueba 10

	CerrarSeccion();
}



Array<Puntero<NodoArbol<int>>> CasoDePrueba::CrearArbolPrueba(int nroPrueba) const
{
	Array<Puntero<NodoArbol<int>>> retorno;

	if (nroPrueba == 0)
	{
		retorno = Array<Puntero<NodoArbol<int>>>(3);
	} 
	else if (nroPrueba == 1)
	{
		retorno = Array<Puntero<NodoArbol<int>>>(7);
	}
	else if (nroPrueba == 2)
	{
		retorno = Array<Puntero<NodoArbol<int>>>(13);
	}

	for (nat i = 0; i < retorno.Largo; i++)
	{
		retorno[i] = new NodoArbol<int>();
		retorno[i]->der = nullptr;
		retorno[i]->izq = nullptr;
	}
	
	retorno[0]->dato = 60;
	retorno[1]->dato = 84;
	retorno[2]->dato = 36;

	retorno[0]->der = retorno[1];
	retorno[0]->izq = retorno[2];

	if (nroPrueba > 0)
	{
		retorno[3]->dato = 75;
		retorno[4]->dato = 93;
		retorno[5]->dato = 81;
		retorno[6]->dato = 51;

		retorno[1]->izq = retorno[3];
		retorno[1]->der = retorno[4];
		retorno[3]->der = retorno[5];
		retorno[2]->der = retorno[6];
	}
	if (nroPrueba > 1)
	{
		retorno[7]->dato = 21;
		retorno[8]->dato = 30;		
		retorno[9]->dato = 27;
		retorno[10]->dato = 45;
		retorno[11]->dato = 57;
		retorno[12]->dato = 12;

		retorno[2]->izq = retorno[7];
		retorno[7]->der = retorno[8];
		retorno[8]->izq = retorno[9];
		retorno[6]->izq = retorno[10];
		retorno[6]->der = retorno[11];
		retorno[7]->izq = retorno[12];
	}
	return retorno;
}

void CasoDePrueba::PruebaEsAVL()
{
	IniciarSeccion("Pruebas EsAVL");
	Puntero<Sistema> interfaz = InicializarSistema();
	Cadena textoEsAvl = "El parametro es un AVL";
	Cadena textoNoAvl = "El parametro no es un AVL";

	Puntero<NodoArbol<int>> pNodo = new NodoArbol<int>();
	pNodo->dato = 1;
	Verificar(interfaz->EsAVL<int>(pNodo, Comparador<int>::Default), true, textoEsAvl);


	Array<Puntero<NodoArbol<int>>> nodos = CrearArbolPrueba(0);
	Verificar(interfaz->EsAVL<int>(nodos[0], Comparador<int>::Default), true, textoEsAvl);
	
	nodos = CrearArbolPrueba(1);
	Verificar(interfaz->EsAVL<int>(nodos[0], Comparador<int>::Default), true, textoEsAvl);

	nodos = CrearArbolPrueba(2);
	Verificar(interfaz->EsAVL<int>(nodos[0], Comparador<int>::Default), true, textoEsAvl);
	
	nodos = CrearArbolPrueba(2);
	nodos[3]->dato = 58;
	Verificar(interfaz->EsAVL<int>(nodos[0], Comparador<int>::Default), false, textoNoAvl);

	nodos = CrearArbolPrueba(2);
	nodos[9]->dato = 100;
	Verificar(interfaz->EsAVL<int>(nodos[0], Comparador<int>::Default), false, textoNoAvl);

	nodos = CrearArbolPrueba(2);
	nodos[3]->der = nullptr; 
	Verificar(interfaz->EsAVL<int>(nodos[0], Comparador<int>::Default), false, textoNoAvl);

	nodos = CrearArbolPrueba(2);
	nodos[7]->izq = nullptr;
	Verificar(interfaz->EsAVL<int>(nodos[0], Comparador<int>::Default), false, textoNoAvl);

	CerrarSeccion();
}