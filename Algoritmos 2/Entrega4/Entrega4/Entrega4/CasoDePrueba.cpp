#include "CasoDePrueba.h"
#include "CadenaFuncionHash.h"
#include "FuncionCostoCadenaInt.h"

CasoDePrueba::CasoDePrueba(Puntero<Sistema>(*inicializar)(nat max_ciudades))
{
	this->inicializar = inicializar;
	maxVertices = 20;
}

Puntero<Sistema> CasoDePrueba::InicializarSistema()
{
	Puntero<Sistema> interfaz = inicializar(maxVertices);
	ignorarOK = false;
	return interfaz;
}

Cadena CasoDePrueba::GetNombre()const
{
	return "Casos de Prueba";
}

void CasoDePrueba::CorrerPruebaConcreta()
{
	Prueba1TADGrafo();
	Prueba2TADGrafo();
	Prueba3TADGrafo();
	Prueba4TADGrafo();
	Prueba5TADGrafoA();
	Prueba5TADGrafoB();
	Prueba6TADGrafo();
	Prueba1Ej2();
	Prueba2Ej2();
	Prueba3Ej2();
	Prueba4Ej2();
	Prueba5Ej2();
	Prueba6Ej2();
	Prueba7Ej2();
	Prueba8Ej2();
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
bool CasoDePrueba::MismosElementos(Iterador<T> obtenidos, Iterador<T> esperados) const
{
	T aux;
	
	foreach(T obtenido, obtenidos)
	{
		if (!Pertenece(obtenido, esperados, aux))
		{
			return false;
		}
	}

	foreach(T esperado, esperados)
	{
		if (!Pertenece(esperado, obtenidos, aux))
		{
			return false;
		}
	}

	return true;
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
	Cadena ret = " ({0} - {1}) ";
	return ret.DarFormato(ObtenerTexto(t.Dato1), ObtenerTexto(t.Dato2));
}
Cadena CasoDePrueba::ObtenerTexto(const Tupla<nat, nat>& t) const
{
	Cadena ret = " {0} - {1} ";
	return ret.DarFormato(ObtenerTexto(t.Dato1), ObtenerTexto(t.Dato2));
}
Cadena CasoDePrueba::ObtenerTexto(TipoConexo tipo) const
{
	Cadena retorno = "error";
	switch (tipo)
	{
	case NO_CONEXO:
		retorno = "No Conexo";
		break;
	case DEBILMENTE_CONEXO:
		retorno = "Debilmente Conexo";
		break;
	case FUERTEMENTE_CONEXO:
		retorno = "Fuertemente Conexo";
		break;
	default:
		break;
	}

	return retorno;
}
Cadena CasoDePrueba::ObtenerTexto(Cadena n) const
{
	return n;
}
Cadena CasoDePrueba::ObtenerTexto(int n) const
{
	nat nro = n;
	Cadena ret = ObtenerTexto(nro);
	if (n < 0)
	{
		ret = Cadena("-") + ret;
	}
	return ret;
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
bool CasoDePrueba::SonIguales(const Tupla<Cadena, Cadena>& obtenido, const Tupla<Cadena, Cadena>& esperado) const
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
bool CasoDePrueba::SonIguales(const int obtenido, const int esperado) const
{
	return obtenido == esperado;
}
bool CasoDePrueba::SonIguales(const nat obtenido, const nat esperado) const
{
	return obtenido == esperado;
}
bool CasoDePrueba::SonIguales(const TipoConexo obtenido, const TipoConexo esperado) const
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

Array<Cadena> CasoDePrueba::InicializarGrafoCadenas(Puntero<Grafo<Cadena, int>> grafo) const
{
	// Creamos datos de pruebas en el grafo
	Array<Cadena> ciudades1(5);
	ciudades1[0] = "Montevideo";
	ciudades1[1] = "Maldonado";
	ciudades1[2] = "La Paz";
	ciudades1[3] = "Salto";
	ciudades1[4] = "Durazno";

	foreach (Cadena ciudad, ciudades1.ObtenerIterador())
	{
		grafo->AgregarVertice(ciudad);
	}

	// Cramos aristas de nivel 1
	grafo->AgregarArco(ciudades1[0], ciudades1[1], 10);
	grafo->AgregarArco(ciudades1[0], ciudades1[2], 17);
	grafo->AgregarArco(ciudades1[2], ciudades1[3], 1);
	grafo->AgregarArco(ciudades1[2], ciudades1[4], 3);
	grafo->AgregarArco(ciudades1[3], ciudades1[4], 10);

	return ciudades1;
}

Array<Cadena> CasoDePrueba::InicializarGrafoCadenas2(Puntero<Grafo<Cadena, int>> grafo) const
{
	// Creamos datos de pruebas en el grafo
	Array<Cadena> ciudades1(5);
	ciudades1[0] = "Montevideo";
	ciudades1[1] = "Maldonado";
	ciudades1[2] = "La Paz";
	ciudades1[3] = "Salto";
	ciudades1[4] = "Durazno";

	foreach(Cadena ciudad, ciudades1.ObtenerIterador())
	{
		grafo->AgregarVertice(ciudad);
	}

	// Cramos aristas de nivel 1
	grafo->AgregarArco(ciudades1[0], ciudades1[1], 10);
	grafo->AgregarArco(ciudades1[0], ciudades1[2], 17);
	grafo->AgregarArco(ciudades1[2], ciudades1[3], 1);
	grafo->AgregarArco(ciudades1[2], ciudades1[4], 10);
	grafo->AgregarArco(ciudades1[3], ciudades1[4], 3);

	return ciudades1;
}
//Operacion 1:
void CasoDePrueba::Prueba1TADGrafo()
{
	IniciarSeccion("TAD Grafo");
	Puntero<Sistema> interfaz = InicializarSistema();

	Cadena mensaje = "";
	nat cantidades = 0;

	Tupla<TipoRetorno, Puntero<Grafo<Cadena, int>>> retorno = interfaz->CrearGrafo<Cadena, int>(maxVertices, new CadenaFuncionHash(), Comparador<Cadena>::Default);

	Verificar(retorno.Dato1, OK, "Se crea el grafo.");

	Puntero<Grafo<Cadena, int>> grafo = retorno.Dato2;
	if (grafo == nullptr)
	{
		Verificar(ERROR, OK, "El grafo creado es nulo.");
	}
	else
	{
		IniciarSeccion("Pruebas creacion del grafo", OK);
		Array<Cadena> ciudades = InicializarGrafoCadenas(grafo);
		CerrarSeccion();

		IniciarSeccion("Pruebas Vertices del grafo", OK);

		Verificar(grafo->CantidadVertices(), ciudades.Largo, "Cantidad de vertices esperada '{1}', obtenida '{0}'");
		cantidades = 5;
		Verificar(grafo->CantidadArcos(), cantidades, "Cantidad de arcos esperada '{1}', obtenida '{0}'");

		Cadena existeVertice = "El vertice '{0}' pertenece al grafo.";
		foreach(Cadena ciudad, ciudades.ObtenerIterador())
		{
			if (grafo->ExisteVertice(ciudad))
			{
				Verificar(OK, OK, existeVertice.DarFormato(ciudad));
			}
			else
			{
				Verificar(ERROR, OK, existeVertice.DarFormato(ciudad));
			}
		}

		VerificarConjuntos(grafo->Vertices(), ciudades.ObtenerIterador());

		CerrarSeccion();

		IniciarSeccion("Pruebas Adjacentes", OK);

		Cadena adj = "Cantidad de vertieces adjacentes a '{0}' {1}";
		Cadena aux = "esperado '{1}' obtenido '{0}'";
		cantidades = 2;
		Verificar(grafo->CantidadAdyacentes(ciudades[2]), cantidades, adj.DarFormato(ciudades[2], aux));
		Verificar(grafo->CantidadAdyacentes(ciudades[0]), cantidades, adj.DarFormato(ciudades[0], aux));

		Cadena incidentes = "Cantidad de vertieces incidentes a '{0}' {1}";
		Verificar(grafo->CantidadIncidentes(ciudades[4]), cantidades, incidentes.DarFormato(ciudades[4], aux));

		Array<Cadena> adjacentes(2);
		adjacentes[0] = ciudades[4];
		adjacentes[1] = ciudades[3];

		VerificarConjuntos(grafo->Adyacentes(ciudades[2]), adjacentes.ObtenerIterador());

		VerificarArco(grafo, ciudades[0], ciudades[1], 10);
		VerificarArco(grafo, ciudades[2], ciudades[3], 1);
		VerificarArco(grafo, ciudades[2], ciudades[4], 3);
		VerificarArco(grafo, ciudades[0], ciudades[2], 17);
		CerrarSeccion();
	}

	CerrarSeccion();
}
void CasoDePrueba::VerificarArco(Puntero<Grafo<Cadena, int>> grafo, Cadena origen, Cadena destino, int arcoEsperado)
{
	Cadena existeArco = "Arco entre '{0} -> {1}' {2}";
	Cadena aux = "esperado '{1}' obtenido '{0}'";
	int arco = 0;

	if (grafo->ExisteArco(origen, destino))
	{
		Verificar(OK, OK, existeArco.DarFormato(origen, destino, "existe"));
		arco = grafo->ObtenerArco(origen, destino);
		Verificar(arco, arcoEsperado, existeArco.DarFormato(origen, destino, aux));
	}
	else
	{
		Verificar(ERROR, OK, existeArco.DarFormato(origen, destino, "existe"));
	}
}
void CasoDePrueba::Prueba2TADGrafo()
{
	IniciarSeccion("TAD Grafo - Orden topologico");
	Puntero<Sistema> interfaz = InicializarSistema();
	Cadena mensaje = "";
	nat cantidades = 0;

	ignorarOK = true;
	Tupla<TipoRetorno, Puntero<Grafo<Cadena, int>>> retorno = interfaz->CrearGrafo<Cadena, int>(maxVertices, new CadenaFuncionHash(), Comparador<Cadena>::Default);
	
	
	Puntero<Grafo<Cadena, int>> grafo = retorno.Dato2;
	if (grafo != nullptr)
	{
		Array<Cadena> ciudades = InicializarGrafoCadenas(grafo);
		ignorarOK = false;

		Matriz<bool> precedencias(5);
		precedencias[0][1] = true;
		precedencias[0][2] = true;
		precedencias[2][3] = true;
		precedencias[2][4] = true;
		precedencias[3][4] = true;

		Iterador<Cadena> orden = grafo->OrdenTopologico();
		ComprobarOrdenTopologico(orden, ciudades, precedencias);
	}
	CerrarSeccion();
}
void CasoDePrueba::ComprobarOrdenTopologico(const Iterador<Cadena> &orden, const Array<Cadena> &ciudades, const Matriz<bool> &precedencias)
{
	Array<nat> indices(ciudades.Largo);
	int idx = 0;
	foreach(Cadena ciudad, orden)
	{
		for (nat i = 0; i < indices.Largo; i++)
		{
			if (ciudades[i] == ciudad)
			{
				indices[idx++] = i;
				break;
			}
		}
	}
	Cadena obtenido = "Se obtuvo el orden: '{0}'";

	Verificar(OK, OK, obtenido.DarFormato(ObtenerTexto(orden)));
	
	Cadena hayarco = "Hay un arco entre '{0}'y '{1}'";

	for (nat i = 0; i < indices.Largo; i++)
	{
		for (nat j = i + 1; j < indices.Largo; j++)
		{
			if (precedencias[indices[j]][indices[i]])
			{
				Verificar(ERROR, OK, hayarco.DarFormato(ciudades[indices[j]], ciudades[indices[i]]));				
			}
		}
	}
}
void CasoDePrueba::CheckHayCamino(Puntero<Sistema> interfaz, Puntero<Grafo<Cadena, int>> grafo, Cadena origen, Cadena destino, bool esperado)
{
	Cadena hayCamino = "No hay camino entre el vertice '{0}' y '{1}'";
	if (esperado)
	{
		hayCamino = "Hay camino entre el vertice '{0}' y '{1}'";
	}
	if (esperado == grafo->HayCamino(origen, destino))
	{
		Verificar(OK, OK, hayCamino.DarFormato(origen, destino));
	}
	else
	{
		Verificar(ERROR, OK, hayCamino.DarFormato(origen, destino));
	}
}
void CasoDePrueba::Prueba3TADGrafo()
{
	IniciarSeccion("TAD Grafo - HayCamino");
	Puntero<Sistema> interfaz = InicializarSistema();

	ignorarOK = true;
	Tupla<TipoRetorno, Puntero<Grafo<Cadena, int>>> retorno = interfaz->CrearGrafo<Cadena, int>(maxVertices, new CadenaFuncionHash(), Comparador<Cadena>::Default);

	Puntero<Grafo<Cadena, int>> grafo = retorno.Dato2;
	if (grafo != nullptr)
	{
		Array<Cadena> ciudades = InicializarGrafoCadenas(grafo);
		ignorarOK = false;

		CheckHayCamino(interfaz, grafo, ciudades[0], ciudades[1], true);
		CheckHayCamino(interfaz, grafo, ciudades[1], ciudades[0], false);
		CheckHayCamino(interfaz, grafo, ciudades[0], ciudades[3], true);
		CheckHayCamino(interfaz, grafo, ciudades[0], ciudades[4], true);
		CheckHayCamino(interfaz, grafo, ciudades[3], ciudades[0], false);
	}
	CerrarSeccion();
}
void CasoDePrueba::Prueba4TADGrafo()
{
	IniciarSeccion("TAD Grafo - Es conexo");
	Puntero<Sistema> interfaz = InicializarSistema();

	ignorarOK = true;
	Tupla<TipoRetorno, Puntero<Grafo<Cadena, int>>> retorno = interfaz->CrearGrafo<Cadena, int>(maxVertices, new CadenaFuncionHash(), Comparador<Cadena>::Default);

	Puntero<Grafo<Cadena, int>> grafo = retorno.Dato2;
	if (grafo != nullptr)
	{
		Array<Cadena> ciudades = InicializarGrafoCadenas(grafo);
		ignorarOK = false;

		Cadena mensaje = "Se esperaba un grafo '{1}' y se obtuvo '{0}'";
		Verificar(grafo->EsConexo(), DEBILMENTE_CONEXO, mensaje);

		grafo->AgregarArco(ciudades[1], ciudades[4], 10);
		grafo->AgregarArco(ciudades[4], ciudades[0], 10);

		Verificar(grafo->EsConexo(), FUERTEMENTE_CONEXO, mensaje);

		grafo->AgregarVertice("cadena1");
		grafo->AgregarVertice("cadena2");
		grafo->AgregarArco("cadena2", "cadena1", 10);
		grafo->AgregarArco("cadena1", "cadena2", 10);
		Verificar(grafo->EsConexo(), NO_CONEXO, mensaje);
	}
	CerrarSeccion();
}
void CasoDePrueba::Prueba5TADGrafoA()
{
	IniciarSeccion("TAD Grafo - cubrimiento minimo A");
	Puntero<Sistema> interfaz = InicializarSistema();

	ignorarOK = true;
	Tupla<TipoRetorno, Puntero<Grafo<Cadena, int>>> retorno = interfaz->CrearGrafo<Cadena, int>(maxVertices, new CadenaFuncionHash(), Comparador<Cadena>::Default);

	Puntero<Grafo<Cadena, int>> grafo = retorno.Dato2;
	if (grafo != nullptr)
	{
		Array<Cadena> ciudades = InicializarGrafoCadenas2(grafo);
		ignorarOK = false;

		Iterador<Tupla<Cadena, Cadena>> esperado1;
		Iterador<Tupla<Cadena, Cadena>> esperado2;
		Iterador<Tupla<Cadena, Cadena>> esperado3;

		Iterador<Tupla<Cadena, Cadena>> obtenido;

		Array<Tupla<Cadena, Cadena>> arbol1(4);
		arbol1[0] = Tupla<Cadena, Cadena>(ciudades[0], ciudades[1]);
		arbol1[1] = Tupla<Cadena, Cadena>(ciudades[0], ciudades[2]);
		arbol1[2] = Tupla<Cadena, Cadena>(ciudades[2], ciudades[3]);
		arbol1[3] = Tupla<Cadena, Cadena>(ciudades[2], ciudades[4]);

		Array<Tupla<Cadena, Cadena>> arbol2(4);
		arbol2[0] = Tupla<Cadena, Cadena>(ciudades[0], ciudades[1]);
		arbol2[1] = Tupla<Cadena, Cadena>(ciudades[0], ciudades[2]);
		arbol2[2] = Tupla<Cadena, Cadena>(ciudades[2], ciudades[4]);
		arbol2[3] = Tupla<Cadena, Cadena>(ciudades[4], ciudades[3]);

		Array<Tupla<Cadena, Cadena>> arbol3(4);
		arbol3[0] = Tupla<Cadena, Cadena>(ciudades[0], ciudades[1]);
		arbol3[1] = Tupla<Cadena, Cadena>(ciudades[0], ciudades[2]);
		arbol3[2] = Tupla<Cadena, Cadena>(ciudades[2], ciudades[3]);
		arbol3[3] = Tupla<Cadena, Cadena>(ciudades[3], ciudades[4]);
		
		esperado1 = arbol1.ObtenerIterador();
		esperado2 = arbol2.ObtenerIterador();
		esperado3 = arbol3.ObtenerIterador();

		obtenido = grafo->ArbolCubrimientoMinimo();

		if (MismosElementos(obtenido, esperado1)) 
		{
			VerificarConjuntos(obtenido, esperado1);
		}
		else if (MismosElementos(obtenido, esperado2)) 
		{
			VerificarConjuntos(obtenido, esperado2);
		}
		else if (MismosElementos(obtenido, esperado3)) 
		{
			VerificarConjuntos(obtenido, esperado3);
		}
		else
		{
			VerificarConjuntos(obtenido, esperado1);
		}		
		
	}
	CerrarSeccion();
}

void CasoDePrueba::Prueba5TADGrafoB()
{
	IniciarSeccion("TAD Grafo - cubrimiento minimo B");
	Puntero<Sistema> interfaz = InicializarSistema();

	ignorarOK = true;
	Tupla<TipoRetorno, Puntero<Grafo<Cadena, int>>> retorno = interfaz->CrearGrafo<Cadena, int>(maxVertices, new CadenaFuncionHash(), Comparador<Cadena>::Default);

	Puntero<Grafo<Cadena, int>> grafo = retorno.Dato2;
	if (grafo != nullptr)
	{
		Array<Cadena> ciudades = InicializarGrafoCadenas2(grafo);
		ignorarOK = false;

		Iterador<Tupla<Cadena, Cadena>> esperado;
		Iterador<Tupla<Cadena, Cadena>> obtenido;

		Array<Tupla<Cadena, Cadena>> arbol(4);
		arbol[0] = Tupla<Cadena, Cadena>(ciudades[0], ciudades[1]);
		arbol[1] = Tupla<Cadena, Cadena>(ciudades[0], ciudades[2]);
		arbol[2] = Tupla<Cadena, Cadena>(ciudades[2], ciudades[3]);
		arbol[3] = Tupla<Cadena, Cadena>(ciudades[3], ciudades[4]);

		esperado = arbol.ObtenerIterador();
		obtenido = grafo->ArbolCubrimientoMinimo(FuncionCostoCadenaInt());
			
		VerificarConjuntos(obtenido, esperado);
	}	
	CerrarSeccion();
}

void CasoDePrueba::VerificarComponentes(const Iterador<Iterador<Cadena>> &obtenidos, const Iterador<Iterador<Cadena>> &esperados)
{
	bool verificarCantidad = true;
	nat totalObtenidos = 0;
	Cadena comentarioEncontrado = "Se encontro la componente '{0}'";
	Cadena comentarioSobra = "Sobra la componente '{0}'";
	Cadena comentarioFalta = "Falta la componente '{0}'";

	foreach(Iterador<Cadena> obtenido, obtenidos)
	{
		totalObtenidos++;
		if (Pertenece(obtenido, esperados))
			Verificar(OK, OK, comentarioEncontrado.DarFormato(ObtenerTexto(obtenido)));
		else
		{
			Verificar(ERROR, OK, comentarioSobra.DarFormato(ObtenerTexto(obtenido)));
			verificarCantidad = false;
		}
	}
	nat totalEsperados = 0;

	foreach(Iterador<Cadena> esperado, esperados)
	{
		totalEsperados++;
		if (!Pertenece(esperado, obtenidos))
		{
			Verificar(ERROR, OK, comentarioFalta.DarFormato(ObtenerTexto(esperado)));
			verificarCantidad = false;
		}
	}
	if (verificarCantidad && totalObtenidos != totalEsperados)
		Verificar(ERROR, OK, "Se verifica la cantidad de elementos de los conjuntos");
}
bool CasoDePrueba::Pertenece(const Iterador<Cadena>& dato, const Iterador<Iterador<Cadena>> &iterador) const
{
	foreach(Iterador<Cadena> dato2, iterador)
	{
		if (MismosElementos(dato, dato2))
		{
			return true;
		}
	}
	return false;
}
void CasoDePrueba::Prueba6TADGrafo()
{
	IniciarSeccion("TAD Grafo - componentes conexas");
	Puntero<Sistema> interfaz = InicializarSistema();

	ignorarOK = true;
	Tupla<TipoRetorno, Puntero<Grafo<Cadena, int>>> retorno = interfaz->CrearGrafo<Cadena, int>(maxVertices, new CadenaFuncionHash(), Comparador<Cadena>::Default);

	Puntero<Grafo<Cadena, int>> grafo = retorno.Dato2;
	if (grafo != nullptr)
	{
		Array<Cadena> ciudades = InicializarGrafoCadenas(grafo);
		ignorarOK = false;
		/*
		grafo->AgregarArco(ciudades[0], ciudades[1], 10);
		grafo->AgregarArco(ciudades[0], ciudades[2], 17);
		grafo->AgregarArco(ciudades[2], ciudades[3], 1);
		grafo->AgregarArco(ciudades[2], ciudades[4], 3);
		grafo->AgregarArco(ciudades[3], ciudades[4], 10);
		*/
		
		Iterador<Iterador<Cadena>> obtenido = grafo->ComponentesConexas();
		Array<Iterador<Cadena>> esperado(1);
		esperado[0] = ciudades.ObtenerIterador();

		VerificarComponentes(obtenido, esperado.ObtenerIterador());		
	}
	CerrarSeccion();
}

Array<Cadena> CasoDePrueba::InicializarCiudades1(Puntero<Sistema> interfaz, bool conexiones)
{
	// Creamos datos de pruebas en el grafo
	Array<Cadena> ciudades1(5);
	ciudades1[0] = "Montevideo";
	ciudades1[1] = "Maldonado";
	ciudades1[2] = "La Paz";
	ciudades1[3] = "Salto";
	ciudades1[4] = "Durazno";

	Cadena mensaje = "Se da de alta la ciuadad '{0}'";

	foreach(Cadena ciudad, ciudades1.ObtenerIterador())
	{
		Verificar(interfaz->AltaCiudad(ciudad), OK, mensaje.DarFormato(ciudad));
	}

	if (conexiones)
	{
		// Creamos datos de pruebas en el grafo
		mensaje = "Se da de alta la conexion '{0}-{1}'";
		Verificar(interfaz->AltaConexion(ciudades1[0], ciudades1[1], OMNIBUS, 1000, 100, 10), OK, mensaje.DarFormato(ciudades1[0], ciudades1[1]));
		Verificar(interfaz->AltaConexion(ciudades1[0], ciudades1[2], OMNIBUS, 70, 10, 1), OK, mensaje.DarFormato(ciudades1[0], ciudades1[2]));
		Verificar(interfaz->AltaConexion(ciudades1[2], ciudades1[0], OMNIBUS, 70, 10, 1), OK, mensaje.DarFormato(ciudades1[2], ciudades1[0]));
		Verificar(interfaz->AltaConexion(ciudades1[0], ciudades1[3], AVION, 500, 50, 1), OK, mensaje.DarFormato(ciudades1[0], ciudades1[3]));

		Verificar(interfaz->AltaConexion(ciudades1[2], ciudades1[3], OMNIBUS, 200, 40, 4), OK, mensaje.DarFormato(ciudades1[2], ciudades1[3]));
		Verificar(interfaz->AltaConexion(ciudades1[2], ciudades1[4], OMNIBUS, 100, 20, 8), OK, mensaje.DarFormato(ciudades1[2], ciudades1[4]));
		Verificar(interfaz->AltaConexion(ciudades1[4], ciudades1[3], OMNIBUS, 50, 20, 8), OK, mensaje.DarFormato(ciudades1[4], ciudades1[3]));
		Verificar(interfaz->AltaConexion(ciudades1[3], ciudades1[1], OMNIBUS, 500, 200, 1), OK, mensaje.DarFormato(ciudades1[3], ciudades1[1]));
	}

	return ciudades1;
}
Array<Cadena> CasoDePrueba::InicializarCiudades2(Puntero<Sistema> interfaz, bool conexiones)
{
	// Creamos datos de pruebas en el grafo
	Array<Cadena> ciudades1(3);
	ciudades1[0] = "Gualeguaychu";
	ciudades1[1] = "Mar del Plata";
	ciudades1[2] = "Buenos Aires";

	Cadena mensaje = "Se da de alta la ciuadad '{0}'";

	foreach(Cadena ciudad, ciudades1.ObtenerIterador())
	{
		Verificar(interfaz->AltaCiudad(ciudad), OK, mensaje.DarFormato(ciudad));
	}

	if (conexiones)
	{
		// Creamos datos de pruebas en el grafo
		mensaje = "Se da de alta la conexion '{0}-{1}'";
		//const TipoTransporte &tipo, const nat &costo, const nat &tiempo, const nat &nroParadas);
		Verificar(interfaz->AltaConexion(ciudades1[0], ciudades1[1], OMNIBUS, 100, 110, 8), OK, mensaje.DarFormato(ciudades1[0], ciudades1[1]));
		Verificar(interfaz->AltaConexion(ciudades1[0], ciudades1[2], OMNIBUS, 50, 100, 3), OK, mensaje.DarFormato(ciudades1[0], ciudades1[2]));
		Verificar(interfaz->AltaConexion(ciudades1[1], ciudades1[2], OMNIBUS, 49, 10, 4), OK, mensaje.DarFormato(ciudades1[1], ciudades1[2]));
		Verificar(interfaz->AltaConexion(ciudades1[2], ciudades1[1], OMNIBUS, 49, 10, 4), OK, mensaje.DarFormato(ciudades1[2], ciudades1[1]));
		Verificar(interfaz->AltaConexion(ciudades1[2], ciudades1[0], OMNIBUS, 30, 20, 1), OK, mensaje.DarFormato(ciudades1[2], ciudades1[0]));
	}
	return ciudades1;
}
Array<Cadena> CasoDePrueba::InicializarCiudades3(Puntero<Sistema> interfaz, bool conexiones)
{
	// Creamos datos de pruebas en el grafo
	Array<Cadena> ciudades1(4);
	ciudades1[0] = "San Pablo";
	ciudades1[1] = "Brasilia";
	ciudades1[2] = "Natal";
	ciudades1[3] = "Rio";

	Cadena mensaje = "Se da de alta la ciuadad '{0}'";

	foreach(Cadena ciudad, ciudades1.ObtenerIterador())
	{
		Verificar(interfaz->AltaCiudad(ciudad), OK, mensaje.DarFormato(ciudad));
	}

	if (conexiones)
	{
		// Creamos datos de pruebas en el grafo
		mensaje = "Se da de alta la conexion '{0}-{1}'";
		//const TipoTransporte &tipo, const nat &costo, const nat &tiempo, const nat &nroParadas);
		Verificar(interfaz->AltaConexion(ciudades1[0], ciudades1[1], AVION, 700, 30, 8), OK, mensaje.DarFormato(ciudades1[0], ciudades1[1]));
		Verificar(interfaz->AltaConexion(ciudades1[1], ciudades1[2], AVION, 300, 70, 1), OK, mensaje.DarFormato(ciudades1[1], ciudades1[2]));
		Verificar(interfaz->AltaConexion(ciudades1[2], ciudades1[3], AVION, 5000, 1000, 4), OK, mensaje.DarFormato(ciudades1[2], ciudades1[3]));
		Verificar(interfaz->AltaConexion(ciudades1[3], ciudades1[0], AVION, 3000, 50, 1), OK, mensaje.DarFormato(ciudades1[3], ciudades1[0]));
	}
	return ciudades1;
}
void CasoDePrueba::InicializarConexionesExtra(Puntero<Sistema> interfaz)
{
	Cadena mensaje = "Se da de alta la conexion '{0}-{1}'";

	Verificar(interfaz->AltaConexion("Montevideo", "Buenos Aires", AVION, 1000, 1000, 7), OK, mensaje.DarFormato("Montevideo", "Buenos Aires"));
	Verificar(interfaz->AltaConexion("Salto", "Buenos Aires", AVION, 500, 10, 1), OK, mensaje.DarFormato("Salto", "Buenos Aires"));
	Verificar(interfaz->AltaConexion("Salto", "Gualeguaychu", OMNIBUS, 20, 10, 1), OK, mensaje.DarFormato("Salto", "Gualeguaychu"));

	Verificar(interfaz->AltaConexion("Montevideo", "San Pablo", AVION, 20, 10, 100), OK, mensaje.DarFormato("Montevideo", "San Pablo"));
	Verificar(interfaz->AltaConexion("Maldonado", "Natal", AVION, 20, 10, 1), OK, mensaje.DarFormato("Maldonado", "Natal"));
}
//Ejercicio 2:
void CasoDePrueba::Prueba1Ej2()
{
	IniciarSeccion("Ejercicio Grafo 1 - Creacion");
	Puntero<Sistema> interfaz = InicializarSistema();

	Array<Cadena> ciudades = InicializarCiudades1(interfaz, true);
	InicializarCiudades2(interfaz, true);
	InicializarCiudades3(interfaz, true);
	InicializarConexionesExtra(interfaz);

	Cadena errorCiudad = "La ciudad '{0}' ya existe";
	Verificar(interfaz->AltaCiudad(ciudades[0]), ERROR, errorCiudad.DarFormato(ciudades[0]));
	Verificar(interfaz->AltaCiudad(ciudades[2]), ERROR, errorCiudad.DarFormato(ciudades[2]));	
	Verificar(interfaz->AltaConexion("Roma", ciudades[0], OMNIBUS, 100, 10, 1), ERROR, "No existe ciudad 'Roma'");
	Verificar(interfaz->AltaConexion(ciudades[0], "Roma", OMNIBUS, 100, 10, 1), ERROR, "No existe ciudad 'Roma'");
		
	CerrarSeccion();
}
void CasoDePrueba::VerificarCamino(Tupla<TipoRetorno, Iterador<Cadena>> &obtenido, Tupla<TipoRetorno, Iterador<Cadena>> &esperado, const Cadena &comentario)
{
	if (obtenido.Dato1 == OK && esperado.Dato1 == OK)
	{
		IniciarSeccion(comentario, esperado.Dato1);
		VerificarSecuencias(obtenido.Dato2, esperado.Dato2);
		CerrarSeccion();
	}
	else
		Verificar(obtenido.Dato1, esperado.Dato1, comentario);
}
void CasoDePrueba::Prueba2Ej2()
{
	IniciarSeccion("Ejercicio Grafo 2 - CAmino Mas Barato");
	Puntero<Sistema> interfaz = InicializarSistema();

	//No queremos que cuente los OK pq ya se probaron antes
	ignorarOK = true;
	Array<Cadena> ciudades1 = InicializarCiudades1(interfaz, true);
	ignorarOK = false;

	Cadena comentario = "Se verifica camino mas barato entre '{0}-{1}'";
	Tupla<TipoRetorno, Iterador<Cadena>> obtenido;
	Tupla<TipoRetorno, Iterador<Cadena>> esperado(OK, nullptr);

	Array<Cadena> camino;
		
	camino = Array<Cadena>(4);
	camino[0] = ciudades1[0];
	camino[1] = ciudades1[2];
	camino[2] = ciudades1[4];
	camino[3] = ciudades1[3];

	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMasBarato(ciudades1[0], ciudades1[3]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades1[0], ciudades1[3]));	

	ignorarOK = true;
	Array<Cadena> ciudades2 = InicializarCiudades2(interfaz, true);
	Array<Cadena> ciudades3 = InicializarCiudades3(interfaz, true);
	ignorarOK = false;
	
	//Mismo resultado
	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMasBarato(ciudades1[0], ciudades1[3]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades1[0], ciudades1[3]));
	
	camino = Array<Cadena>(3);
	camino[0] = ciudades2[0];
	camino[1] = ciudades2[2];
	camino[2] = ciudades2[1];	
	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMasBarato(ciudades2[0], ciudades2[1]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades2[0], ciudades2[1]));

	ignorarOK = true;
	InicializarConexionesExtra(interfaz);
	ignorarOK = false;

	camino = Array<Cadena>(4);
	camino[0] = ciudades1[0];
	camino[1] = ciudades1[2];
	camino[2] = ciudades1[4];
	camino[3] = ciudades1[3];

	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMasBarato(ciudades1[0], ciudades1[3]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades1[0], ciudades1[3]));

	camino = Array<Cadena>(3);
	camino[0] = ciudades2[0];
	camino[1] = ciudades2[2];
	camino[2] = ciudades2[1];
	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMasBarato(ciudades2[0], ciudades2[1]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades2[0], ciudades2[1]));

	//Cruzados
	camino = Array<Cadena>(7);
	camino[0] = ciudades1[0];
	camino[1] = ciudades1[2];
	camino[2] = ciudades1[4];
	camino[3] = ciudades1[3];
	camino[4] = ciudades2[0];
	camino[5] = ciudades2[2];
	camino[6] = ciudades2[1];

	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMasBarato(ciudades1[0], ciudades2[1]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades1[0], ciudades2[1]));

	CerrarSeccion();
}
void CasoDePrueba::Prueba3Ej2()
{
	IniciarSeccion("Ejercicio Grafo 2 - CAmino Menor tiempo");
	Puntero<Sistema> interfaz = InicializarSistema();

	//No queremos que cuente los OK pq ya se probaron antes
	ignorarOK = true;
	Array<Cadena> ciudades1 = InicializarCiudades1(interfaz, true);
	ignorarOK = false;

	Cadena comentario = "Se verifica camino de menor tiempo entre '{0}-{1}'";
	Tupla<TipoRetorno, Iterador<Cadena>> obtenido;
	Tupla<TipoRetorno, Iterador<Cadena>> esperado(OK, nullptr);

	Array<Cadena> camino;

	camino = Array<Cadena>(4);
	camino[0] = ciudades1[0];
	camino[1] = ciudades1[2];
	camino[2] = ciudades1[4];
	camino[3] = ciudades1[3];

	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMenorTiempo(ciudades1[0], ciudades1[3]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades1[0], ciudades1[3]));

	ignorarOK = true;
	Array<Cadena> ciudades2 = InicializarCiudades2(interfaz, true);
	Array<Cadena> ciudades3 = InicializarCiudades3(interfaz, true);
	InicializarConexionesExtra(interfaz);
	ignorarOK = false;

	camino = Array<Cadena>(4);
	camino[0] = ciudades1[0];
	camino[1] = ciudades1[2];
	camino[2] = ciudades1[4];
	camino[3] = ciudades1[3];

	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMenorTiempo(ciudades1[0], ciudades1[3]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades1[0], ciudades1[3]));

	//Cruzados
	camino = Array<Cadena>(6);
	camino[0] = ciudades1[0];
	camino[1] = ciudades1[2];
	camino[2] = ciudades1[4];
	camino[3] = ciudades1[3];
	camino[4] = ciudades2[2];
	camino[5] = ciudades2[1];

	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMenorTiempo(ciudades1[0], ciudades2[1]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades1[0], ciudades2[1]));


	//Por mvd hay uno igual tiempo y costo
	camino = Array<Cadena>(3);
	camino[0] = ciudades1[0];
	camino[1] = ciudades1[1];
	camino[2] = ciudades3[2];
	
	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMenorTiempo(ciudades1[0], ciudades3[2]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades1[0], ciudades3[2]));

	CerrarSeccion();
}
void CasoDePrueba::Prueba4Ej2()
{
	IniciarSeccion("Ejercicio Grafo 2 - CAmino Menos ciudades");
	Puntero<Sistema> interfaz = InicializarSistema();

	//No queremos que cuente los OK pq ya se probaron antes
	ignorarOK = true;
	Array<Cadena> ciudades1 = InicializarCiudades1(interfaz, true);
	Array<Cadena> ciudades2 = InicializarCiudades2(interfaz, true);
	Array<Cadena> ciudades3 = InicializarCiudades3(interfaz, true);
	InicializarConexionesExtra(interfaz);
	ignorarOK = false;

	Cadena comentario = "Se verifica camino de menos ciudades entre '{0}-{1}'";
	Tupla<TipoRetorno, Iterador<Cadena>> obtenido;
	Tupla<TipoRetorno, Iterador<Cadena>> esperado(OK, nullptr);

	Array<Cadena> camino;

	camino = Array<Cadena>(2);
	camino[0] = ciudades1[0];
	camino[1] = ciudades1[3];

	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMenosCiudades(ciudades1[0], ciudades1[3]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades1[0], ciudades1[3]));

	camino = Array<Cadena>(3);
	camino[0] = ciudades1[0];
	camino[1] = ciudades1[3];
	camino[2] = ciudades2[0];
	
	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMenosCiudades(ciudades1[0], ciudades2[0]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades1[0], ciudades2[0]));

	camino = Array<Cadena>(3);
	camino[0] = ciudades1[0];
	camino[1] = ciudades1[1];
	camino[2] = ciudades3[2];

	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMenosCiudades(ciudades1[0], ciudades3[2]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades1[0], ciudades3[2]));

	CerrarSeccion();
}
void CasoDePrueba::Prueba5Ej2()
{
	IniciarSeccion("Ejercicio Grafo 2 - CaminoMenosTrayectosOmnibus");
	Puntero<Sistema> interfaz = InicializarSistema();

	//No queremos que cuente los OK pq ya se probaron antes
	ignorarOK = true;
	Array<Cadena> ciudades1 = InicializarCiudades1(interfaz, true);
	Array<Cadena> ciudades2 = InicializarCiudades2(interfaz, true);
	Array<Cadena> ciudades3 = InicializarCiudades3(interfaz, true);
	InicializarConexionesExtra(interfaz);
	ignorarOK = false;

	Cadena comentario = "Se verifica camino de menos trayecto omnibus entre '{0}-{1}'";
	Tupla<TipoRetorno, Iterador<Cadena>> obtenido;
	Tupla<TipoRetorno, Iterador<Cadena>> esperado(OK, nullptr);

	Array<Cadena> camino;

	camino = Array<Cadena>(2);
	camino[0] = ciudades1[0];
	camino[1] = ciudades1[3];

	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMenosTrayectosOmnibus(ciudades1[0], ciudades1[3]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades1[0], ciudades1[3]));

	CerrarSeccion();
}
void CasoDePrueba::Prueba6Ej2()
{
	IniciarSeccion("Ejercicio Grafo 2 - CaminoMenosTrayectosAvion");
	Puntero<Sistema> interfaz = InicializarSistema();

	//No queremos que cuente los OK pq ya se probaron antes
	ignorarOK = true;
	Array<Cadena> ciudades1 = InicializarCiudades1(interfaz, true);
	Array<Cadena> ciudades2 = InicializarCiudades2(interfaz, true);
	Array<Cadena> ciudades3 = InicializarCiudades3(interfaz, true);
	Verificar(interfaz->AltaConexion("Montevideo", "Durazno", OMNIBUS, 10, 10, 7), OK, "Se da de alta un trayecto auxiliar entre Montevideo Durazno");
	InicializarConexionesExtra(interfaz);
	ignorarOK = false;

	Cadena comentario = "Se verifica camino de menos trayecto avion entre '{0}-{1}'";
	Tupla<TipoRetorno, Iterador<Cadena>> obtenido;
	Tupla<TipoRetorno, Iterador<Cadena>> esperado(OK, nullptr);

	Array<Cadena> camino;

	camino = Array<Cadena>(3);
	camino[0] = ciudades1[0];
	camino[1] = ciudades1[4];
	camino[2] = ciudades1[3];

	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMenosTrayectosAvion(ciudades1[0], ciudades1[3]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades1[0], ciudades1[3]));

	camino = Array<Cadena>(2);
	camino[0] = ciudades1[0];
	camino[1] = ciudades3[0];
	

	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMenosTrayectosAvion(ciudades1[0], ciudades3[0]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades1[0], ciudades3[0]));

	CerrarSeccion();
}
void CasoDePrueba::Prueba7Ej2()
{
	IniciarSeccion("Ejercicio Grafo 2 - CaminoMenosParadasIntermedias");
	Puntero<Sistema> interfaz = InicializarSistema();

	//No queremos que cuente los OK pq ya se probaron antes
	ignorarOK = true;
	Array<Cadena> ciudades1 = InicializarCiudades1(interfaz, true);
	Array<Cadena> ciudades2 = InicializarCiudades2(interfaz, true);
	Array<Cadena> ciudades3 = InicializarCiudades3(interfaz, true);
	InicializarConexionesExtra(interfaz);
	ignorarOK = false;

	Cadena comentario = "Se verifica camino de menos paradas intermedias entre '{0}-{1}'";
	Tupla<TipoRetorno, Iterador<Cadena>> obtenido;
	Tupla<TipoRetorno, Iterador<Cadena>> esperado(OK, nullptr);

	Array<Cadena> camino;

	camino = Array<Cadena>(2);
	camino[0] = ciudades1[0];
	camino[1] = ciudades1[3];

	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMenosParadasIntermedias(ciudades1[0], ciudades1[3]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades1[0], ciudades1[3]));

	CerrarSeccion();
}
void CasoDePrueba::Prueba8Ej2()
{
	IniciarSeccion("Ejercicio Grafo 2 - CaminoMasBaratoOminbus");
	Puntero<Sistema> interfaz = InicializarSistema();

	//No queremos que cuente los OK pq ya se probaron antes
	ignorarOK = true;
	Array<Cadena> ciudades1 = InicializarCiudades1(interfaz, true);
	Array<Cadena> ciudades2 = InicializarCiudades2(interfaz, true);
	Array<Cadena> ciudades3 = InicializarCiudades3(interfaz, true);
	InicializarConexionesExtra(interfaz);
	ignorarOK = false;

	Cadena comentario = "Se verifica camino mas barato por omnibus entre '{0}-{1}'";
	Tupla<TipoRetorno, Iterador<Cadena>> obtenido;
	Tupla<TipoRetorno, Iterador<Cadena>> esperado(OK, nullptr);

	Array<Cadena> camino;

	camino = Array<Cadena>(4);
	camino[0] = ciudades1[0];
	camino[1] = ciudades1[2];
	camino[2] = ciudades1[4];
	camino[3] = ciudades1[3];

	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMasBaratoOminbus(ciudades1[0], ciudades1[3]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades1[0], ciudades1[3]));
	
	interfaz->AltaConexion(ciudades1[0], ciudades3[1], OMNIBUS, 420, 1000, 20);

	//Por mvd-mald hay uno igual tiempo y costo
	camino = Array<Cadena>(3);
	camino[0] = ciudades1[0];
	camino[1] = ciudades3[1];
	camino[2] = ciudades3[2];

	esperado.Dato2 = camino.ObtenerIterador();
	obtenido = interfaz->CaminoMasBaratoOminbus(ciudades1[0], ciudades3[2]);
	VerificarCamino(obtenido, esperado, comentario.DarFormato(ciudades1[0], ciudades3[2]));

	CerrarSeccion();
}