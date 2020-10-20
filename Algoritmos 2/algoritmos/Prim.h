Matriz<int> prim(Matriz<int> matAdy)
{
	int largo = matAdy.ObtenerLargo();
	// Creo arreglo de visitados, inicializado completamente en false
	Array<bool> vis = Array<bool>(largo, false);
	
	// Creo matriz a retornar, la cual debe ser de tamaño igual a matAdy y tener INF en todos lados
	Matriz<int> ret = Matriz<int>(largo);
	for(int i = 0; i < largo; i++)
		for(int j = 0; j < largo; j++)
			ret[i][j] = INF;
	
	// Elijo uno al azar, y lo visito
	vis[0] = true;
	
	// Busco reiteradamente la mejor conexión (la más chica) entre un visitado y un no visitado
	for(int k = 0; k < largo; k++)
	{
		int posOrigen = -1, posDestino = -1, min = INF;
		// Evaluo cada visitado
		for(int i = 0; i < largo; i++)
		{
			if(vis[i])
			{
				// Cotejo con no visitados
				for(int j = 0; j < largo; j++)
				{
					// Si tengo arista, y es el menor valor hasta ahora, actualizo
					if(!vis[j] && matAdy[i][j] < min)
					{
						min = matAdy[i][j];
						posOrigen = i;
						posDestino = j;
					}
				}
			}
		}
		
		// Si no encontré mínimo me voy, ya que no hay más aristas
		if(min == INF)
			return ret;
		
		// Ingreso la arista en la matriz a retornar, visitando al vértice destino
		ret[posOrigen][posDestino] = min;
		ret[posDestino][posOrigen] = min;
		vis[posDestino] = true;
	}
	return ret;	
}