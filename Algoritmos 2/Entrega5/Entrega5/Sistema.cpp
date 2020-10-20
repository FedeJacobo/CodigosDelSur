#include "Sistema.h"

Sistema::Sistema()
{

}

void Sistema::TransponerMatriz(Matriz<nat> matriz)
{
	imprimir(matriz);
	TransponerMatrizAux(matriz, 0, 0, matriz.Largo);
	imprimir(matriz);
}

void Sistema::imprimir(Matriz<nat> matriz) {
	cout << "-------------------------------------";
	cout << endl;
	for (nat i = 0; i < matriz.Largo; i++)
	{
		for (nat j = 0; j < matriz.Ancho; j++)
		{
			cout << matriz[i][j];
		}
		cout << endl;
	}
	cout << "-------------------------------------";
	cout << endl;
}

void Sistema::TransponerMatrizAux(Matriz<nat> &matriz, nat desdex, nat desdey, nat n) {
	if (n == 1)return;
	else {
		assert(n % 2 == 0);
		TransponerMatrizAux(matriz, desdex, desdey, n / 2);
		TransponerMatrizAux(matriz, desdex + n / 2, desdey, n / 2);
		TransponerMatrizAux(matriz, desdex, desdey + n / 2, n / 2);
		TransponerMatrizAux(matriz, desdex + n / 2, desdey + n / 2, n / 2);
		Swap(desdex + n / 2, desdey, desdex, desdey + n / 2, n / 2, matriz);
	}
}

void Sistema::Swap(nat x1, nat y1, nat x2, nat y2, nat largo, Matriz<nat> &mat) {
	for (nat i = 0; i < largo; i++) {
		for (nat j = 0; j < largo; j++) {
			nat aux = mat[x1 + i][y1 + j];
			mat[x1 + i][y1 + j] = mat[x2 + i][y2 + j];
			mat[x2 + i][y2 + j] = aux;
		}
	}
}

Array<Puntero<ITira>> Sistema::CalcularSiluetaDeLaCiudad(Array<Puntero<IEdificio>> ciudad)
{
	Array<Tupla<Puntero<ITira>, Puntero<ITira>>> tira = Array<Tupla<Puntero<ITira>, Puntero<ITira>>>(ciudad.ObtenerLargo());
	nat pos = 0;
	for (nat i = 0; i < ciudad.ObtenerLargo(); i++)
	{
		Puntero<ITira> t1 = new Tira(ciudad[i]->ObtenerXInicial(), ciudad[i]->ObtenerAltura());
		Puntero<ITira> t2 = new Tira(ciudad[i]->ObtenerXFinal(), 0);
		Tupla < Puntero<ITira>, Puntero < ITira >> t = Tupla<Puntero<ITira>, Puntero<ITira>>(t1, t2);
		tira[pos] = t;
		pos++;
	}
	return CalcularSiluetaDeLaCiudadAux(tira, 0, tira.ObtenerLargo() - 1);
};

Array<Puntero<ITira>> Sistema::CalcularSiluetaDeLaCiudadAux(Array<Tupla<Puntero<ITira>, Puntero<ITira>>> ciudad, nat izq, nat der) {
	if (izq<der) {
		nat medio = (izq + der) / 2;
		Array<Puntero<ITira>> siluetaIzq = CalcularSiluetaDeLaCiudadAux(ciudad, izq, medio);
		Array<Puntero<ITira>>siluetaDer = CalcularSiluetaDeLaCiudadAux(ciudad, medio + 1, der);
		return Intercalar(siluetaIzq, siluetaDer);
	}
	else {
		assert(izq == der);
		Array<Puntero<ITira>>ret = Array<Puntero<ITira>>(2);
		ret[0] = ciudad[izq].ObtenerDato1();
		ret[1] = ciudad[izq].ObtenerDato2();
		return ret;
	}
	assert(false);
	return NULL;
}

Array<Puntero<ITira>> Sistema::Intercalar(Array<Puntero<ITira>> siluetaIzq, Array<Puntero<ITira>> siluetaDer)
{
	Array<Puntero<ITira>>ret = Array<Puntero<ITira>>(siluetaIzq.ObtenerLargo() + siluetaDer.ObtenerLargo());
	nat h1 = 0;
	nat h2 = 0;
	nat hAnt = 0;
	nat pos1 = 0;
	nat pos2 = 0;
	nat cant = 0;
	while (pos1 != siluetaIzq.ObtenerLargo() && pos2 != siluetaDer.ObtenerLargo())
	{
		if (siluetaIzq[pos1]->ObtenerX() < siluetaDer[pos2]->ObtenerX()) {
			h1 = siluetaIzq[pos1]->ObtenerAltura();
			Agregar(ret, siluetaIzq[pos1]->ObtenerX(), h1 > h2 ? h1 : h2, hAnt, cant);
			pos1++;
		}
		else if (siluetaIzq[pos1]->ObtenerX() > siluetaDer[pos2]->ObtenerX()) {
			h2 = siluetaDer[pos2]->ObtenerAltura();
			Agregar(ret, siluetaDer[pos2]->ObtenerX(), h1 > h2 ? h1 : h2, hAnt, cant);
			pos2++;
		}
		else {
			h1 = siluetaIzq[pos1]->ObtenerAltura();
			h2 = siluetaDer[pos2]->ObtenerAltura();
			Agregar(ret, siluetaDer[pos2]->ObtenerX(), h1 > h2 ? h1 : h2, hAnt, cant);
			pos2++;
			pos1++;
		}
	}
	if (pos1 != siluetaIzq.ObtenerLargo() && pos2 == siluetaDer.ObtenerLargo()) {
		for (nat i = pos1; i < siluetaIzq.ObtenerLargo(); i++)
		{
			h1 = siluetaIzq[i]->ObtenerAltura();
			Agregar(ret, siluetaIzq[i]->ObtenerX(), h1, hAnt, cant);
		}
	}
	else if (pos1 == siluetaIzq.ObtenerLargo() && pos2 != siluetaDer.ObtenerLargo()) {
		for (nat i = pos2; i < siluetaDer.ObtenerLargo(); i++)
		{
			h2 = siluetaDer[i]->ObtenerAltura();
			Agregar(ret, siluetaDer[i]->ObtenerX(), h2, hAnt, cant);
		}
	}
	Array<Puntero<ITira>> filtrado = Filtrar(ret, cant);
	return filtrado;
}


void Sistema::Agregar(Array<Puntero<ITira>>& ret, nat x, nat h, nat & hAnt, nat &cant)
{
	if (h != hAnt) {
		Puntero<ITira>t = new Tira(x, h);
		ret[cant] = t;
		hAnt = h;
		cant++;
	}
}

Array<Puntero<ITira>> Sistema::Filtrar(Array<Puntero<ITira>> a, nat cant)
{
	if (cant == 0) {
		return a;
	}
	Array<Puntero<ITira>>ret = Array<Puntero<ITira>>(cant);
	for (nat i = 0; i < cant; i++)
	{
		ret[i] = a[i];
	}
	return ret;
}

nat Sistema::CalcularCoeficienteBinomial(nat n, nat k)
{
	if (n == k) return 1;
	if (k == 0) return 0;
	Array<nat>ant = Array<nat>(k + 1, 0);
	nat hasta = n;
	ant[0] = 1;
	while (hasta != 0) {
		Array<nat>act = Array<nat>(k + 1);
		for (nat i = 0; i <k + 1; i++)
		{
			if (i == 0) {
				act[i] = 1;
			}
			else {
				act[i] = ant[i - 1] + ant[i];
			}
		}
		hasta--;
		ant = act;
	}
	return ant[k];
};


