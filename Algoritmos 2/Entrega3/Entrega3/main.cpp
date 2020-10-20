#include "CasoDePrueba.h"
#include "PruebaMemoria.h"
#include "ConductorPrueba.h"
#include "Sistema.h"

Puntero<Sistema> Inicializar()
{
	return new Sistema();
}

void main()
{
	bool consola = false;

	if (!consola) {
		Puntero<ConductorPrueba> cp = new ConductorPrueba();
		Array<Puntero<Prueba>> pruebas = Array<Puntero<Prueba>>(3);
		pruebas[0] = new PruebaMemoria();
		pruebas[1] = new CasoDePrueba(Inicializar);
		pruebas[2] = pruebas[0];
		cp->CorrerPruebas(pruebas.ObtenerIterador());
	}
	else {

		cout << endl << "--- Prueba por consola del Juego del 8 (Prioridad por defecto: A)---" << endl << endl;
		cout << "Ingrese la dimension del tablero: ";
		int n;
		cin >> n;
		cout << endl << "Ingrese el tablero. Una fila por linea, separando los numeros con espacios. Use 0 para la posicion libre." << endl;
		
		Matriz<int> bloques = Matriz<int>(n);

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> bloques[i][j];

		Puntero<Prioridad> prioridadA = new PrioridadA();
		Tablero* inicial = new Tablero(bloques, prioridadA);

		Puntero<Sistema> s = new Sistema();

		s->EstablecerTableroInicial(*inicial);

		cout << endl;

		if (!s->TieneSolucion())
		{
			cout << "Sin solucion." << endl;
		}
		else {
			Iterador<Tablero> pasos = s->Solucionar();

			pasos.Reiniciar();

			while (pasos.HayElemento())
			{
				cout << pasos.ElementoActual().Imprimir() << endl;
				pasos.Avanzar();
			}
			Cadena c = "Cantidad de movimientos requeridos = ";
			cout << endl << c << s->Movimientos() << endl;
		}
	}
	system("pause");
}
