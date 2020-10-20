#ifndef ISISTEMA_H
#define ISISTEMA_H

#include "Cadena.h"
#include "Iterador.h"
#include "Puntero.h"
#include "TipoRetorno.h"
#include "Tupla.h"
#include "Matriz.h"
#include "ICiudad.h"
#include "Producto.h"

struct Accion{
	nat veterinarios;
	nat vehiculos;
	nat dinero;
	nat vacunas;
	nat voluntarios;
	nat impacto;
	
	Accion()
	{
	}
	Accion(nat vet, nat veh, nat din, nat vac, nat vol, nat imp)
	{
		veterinarios = vet;
		vehiculos = veh;
		dinero = din;
		vacunas = vac;
		voluntarios = vol;
		impacto = imp;
	}
};


class ISistema abstract
{
public:
	virtual ~ISistema(){}

	virtual Iterador<Tupla<nat,nat>> Laberinto(Tupla<nat,nat> &inicio, Tupla<nat,nat> &fin, Matriz<nat> &laberinto) abstract;
	
	virtual Iterador<Iterador<Puntero<ICiudad>>> Viajero(Array<Puntero<ICiudad>> &ciudadesDelMapa, Matriz<nat> &mapa, Puntero<ICiudad> &ciudadPartida, Iterador<Puntero<ICiudad>> &ciudadesPasar, nat costoMax) abstract;
	
	virtual Array<nat> Degustacion(Array<Producto> productos, nat maxDinero, nat maxCalorias, nat maxAlcohol) abstract;
	
	//PRE: relacionesCiudades representa la matriz de adyacencia. Para un par de ciudades i,j relacionCiudades[i][j] devuelve una tupla con el costo, distancia y dinero (en ese orden) necesarios para viajar desde i hasta j.
	//POS: se retorna OK y un iterador con las ciudades a recorrer en orden.
	virtual Tupla<TipoRetorno, Iterador<nat>> Viajero2(Matriz<Tupla<nat, nat, nat>> relacionesCiudades, Iterador<nat> CiudadesPasar, Iterador<nat> CiudadesNoPasar) abstract;

	//PRE: recibe una array con todas las acciones posibles, indicando los recursos que se necesitan para cada accion y el impacto que tiene.
	//POST: retorna OK y un array de booleanos indicando cuántas veces realizar cada acción para maximiazar el impacto.
	virtual Tupla<TipoRetorno,  Array<nat>> ProteccionAnimales(Array<Accion> acciones, nat maxVeterinarios, nat maxVehiculos, nat maxDinero, nat maxVacunas, nat maxVoluntarios) abstract;

	//POST: Ordena el array usando la tecnica de quicksort.
	virtual Array<nat> QuickSort(Array<nat> elementos) abstract;

	//PRE: pasar y noPasar son iteradores de casillas validas
	//POS: OK si existe camino. Iterador de mejores camino (cada camino se representa con un Iterador de casillas o Tuplas<int, int>)
	virtual Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>> CaminoCaballo(Tupla<int, int>& salida, Tupla<int, int>& destino, nat cantAPasar, nat tamTablero, Iterador<Tupla<int, int>>& pasar, Iterador<Tupla<int, int>>& noPasar, nat cantMaxAPasarPorCualquierCasilla) abstract;

	//PRE: semillas es un Array que contiene una Tupla de <costo siembra, agua necesaria, ganancia>
	//POS: se retorna OK, y un array indicando cantidad de hectáreas por especie.
	virtual Tupla<TipoRetorno, Array<nat>> OptimizarGranja(Array<Tupla<nat, nat, nat>>& semillas, nat dinero, nat tierra, nat agua) abstract;

	//PRE: matutino y nocturno representan un Iterador de Tupla<materia, creditos, horas>
	//POS: OK si existe solución y un iterador de Tupla<materia, es de turno matutino>
	virtual Tupla<TipoRetorno, Iterador<Tupla<Cadena, bool>>> InscribirMaterias(Iterador<Tupla<Cadena, nat, nat>> matutino, Iterador<Tupla<Cadena, nat, nat>> nocturno, nat horasM, nat horasN) abstract;
};

#endif
