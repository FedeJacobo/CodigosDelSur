Matriz<int> kruskal(Matriz<int> matAdy)
{
	int largo = matAdy.ObtenerLargo();
	int cantAristas = 0;
	// Creo matriz a retornar, la cual debe ser de tamaño igual a matAdy y tener INF en todos lados
	Matriz<int> ret = Matriz<int>(largo);
	for(int i = 0; i < largo; i++)
		for(int j = 0; j < largo; j++)
			ret[i][j] = INF;
		
	// Creo cola de prioridad, y agrego una por una todas las aristas, con formato <prioridad, Tupla<origen, destino> >
	Puntero<ColaPrioridad<int, Tupla<int, int> > > aristasOrdenadas = new ColaPrioridadHeap<int, Tupla<int, int> >(largo);
	for(int i = 0; i < largo; i++)
		for(int j = 0; j < largo; j++)
			if(matAdy[i][j] != INF)
				aristasOrdenadas.insertar(matAdy[i][j], Tupla<int, int>(i, j));
	
	// Armo arreglo con las distintas componentes conexas. Inicialmente, cada nodo será una componente conexa.
	Array<Puntero<Set<int> > > compsConexas = Array<Puntero<Set<int> > >(largo);
	for(int i = 0; i < largo; i++)
	{
		Puntero<Set<int> > nuevo = new Set<int>();
		nuevo -> insertar(i);
		compsConexas[i] = nuevo;
	}
	
	// Intento colocar nuevas aristas mientras no tenga |V| - 1 aristas y tenga elementos en la cola
	while(!aristasOrdenadas.esVacia() && cantAristas < largo - 1)
	{
		Tupla<int, int> arista = aristasOrdenadas.borrarMin();
		// Hallo la posición de las componentes conexas del origen y el destino
		int posOrigen = -1, posDestino = -1;
		for(int i = 0; i < largo; i++){
			Puntero<Set<int> > comp = compsConexas[i];
			if(comp -> pertenece(arista.ObtenerDato1()))
				posOrigen = i;
			if(comp -> pertenece(arista.ObtenerDato2()))
				posDestino = i;
		}
		// Si están en la misma componente conexa ignoro a la arista
		if(posOrigen == posDestino)
			continue;
		
		// Uno las componentes conexas
		compsConexas[posOrigen] -> union(compsConexas[posDestino] -> Clon());
		compsConexas[posDestino] -> vaciar();
		
		// Agrego la arista
		ret[arista.ObtenerDato1()][arista.ObtenerDato2()] = matAdy[arista.ObtenerDato1()][arista.ObtenerDato2()];
		ret[arista.ObtenerDato2()][arista.ObtenerDato1()] = matAdy[arista.ObtenerDato2()][arista.ObtenerDato1()];
		cantAristas++;		
	}
	return ret;
}