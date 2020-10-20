#ifndef GRAFOIMP_CPP
#define GRAFOIMP_CPP
#include "GrafoImp.h"

template <class V, class A>
GrafoImp<V, A>::GrafoImp(nat maxVertices, Puntero<FuncionHash<V>> funcionHash, const Comparador<V>& comp) {
	matAdy = Matriz<Puntero<Nodo<A>>>(maxVertices);
	verticesPos = new TablaHashA<V, int>(maxVertices, funcionHash, comp);
	posVertices = new TablaHashA<int, V>(maxVertices, new IntFuncionHash(), Comparador<int>::Default);
	compV = comp;
	cantV = 0;
	cantA = 0;
	pos = 0;
	max = maxVertices;
	paraUsar = NULL;
	for (nat i = 0; i < maxVertices; i++)
	{
		for (nat j = 0; j < maxVertices; j++)
		{
			matAdy[i][j] = NULL;
		}
	}
}

template <class V, class A>
void GrafoImp<V, A>::AgregarVertice(const V& v) {
	if (paraUsar) {
		int posAux = paraUsar->dato;
		paraUsar = paraUsar->sig;
		verticesPos->Agregar(v, posAux);
		posVertices->Agregar(posAux, v);
	}
	else {
		verticesPos->Agregar(v, pos);
		posVertices->Agregar(pos, v);
		pos++;
		cantV++;
	}
}

template <class V, class A>
void GrafoImp<V, A>::BorrarVertice(const V& v) {
	nat posAux = verticesPos->Obtener(v);
	verticesPos->Borrar(v);
	posVertices->Borrar(pos);
	if (posAux == (pos - 1)) {
		pos--;
	}
	else {
		Puntero<NodoLista<int>> nodo = new NodoLista<int>(posAux, NULL, NULL);
		nodo->sig = paraUsar;
		paraUsar = nodo;
	}
	for (nat i = 1; i < matAdy.Ancho; i++)
	{
		if (matAdy[i][pos]) {
			matAdy[i][pos] = nullptr;
			cantA--;
		}
		if (matAdy[pos][i]) {
			matAdy[pos][i] = nullptr;
			cantA--;
		}
	}
	cantV--;
}

template <class V, class A>
void GrafoImp<V, A>::AgregarArco(const V& v1, const V& v2, const A& arco) {
	int posV1 = verticesPos->Obtener(v1);
	int posV2 = verticesPos->Obtener(v2);
	matAdy[posV1][posV2] = new Nodo<A>(arco);
	cantA++;
}

template <class V, class A>
void GrafoImp<V, A>::BorrarArco(const V& v1, const V& v2) {
	int posV1 = verticesPos->Obtener(v1);
	int posV2 = verticesPos->Obtener(v2);
	matAdy[posV1][posV2] = nullptr;
	cantA--;
}

template <class V, class A>
int GrafoImp<V, A>::ObtenerNumInterno(const V &v) const {
	return verticesPos->Obtener(v);
};

template <class V, class A>
V GrafoImp<V, A>::ObtenerVertice(int num) const {
	return posVertices->Obtener(num);
};

template <class V, class A>
Iterador<V> GrafoImp<V, A>::Vertices() const {
	Array <V> ret = Array <V>(cantV);
	Iterador<Tupla<V, int>> aux = verticesPos->ObtenerIterador();
	int cont = 0;
	while (aux.HayElemento()) {
		ret[cont++] = aux.ElementoActual().ObtenerDato1();
		aux.Avanzar();
	}
	return ret.ObtenerIterador();
}

template <class V, class A>
Iterador<V> GrafoImp<V, A>::Adyacentes(const V& v) const {
	Array <V> aux = Array <V>(cantV);
	nat pos = verticesPos->Obtener(v);
	nat cont = 0;
	for (nat i = 1; i < matAdy.Largo; i++)
	{
		if (matAdy[pos][i]) {
			aux[cont] = posVertices->Obtener(i);
			cont++;
		}
	}
	Array <V> ret = Array <V>(cont);
	for (nat i = 0; i < cont; i++)
	{
		ret[i] = aux[i];
	}
	return ret.ObtenerIterador();
}

