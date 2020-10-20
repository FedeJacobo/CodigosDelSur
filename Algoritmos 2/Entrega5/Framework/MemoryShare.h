#pragma once

#pragma warning(error:4150; error:4172; error:4700; error:4715; error:4018)

class PruebaMemoria;

#define MEMORY_BUCKETS 1031
#define MAX_USE_CACHE MEMORY_BUCKETS * 10

class MemoryShare abstract
{
	friend class PruebaMemoria;

public:
	virtual ~MemoryShare();

private:
	enum MemoryInfo : unsigned char
	{
		PUNTERO = 1,
		ARRAY = 2,
		USADO = 4
	};
	struct MemoryUsage
	{
		const char* TypeName;
		unsigned int Contador;
		void* Memoria;
		void (*Liberar)(void* memoria);
		MemoryInfo Info;
		MemoryUsage* NextUsage;
	};

	MemoryUsage* m_Used;

	static void IncrementarContador(MemoryUsage* used);
	void DecrementarContador();
	bool FueUtilizado() const;

	static void RemoveFromGeneralUse(MemoryUsage* usage);
	static void AddToGeneralUse(MemoryUsage* usage);
	static MemoryUsage* GetFromGeneralUse(void* memoria);

	static MemoryUsage* s_GeneralUse[MEMORY_BUCKETS];
	static MemoryUsage* s_FirstCheck[MEMORY_BUCKETS];
	static MemoryUsage* s_FreeUsage;
	static unsigned int s_FreeCount;

protected:
	MemoryShare();
	//void MarcarUtilizado() const;
	void AsignarMemoria(const char* typeName, void* memoria, void (*liberar)(void*), bool esPuntero);
};
