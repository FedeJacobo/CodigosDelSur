#ifndef GRAFOIMP_H
#define GRAFOIMP_H

#include "Grafo.h"

template <class V, class A>
class GrafoImp : public Grafo<V, A>
{
private:
	Matriz<Puntero<Nodo<A>>> matAdy;
	Puntero<Tabla<V, int>> verticesPos;
	Puntero<Tabla<int, V>> posVertices;
	Puntero<FuncionHash<V>> fHash;
	Puntero<FuncionHash<int>> fHashInt;
	Comparador<V> compV;
	Comparador<int> compInt;
	nat cantV;
	nat cantA;
	nat max;
	nat pos;
	Puntero<NodoLista<int>> paraUsar;

	//metodos
	void wharshall(Matriz<bool> &A) const;
	bool verificarMatrizEnTrue(Matriz<bool> a) const;
	void simetrizarMatriz(Matriz<bool> &a) const;
	Array<int> ObtenerArrayGradosEntrantes() const;
	int ObtenerVerticeGradoEntranteCero(Array<int> gE) const;
	int gradoEntrada(const V &v) const;
	void primModificado(nat &cuantosV, Array<bool> &vis, nat primeroAVis, Array<V> &vertices, const FuncionCosto<V, A>& costo = FuncionCosto<V, A>::Default) const;

public:
	GrafoImp(nat maxVertices, Puntero<FuncionHash<V>> funcionHash, const Comparador<V>& comp);

	~GrafoImp() {}

	// CONSTRUCTORAS
	void AgregarVertice(const V& v);

	void BorrarVertice(const V& v);

	void AgregarArco(const V& v1, const V& v2, const A& arco);

	void BorrarArco(const V& v1, const V& v2);

	//Operaciones agregadas
	int ObtenerNumInterno(const V &v) const;

	V ObtenerVertice(int num) const;

	// SELECTORAS y PREDICADOS

	Iterador<V> Vertices() const;

	Iterador<V> Adyacentes(const V& v) const;

	Iterador<V> Incidentes(const V& v) const;

	const A& ObtenerArco(const V& v1, const V& v2) const;

	nat CantidadVertices() const;

	nat CantidadArcos() const;

	nat CantidadAdyacentes(const V& v) const;

	nat CantidadIncidentes(const V& v) const;

	bool ExisteVertice(const V& v) const;

	bool ExisteArco(const V& v1, const V& v2) const;

	bool EstaLleno() const;

	bool EstaVacio() const;

	bool HayCamino(const V& vO, const V& vD) const;

	TipoConexo EsConexo() const;
	
	Iterador<V> OrdenTopologico() const;

	Iterador<Tupla<V, V>> ArbolCubrimientoMinimo(const FuncionCosto<V, A>& costo = FuncionCosto<V, A>::Default) const;

	Iterador<Iterador<V>> ComponentesConexas() const;

	Puntero<Grafo<V, A>> Clon() const;
};
#include "GrafoImp.cpp"
#endif