template <class V, class A>
Iterador<V> GrafoImp<V, A>::Incidentes(const V& v) const {
	Array <V> aux = Array <V>(cantV);
	nat pos = verticesPos->Obtener(v);
	nat cont = 0;
	for (nat i = 1; i < matAdy.Largo; i++)
	{
		if (matAdy[i][pos]) {
			aux[cont] = posVertices->Obtener(i);
			cont++;
		}
	}
	Array <V> ret = Array <V>(cont);
	for (nat i = 0; i < cont; i++)
	{
		ret[i] = aux[i];
	}
	return ret.ObtenerIterador();
}

template <class V, class A>
const A& GrafoImp<V, A>::ObtenerArco(const V& v1, const V& v2) const {
	int posV1 = verticesPos->Obtener(v1);
	int posV2 = verticesPos->Obtener(v2);
	return matAdy[posV1][posV2]->arco;
}

template <class V, class A>
nat GrafoImp<V, A>::CantidadVertices() const {
	return cantV;
}

template <class V, class A>
nat GrafoImp<V, A>::CantidadArcos() const {
	return cantA;
}

template <class V, class A>
nat GrafoImp<V, A>::CantidadAdyacentes(const V& v) const {
	nat pos = verticesPos->Obtener(v);
	nat ret = 0;
	for (nat i = 1; i < matAdy.Ancho; i++)
	{
		if (matAdy[pos][i]) ret++;
	}
	return ret;
}

template <class V, class A>
nat GrafoImp<V, A>::CantidadIncidentes(const V& v) const {
	nat pos = verticesPos->Obtener(v);
	nat ret = 0;
	for (nat i = 1; i < matAdy.Ancho; i++)
	{
		if (matAdy[i][pos]) ret++;
	}
	return ret;
}

template <class V, class A>
bool GrafoImp<V, A>::ExisteVertice(const V& v) const {
	return verticesPos->EstaDefinida(v);
}

template <class V, class A>
bool GrafoImp<V, A>::ExisteArco(const V& v1, const V& v2) const {
	int posV1 = verticesPos->Obtener(v1);
	int posV2 = verticesPos->Obtener(v2);
	return matAdy[posV1][posV2];
}

template <class V, class A>
bool GrafoImp<V, A>::EstaLleno() const {
	return cantV == max;
}

template <class V, class A>
bool GrafoImp<V, A>::EstaVacio() const {
	return cantV == 0;
}

template <class V, class A>
bool GrafoImp<V, A>::HayCamino(const V& vO, const V& vD) const {
	int posV1 = verticesPos->Obtener(vO);
	int posV2 = verticesPos->Obtener(vD);
	Matriz<bool> wshl = Matriz<bool>(cantV);
	for (nat i = 0; i < cantV; i++)
	{
		for (nat j = 0; j < cantV; j++)
		{
			if (matAdy[i][j]) wshl[i][j] = true;
		}
	}
	wharshall(wshl);
	return wshl[posV1][posV2];
}

template <class V, class A>
void GrafoImp<V, A>::wharshall(Matriz<bool> &a) const{
	for (nat k = 0; k < cantV; k++)
	{
		for (nat i = 0; i < cantV; i++)
		{
			for (nat j = 0; j < cantV; j++)
			{
				a[i][j] = a[i][j] || a[i][k] && a[k][j];
			}
		}
	}
}

template <class V, class A>
TipoConexo GrafoImp<V, A>::EsConexo() const {
	Matriz<bool> wshl = Matriz<bool>(cantV);
	for (nat i = 0; i < cantV; i++)
	{
		for (nat j = 0; j < cantV; j++)
		{
			if (matAdy[i][j]) wshl[i][j] = true;
		}
	}
	wharshall(wshl);
	if (verificarMatrizEnTrue(wshl)) return FUERTEMENTE_CONEXO;
	simetrizarMatriz(wshl);
	wharshall(wshl);
	if (verificarMatrizEnTrue(wshl)) return DEBILMENTE_CONEXO;
	return NO_CONEXO;
}

