#pragma once

#include "Tupla.h"
#include "Conversor.h"

template<class T1, class T2_1, class T2_2, class T3 = DatoNulo>
class ExpandirTupla2_2 : public Conversor<Tupla<T1,Tupla<T2_1, T2_2>,T3>, Tupla<T1,T2_1,T2_2,T3>>
{
protected:
	Tupla<T1,T2_1,T2_2,T3> Convertir(const Tupla<T1,Tupla<T2_1, T2_2>,T3>& t) const
	{
		return Tupla<T1,T2_1,T2_2,T3>(t.Dato1, t.Dato2.Dato1, t.Dato2.Dato2, t.Dato3);
	}
};
