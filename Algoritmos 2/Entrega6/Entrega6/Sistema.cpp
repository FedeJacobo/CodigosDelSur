#include "Sistema.h"

Sistema::Sistema()
{

}

Iterador<Iterador<Puntero<ICiudad>>> Sistema::Viajero(Array<Puntero<ICiudad>> &ciudadesDelMapa, Matriz<nat> &mapa, Puntero<ICiudad> &ciudadPartida, Iterador<Puntero<ICiudad>> &ciudadesPasar, nat costoMax)
{
	/*Array<Puntero<ICiudad>> caminoA = Array<Puntero<ICiudad>>(ciudadesDelMapa.Largo);
	Array<Puntero<ICiudad>> caminoO = Array<Puntero<ICiudad>>(ciudadesDelMapa.Largo);
	int cantCiudadesA = 0;
	int cantCiudadesO = 1000000;*/
	return NULL;
}

Iterador<Tupla<nat, nat>> Sistema::Laberinto(Tupla<nat, nat> &inicio, Tupla<nat, nat> &fin, Matriz<nat> &laberinto)
{
	Array<Tupla<nat, nat>> caminoRet = Array<Tupla<nat, nat>>(laberinto.Largo * laberinto.Ancho, Tupla<nat, nat>(-1, -1));
	Array<Tupla<nat, nat>> caminoAux = Array<Tupla<nat, nat>>(laberinto.Largo * laberinto.Ancho, Tupla<nat, nat>(-1, -1));
	Matriz<bool> vis = Matriz<bool>(laberinto.Largo, laberinto.Ancho);
	char dir = '-';
	int cant = 0;
	int cambiosO = 10000000;
	int numPasosO = 10000000;
	laberintosAux(inicio, fin, laberinto, dir, 0, cambiosO, caminoRet, caminoAux, cant, numPasosO, vis);
	if (numPasosO == 10000000) {
		return  Iterador<Tupla<nat, nat>>();
	}
	Array<Tupla<nat, nat>> ret = Array<Tupla<nat, nat>>(numPasosO);
	for (int i = 0; i < numPasosO; i++)
	{
		ret[i] = caminoRet[i];
	}
	return ret.ObtenerIterador();
}