template <class V, class A>
void GrafoImp<V, A>::simetrizarMatriz(Matriz<bool> &a) const{
	for (nat i = 0; i < cantV; i++)
	{
		for (nat j = 0; j < cantV; j++)
		{
			if (a[i][j] == true) {
				a[j][i] = true;
			}
		}
	}
}

template <class V, class A>
bool GrafoImp<V, A>::verificarMatrizEnTrue(Matriz<bool> a) const{
	for (nat i = 0; i < cantV; i++)
	{
		for (nat j = 0; j < cantV; j++)
		{
			if (!a[i][j]) return false;
		}
	}
	return true;
}

template <class V, class A>
Iterador<V> GrafoImp<V, A>::OrdenTopologico() const {
	Array<V> ret = Array<V>(cantV);
	Array<int> gradosEntrantes = ObtenerArrayGradosEntrantes();
	for (nat i = 0; i < cantV; i++)
	{
		int posVertice = ObtenerVerticeGradoEntranteCero(gradosEntrantes);
		if (posVertice == -1) {
			Array <V> error = Array<V>(0);
			return error.ObtenerIterador();
		}
		ret[i] = posVertices->Obtener(posVertice);
		for (nat j = 0; j < cantV; j++)
		{
			if (matAdy[posVertice][j]) gradosEntrantes[j]--;
		}
	}
	return ret.ObtenerIterador();
}

template <class V, class A>
int GrafoImp<V, A>::ObtenerVerticeGradoEntranteCero(Array<int> gE) const{
	for (nat i = 0; i < gE.Largo; i++)
	{
		if (gE[i] == 0) {
			gE[i] = -1;
			return i;
		}
	}
	return -1;
}

template <class V, class A>
Array<int> GrafoImp<V, A>::ObtenerArrayGradosEntrantes() const{
	Array<int> ret = Array<int>(cantV);
	nat pos = 0;
	for (nat i = 1; i < matAdy.Largo; i++)
	{
		int cont = 0;
		for (nat j = 1; j < matAdy.Largo; j++)
		{
			if (matAdy[i][j]) cont++;
		}
		if (cont != 0) {
			ret[pos] = cont;
			pos++;
		}
	}
	return ret;
}

template <class V, class A>
int GrafoImp<V, A>::gradoEntrada(const V &v) const {
	int cont = 0;
	Iterador<V> vertices = this->Vertices();
	while (vertices.HayElemento()) {
		V w = vertices.ElementoActual();
		Iterador<V> ady = this->Adyacentes(w);
		while (ady.HayElemento()) {
			if (this->compV.SonIguales(ady.ElementoActual(), v)) {
				cont++;
			}
			ady.Avanzar();
		}
		vertices.Avanzar();
	}
	return cont;
}

template <class V, class A>
Iterador<Tupla<V, V>> GrafoImp<V, A>::ArbolCubrimientoMinimo(const FuncionCosto<V, A>& costo = FuncionCosto<V, A>::Default) const {
	Array<Tupla<V, V>> ret = Array<Tupla<V, V>>(1000);
	nat cont = 0;
	Array<bool> vis = Array<bool>(cantV, false);
	vis[0] = true;
	for (nat k = 0; k < cantV; k++)
	{
		V posOrigen = NULL;
		V posDestino = NULL;
		nat min = 9999999;
		for (nat i = 0; i < cantV; i++)
		{
			if (vis[i]) {
				for (nat j = 0; j < cantV; j++)
				{
					V origen = posVertices->Obtener(i);
					V destino = posVertices->Obtener(j);
					if (!vis[j] && matAdy[i][j] && ((costo(origen, destino, (matAdy[i][j])->arco)) < min)) {
						min = costo(origen, destino, (matAdy[i][j])->arco);
						posOrigen = origen;
						posDestino = destino;
					}
				}
			}
		}
		if (min == 9999999) {
			Array<Tupla<V, V>> aux = Array<Tupla<V, V>>(cont);
			for (nat i = 0; i < cont; i++)
			{
				aux[i] = ret[i];
			}
			return aux.ObtenerIterador();
		}
		Tupla<V, V> ag = Tupla<V, V>(posOrigen, posDestino);
		ret[cont++] = ag;
		vis[verticesPos->Obtener(posDestino)] = true;
	}
	Array<Tupla<V, V>> aux = Array<Tupla<V, V>>(cont);
	for (nat i = 0; i < cont; i++)
	{
		aux[i] = ret[i];
	}
	return aux.ObtenerIterador();
}

