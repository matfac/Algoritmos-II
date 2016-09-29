#include <iostream>
#include "mini_test.h"

#include "Conjunto.hpp"

void test_insertar() {
	Conjunto<int> c;
	c.insertar(42);
	c.insertar(43);
	ASSERT( c.pertenece(42) );

	// Chequear insertar más elementos
}

void test_cardinal() {
	// Completar
	Conjunto<int> c;
	c.insertar(42);
	c.insertar(43);
	c.insertar(44);
	c.insertar(45);
	c.insertar(46);
	ASSERT( c.cardinal() == 5 );
}

void test_remover() {
	// Chequear por lo menos los siguientes 3 casos:
 	// - Borrar una hoja
 	// - Borrar un nodo interno con un hijo
 	// - Borrrun nodo interno con dos hijos
 	Conjunto<int> c;
 	c.insertar(42);
 	c.insertar(44);
 	c.insertar(104);
 	c.insertar(450);
 	c.insertar(-46);
 	c.insertar(-460);
 	c.insertar(130);
 	c.insertar(43);

//	c.mostrar(std::cout);

	bool pertenencia;


	// caso que chequea borrar una hoja
	c.remover(44);
	//c.mostrar(std::cout);
	pertenencia = c.pertenece(42) && !c.pertenece(44) && c.pertenece(104)
				&& c.pertenece(450) && c.pertenece(-46) && c.pertenece(-460)
				&& c.pertenece(130) && c.pertenece(43);
 	ASSERT( pertenencia );

	std::cout << "@@@@@@@@@@@@@@"<<std::endl;

	Conjunto<int> d;
	d.insertar(55);
	d.remover(55);

	std::cout << "cardinal "<<d.cardinal() <<std::endl;
	ASSERT(d.cardinal() == 0 );

}

void test_maximo() {
	// Completar
 	ASSERT( false );
}

void test_minimo() {
	// Completar
	ASSERT( false );
}

int main() {

	RUN_TEST(test_insertar);
	RUN_TEST(test_cardinal);
	RUN_TEST(test_remover);
	RUN_TEST(test_maximo);
	RUN_TEST(test_minimo);
	return 0;
}
