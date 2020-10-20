#include "CasoDePrueba.h"

CasoDePrueba::CasoDePrueba(Puntero<ISistema> (*inicializar)())
{
	this->inicializar = inicializar;
}

Puntero<ISistema> CasoDePrueba::InicializarSistema()
{
	Puntero<ISistema> interfaz = inicializar();
	ignorarOK = false;
	return interfaz;
}

Cadena CasoDePrueba::GetNombre()const
{
	return "Casos de Prueba";
}

void CasoDePrueba::CorrerPruebaConcreta()
{
	PruebaTransponerMatriz();
	PruebaCalcularSilueta();
	PruebaCalcularCoeficienteBinomial();
}

void CasoDePrueba::Verificar(TipoRetorno obtenido, TipoRetorno esperado, Cadena comentario)
{
	if (!ignorarOK || obtenido != esperado)
		Prueba::Verificar(obtenido, esperado, comentario);
}

template <class T>
void CasoDePrueba::Verificar(const T& obtenido, const T& esperado, Cadena comentario)
{
	Verificar(SonIguales(obtenido, esperado) ? OK : ERROR, OK, comentario.DarFormato(ObtenerTexto(obtenido), ObtenerTexto(esperado)));
}

template <class T>
void CasoDePrueba::VerificarConjuntos(Iterador<T> obtenidos, Iterador<T> esperados, Cadena comentarioEncontrado, Cadena comentarioFalta, Cadena comentarioSobra)
{
	bool verificarCantidad = true;
	nat totalObtenidos = 0;
	T aux;
	obtenidos.Reiniciar();
esperados.Reiniciar();
	foreach (T obtenido, obtenidos)
	{
		totalObtenidos++;
		if (Pertenece(obtenido, esperados, aux))
			Verificar(obtenido, obtenido, comentarioEncontrado);
		else
		{
			Verificar(ERROR, OK, comentarioSobra.DarFormato(ObtenerTexto(obtenido)));
			verificarCantidad = false;
		}
	}
	nat totalEsperados = 0;
	foreach (T esperado, esperados)
	{
		totalEsperados++;
		if (!Pertenece(esperado, obtenidos, aux))
		{
			Verificar(ERROR, OK, comentarioFalta.DarFormato(ObtenerTexto(esperado)));
			verificarCantidad = false;
		}
	}
	if (verificarCantidad && totalObtenidos != totalEsperados)
		Verificar(ERROR, OK, "Se verifica la cantidad de elementos de los conjuntos");
}

template <class T>
void CasoDePrueba::VerificarSecuencias(Iterador<T> obtenidos, Iterador<T> esperados, Cadena comentarioEncontrado, Cadena comentarioFalta, Cadena comentarioSobra)
{
	esperados.Reiniciar();

	foreach (T obtenido, obtenidos)
	{
		if (esperados.HayElemento())
		{
			T esperado = *esperados;
			++esperados;
			Verificar(obtenido, esperado, comentarioEncontrado);
		}
		else
			Verificar(ERROR, OK, comentarioSobra.DarFormato(ObtenerTexto(obtenido)));
	}

	while (esperados.HayElemento())
	{
		T esperado = *esperados;
		++esperados;
		Verificar(ERROR, OK, comentarioFalta.DarFormato(ObtenerTexto(esperado)));
	}
}

template <class T>
bool CasoDePrueba::SonIguales(Iterador<T> obtenidos, Iterador<T> esperados) const
{
	obtenidos.Reiniciar();
	esperados.Reiniciar();
	while (obtenidos.HayElemento() && esperados.HayElemento())
	{
		if (!SonIguales(*obtenidos, *esperados))
			return false;
		++obtenidos;
		++esperados;
	}

	return esperados.HayElemento() == obtenidos.HayElemento();
}

bool CasoDePrueba::SonIguales(const nat obtenido, const nat esperado) const
{
	return esperado == obtenido;
}

bool CasoDePrueba::SonIguales(Puntero<ITira> obtenida, Puntero<ITira> esperada) const
{
	return obtenida->ObtenerX() == esperada->ObtenerX() &&
		obtenida ->ObtenerAltura() == esperada->ObtenerAltura();
}

bool CasoDePrueba::SonIguales(Cadena obtenida, Cadena esperada) const
{
	return obtenida == esperada;
}