template <class V, class A>
Iterador<Iterador<V>> GrafoImp<V, A>::ComponentesConexas() const {
	Array<Iterador<V>> aux = Array<Iterador<V>>(cantV);
	nat cont = 0;
	Array<bool> vis = Array<bool>(cantV);
	bool termino = false;
	nat primeroAVis = 0;
	nat cantComp = 0;
	while (!termino) {
		Array<V> verticesAux = Array<V>(cantV);
		nat cuantosV = 0;
		primModificado(cuantosV, vis, primeroAVis, verticesAux);
		Array<V> vertices = Array<V>(cuantosV);
		for (nat i = 0; i < cuantosV; i++)
		{
			vertices[i] = verticesAux[i];
		}
		aux[cont] = vertices.ObtenerIterador();
		cantComp++;
		termino = true;
		for (nat i = 0; i < cantV; i++)
		{
			if (!vis[i])
			{
				primeroAVis = i;
				termino = false;
				break;
			}
		}
	}
	Array<Iterador<V>> ret = Array<Iterador<V>>(cantComp);
	for (nat i = 0; i < cantComp; i++)
	{
		ret[i] = aux[i];
	}
	return ret.ObtenerIterador();
}

template <class V, class A>
void GrafoImp<V, A>::primModificado(nat &cuantosV, Array<bool> &vis, nat primeroAVis, Array<V> &vertices, const FuncionCosto<V, A>& costo = FuncionCosto<V, A>::Default) const{
	nat cont = 0;
	nat pos = 0;
	vis[primeroAVis] = true;
	vertices[pos++] = posVertices->Obtener(primeroAVis);
	cuantosV++;
	for (nat k = 0; k < cantV; k++)
	{
		V posOrigen = NULL;
		V posDestino = NULL;
		nat min = 9999999;
		for (nat i = 0; i < cantV; i++)
		{
			if (vis[i]) {
				for (nat j = 0; j < cantV; j++)
				{
					V origen = posVertices->Obtener(i);
					V destino = posVertices->Obtener(j);
					if (!vis[j] && matAdy[i][j] && (costo(origen, destino, (matAdy[i][j])->arco) < min)) {
						min = costo(origen, destino, (matAdy[i][j])->arco);
						posOrigen = origen;
						posDestino = destino;
					}
				}
			}
		}
		if (min == 9999999) return ;
		vis[verticesPos->Obtener(posDestino)] = true;
		vertices[pos++] = posDestino;
		cuantosV++;
	}
}

template <class V, class A>
Puntero<Grafo<V, A>> GrafoImp<V, A>::Clon() const {
	Puntero<Grafo<V, A>> ret = new GrafoImp<V, A>(max, fHash, compV);
	Iterador<V> iteV = Vertices();
	while (iteV.HayElementos())
	{
		ret->AgregarVertice(iteV.ElementoActual());
		iteV.Avanzar();
	}
	for (nat i = 1; i < cantV; i++)
	{
		for (nat j = 1; j < cantV; j++)
		{
			if (matAdy[i][j]) {
				V v1 = posVertices->Obtener(i);
				V v2 = posVertices->Obtener(j);
				A a = matAdy[i][j]->arco;
				ret->AgregarArco(v1, v2, a);
			}
		}
	}
	return ret;
}

#endif