void Sistema::laberintosAux(Tupla<nat, nat> pos, Tupla<nat, nat> fin, Matriz<nat> mat, char dir, int cambiosDirAct, int &cambiosDirOpt, Array<Tupla<nat, nat>> &ret, Array<Tupla<nat, nat>> caminoAux, int cantElem, int &cantElemO, Matriz<bool> vis) {
	nat posI = pos.ObtenerDato1();
	nat posJ = pos.ObtenerDato2();
	if (cambiosDirAct <= cambiosDirOpt) {
		if (esPosValida(posI, posJ, mat)) {
			if (!Pase(pos, caminoAux, cantElem)) {
				if (mat[posI][posJ] == 1) {
					caminoAux[cantElem] = pos;
					if (pos == fin) {
						Copiar(caminoAux, ret);
						cambiosDirOpt = cambiosDirAct;
						cantElemO = cantElem;
					}
					if (dir == 'L') {
						laberintosAux(Tupla<nat, nat>(posI + 1, posJ), fin, mat, 'U', cambiosDirAct + 1, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
						laberintosAux(Tupla<nat, nat>(posI, posJ + 1), fin, mat, 'L', cambiosDirAct, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
						laberintosAux(Tupla<nat, nat>(posI, posJ - 1), fin, mat, 'R', cambiosDirAct, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
						laberintosAux(Tupla<nat, nat>(posI - 1, posJ), fin, mat, 'D', cambiosDirAct + 1, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
					}
					else if (dir == 'R') {
						laberintosAux(Tupla<nat, nat>(posI + 1, posJ), fin, mat, 'U', cambiosDirAct + 1, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
						laberintosAux(Tupla<nat, nat>(posI, posJ - 1), fin, mat, 'R', cambiosDirAct, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
						laberintosAux(Tupla<nat, nat>(posI, posJ + 1), fin, mat, 'L', cambiosDirAct, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
						laberintosAux(Tupla<nat, nat>(posI - 1, posJ), fin, mat, 'D', cambiosDirAct + 1, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
					}
					else if (dir == 'U') {
						laberintosAux(Tupla<nat, nat>(posI + 1, posJ), fin, mat, 'U', cambiosDirAct, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
						laberintosAux(Tupla<nat, nat>(posI - 1, posJ), fin, mat, 'D', cambiosDirAct, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
						laberintosAux(Tupla<nat, nat>(posI, posJ + 1), fin, mat, 'L', cambiosDirAct + 1, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
						laberintosAux(Tupla<nat, nat>(posI, posJ - 1), fin, mat, 'R', cambiosDirAct + 1, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
					}
					else if (dir == 'D') {
						laberintosAux(Tupla<nat, nat>(posI - 1, posJ), fin, mat, 'D', cambiosDirAct, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
						laberintosAux(Tupla<nat, nat>(posI + 1, posJ), fin, mat, 'U', cambiosDirAct, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
						laberintosAux(Tupla<nat, nat>(posI, posJ + 1), fin, mat, 'L', cambiosDirAct + 1, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
						laberintosAux(Tupla<nat, nat>(posI, posJ - 1), fin, mat, 'R', cambiosDirAct + 1, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
					}
					else {
						laberintosAux(Tupla<nat, nat>(posI - 1, posJ), fin, mat, 'D', cambiosDirAct + 1, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
						laberintosAux(Tupla<nat, nat>(posI, posJ + 1), fin, mat, 'L', cambiosDirAct + 1, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
						laberintosAux(Tupla<nat, nat>(posI, posJ - 1), fin, mat, 'R', cambiosDirAct + 1, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
						laberintosAux(Tupla<nat, nat>(posI + 1, posJ), fin, mat, 'D', cambiosDirAct + 1, cambiosDirOpt, ret, caminoAux, cantElem + 1, cantElemO, vis);
					}
				}
			}
		}
	}
}

bool Sistema::Pase(Tupla<nat, nat> pos, Array<Tupla<nat, nat>>caminoA, nat nroPasosA) {
	for (nat i = 0; i < nroPasosA; i++)
	{
		nat xa = caminoA[i].ObtenerDato1();
		nat ya = caminoA[i].ObtenerDato2();
		if (xa == pos.ObtenerDato1() && ya == pos.ObtenerDato2()) {
			return true;
		}
	}
	return false;
}

void Sistema::Copiar(Array<Tupla<nat, nat>>caminoA, Array<Tupla<nat, nat>>&caminoO) {
	for (nat i = 0; i < caminoA.ObtenerLargo(); i++)
	{
		caminoO[i] = caminoA[i];
	}
}

bool Sistema::esPosValida(nat i, nat j, Matriz<nat> &mat) {
	return i < mat.Largo && i >= 0 && j < mat.Ancho && j >= 0;
}

Array<nat> Sistema::Degustacion(Array<Producto> productos, nat maxDinero, nat maxCalorias, nat maxAlcohol)
{
	Array<nat> solA = Array<nat>(productos.Largo);
	Array<nat> solO = Array<nat>(productos.Largo);
	int d = maxDinero;
	int c = maxCalorias;
	int a = maxAlcohol;
	int valA = 0;
	int valO = -9999999;
	mochilaDegustacion(productos, 0, solA, solO, d, c, a, valA, valO);
	return solO;
}

void Sistema::mochilaDegustacion(Array<Producto> prod, nat objAct, Array<nat> solA, Array<nat> &solO, int maxDinero, int maxCalorias, int maxAlcohol, int valA, int &valO) {
	if (objAct == solA.ObtenerLargo()) {
		if (valA > valO) {
			copiar(solA, solO);
			valO = valA;
		}
	}
	else {
		for (nat i = 0; i <= prod[objAct].maxUnidades; i++)
		{
			int c = maxCalorias - (i*prod[objAct].calorias);
			int d = maxDinero - (i*prod[objAct].precio);
			int a = maxAlcohol - (i*prod[objAct].alcohol);
			if (c >= 0 && d >= 0 && a >= 0)
			{
				solA[objAct] = i;
				int preferencia =  valA + (i*prod[objAct].preferencia);
				mochilaDegustacion(prod, objAct + 1, solA, solO, d, c, a, preferencia, valO);
			}
		}
	}
}

void Sistema::copiar(Array<nat> solucionA, Array<nat>& solucionO) {
	for (nat i = 0; i < solucionA.ObtenerLargo(); i++)
	{
		solucionO[i] = solucionA[i];
	}
}

Tupla<TipoRetorno, Iterador<nat>> Sistema::Viajero2(Matriz<Tupla<nat, nat, nat>> relacionesCiudades, Iterador<nat> CiudadesPasar, Iterador<nat> CiudadesNoPasar)
{
	//Implementar.

	return Tupla<TipoRetorno, Iterador<nat>>();
}

Tupla<TipoRetorno, Array<nat>> Sistema::ProteccionAnimales(Array<Accion> acciones, nat maxVeterinarios, nat maxVehiculos, nat maxDinero, nat maxVacunas, nat maxVoluntarios)
{
	Array<nat> accionesA = Array<nat>(acciones.Largo);
	Array<nat> accionesO = Array<nat>(acciones.Largo, 0);
	int impactoA = 0;
	int impactoO = -99999;
	int accionA = 0;
	ProteccionAnimalesAux(acciones, accionA, accionesA, accionesO, impactoA, impactoO, maxVeterinarios, maxVehiculos, maxDinero, maxVacunas, maxVoluntarios);
	return Tupla<TipoRetorno, Array<nat>>(OK, accionesO);
}

void Sistema::ProteccionAnimalesAux(Array<Accion> acciones, int accionA, Array<nat> accionesA, Array<nat> &accionesO, int impactoA, int &impactoO, int maxVeterinarios, int maxVehiculos, int maxDinero, int maxVacunas, int maxVoluntarios) {
	if (accionA == acciones.Largo) {
		if (impactoA > impactoO)
		{
			copiar(accionesA, accionesO);
			impactoO = impactoA;
		}
	}
	else {
		bool listo = false;
		for (int i = 0; !listo; i++)
		{
			int maxVet = maxVeterinarios - i*acciones[accionA].veterinarios;
			int maxVeh = maxVehiculos - i*acciones[accionA].vehiculos;
			int maxD = maxDinero - i*acciones[accionA].dinero;
			int maxVac = maxVacunas - i*acciones[accionA].vacunas;
			int maxVol = maxVoluntarios - i*acciones[accionA].voluntarios;
			if (maxVet >= 0 && maxVeh >= 0 && maxD >= 0 && maxVac >= 0 && maxVol >= 0)
			{
				accionesA[accionA] = i;
				int imp = impactoA + i*acciones[accionA].impacto;
				ProteccionAnimalesAux(acciones, accionA + 1, accionesA, accionesO, imp, impactoO, maxVet, maxVeh, maxD, maxVac, maxVol);
			}
			else {
				listo = true;
			}
		}
	}
}

Array<nat> Sistema::QuickSort(Array<nat> elementos)
{
	quicksortAux(elementos, 0, elementos.ObtenerLargo() - 1);
	return elementos;
}

void Sistema::quicksortAux(Array<nat>&elem, int izq, int der) {
	nat pivote = elem[izq];
	int i = izq;
	int j = der;
	nat auxIntercambio;
	while (i < j) {
		while (elem[i] <= pivote && i < j) {
			i++;
		}
		while (elem[j] > pivote) {
			j--;
		}
		if (i < j) {
			auxIntercambio = elem[i];
			elem[i] = elem[j];
			elem[j] = auxIntercambio;
		}
	}
	elem[izq] = elem[j];
	elem[j] = pivote;
	if (izq < j - 1) {
		quicksortAux(elem, izq, j - 1);
	}
	if (j + 1 < der) {
		quicksortAux(elem, j + 1, der);
	}
}

Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>> Sistema::CaminoCaballo(Tupla<int, int>& salida, Tupla<int, int>& destino, nat cantAPasar, nat tamTablero, Iterador<Tupla<int, int>>& pasar, Iterador<Tupla<int, int>>& noPasar, nat cantMaxAPasarPorCualquierCasilla)
{
	return Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>>();
	Array<Tupla<int, int>> caminoA = Array<Tupla<int, int>>(tamTablero * tamTablero);
	Array<Tupla<int, int>> caminoO = Array<Tupla<int, int>>(tamTablero * tamTablero);
	int cantPasosA = 0;
	int cantPasosO = 100000;
	Matriz<int> tablero = Matriz<int>(tamTablero, tamTablero);
	Matriz<int> cantPasadas = Matriz<int>(tamTablero, tamTablero);
	for (nat i = 0; i < tamTablero; i++)
	{
		for (nat j = 0; j < tamTablero; j++)
		{
			cantPasadas[i][j] = 0;
			bool pas = false;
			bool noPas = false;
			while (pasar.HayElemento())
			{
				if (pasar.ElementoActual().ObtenerDato1() == i && pasar.ElementoActual().ObtenerDato2() == j) pas = true;
				pasar.Avanzar();
			}
			while (noPasar.HayElemento())
			{
				if (noPasar.ElementoActual().ObtenerDato1() == i && noPasar.ElementoActual().ObtenerDato2() == j) noPas = true;
				noPasar.Avanzar();
			}
			if (pas) tablero[i][j] = 1;
			else if (noPas) tablero[i][j] = -1;
			else tablero[i][j] = 0;
		}
	}
	Array<Iterador<Tupla<int, int>>> aux = Array<Iterador<Tupla<int, int>>>(1000);
	CaminoCaballoAux(salida, destino, caminoA, caminoO, cantPasosA, cantPasosO, tablero, cantPasadas, cantAPasar, 0, aux);
	Array<Iterador<Tupla<int, int>>> ret = Array<Iterador<Tupla<int, int>>>(cantPasosO);
	for (int i = 0; i < cantPasosO; i++)
	{
		ret[i] = aux[i];
	}
	return Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>>(OK, ret.ObtenerIterador());
}

void Sistema::CaminoCaballoAux(Tupla<int, int> salida, Tupla<int, int> destino, Array<Tupla<int, int>> caminoA, Array<Tupla<int, int>> &caminoO, int cantPasosA, int &cantPasosO, Matriz<int> tablero, Matriz<int> cantPasadas, int cantAPasar, int pos, Array<Iterador<Tupla<int, int>>> &ret) {
	int iniI = salida.ObtenerDato1();
	int iniJ = salida.ObtenerDato2();
	if (cantPasosO >= cantPasosA) {
		if (esPosValidaInt(iniI, iniJ, tablero)) {
			if (cantPasadas[iniI][iniJ] == 0 || tablero[iniI][iniJ] == 1) {
				if (tablero[iniI][iniJ] != -1)
				{
					caminoA[cantPasosA] = Tupla<int, int>(iniI, iniJ);
					if ((tablero[iniI][iniJ] == 0 && cantPasadas[iniI][iniJ] == 0) || tablero[iniI][iniJ] == 1) cantAPasar--;
					cantPasadas[iniI][iniJ]++;
					if (salida == destino) {
						if (cantPasosA == cantPasosO) {
							for (nat i = 0; i < caminoA.Largo; i++)
							{
								caminoO[i] = caminoA[i];
							}
							cantPasosO = cantPasosA;
							ret[pos++] = caminoO.ObtenerIterador();
						}
						else {
							cantPasosO = cantPasosA;
							for (nat i = 0; i < caminoA.Largo; i++)
							{
								caminoO[i] = caminoA[i];
							}
							cantPasosO = cantPasosA;
							pos = 0;
							ret[pos++] = caminoO.ObtenerIterador();
						}

					}
					else {
						CaminoCaballoAux(Tupla<int, int>(iniI + 2, iniJ - 1), destino, caminoA, caminoO, cantPasosA + 1, cantPasosO, tablero, cantPasadas, cantAPasar, pos, ret);
						CaminoCaballoAux(Tupla<int, int>(iniI + 2, iniJ + 1), destino, caminoA, caminoO, cantPasosA + 1, cantPasosO, tablero, cantPasadas, cantAPasar, pos, ret);
						CaminoCaballoAux(Tupla<int, int>(iniI - 2, iniJ + 1), destino, caminoA, caminoO, cantPasosA + 1, cantPasosO, tablero, cantPasadas, cantAPasar, pos, ret);
						CaminoCaballoAux(Tupla<int, int>(iniI - 2, iniJ - 1), destino, caminoA, caminoO, cantPasosA + 1, cantPasosO, tablero, cantPasadas, cantAPasar, pos, ret);
						CaminoCaballoAux(Tupla<int, int>(iniI + 1, iniJ + 1), destino, caminoA, caminoO, cantPasosA + 1, cantPasosO, tablero, cantPasadas, cantAPasar, pos, ret);
						CaminoCaballoAux(Tupla<int, int>(iniI - 1, iniJ + 2), destino, caminoA, caminoO, cantPasosA + 1, cantPasosO, tablero, cantPasadas, cantAPasar, pos, ret);
						CaminoCaballoAux(Tupla<int, int>(iniI + 1, iniJ - 1), destino, caminoA, caminoO, cantPasosA + 1, cantPasosO, tablero, cantPasadas, cantAPasar, pos, ret);
						CaminoCaballoAux(Tupla<int, int>(iniI - 1, iniJ - 2), destino, caminoA, caminoO, cantPasosA + 1, cantPasosO, tablero, cantPasadas, cantAPasar, pos, ret);
					}
				}
			}
		}
	}
}


bool Sistema::esPosValidaInt(nat i, nat j, Matriz<int> &mat) {
	return i < mat.Largo && i >= 0 && j < mat.Ancho && j >= 0;
}

Tupla<TipoRetorno, Array<nat>> Sistema::OptimizarGranja(Array<Tupla<nat, nat, nat>>& semillas, nat dinero, nat tierra, nat agua)
{
	
	Array<nat> solucionA = Array<nat>(semillas.ObtenerLargo());
	Array<nat> solucionO = Array<nat>(semillas.ObtenerLargo());
	int gananciaA = 0;
	int gananciaO = -99999;
	mochilaGranja(0, gananciaA, gananciaO, solucionA, solucionO, semillas, dinero, tierra, agua);

	return Tupla<TipoRetorno, Array<nat>>(OK, solucionO);
}

void Sistema::mochilaGranja(int especieActual, int gananciaA, int &gananciaO, Array<nat> solucionA, Array<nat> &solucionO, Array<Tupla<nat, nat, nat>>& semillas, int dinero, int tierra, int agua) {
	if (especieActual == semillas.Largo) {
		if (gananciaA > gananciaO) {
			gananciaO = gananciaA;
			for (nat i = 0; i < solucionO.Largo; i++) {
				solucionO[i] = solucionA[i];
			}
		}
	}
	else {
		bool salgo = true;
		for (int k = 0; salgo; k++)
		{
			int dineroFin = dinero - k*(semillas[especieActual].ObtenerDato1());
			int tierraFin = tierra - k;
			int aguaFin = agua - (k*semillas[especieActual].ObtenerDato2());
			if(dineroFin >= 0 && tierraFin >= 0 && aguaFin >= 0)
			{
								int gananciaAFin = gananciaA + semillas[especieActual].ObtenerDato3()*k;
				solucionA[especieActual] = k;
				mochilaGranja(especieActual + 1, gananciaAFin, gananciaO, solucionA, solucionO, semillas, dineroFin, tierraFin, aguaFin);
			}
			else salgo = false;
		}
	}
}


Tupla<TipoRetorno, Iterador<Tupla<Cadena, bool>>> Sistema::InscribirMaterias(Iterador<Tupla<Cadena, nat, nat>> matutino, Iterador<Tupla<Cadena, nat, nat>> nocturno, nat horasM, nat horasN)
{
int creditosO = 0;
Array<Tupla<Cadena, nat, nat, nat>> materiasDisponibles = Array<Tupla<Cadena, nat, nat, nat>>(horasN*horasM + horasN*horasM);
int contMaterias = 0;
while (matutino.HayElemento()) {
	Tupla<Cadena, nat, nat> aux = matutino.ElementoActual();
	Tupla<Cadena, nat, nat, nat> act = Tupla<Cadena, nat, nat, nat>(aux.ObtenerDato1(), aux.ObtenerDato2(), aux.ObtenerDato3(), 0);
	materiasDisponibles[contMaterias] = act;
	contMaterias++;
	matutino.Avanzar();
}
while (nocturno.HayElemento()) {
	Tupla<Cadena, nat, nat> aux = nocturno.ElementoActual();
	Tupla<Cadena, nat, nat, nat> act = Tupla<Cadena, nat, nat, nat>(aux.ObtenerDato1(), aux.ObtenerDato2(), aux.ObtenerDato3(), 1);
	if (noEstaContenida(materiasDisponibles, contMaterias, act)) {
		materiasDisponibles[contMaterias] = act;
		contMaterias++;
	}
	else {
		for (int i = 0; i < contMaterias; i++)
		{
			if (act.ObtenerDato1() == materiasDisponibles[i].ObtenerDato1()) {
				materiasDisponibles[i].AsignarDato4(1);
			}
		}
	}
	nocturno.Avanzar();
}
//resize
Array<Tupla<Cadena, nat, nat, nat>> materiasFinal = Array<Tupla<Cadena, nat, nat, nat>>(contMaterias);
for (int i = 0; i < contMaterias; i++)
{
	materiasFinal[i] = materiasDisponibles[i];
}

Array<Tupla<Cadena, nat, nat, nat>> solActual = Array<Tupla<Cadena, nat, nat, nat>>(contMaterias);
Array<Tupla<Cadena, nat, nat, nat>> solO = Array<Tupla<Cadena, nat, nat, nat>>(contMaterias);
for (int i = 0; i < contMaterias; i++) {
	solActual[i].AsignarDato4(-1);
	solO[i].AsignarDato4(-1);
}

//llamo a la mochila
mochilasMaterias(horasN, horasM, contMaterias - 1, materiasFinal, solActual, solO, 0, creditosO);

//Armo el retorno
Array<Tupla<Cadena, bool>> ret = Array<Tupla<Cadena, bool>>(contMaterias);
for (int i = 0; i < contMaterias; i++) {
	ret[i] = Tupla<Cadena, bool>();
	if (solO[i].ObtenerDato4() != -1) {
		ret[i].AsignarDato1(materiasFinal[i].ObtenerDato1());

		if (solO[i].ObtenerDato4() == 0) {
			ret[i].AsignarDato2(true);
		}
		if (solO[i].ObtenerDato4() == 1) {
			ret[i].AsignarDato2(false);
		}
	}
}

return Tupla<TipoRetorno, Iterador<Tupla<Cadena, bool>>>(OK, ret.ObtenerIterador());
}

bool Sistema::noEstaContenida(Array<Tupla<Cadena, nat, nat, nat>> materiasDisponibles, int contMaterias, Tupla<Cadena, nat, nat, nat > act) {
	for (int i = 0; i < contMaterias; i++)
	{
		if (act.ObtenerDato1() == materiasDisponibles[i].ObtenerDato1()) {
			return false;
		}
	}
	return true;
}

void Sistema::mochilasMaterias(int hN, int hM, int materiaHasta, Array<Tupla<Cadena, nat, nat, nat>> & materiasDisponibles, Array<Tupla<Cadena, nat, nat, nat>> solActual, Array<Tupla<Cadena, nat, nat, nat>>& solO, int creditosActual, int & creditosO) {
	if (hN> 0 && hM> 0)
	{
		if (materiaHasta >= 0)
		{
			//no cursarla
			solActual[materiaHasta].ObtenerDato4() = -1;
			mochilasMaterias(hN, hM, materiaHasta - 1, materiasDisponibles, solActual, solO, creditosActual, creditosO);
			//cursarla de manana
			if (materiasDisponibles[materiaHasta].ObtenerDato4() == 0)
			{
				solActual[materiaHasta].ObtenerDato4() = 0;
				mochilasMaterias(hN, hM - materiasDisponibles[materiaHasta].ObtenerDato3(), materiaHasta - 1, materiasDisponibles, solActual, solO, creditosActual + materiasDisponibles[materiaHasta].ObtenerDato2(), creditosO);
			}
			//cursarla de noche
			if (materiasDisponibles[materiaHasta].ObtenerDato4() == 1)
			{
				solActual[materiaHasta].ObtenerDato4() = 1;
				mochilasMaterias(hN - materiasDisponibles[materiaHasta].ObtenerDato3(), hM, materiaHasta - 1, materiasDisponibles, solActual, solO, creditosActual + materiasDisponibles[materiaHasta].ObtenerDato2(), creditosO);
			}
		}
		else // consideré todas las materias
		{
			if (creditosActual> creditosO)
			{
				creditosO = creditosActual;
				solO = solActual;
			}
		}
	}
}