Cadena CasoDePrueba::ObtenerTexto(nat n) const
{
	switch (n)
	{
	case 0:
		return "0";
	case 1:
		return "1";
	case 2:
		return "2";
	case 3:
		return "3";
	case 4:
		return "4";
	case 5:
		return "5";
	case 6:
		return "6";
	case 7:
		return "7";
	case 8:
		return "8";
	case 9:
		return "9";
	default:
		Cadena ret = "";
		while (n != 0)
		{
			ret = ObtenerTexto(n % 10) + ret;
			n /= 10;
		}
		return ret;
	}
}

Cadena CasoDePrueba::ObtenerTexto(Puntero<ITira> t) const
{
	Cadena retorno = "(";
	retorno+=ObtenerTexto(t->ObtenerX());
	retorno+=",";
	retorno+=ObtenerTexto(t->ObtenerAltura());
	retorno+=")";

	return retorno;
}

template <class T>
Cadena CasoDePrueba::ObtenerTexto(Iterador<T> it) const
{
	Cadena sepVacio = "";
	Cadena sepGuion = "-";
	Cadena sep = sepVacio;
	Cadena retorno = sepVacio;
	foreach (auto t, it)
	{
		retorno += sep + ObtenerTexto(t);
		sep = sepGuion;
	}
	return retorno;
}

Cadena CasoDePrueba::ObtenerTexto(Cadena c) const
{
	return c;
}

template <class T>
bool CasoDePrueba::Pertenece(const T& dato, Iterador<T> iterador, T& encontrado) const
{
	iterador.Reiniciar();
	foreach (T dato2, iterador)
	{
		if (SonIguales(dato, dato2))
		{
			encontrado = dato2;
			return true;
		}
	}
	return false;
}

template <class T>
void CasoDePrueba::VerificarMatrices(Iterador<const Array<T>> filasObtenidas,Iterador<const Array<T>> filasEsperadas)
{
	filasObtenidas.Reiniciar();
	filasEsperadas.Reiniciar();

	Array<T> obtenidos = ConvertirMatrizAArray(filasObtenidas);
	Array<T> esperados = ConvertirMatrizAArray(filasEsperadas);
	cout<<"A continuacion se listan cada uno de los elementos de la matriz por fila y arrancando desde la posicion [0][0]"<<endl;
	VerificarSecuencias(obtenidos.ObtenerIterador(),esperados.ObtenerIterador(), "Se obtuvo {0} y se esperaba {1}", "Se esperaba {0}", "No se esperaba {0}");
}
template <class T>
Array<T> CasoDePrueba::ConvertirMatrizAArray(Iterador<const Array<T>> filas)
{
	filas.Reiniciar();
	nat largoDelNuevoArray = 0;

	while(filas.HayElemento())
	{
		Array<T> arrayInterno = filas.ElementoActual();
		largoDelNuevoArray += arrayInterno.Largo;
		filas.Avanzar();
	}

	filas.Reiniciar();

	Array<T> nuevoArray = Array<T>(largoDelNuevoArray);
	nat posActual = 0;
	while(filas.HayElemento())
	{
		Array<T> arrayInterno = filas.ElementoActual();
		nuevoArray.Copiar(arrayInterno,nuevoArray,posActual);
		posActual+=arrayInterno.Largo;
		filas.Avanzar();
	}

	return nuevoArray;

}

void CasoDePrueba::PruebaTransponerMatriz()
{
	PruebaTransMat1();
	PruebaTransMat2();
	PruebaTransMat3();
}

void CasoDePrueba::PruebaTransMat1()
{
	IniciarSeccion("Ejercicio Transponer Matriz: Prueba 1");
	Puntero<ISistema> interfaz = InicializarSistema();

	Matriz<nat> unaMatriz = Matriz<nat>(4,4);
	unaMatriz[0][0] = 4;
	unaMatriz[0][1] = 6;
	unaMatriz[0][2] = 1;
	unaMatriz[0][3] = 1;
	unaMatriz[1][0] = 2;
	unaMatriz[1][1] = 9;
	unaMatriz[1][2] = 0;
	unaMatriz[1][3] = 9;
	unaMatriz[2][0] = 2;
	unaMatriz[2][1] = 3;
	unaMatriz[2][2] = 6;
	unaMatriz[2][3] = 3;
	unaMatriz[3][0] = 2;
	unaMatriz[3][1] = 4;
	unaMatriz[3][2] = 2;
	unaMatriz[3][3] = 9;

	Matriz<nat> esperada = Matriz<nat>(4,4);
	esperada[0][0] = 4;
	esperada[0][1] = 2;
	esperada[0][2] = 2;
	esperada[0][3] = 2;
	esperada[1][0] = 6;
	esperada[1][1] = 9;
	esperada[1][2] = 3;
	esperada[1][3] = 4;
	esperada[2][0] = 1;
	esperada[2][1] = 0;
	esperada[2][2] = 6;
	esperada[2][3] = 2;
	esperada[3][0] = 1;
	esperada[3][1] = 9;
	esperada[3][2] = 3;
	esperada[3][3] = 9;

	interfaz->TransponerMatriz(unaMatriz);
	
	VerificarMatrices(unaMatriz.ObtenerIterador(),esperada.ObtenerIterador());

	CerrarSeccion();
}

