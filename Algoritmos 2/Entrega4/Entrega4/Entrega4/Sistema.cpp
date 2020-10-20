#ifndef SISTEMA_CPP
#define SISTEMA_CPP

#include "Sistema.h"
#include "ComparacionCosto.h"
#include "ComparacionTiempo.h"
#include "ComparacionAvion.h"
#include "ComparacionCiudades.h"
#include "ComparacionMasBaratoOmnibos.h"
#include "ComparacionOmnibus.h"
#include "ComparacionParadas.h"


Sistema::Sistema(nat MAX_CIUDADES)
{
	Puntero<FuncionHash<Cadena>> fHash = new CadenaFuncionHash();
	grafo = new GrafoImp<Cadena, NodoArco>(MAX_CIUDADES, fHash, Comparador<Cadena>());
}
Sistema::~Sistema()
{
}
TipoRetorno Sistema::AltaCiudad(const Cadena &ciudadNombre)
{
	if (grafo->ExisteVertice(ciudadNombre)) return ERROR;
	grafo->AgregarVertice(ciudadNombre);
	return OK;
}
TipoRetorno Sistema::AltaConexion(const Cadena &ciudadOrigen, const Cadena &ciudadDestino, const TipoTransporte &tipo, const nat &costo, const nat &tiempo, const nat &nroParadas)
{
	if (!grafo->ExisteVertice(ciudadOrigen) || !grafo->ExisteVertice(ciudadDestino) || costo == 0 || tiempo == 0) return ERROR;
	NodoArco ag = NodoArco();
	ag.costo = costo;
	ag.nroParadas = nroParadas;
	ag.tiempo = tiempo;
	ag.tipo = tipo;
	ag.vertices = 1;
	if (tipo == AVION) {
		ag.cantA = 1;
		ag.cantO = 0;
	}
	else {
		ag.cantA = 0;
		ag.cantO = 1;
	}
	grafo->AgregarArco(ciudadOrigen, ciudadDestino, ag);
	return OK;
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMasBarato(const Cadena &ciudadOrigen, const Cadena &ciudadDestino)
{

	Comparador<NodoArco> comp = Comparador<NodoArco>(new ComparacionCosto());
	int posO = grafo->ObtenerNumInterno(ciudadOrigen);
	int posD = grafo->ObtenerNumInterno(ciudadDestino);
	Iterador<Cadena> ret = dijkstra(posO, posD, comp);
	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, ret);
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenorTiempo(const Cadena &ciudadOrigen, const Cadena &ciudadDestino)
{
	
	Comparador<NodoArco> comp = Comparador<NodoArco>(new ComparacionTiempo());
	int posO = grafo->ObtenerNumInterno(ciudadOrigen);
	int posD = grafo->ObtenerNumInterno(ciudadDestino);
	Iterador<Cadena> ret = dijkstra(posO, posD, comp);
	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, ret);
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenosCiudades(const Cadena &ciudadOrigen, const Cadena &ciudadDestino)
{
	Comparador<NodoArco> comp = Comparador<NodoArco>(new ComparacionCiudades());
	int posO = grafo->ObtenerNumInterno(ciudadOrigen);
	int posD = grafo->ObtenerNumInterno(ciudadDestino);
	Iterador<Cadena> ret = dijkstra(posO, posD, comp);
	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, ret);
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenosTrayectosOmnibus(const Cadena &ciudadOrigen, const Cadena &ciudadDestino)
{
	Comparador<NodoArco> comp = Comparador<NodoArco>(new ComparacionOmnibus());
	int posO = grafo->ObtenerNumInterno(ciudadOrigen);
	int posD = grafo->ObtenerNumInterno(ciudadDestino);
	Iterador<Cadena> ret = dijkstra(posO, posD, comp);
	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, ret);
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenosTrayectosAvion(const Cadena &ciudadOrigen, const Cadena &ciudadDestino)
{
	Comparador<NodoArco> comp = Comparador<NodoArco>(new ComparacionAvion());
	int posO = grafo->ObtenerNumInterno(ciudadOrigen);
	int posD = grafo->ObtenerNumInterno(ciudadDestino);
	Iterador<Cadena> ret = dijkstra(posO, posD, comp);
	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, ret);
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenosParadasIntermedias(const Cadena &ciudadOrigen, const Cadena &ciudadDestino)
{
	Comparador<NodoArco> comp = Comparador<NodoArco>(new ComparacionParadas());
	int posO = grafo->ObtenerNumInterno(ciudadOrigen);
	int posD = grafo->ObtenerNumInterno(ciudadDestino);
	Iterador<Cadena> ret = dijkstra(posO, posD, comp);
	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, ret);
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMasBaratoOminbus(const Cadena &ciudadOrigen, const Cadena &ciudadDestino)
{
	Comparador<NodoArco> comp = new ComparacionMasBaratoOmnibus();
	int posO = grafo->ObtenerNumInterno(ciudadOrigen);
	int posD = grafo->ObtenerNumInterno(ciudadDestino);
	Iterador<Cadena> ret = dijkstra(posO, posD, comp);
	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, ret);
}

