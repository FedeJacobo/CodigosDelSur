#pragma once

#include "Tupla.h"
#include "Conversor.h"

template<class T1_1, class T1_2, class T2, class T3 = DatoNulo>
class ExpandirTupla1_2 : public Conversor<Tupla<Tupla<T1_1, T1_2>,T2,T3>, Tupla<T1_1,T1_2,T2,T3>>
{
protected:
	Tupla<T1_1,T1_2,T2,T3> Convertir(const Tupla<Tupla<T1_1, T1_2>,T2,T3>& t) const
	{
		return Tupla<T1_1,T1_2,T2,T3>(t.Dato1.Dato1, t.Dato1.Dato2, t.Dato2, t.Dato3);
	}
};