void CasoDePrueba::PruebaTransMat2(){

	IniciarSeccion("Ejercicio Transponer Matriz: Prueba 2");
	Puntero<ISistema> interfaz = InicializarSistema();

	Matriz<nat> unaMatriz = Matriz<nat>(8,8);
	Matriz<nat> esperada = Matriz<nat>(8,8);
	nat cantCeldas = 0;
	for (nat i = 0; i < unaMatriz.Largo; i++)
	{
		if(cantCeldas == 32) cantCeldas = 0;
		for (nat j = 0; j < unaMatriz.Ancho; j++)
		{
			unaMatriz[i][j] = ++cantCeldas;
			esperada[j][i] = cantCeldas;
		}
	}

	interfaz->TransponerMatriz(unaMatriz);
	
	VerificarMatrices(unaMatriz.ObtenerIterador(),esperada.ObtenerIterador());

	CerrarSeccion();

}

void CasoDePrueba::PruebaTransMat3(){

	IniciarSeccion("Ejercicio Transponer Matriz: Prueba 3");
	Puntero<ISistema> interfaz = InicializarSistema();

	Matriz<nat> unaMatriz = Matriz<nat>(2,2);
	unaMatriz[0][0] = 1;
	unaMatriz[0][1] = 0;
	unaMatriz[1][0] = 0;
	unaMatriz[1][1] = 1;

	Matriz<nat> esperada = Matriz<nat>(2,2);
	esperada[0][0] = 1;
	esperada[0][1] = 0;
	esperada[1][0] = 0;
	esperada[1][1] = 1;

	interfaz->TransponerMatriz(unaMatriz);
	
	VerificarMatrices(unaMatriz.ObtenerIterador(),esperada.ObtenerIterador());

	CerrarSeccion();

}

void CasoDePrueba::PruebaCalcularSilueta()
{
	PruebaCalcSil1();
	PruebaCalcSil2();
	PruebaCalcSil3();
	PruebaCalcSil4();
}

void CasoDePrueba::PruebaCalcSil1()
{
	IniciarSeccion("Ejercicio Calcular Silueta de Ciudad: Prueba 1");
	Puntero<ISistema> interfaz = InicializarSistema();

	Array<Puntero<IEdificio>> ciudad(5);
	ciudad[0] = new EdificioMock(2,9,10);
	ciudad[1] = new EdificioMock(3,7,15);
	ciudad[2] = new EdificioMock(5,12,12);
	ciudad[3] = new EdificioMock(15,20,10);
	ciudad[4] = new EdificioMock(19,24,8);
	
	Array<Puntero<ITira>> siluetaEsperada(7);
	siluetaEsperada[0] = new TiraMock(2,10);
	siluetaEsperada[1] = new TiraMock(3,15);
	siluetaEsperada[2] = new TiraMock(7,12);
	siluetaEsperada[3] = new TiraMock(12,0);
	siluetaEsperada[4] = new TiraMock(15,10);
	siluetaEsperada[5] = new TiraMock(20,8);
	siluetaEsperada[6] = new TiraMock(24,0);

	Array<Puntero<ITira>> siluetaObtenida = interfaz ->CalcularSiluetaDeLaCiudad(ciudad);

	VerificarSecuencias(siluetaObtenida.ObtenerIterador(),siluetaEsperada.ObtenerIterador(), "Se obtuvo {0} y se esperaba {1}", "Se esperaba {0}", "No se esperaba {0}");

	CerrarSeccion();
};

