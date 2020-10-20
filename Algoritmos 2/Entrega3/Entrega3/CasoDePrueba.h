#pragma once

#include "Sistema.h"
#include "Prueba.h"
#include "Tupla.h"
#include "Tablero.h"
#include "Prioridad.h"

class CasoDePrueba : public Prueba
{
public:
	CasoDePrueba(Puntero<Sistema>(*inicializar)());

protected:
	void CorrerPruebaConcreta() override;
	Cadena GetNombre() const override;

private:
	Puntero<Sistema>(*inicializar)();
	Puntero<Sistema> InicializarSistema();

	bool ignorarOK;
	void Verificar(TipoRetorno obtenido, TipoRetorno esperado, Cadena comentario);
	template <class T>
	void Verificar(const T& obtenido, const T& esperado, Cadena comentario);
	template <class T>
	void VerificarConjuntos(Iterador<T> obtenidos, Iterador<T> esperados, Cadena comentarioEncontrado, Cadena comentarioFalta, Cadena comentarioSobra);
	template <class T>
	void VerificarSecuencias(Iterador<T> obtenidos, Iterador<T> esperados, Cadena comentarioEncontrado, Cadena comentarioFalta, Cadena comentarioSobra);
	void VerificarSolucionTablero(Matriz<int> inicial, Iterador<Tablero> obtenido);
	template <class T>
	bool SonIguales(Iterador<T> obtenidos, Iterador<T> esperados) const;
	bool SonIguales(const Tupla<Cadena, nat>& obtenido, const Tupla<Cadena, nat>& esperado) const;
	bool SonIguales(const Tupla<nat, nat>& obtenido, const Tupla<nat, nat>& esperado) const;
	bool SonIguales(const Cadena& obtenido, const Cadena& esperado) const;
	bool SonIguales(const bool obtenido, const bool esperado) const;
	bool SonIguales(const int obtenido, const int esperado) const;
	bool SonIguales(const Matriz<int>& obtenido, const Matriz<int>& esperado) const;
	bool SonVecinos(const Matriz<int>& obtenido, const Matriz<int>& esperado) const;
	bool SonIguales(const Puntero<Tablero> obtenido, const Puntero<Tablero> esperado) const;
	template <class T>
	Cadena ObtenerTexto(Iterador<T> it) const;
	Cadena ObtenerTexto(const Tupla<nat, nat>& t) const;
	Cadena ObtenerTexto(const Tupla<Cadena, nat>& t) const;
	Cadena ObtenerTexto(nat n) const;
	Cadena ObtenerTexto(Cadena) const;
	Cadena ObtenerTexto(Puntero<Tablero>) const;
	template <class T>
	bool Pertenece(const T& dato, Iterador<T> iterador, T& encontrado) const;

	void PruebaTablero1(Puntero<Prioridad> p);
	void PruebaTablero2(Puntero<Prioridad> p);
	void PruebaTablero3(Puntero<Prioridad> p);
	void PruebaTablero4(Puntero<Prioridad> p);
	void PruebaTablero5(Puntero<Prioridad> p);
	void PruebaTablero6(Puntero<Prioridad> p);
	void PruebaColaPrioridadExtendida();
};

