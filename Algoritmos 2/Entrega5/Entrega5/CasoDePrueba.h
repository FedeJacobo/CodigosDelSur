#pragma once

#include "ISistema.h"
#include "Prueba.h"
#include "PruebasMock.h"


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
	template <class T>
	void VerificarMatrices(Iterador<const Array<T>> filasObtenidas,Iterador<const Array<T>> filasEsperadas);
	template <class T>
	Array<T> ConvertirMatrizAArray(Iterador<const Array<T>> filas);

	template <class T>
	bool SonIguales(Iterador<T> obtenidos, Iterador<T> esperados) const;
	bool SonIguales(Puntero<ITira> obtenida, Puntero<ITira> esperada) const;
	bool SonIguales(const Tupla<nat, nat>& obtenido, const Tupla<nat, nat>& esperado) const;
	bool SonIguales(Cadena obtenida, Cadena esperada) const;
	Cadena ObtenerTexto(nat n) const;
	Cadena ObtenerTexto(Cadena c) const;
	Cadena ObtenerTexto(Puntero<ITira> t) const;
	template <class T>
	Cadena ObtenerTexto(Iterador<T> it) const;
	Cadena ObtenerTexto(const Tupla<nat, nat>& t) const;
	template <class T>
	bool Pertenece(const T& dato, Iterador<T> iterador, T& encontrado) const;
	template <class T>
	int ObtenerLargoIterador(Iterador<T> iteradorFuente);
	bool SonIguales(const nat obtenido, const nat esperado) const;

	void PruebaTransponerMatriz();
	void PruebaTransMat1();
	void PruebaTransMat2();
	void PruebaTransMat3();

	void PruebaCalcularSilueta();
	void PruebaCalcSil1();
	void PruebaCalcSil2();
	void PruebaCalcSil3();
	void PruebaCalcSil4();

	void PruebaCalcularCoeficienteBinomial();
	void PruebaCalcCoefBin();
	void PruebaCalcCoefBin2();
	void PruebaCalcCoefBin3();
	void PruebaCalcCoefBin4();
	void PruebaCalcCoefBin5();
	void PruebaCalcCoefBin6();
	void PruebaCalcCoefBin7();

};