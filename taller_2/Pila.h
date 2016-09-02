#include <ostream>
#include "TiposBasicos.h"

/**
 * Esta clase representa una Pila de objetos de tipo genérico T.
 *
 * ATENCION: Las únicas cosas que se pueden asumir sobre 'T' es que tiene
 * definido el constructor por copia, el operador '<< (std::ostream&)' y
 * el operador de comparación '=='.
 */
template <typename T>
class Pila
{
  public:

    // Constructor sin parámetros. Crea una pila vacía.
    Pila();

    // Constructor por copia. Crea una nueva instancia de una Pila
    // que debe ser igual a la pasada por parámetro.
    Pila(const Pila& otra);

    // Destructor. Limpia toda la memoria dinámica que aún esté en uso.
    ~Pila();

    // El constructor puede ser visto como un generador
    void apilar(const T& elem);

    // En este caso, a diferencia del TAD, desapilar cambia el estado interno de mi instancia de clase
    // PRE: la pila no es vacía
    void desapilar();

  // Observadores básicos

    // Devuelve true si la Pila es vacía, false en caso contrario.
    bool esVacia() const;

    // Devuelve una referencia al elemento en el tope de la Pila.
    // PRE: La Pila no está vacía.
    T& tope();

    // Devuelve una referencia al elemento en el tope de la Pila.
    // PRE: La Pila no está vacía.
    const T& tope() const;

  // Otras operaciones

    // Devuelve la cantidad de elementos que hay en la pila.
    aed2::Nat tamanio() const;

    // Modifica esta instancia de Pila de tal manera que termine
    // siendo una copia de la Pila pasada por parámetro.
    // Devuelve una referencia a si misma.
    Pila& operator = (const Pila& otra);

    // IMPLEMENTACION OPCIONAL (no va a ser evaluada).
    // Compara dos instancias de Pila. Devuelve true si son iguales
    // y false en caso contrario.
    bool operator == (const Pila& otra) const;

    /**
     * Muestra la lista en un ostream.
     * formato de salida:
     *   [e_0, e_1, e_2, ...]
     * donde e_i es el resultado del "mostrar" el elemento i.
     * PRE: está definido el operador '<<' para los elementos de tipo 'T'.
     *
     * Nota: imprimir sobre os, es decir: os << "[" << ...
     *
     * ATENCION:
     *
     *  - entre elemento y elemento de la pila debe haber una coma y un espacio.
     *
     *  - El primer elemento que se muestra representa al tope de la pila, es
     *    decir, los elementos se muestran en orden inverso al que fueron apilados.
     */
    template<typename S>
    friend std::ostream& operator << (std::ostream& os, const Pila<S>& pila);

  private:

    struct Nodo {
      T* elem;
      Nodo *sig;

      Nodo(){
        this->elem = NULL;
        this->sig = NULL;
      }

      Nodo(const T& elem)
      {
        this->elem = new T(elem);
        this->sig = NULL;
      }

      Nodo(const T& elem, Nodo* next)
      :sig(next){
        this->elem = new T(elem);
      }

      Nodo(const Nodo &n) {
         this->elem = new T(*n.elem);
         this->sig = n.sig;
      }

      ~Nodo(){
        delete this->elem;
      }

    };

    Nodo* tope_;
    aed2::Nat tamanio_;
};

template <typename T>
Pila<T>::Pila()
{
  tope_ = NULL;
  tamanio_ = 0;
}

template <typename T>
Pila<T>::Pila(const Pila& otra)
{
    tamanio_ = otra.tamanio_;
    Nodo* currentOther = otra.tope_;
    Nodo* current = NULL;
    tope_ = NULL;

    while(currentOther !=NULL){
      Nodo* aux = new Nodo(*(currentOther->elem));

      if(tope_ == NULL){
        tope_ = aux;
      } else {
        current->sig = aux;
      }
      current = aux;
      currentOther = currentOther->sig;
  }
}
  /**
  Alternativa original, no pasa el test de copia pila-pila
  **/
  // Nodo * actual = otra.tope_;
  // while(actual != NULL){
  //     apilar(*(actual->elem));
  //     actual = actual->sig;
  // }

  /**
  Esta opcion es mas limpia, tira el mismo error de memoria, con lo cual no es problematica pero
  No me cierra la copia del nodo. (la parte de n.sig)
  **/
  // tamanio_ = otra.tamanio_;
  //
  // if(otra.tope_!=NULL){
  //
  //   Nodo* current = new Nodo(*otra.tope_);
  //   tope_ = current;
  //   Nodo* currentOtra = otra.tope_;
  //
  //   while(currentOtra->sig !=NULL){
  //     currentOtra = currentOtra->sig;
  //     current->sig = new Nodo(*currentOtra);
  //   }
  //
  // } else {
  //   tope_ = NULL;
  // }

template <typename T>
Pila<T>::~Pila()
{
  while(tope_!=NULL){
    desapilar();
  }
}

template <typename T>
void Pila<T>::apilar(const T& elem)
{
  Nodo* nuevoNodo = new Nodo(elem, tope_);
  tope_ = nuevoNodo;
  tamanio_ ++;
}
/**
Otra opción horrible de apilar.

Nodo* nodoNuevo = new Nodo(elem);

if(tamanio_ == 0){
  tope_ = nodoNuevo;
  tamanio_++;
  return;
}
nodoNuevo->sig = tope_;
tope_ = nodoNuevo;
tamanio_++;

**/

template <typename T>
void Pila<T>::desapilar()
{
  Nodo *aux = tope_;
  tope_ = aux->sig;
  delete aux;
  tamanio_ --;
}
/**
Opcion anterior de desapilar, menos elegante, retiraba el primero tipo queue

Nodo* actual = tope_;
Nodo* anterior = tope_;

while(actual->sig !=NULL){
  anterior = actual;
  actual = actual->sig;
}

anterior->sig = NULL;
delete actual;
tamanio_--;
**/

template <typename T>
bool Pila<T>::esVacia() const
{
  return tope_ == NULL;
}

template <typename T>
T& Pila<T>::tope()
{
  return *(tope_->elem);
}

template <typename T>
const T& Pila<T>::tope() const
{
  return *(tope_->elem);
}

template <typename T>
aed2::Nat Pila<T>::tamanio() const
{
  return tamanio_;
}

template <typename T>
Pila<T>& Pila<T>::operator = (const Pila& otra)
{

  while(tope_!=NULL){
    desapilar();
  }

  typename Pila<T>::Nodo * actual = otra.tope_;

  while(actual != NULL){
      apilar(*(actual->elem));
      actual = actual->sig;
  }
  return *this;
}

template <typename T>
std::ostream& operator << (std::ostream& os, const Pila<T>& pila)
{
  typename Pila<T>::Nodo * actual = pila.tope_;

  os<<"[";

  while(actual!=NULL){
    os << *(actual->elem);
    if(actual->sig !=NULL){
      os<< ", ";
    }
    actual = actual->sig;
  }

  os<<"]";

  return os;
}
