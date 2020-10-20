#pragma once

#include "Tupla.h"
#include "Conversor.h"

template<class T1, class T2_1, class T2_2, class T2_3>
class ExpandirTupla2_3 : public Conversor<Tupla<T1,Tupla<T2_1, T2_2, T2_3>>, Tupla<T1,T2_1,T2_2,T2_3>>
{
protected:
	Tupla<T1,T2_1,T2_2,T2_3> Convertir(const Tupla<T1,Tupla<T2_1, T2_2, T2_3>>& t) const
	{
		return Tupla<T1,T2_1,T2_2,T2_3>(t.Dato1, t.Dato2.Dato1, t.Dato2.Dato2, t.Dato2.Dato3);
	}
};
