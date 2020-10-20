#pragma once

#include "Tupla.h"
#include "Conversor.h"

template<class T1_1, class T1_2, class T1_3, class T2>
class ExpandirTupla1_3 : public Conversor<Tupla<Tupla<T1_1, T1_2, T1_3>,T2>, Tupla<T1_1,T1_2,T1_3,T2>>
{
protected:
	Tupla<T1_1,T1_2,T1_3,T2> Convertir(const Tupla<Tupla<T1_1, T1_2, T1_3>,T2>& t) const
	{
		return Tupla<T1_1,T1_2,T1_3,T2>(t.Dato1.Dato1, t.Dato1.Dato2, t.Dato1.Dato3, t.Dato2);
	}
};
