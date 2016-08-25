#include "Pila.h"
#include "mini_test.h"

// para compilar:$ g++ -g tests.cpp Pila.cpp -o Pila
// para ejecutar con valgrind:$ valgrind --leak-check=full -v ./Pila

void test_vacia() {
  Pila p;
  ASSERT_EQ(p.tamanio(), 0);
}

void test_apilar() {
  Pila p;

  for(int i = 0; i < 5; i++){
    ElemPila elemento;
    elemento.id = i;
    elemento.nombre = "lucas";
    elemento.descripcion = "Esto es una desc";
    p.apilar(elemento);
  }

  ASSERT_EQ(p.tamanio(), 5);
}

void test_desapilar() {
  Pila p;

  for(int i = 0; i < 5; i++){
    ElemPila elemento;
    elemento.id = i;
    elemento.nombre = "lucas";
    elemento.descripcion = "Esto es una desc";
    p.apilar(elemento);
  }

  for(int i = 0; i < 5; i++){
    p.desapilar();
  }

  ASSERT_EQ(p.tamanio(), 0);
}

void test_asignacion() {
  bool asignacion = true;

  Pila p1;
  Pila p2;

  for(int i = 0; i < 5; i++){
    ElemPila elemento;
    elemento.id = i;
    elemento.nombre = "lucas";
    elemento.descripcion = "Esto es una desc";
    p2.apilar(elemento);
  }


  p1 = p2;
  bool mismoTamanio = p1.tamanio() == p2.tamanio();
  int tamanio = p2.tamanio();
  while(tamanio > 0){
    tamanio--;
    ElemPila epila1 = p1.desapilar();
    ElemPila epila2 = p2.desapilar();
    if(epila1.id != epila2.id || epila1.nombre != epila2.nombre || epila1.descripcion != epila2.descripcion){
      asignacion = false;
    }
  }

  ASSERT(asignacion && mismoTamanio);
}

int main() {
  RUN_TEST(test_vacia);
  RUN_TEST(test_apilar);
  RUN_TEST(test_desapilar);
  RUN_TEST(test_asignacion);
  // HACER MAS TEST
  return 0;
}
