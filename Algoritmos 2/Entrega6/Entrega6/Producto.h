#ifndef PRODUCTO_H
#define PRODUCTO_H

typedef unsigned int nat;

struct Producto
{
	nat calorias;
	nat precio;
	nat alcohol;
	nat maxUnidades;
	nat preferencia;

	Producto(){};

	Producto(nat calorias, nat precio, nat alcohol, nat maxUnidades, nat preferencia)
	{
		this->calorias = calorias;
		this->precio = precio;
		this->alcohol = alcohol;
		this->maxUnidades = maxUnidades;
		this->preferencia = preferencia;
	};
};

#endif