void CasoDePrueba::PruebaCalcSil2()
{
	IniciarSeccion("Ejercicio Calcular Silueta de Ciudad: Prueba 2");
	Puntero<ISistema> interfaz = InicializarSistema();

	Array<Puntero<IEdificio>> ciudad(6);
	ciudad[0] = new EdificioMock(1,5,11);
	ciudad[1] = new EdificioMock(2,7,6);
	ciudad[2] = new EdificioMock(3,9,13);
	ciudad[3] = new EdificioMock(12,16,7);
	ciudad[4] = new EdificioMock(14,25,3);
	ciudad[5] = new EdificioMock(19,22,18);

	Array<Puntero<ITira>> siluetaEsperada(8);
	siluetaEsperada[0] = new TiraMock(1,11);
	siluetaEsperada[1] = new TiraMock(3,13);
	siluetaEsperada[2] = new TiraMock(9,0);
	siluetaEsperada[3] = new TiraMock(12,7);
	siluetaEsperada[4] = new TiraMock(16,3);
	siluetaEsperada[5] = new TiraMock(19,18);
	siluetaEsperada[6] = new TiraMock(22,3);
	siluetaEsperada[7] = new TiraMock(25,0);

	Array<Puntero<ITira>> siluetaObtenida = interfaz ->CalcularSiluetaDeLaCiudad(ciudad);

	VerificarSecuencias(siluetaObtenida.ObtenerIterador(),siluetaEsperada.ObtenerIterador(), "Se obtuvo {0} y se esperaba {1}", "Se esperaba {0}", "No se esperaba {0}");

	CerrarSeccion();
};

void CasoDePrueba::PruebaCalcSil3()
{
	IniciarSeccion("Ejercicio Calcular Silueta de Ciudad: Prueba 3");
	Puntero<ISistema> interfaz = InicializarSistema();

	Array<Puntero<IEdificio>> ciudad(1);
	ciudad[0] = new EdificioMock(1,5,11);

	Array<Puntero<ITira>> siluetaEsperada(2);
	siluetaEsperada[0] = new TiraMock(1,11);
	siluetaEsperada[1] = new TiraMock(5,0);

	Array<Puntero<ITira>> siluetaObtenida = interfaz ->CalcularSiluetaDeLaCiudad(ciudad);

	VerificarSecuencias(siluetaObtenida.ObtenerIterador(),siluetaEsperada.ObtenerIterador(), "Se obtuvo {0} y se esperaba {1}", "Se esperaba {0}", "No se esperaba {0}");

	CerrarSeccion();
};

void CasoDePrueba::PruebaCalcSil4()
{
	IniciarSeccion("Ejercicio Calcular Silueta de Ciudad: Prueba 4");
	Puntero<ISistema> interfaz = InicializarSistema();

	Array<Puntero<IEdificio>> ciudad(6);
	ciudad[0] = new EdificioMock(0,2,7);
	ciudad[1] = new EdificioMock(1,5,2);
	ciudad[2] = new EdificioMock(3,6,7);
	ciudad[3] = new EdificioMock(4,9,10);
	ciudad[4] = new EdificioMock(8,12,14);
	ciudad[5] = new EdificioMock(12,15,14);

	Array<Puntero<ITira>> siluetaEsperada(6);
	siluetaEsperada[0] = new TiraMock(0,7);
	siluetaEsperada[1] = new TiraMock(2,2);
	siluetaEsperada[2] = new TiraMock(3,7);
	siluetaEsperada[3] = new TiraMock(4,10);
	siluetaEsperada[4] = new TiraMock(8,14);
	siluetaEsperada[5] = new TiraMock(15,0);

	Array<Puntero<ITira>> siluetaObtenida = interfaz ->CalcularSiluetaDeLaCiudad(ciudad);

	VerificarSecuencias(siluetaObtenida.ObtenerIterador(),siluetaEsperada.ObtenerIterador(), "Se obtuvo {0} y se esperaba {1}", "Se esperaba {0}", "No se esperaba {0}");

	CerrarSeccion();
};

void CasoDePrueba::PruebaCalcularCoeficienteBinomial()
{
	PruebaCalcCoefBin();
	PruebaCalcCoefBin2();
	PruebaCalcCoefBin3();
	PruebaCalcCoefBin4();
	PruebaCalcCoefBin5(); 
	PruebaCalcCoefBin6();
	PruebaCalcCoefBin7();
}

void CasoDePrueba::PruebaCalcCoefBin()
{
	IniciarSeccion("Ejercicio Calcular Coeficiente Binomial: Prueba 1");
	Puntero<ISistema> interfaz = InicializarSistema();
	
	nat resultadoEsperado = 1;

	nat resultadoObtenido = interfaz ->CalcularCoeficienteBinomial(0,0);
	Verificar(resultadoObtenido,resultadoEsperado,"Se obtuvo {0} y se esperaba {1}");

	resultadoObtenido = interfaz ->CalcularCoeficienteBinomial(1,1);
	Verificar(resultadoObtenido,resultadoEsperado,"Se obtuvo {0} y se esperaba {1}");

	resultadoObtenido = interfaz ->CalcularCoeficienteBinomial(5,5);
	Verificar(resultadoObtenido,resultadoEsperado,"Se obtuvo {0} y se esperaba {1}");

	resultadoObtenido = interfaz ->CalcularCoeficienteBinomial(20,20);
	Verificar(resultadoObtenido,resultadoEsperado,"Se obtuvo {0} y se esperaba {1}");

	CerrarSeccion();
}

