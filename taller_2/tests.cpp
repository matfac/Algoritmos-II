#include "Pila.h"
#include "mini_test.h"
#include "TiposBasicos.h"

// para compilar:
//   $ g++ -g tests.cpp -o tests
// para ejecutar con valgrind:
//   $ valgrind --leak-check=full -v ./tests

// ========================================================================== //

template<typename T>
std::string to_s(const T& m) {
 	std::ostringstream os;
	os << m;
	return os.str();
}

// ========================================================================== //

/**
 * Esto es una clase sin operador asignación. Sirve para testear
 * que estén utilizando el constructor por copia al asignar los elementos
 * de la colección.
 */
class Punto
{
  public:

    Punto(aed2::Nat x, aed2::Nat y)
      : x_(x), y_(y)
    {}

    Punto(const Punto& otro)
      : x_(otro.x_), y_(otro.y_)
    {}

    friend std::ostream& operator << (std::ostream& os, const Punto& punto);

  private:

    aed2::Nat x_, y_;

    Punto& operator = (const Punto&);
};

std::ostream& operator << (std::ostream& os, const Punto& punto)
{
  return os << "(" << punto.x_ << "," << punto.y_ << ")";
}

// ========================================================================== //

void test_vacia()
{
  Pila<aed2::Nat> p;
  ASSERT_EQ(p.tamanio(), 0);
  ASSERT_EQ(to_s(p), "[]");
}

void test_apilar_uno()
{
  Pila<aed2::Nat> p;

  p.apilar(1);

  ASSERT_EQ(p.tamanio(), 1);
  ASSERT_EQ(to_s(p), "[1]");
}

void test_apilar()
{
  ASSERT(true);
}

void test_tope()
{
  ASSERT(true);
}

void test_desapilar()
{
  ASSERT(true);
}

void test_constructor_copia()
{
  ASSERT(true);
}

void test_asignacion()
{
  ASSERT(true);
}

void copiar_sin_asignacion()
{
  Pila<Punto> pp;

  pp.apilar(Punto(1, 0));

  ASSERT_EQ(to_s(pp), "[(1,0)]");

  pp.apilar(Punto(3, 2));

  ASSERT_EQ(to_s(pp), "[(3,2), (1,0)]");
}

void pila_de_pilas()
{
  Pila<Pila<aed2::Nat> > pp;

  {
    Pila<aed2::Nat> p;
    p.apilar(1);
    p.apilar(2);
    pp.apilar(p);
  }

  ASSERT_EQ(pp.tamanio(), 1);

  ASSERT_EQ(to_s(pp), "[[2, 1]]");

  {
    Pila<aed2::Nat> p;
    p.apilar(3);
    p.apilar(4);

    pp.apilar(p);
  }

  ASSERT_EQ(pp.tamanio(), 2);
  ASSERT_EQ(to_s(pp), "[[4, 3], [2, 1]]");

  {
    Pila<aed2::Nat> p;
    p.apilar(5);
    p.apilar(6);

    pp.apilar(p);
  }

  ASSERT_EQ(pp.tamanio(), 3);
  ASSERT_EQ(to_s(pp), "[[6, 5], [4, 3], [2, 1]]");
}

void copiar_pila_de_pilas()
{
  ASSERT(true);
}

int main()
{
  RUN_TEST(test_vacia);
  RUN_TEST(test_apilar_uno);
  RUN_TEST(test_apilar);
  RUN_TEST(test_tope);
  RUN_TEST(test_desapilar);
  RUN_TEST(test_constructor_copia);
  RUN_TEST(test_asignacion);
  RUN_TEST(copiar_sin_asignacion);
  RUN_TEST(pila_de_pilas);
  RUN_TEST(copiar_pila_de_pilas);

  return 0;
}
