#include "Pila.h"

Pila::Pila(){
  this->prim = NULL;
  this->tam = 0;
}


Pila::~Pila(){
  vacia();
}


void Pila::vacia(){
  while(this->tam>0){
    desapilar();
  }
}

void Pila::apilar(ElemPila& elem){

  Nodo* nodoNuevo = new Nodo;
  nodoNuevo->sig = NULL;
  nodoNuevo->elem = elem;

  if(this->tam == 0){
    this->prim = nodoNuevo;
  } else {
    Nodo* actual = this->prim;
    while(actual->sig != NULL){
      actual = actual->sig;
    }
    actual->sig = nodoNuevo;
  }

  this->tam++;
}

bool Pila::esVacia(){

  if(this->tam == 0){
    return true;
  }
  return false;
}

ElemPila& Pila::tope(){
  Nodo* actual = this->prim;

  while(actual->sig !=NULL){
    actual = actual->sig;
  }

  return actual->elem;
}

ElemPila Pila::desapilar(){
  Nodo* actual = this->prim;
  Nodo* anterior = this->prim;

  while(actual->sig !=NULL){
    anterior = actual;
    actual = actual->sig;
  }

  ElemPila elemento = actual->elem;
  anterior->sig = NULL;
  delete actual;
  this->tam--;

  return elemento;
}

Nat Pila::tamanio() const{
  return this->tam;
}

Pila& Pila::operator=(const Pila & aCopiar){
  vacia();
  Nodo* actual = aCopiar.prim;

  while(actual != NULL){
      apilar(actual->elem);
      actual = actual->sig;
  }
  return *this;
}

void Pila::mostrar(ostream& os) const{
  Nodo* actual = this->prim;
  os<<"[";
  while(actual!=NULL){
    os << actual->elem;
    if(actual->sig !=NULL){
      os <<",";
    }
    actual = actual->sig;
  }
  os<<"]";
}