void CasoDePrueba::PruebaCalcCoefBin2()
{
	IniciarSeccion("Ejercicio Calcular Coeficiente Binomial: Prueba 2");
	Puntero<ISistema> interfaz = InicializarSistema();

	nat resultadoObtenido = interfaz ->CalcularCoeficienteBinomial(3,1);
	nat resultadoEsperado = 3;
	Verificar(resultadoObtenido,resultadoEsperado,"Se obtuvo {0} y se esperaba {1}");

	resultadoObtenido = interfaz ->CalcularCoeficienteBinomial(3,2);
	resultadoEsperado = 3;
	Verificar(resultadoObtenido,resultadoEsperado,"Se obtuvo {0} y se esperaba {1}");

	resultadoObtenido = interfaz ->CalcularCoeficienteBinomial(4,1);
	resultadoEsperado = 4;
	Verificar(resultadoObtenido,resultadoEsperado,"Se obtuvo {0} y se esperaba {1}");

	resultadoObtenido = interfaz ->CalcularCoeficienteBinomial(4,3);
	resultadoEsperado = 4;
	Verificar(resultadoObtenido,resultadoEsperado,"Se obtuvo {0} y se esperaba {1}");

	resultadoObtenido = interfaz ->CalcularCoeficienteBinomial(43,1);
	resultadoEsperado = 43;
	Verificar(resultadoObtenido,resultadoEsperado,"Se obtuvo {0} y se esperaba {1}");
	
	resultadoObtenido = interfaz ->CalcularCoeficienteBinomial(43,42);
	resultadoEsperado = 43;
	Verificar(resultadoObtenido,resultadoEsperado,"Se obtuvo {0} y se esperaba {1}");

	CerrarSeccion();
}

void CasoDePrueba::PruebaCalcCoefBin3()
{
	IniciarSeccion("Ejercicio Calcular Coeficiente Binomial: Prueba 3");
	Puntero<ISistema> interfaz = InicializarSistema();

	nat resultadoObtenido = interfaz ->CalcularCoeficienteBinomial(50,48);
	nat resultadoEsperado = 1225;
	Verificar(resultadoObtenido,resultadoEsperado,"Se obtuvo {0} y se esperaba {1}");

	CerrarSeccion();
}

void CasoDePrueba::PruebaCalcCoefBin4()
{
	IniciarSeccion("Ejercicio Calcular Coeficiente Binomial: Prueba 4");
	Puntero<ISistema> interfaz = InicializarSistema();

	nat resultadoObtenido = interfaz ->CalcularCoeficienteBinomial(23,14);
	nat resultadoEsperado = 817190;
	Verificar(resultadoObtenido,resultadoEsperado,"Se obtuvo {0} y se esperaba {1}");

	CerrarSeccion();
}

void CasoDePrueba::PruebaCalcCoefBin5()
{
	IniciarSeccion("Ejercicio Calcular Coeficiente Binomial: Prueba 5");
	Puntero<ISistema> interfaz = InicializarSistema();

	nat resultadoObtenido = interfaz ->CalcularCoeficienteBinomial(20,3);
	nat resultadoEsperado = 1140;
	Verificar(resultadoObtenido,resultadoEsperado,"Se obtuvo {0} y se esperaba {1}");

	CerrarSeccion();
}

void CasoDePrueba::PruebaCalcCoefBin6()
{
	IniciarSeccion("Ejercicio Calcular Coeficiente Binomial: Prueba 6");
	Puntero<ISistema> interfaz = InicializarSistema();

	nat resultadoObtenido = interfaz ->CalcularCoeficienteBinomial(32,6);
	nat resultadoEsperado = 906192;
	Verificar(resultadoObtenido,resultadoEsperado,"Se obtuvo {0} y se esperaba {1}");

	CerrarSeccion();
}

void CasoDePrueba::PruebaCalcCoefBin7()
{
	IniciarSeccion("Ejercicio Calcular Coeficiente Binomial: Prueba 7");
	Puntero<ISistema> interfaz = InicializarSistema();

	nat resultadoObtenido = interfaz ->CalcularCoeficienteBinomial(80,3);
	nat resultadoEsperado = 82160;
	Verificar(resultadoObtenido,resultadoEsperado,"Se obtuvo {0} y se esperaba {1}");

	CerrarSeccion();
}
