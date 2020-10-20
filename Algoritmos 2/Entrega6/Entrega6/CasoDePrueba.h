#pragma once

#include "ISistema.h"
#include "Prueba.h"
#include "PruebasMock.h"
#include "Producto.h"



class CasoDePrueba : public Prueba
{
public:
	CasoDePrueba(Puntero<ISistema> (*inicializar)());

protected:
	void CorrerPruebaConcreta() override;
	Cadena GetNombre() const override;

private:
	Puntero<ISistema> (*inicializar)();
	Puntero<ISistema> InicializarSistema();

	bool ignorarOK;
	void Verificar(TipoRetorno obtenido, TipoRetorno esperado, Cadena comentario);
	template <class T>
	void Verificar(const T& obtenido, const T& esperado, Cadena comentario);
	template <class T>
	void VerificarConjuntos(Iterador<T> obtenidos, Iterador<T> esperados, Cadena comentarioEncontrado, Cadena comentarioFalta, Cadena comentarioSobra);
	template <class T>
	void VerificarSecuencias(Iterador<T> obtenidos, Iterador<T> esperados, Cadena comentarioEncontrado, Cadena comentarioFalta, Cadena comentarioSobra);
	bool ExistePrecedencia(Cadena elementoI, Cadena elementoJ, Matriz<bool> matrizAVerificar,Iterador<Cadena> temas);
		
	template <class T>
	bool SonIguales(Iterador<T> obtenidos, Iterador<T> esperados) const;
	bool SonIguales(const Tupla<nat, nat>& obtenido, const Tupla<nat, nat>& esperado) const;
	bool SonIguales(const Tupla<int, int>& obtenido, const Tupla<int, int>& esperado) const;
	bool SonIguales(const nat& obtenido, const nat& esperado) const;
	bool SonIguales(const Tupla<Cadena, bool>& obtenido, const Tupla<Cadena, bool>& esperado) const;
	bool SonIguales(const Puntero<ICiudad>& obtenido, const Puntero<ICiudad>& esperado) const;
	
	template <class T>
	Cadena ObtenerTexto(Iterador<T> it) const;
	Cadena ObtenerTexto(const Tupla<Cadena, bool>& materia) const;
	Cadena ObtenerTexto(const Tupla<nat, nat>& t) const;
	Cadena ObtenerTexto(const Tupla<int, int>& t) const;
	Cadena ObtenerTexto(nat n) const;
	Cadena ObtenerTexto(const Puntero<ICiudad>& t) const;

	template <class T>
	bool Pertenece(const T& dato, Iterador<T> iterador, T& encontrado) const;
	void InicializarMatrizEnCero(Matriz<nat> matrizAInicializar);
	void InicializarMatriz(Matriz<bool> matrizAInicializar,int largo);	
	template <class T>
	int ObtenerLargoIterador(Iterador<T> iteradorFuente);
	Matriz<bool> CrearMatrizDePrecedencias(Iterador<Tupla<Cadena,Cadena> > relacionesEntreVertices, Iterador<Cadena> verticesQueParticipan);
	int ObtenerNumeroInternoVertice(Cadena verticeABuscar, Iterador<Cadena> iteradorDeVertices);

	void PruebaLaberinto();
	void PruebaViajero();
	void PruebaIntercalar();
	void PruebaDegustacion();

	void VerificarCaminos(const Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>>& obtenido, const Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>>& esperado);
	void VerificarViajero2(const Tupla<TipoRetorno, Iterador<nat>>& obtenido, const Tupla<TipoRetorno, Iterador<nat>>& esperado);
	void VerificarProteccionAnimales(const Array<Accion>& acciones, const Tupla<TipoRetorno, Array<nat>>& esperado, const Tupla<TipoRetorno, Array<nat>>& obtenido, nat maxVeterinarios, nat maxVehiculos, nat maxDinero, nat maxVacunas, nat maxVoluntarios);
	void VerificarGranja(const Array<Tupla<nat, nat, nat>>& semillas, const Tupla<TipoRetorno, Array<nat>>& esperado, const Tupla<TipoRetorno, Array<nat>>& obtenido, nat dinero, nat tierra, nat agua);
	void VerificarMaterias(const Tupla<TipoRetorno, Iterador<Tupla<Cadena, bool>>>& obtenido, const Tupla<TipoRetorno, Iterador<Tupla<Cadena, bool>>>& esperado);

	void PruebaViajero2();
	void PruebaQuickSort();
	void PruebaProteccionAnimales();
	void PruebaCaminoCaballo();
	void PruebaOptimizarGranja();
	void PruebaInscribirMaterias();
};