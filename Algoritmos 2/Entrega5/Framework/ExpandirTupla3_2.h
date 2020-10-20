#pragma once

#include "Tupla.h"
#include "Conversor.h"

template<class T1, class T2, class T3_1, class T3_2>
class ExpandirTupla3_2 : public Conversor<Tupla<T1,T2,Tupla<T3_1, T3_2>>, Tupla<T1,T2,T3_1,T3_2>>
{
protected:
	Tupla<T1,T2,T3_1,T3_2> Convertir(const Tupla<T1,T2,Tupla<T3_1, T3_2>>& t) const
	{
		return Tupla<T1,T2,T3_1,T3_2>(t.Dato1, t.Dato2, t.Dato3.Dato1, t.Dato3.Dato2);
	}
};