Iterador<Cadena> Sistema::dijkstra(int posOrigen, int posDestino, Comparador<NodoArco>& comp) const {
	int cantV = grafo->CantidadVertices();
	Array<NodoArco> dist = Array<NodoArco>(cantV);
	Array<int> ant = Array<int>(cantV);
	Array<bool> vis = Array<bool>(cantV);
	NodoArco ini = NodoArco();
	ini.costo = 99999999;
	ini.nroParadas = 99999999;
	ini.tiempo = 99999999;
	ini.cantA = 99999999;
	ini.cantO = 99999999;
	ini.vertices = 99999999;
	for (int i = 0; i < cantV; dist[i] = ini, ant[i] = -1, vis[i] = false, i++);

	dijkstraInterno(posOrigen, dist, ant, vis, comp);

	Array<Cadena> aux = Array<Cadena>(1000);
	int cant = 0;
	int pos = posDestino;
	while (pos >= 0) {
		Cadena c = grafo->ObtenerVertice(pos);
		aux[cant] = c;
		pos = ant[pos];
		cant++;
	}
	int p = 0;
	Array<Cadena> ret = Array<Cadena>(cant);
	for (int i = cant - 1; i >= 0; i--)
	{
		ret[p] = aux[i];
		p++;
	}
	return ret.ObtenerIterador();
}

void Sistema::dijkstraInterno(int posOrigen, Array<NodoArco>& dist, Array<int>& ant, Array<bool>& vis, Comparador<NodoArco>& comp) const {
	// Inicializo el origen
	int cantV = grafo->CantidadVertices();
	dist[posOrigen].costo = 0;
	vis[posOrigen] = true;
	// Seteo distancias del origen a sus adyacentes
	for (int i = 0; i < cantV; i++)
	{
		Cadena or = grafo->ObtenerVertice(posOrigen);
		Cadena dest = grafo->ObtenerVertice(i);
		if (grafo->ExisteArco(or, dest))
		{
			dist[i] = grafo->ObtenerArco(or, dest);
			ant[i] = posOrigen;
		}
	}

	// Comienzo proceso iterativo
	for (int k = 1; k < cantV; k++)
	{
		// Encuentro candidato
		int posMin = -1;
		NodoArco min = NodoArco();
		min.costo = 99999999;
		min.nroParadas = 99999999;
		min.tiempo = 99999999;
		min.cantA = 99999999;
		min.cantO = 99999999;
		min.vertices = 99999999;
		for (int i = 0; i < cantV; i++) {
			if (!vis[i] && comp.EsMenor (dist[i], min))
			{
				min = dist[i];
				posMin = i;
			}
		}
		// Si no hay adyacentes no visitados, me voy
		if (posMin == -1)
			return;

		vis[posMin] = true;

		// Actualizo distancias del candidato (posMin)
		for (int i = 0; i < cantV; i++) {
			Cadena pMin = grafo->ObtenerVertice(posMin);
			Cadena ii = grafo->ObtenerVertice(i);
			if (!vis[i] && grafo->ExisteArco(pMin, ii))
			{
				NodoArco nodoCandidato = NodoArco();
				nodoCandidato.costo = dist[posMin].costo + grafo->ObtenerArco(pMin, ii).costo;
				nodoCandidato.nroParadas = dist[posMin].nroParadas + grafo->ObtenerArco(pMin, ii).nroParadas;
				nodoCandidato.tiempo = dist[posMin].tiempo + grafo->ObtenerArco(pMin, ii).tiempo;
				nodoCandidato.vertices = dist[posMin].vertices + grafo->ObtenerArco(pMin, ii).vertices;
				nodoCandidato.cantA = dist[posMin].cantA + grafo->ObtenerArco(pMin, ii).cantA;
				nodoCandidato.cantO = dist[posMin].cantO + grafo->ObtenerArco(pMin, ii).cantO;
				if (comp.EsMenor (nodoCandidato, dist[i]))
				{
					dist[i] = nodoCandidato;
					ant[i] = posMin;
				}
			}
		}
	}
}
#endif