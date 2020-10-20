#ifndef SISTEMA_H
#define SISTEMA_H

#include "ISistema.h"
#include "Producto.h"

class Sistema : public ISistema
{
public:
	Sistema();

	Iterador<Tupla<nat,nat>> Laberinto(Tupla<nat,nat> &inicio, Tupla<nat,nat> &fin, Matriz<nat> &laberinto) override;

	virtual Iterador<Iterador<Puntero<ICiudad>>> Viajero(Array<Puntero<ICiudad>> &ciudadesDelMapa, Matriz<nat> &mapa, Puntero<ICiudad> &ciudadPartida, Iterador<Puntero<ICiudad>> &ciudadesPasar, nat costoMax) override;
	
	virtual Array<nat> Degustacion(Array<Producto> productos, nat maxDinero, nat maxCalorias, nat maxAlcohol) override;

	//PRE: relacionesCiudades representa la matriz de adyacencia. Para un par de ciudades i,j relacionCiudades[i][j] devuelve una tupla con el costo, distancia y dinero (en ese orden) necesarios para viajar desde i hasta j.
	//POS: se retorna OK y un iterador con las ciudades a recorrer en orden.
	virtual Tupla<TipoRetorno, Iterador<nat>> Viajero2(Matriz<Tupla<nat, nat, nat>> relacionesCiudades, Iterador<nat> CiudadesPasar, Iterador<nat> CiudadesNoPasar) override;

	//PRE: recibe una array con todas las acciones posibles, indicando los recursos que se necesitan para cada accion y el impacto que tiene.
	//POST: retorna OK y un array de booleanos indicando cuántas veces realizar cada acción para maximizar el impacto.
	virtual Tupla<TipoRetorno,  Array<nat>> ProteccionAnimales(Array<Accion> acciones, nat maxVeterinarios, nat maxVehiculos, nat maxDinero, nat maxVacunas, nat maxVoluntarios) override;

	//POST: Ordena el array usando la tecnica de quicksort.
	virtual Array<nat> QuickSort(Array<nat> elementos) override;

	//PRE: pasar y noPasar son iteradores de casillas validas
	//POS: OK si existe camino. Iterador de mejores camino (cada camino se representa con un Iterador de casillas o Tuplas<int, int>)
	virtual Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>> CaminoCaballo(Tupla<int, int>& salida, Tupla<int, int>& destino, nat cantAPasar, nat tamTablero, Iterador<Tupla<int, int>>& pasar, Iterador<Tupla<int, int>>& noPasar, nat cantMaxAPasarPorCualquierCasilla) override;

	//PRE: semillas es un Array que contiene una Tupla de <costo siembra, agua necesaria, ganancia>
	//POS: se retorna OK, y un array indicando cantidad de hectáreas por especie.
	virtual Tupla<TipoRetorno, Array<nat>> OptimizarGranja(Array<Tupla<nat, nat, nat>>& semillas, nat dinero, nat tierra, nat agua) override;

	//PRE: matutino y nocturno representan un Iterador de Tupla<materia, creditos, horas>
	//POS: OK si existe solución y un iterador de Tupla<materia, es de turno matutino>
	virtual Tupla<TipoRetorno, Iterador<Tupla<Cadena, bool>>> InscribirMaterias(Iterador<Tupla<Cadena, nat, nat>> matutino, Iterador<Tupla<Cadena, nat, nat>> nocturno, nat horasM, nat horasN) override;
private:
	bool Pase(Tupla<nat, nat> pos, Array<Tupla<nat, nat>>caminoA, nat nroPasosA);
	void Copiar(Array<Tupla<nat, nat>>caminoA, Array<Tupla<nat, nat>>&caminoO);
	bool esPosValida(nat i, nat j, Matriz<nat> &mat);
	void Sistema::laberintosAux(Tupla<nat, nat> pos, Tupla<nat, nat> fin, Matriz<nat> mat, char dir, int cambiosDirAct, int &cambiosDirOpt, Array<Tupla<nat, nat>> &ret, Array<Tupla<nat, nat>> caminoAux, int cantElem, int &cantElemO, Matriz<bool> vis);

	void mochilaDegustacion(Array<Producto> prod, nat objAct, Array<nat> solA, Array<nat> &solO, int maxDinero, int maxCalorias, int maxAlcohol, int valA, int &valO);
	void copiar(Array<nat> solucionA, Array<nat>& solucionO);

	void Sistema::ProteccionAnimalesAux(Array<Accion> acciones, int accionA, Array<nat> accionesA, Array<nat> &accionesO, int impactoA, int &impactoO, int maxVeterinarios, int maxVehiculos, int maxDinero, int maxVacunas, int maxVoluntarios);

	void CaminoCaballoAux(Tupla<int, int> salida, Tupla<int, int> destino, Array<Tupla<int, int>> caminoA, Array<Tupla<int, int>> &caminoO, int cantPasosA, int &cantPasosO, Matriz<int> tablero, Matriz<int> cantPasadas, int cantAPasar, int pos, Array<Iterador<Tupla<int, int>>> &ret);
	bool esPosValidaInt(nat i, nat j, Matriz<int> &mat);

	void quicksortAux(Array<nat>&elem, int izq, int der);

	void mochilaGranja(int especieActual, int gananciaA, int &gananciaO, Array<nat> solucionA, Array<nat> &solucionO, Array<Tupla<nat, nat, nat>>& semillas, int dinero, int tierra, int agua);

	bool noEstaContenida(Array<Tupla<Cadena, nat, nat, nat>> materiasDisponibles, int contMaterias, Tupla<Cadena, nat, nat, nat > act);
	void mochilasMaterias(int hN, int hM, int materiaHasta, Array<Tupla<Cadena, nat, nat, nat>> & materiasDisponibles, Array<Tupla<Cadena, nat, nat, nat>> solActual, Array<Tupla<Cadena, nat, nat, nat>>& solO, int creditosActual, int & creditosO);
};

#endif
