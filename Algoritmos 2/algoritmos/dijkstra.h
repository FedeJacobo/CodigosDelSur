int dijkstra(int posOrigen, int posDestino){
	Array<int> dist = Array<int>(tope);
	Array<int> ant = Array<int>(tope);
	Array<bool> vis = Array<bool>(tope);
	
	for(int i = 0; i < tope; dist[i] = INF, ant[i] = -1, vis[i] = false, i++);
	
	dijkstraInterno(posOrigen, dist, ant, vis);
	
	return dist[posDestino];
}


void dijkstraInterno(int posOrigen, Array<int>& dist, Array<int>& ant, Array<bool>& vis){
	// Inicializo el origen
	dist[posOrigen] = 0;
	vis[posOrigen] = true;
	// Seteo distancias del origen a sus adyacentes
	for(int i = 0; i < tope; i++)
	{
		if(matAdy[posOrigen][i] != 0)
		{
			dist[i] = matAdy[posOrigen][i];
			ant[i] = posOrigen;
		}
	}
	
	// Comienzo proceso iterativo
	for(int k = 1; k < tope; k++)
	{
		// Encuentro candidato
		int min = INF, posMin = -1;
		for(int i = 0; i < tope; i++){
			if(!vis[i] && dist[i] < min)
			{
				min = dist[i];
				posMin = i;
			}
		}
		// Si no hay adyacentes no visitados, me voy
		if(posMin == -1)
			return;
		
		vis[posMin] = true;
		
		// Actualizo distancias del candidato (posMin)
		for(int i = 0; i < tope; i++){
			if(!vis[i] && matAdy[posMin][i] != 0)
			{
				int distCandidata = dist[posMin] + matAdy[posMin][i];
				if(distCandidata < dist[i])
				{
					dist[i] = distCandidata;
					ant[i] = posMin;
				}
			}
		}
	}
}