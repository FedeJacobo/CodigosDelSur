#include "MemoryShare.h"
#include <Assert.h>

MemoryShare::MemoryShare()
: m_Used(nullptr)
{
}

MemoryShare::~MemoryShare()
{
	DecrementarContador();
}

void MemoryShare::AsignarMemoria(const char* typeName, void* memoria, void (*liberar)(void*), bool esPuntero)
{
	MemoryUsage* used = nullptr;
	if (memoria != nullptr)
	{
		used = GetFromGeneralUse(memoria);
		if (used == nullptr)
		{
			if (s_FreeCount == 0)
				used = new MemoryUsage();
			else
			{
				used = s_FreeUsage;
				s_FreeUsage = s_FreeUsage->NextUsage;
				s_FreeCount--;
			}
			used->TypeName = typeName;
			used->Contador = 1;
			used->Memoria = memoria;
			used->Liberar = liberar;
			used->Info = esPuntero ? PUNTERO : ARRAY;
			AddToGeneralUse(used);
		}
		else if (m_Used != used)
			IncrementarContador(used);
	}
	if (m_Used == used)
		return;
	// this dejará de usar el contador actual, por lo tanto
	// se decrementa el contador, si como resultado el contador queda en 0,
	// entonces se invoca a liberarMemoria
	DecrementarContador();
	m_Used = used;
}

void MemoryShare::IncrementarContador(MemoryUsage* used)
{
	if (used != nullptr)
	{
		assert(used->Contador > 0);
		used->Contador++;
	}
}

void MemoryShare::DecrementarContador()
{
	if (m_Used != nullptr)
	{
		switch (m_Used->Contador)
		{
		case 0:
			assert(false);
			break;
		case 1:
			//assert(FueUtilizado());
			m_Used->Liberar(m_Used->Memoria);
			RemoveFromGeneralUse(m_Used);
			if (s_FreeCount < MAX_USE_CACHE)
			{
				m_Used->Contador = 0;
				m_Used->Memoria = nullptr;
				m_Used->Liberar = nullptr;
				m_Used->TypeName = nullptr;
				m_Used->NextUsage = s_FreeUsage;
				s_FreeUsage = m_Used;
				s_FreeCount++;
			}
			else
				delete m_Used;
			m_Used = nullptr;
			break;
		default:
			m_Used->Contador--;
			break;
		}
	}
}

void MemoryShare::RemoveFromGeneralUse(MemoryUsage* usage)
{
	int pos = reinterpret_cast<unsigned int>(usage->Memoria) / 4 % MEMORY_BUCKETS;
	if (s_GeneralUse[pos] == nullptr)
		assert(false);
	else 
	{
		if (s_GeneralUse[pos] == usage)
			s_GeneralUse[pos] = usage->NextUsage;
		else
		{
			MemoryUsage* lista = s_GeneralUse[pos];
			while (lista->NextUsage != nullptr && lista->NextUsage != usage)
				lista = lista->NextUsage;
			if (lista->NextUsage != nullptr)
				lista->NextUsage = usage->NextUsage;
			else
				assert(false);
		}

		if (usage == s_FirstCheck[pos])
			s_FirstCheck[pos] = s_FirstCheck[pos]->NextUsage;
	}
}

void MemoryShare::AddToGeneralUse(MemoryUsage* usage)
{
	int pos = reinterpret_cast<unsigned int>(usage->Memoria) / 4 % MEMORY_BUCKETS;
	usage->NextUsage = s_GeneralUse[pos];
	s_GeneralUse[pos] = usage;
}

MemoryShare::MemoryUsage* MemoryShare::GetFromGeneralUse(void* memoria)
{
	int pos = reinterpret_cast<unsigned int>(memoria) / 4 % MEMORY_BUCKETS;
	MemoryUsage* usage = s_GeneralUse[pos];
	while (usage != nullptr)
	{
		if (usage->Memoria == memoria)
			return usage;
		usage = usage->NextUsage;
	}
	return nullptr;
}

MemoryShare::MemoryUsage* MemoryShare::s_GeneralUse[MEMORY_BUCKETS];
MemoryShare::MemoryUsage* MemoryShare::s_FirstCheck[MEMORY_BUCKETS];
MemoryShare::MemoryUsage* MemoryShare::s_FreeUsage = nullptr;
unsigned int MemoryShare::s_FreeCount = 0;

bool MemoryShare::FueUtilizado() const
{
	return m_Used == nullptr || (m_Used->Info & USADO) == USADO;
}

//void MemoryShare::MarcarUtilizado() const
//{
//	if (m_Used != nullptr)
//		m_Used->Info = (MemoryInfo) (m_Used->Info | USADO);
//}
