#ifndef CONJUNTO_HPP_
#define CONJUNTO_HPP_

#include <iostream>
#include <stack>
using namespace std;

template <class T>
class Conjunto
{
	public:

		// Constructor. Genera un conjunto vacío.
		Conjunto();

		// Destructor. Debe dejar limpia la memoria.
		~Conjunto();

		// Inserta un elemento en el conjunto. Si éste ya existe,
		// el conjunto no se modifica.
		void insertar(const T&);

		// Decide si un elemento pertenece al conjunto o no.
		bool pertenece(const T&) const;

		// borra un elemento del conjunto. Si éste no existe,
		// el conjunto no se modifica.
		void remover(const T&);

		// devuelve el mínimo elemento del conjunto según <.
		const T& minimo() const;

		// devuelve el máximo elemento del conjunto según <.
		const T& maximo() const;

		// devuelve la cantidad de elementos que tiene el conjunto.
		unsigned int cardinal() const;

		// muestra el conjunto.
		void mostrar(std::ostream&) const;

		friend ostream& operator<<(ostream& os, const Conjunto<T> &c) {
			c.mostrar(os);
			return os;
		}

	private:

		// la representación de un nodo interno.
		struct Nodo
		{
			// el constructor, toma el elemento al que representa el nodo.
			Nodo(const T& v);
			// el elemento al que representa el nodo.
			T valor;
			// puntero a la raíz del subárbol izq.
			Nodo* izq;
			// puntero a la raíz del subárbol der.
			Nodo* der;
		};

		// puntero a la raíz de nuestro árbol.
		Nodo* raiz_;

		const unsigned int hijos(const Nodo* hijo) const;
		void removerHijo(Nodo* elPadre, Nodo* elHijo);
		void remover2Hijos(Nodo* elPadre, Nodo* elHijo);
		void remover1Hijo(Nodo* elPadre, Nodo* elHijo);
		unsigned int contarHijos(Nodo* nodo) const;
		void buscar(Nodo* &elPadre, Nodo* &elHijo, const T& clave) const;

	// funciones auxiliares



};

template <class T>
Conjunto<T>::Nodo::Nodo(const T& v)
	 : valor(v), izq(NULL), der(NULL)
{}

template <class T>
Conjunto<T>::Conjunto() : raiz_(NULL)
{}

template <class T>
Conjunto<T>::~Conjunto()
{
	while(cardinal()!= 0) remover(raiz_->valor);
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const
{
	Nodo* actual = raiz_;

	while (actual != NULL && actual->valor != clave){
		if(clave <  actual->valor ) { actual = actual->izq; } else { actual = actual->der;}
	}

	return actual!=NULL;
}

template <class T>
void Conjunto<T>::insertar(const T& clave)
{
	Nodo* actual  = raiz_;
	Nodo* previo  = raiz_;
	Nodo* nuevoNodo = new Nodo(clave);

	if(raiz_ == NULL){
		raiz_ = nuevoNodo;
		return;
	}

	while(actual!=NULL){
		previo = actual;
		if(clave == actual->valor) return;
		else if( clave < actual->valor ) actual = actual->izq;
		else actual = actual->der;
	}

	if(clave < previo->valor) previo->izq = nuevoNodo;
	else previo->der = nuevoNodo;

}

template <class T>
unsigned int Conjunto<T>::cardinal() const
{
	return contarHijos(raiz_);
}

template <class T>
unsigned int Conjunto<T>::contarHijos(Nodo* nodo) const {
	if(nodo == NULL) return 0;
	else return (1 + (contarHijos(nodo->izq) + contarHijos(nodo->der)));
}

template <class T>
void Conjunto<T>::remover(const T& clave)
{

	Nodo* elPadre = NULL;
	Nodo* elHijo = NULL;

	buscar(elPadre, elHijo, clave);

	std::cout << "nodos padre" << elPadre << " con valor " << elPadre->valor << std::endl;
	std::cout << "nodo hijo" << elHijo  << " con valor " << elHijo->valor <<std::endl;
	std::cout << "cantidad de hijos " <<hijos(elHijo) << std::endl;
	//Pone padre e hijo en sus nodos correspondientes.
	if (elHijo == NULL){ return; }
	if (hijos(elHijo) == 2) {
		remover2Hijos(elPadre, elHijo); }
	else if (hijos(elHijo) == 1) {
		remover1Hijo(elPadre, elHijo); }
	else { removerHijo(elPadre, elHijo); }
}

template <class T>
void Conjunto<T>::buscar(Nodo* &elPadre, Nodo* &elHijo, const T& clave) const {
	Nodo* actual = raiz_;
	Nodo* previo = raiz_;

	while(actual!=NULL && actual->valor != clave){
		previo = actual;
		std::cout << actual->valor << " vs " << clave << std::endl;
		if(clave < actual->valor) {actual = actual->izq; }
		else actual = actual->der;
	}

	std::cout << "nodos padre" << elPadre << std::endl;
	std::cout <<"nodo hijo"<< elHijo <<std::endl;

	elPadre = previo;
	elHijo = actual;
}


template <class T>
const unsigned int Conjunto<T>::hijos(const Nodo* hijo) const {
	if(hijo->der !=NULL && hijo->izq !=NULL) return 2;
	else if(hijo->der !=NULL || hijo->izq !=NULL) return 1;
	else return 0;
}

template <class T>
void Conjunto<T>::remover2Hijos(Nodo* elPadre, Nodo* elHijo){
	std::cout << "tiene dos hijos"<< std::endl;
	Nodo* actual = elHijo->izq;
	Nodo* previo = elHijo;
	while(actual!=NULL){
		previo = actual;
		actual = actual->der;
	}

	T aux = (previo->valor);
	std::cout << previo->valor << std::endl;
	remover(aux);
	elHijo->valor = aux;
}

template <class T>
void Conjunto<T>::remover1Hijo(Nodo* elPadre, Nodo* elHijo){
	std::cout << "tiene un hijo"<< std::endl;

	if(elHijo->der == NULL) {
		if(elHijo->valor == elPadre->valor){
			raiz_ = elHijo->izq;
		} else{
		if(elHijo->valor < elPadre->valor) elPadre->izq = elHijo->izq;
		else elPadre->der = elHijo->izq;}
	}
	else{
		if(elHijo->valor == elPadre->valor){
			raiz_ = elHijo->der;
		} else {
			if(elHijo->valor < elPadre->valor) elPadre->izq = elHijo->der;
			else elPadre->der = elHijo->der;
		}
	}
	delete elHijo;
}

template <class T>
void Conjunto<T>::removerHijo(Nodo* elPadre, Nodo* elHijo){
	if(elPadre != NULL){
		if(elHijo->valor < elPadre->valor) { elPadre->izq = NULL; }
		else if( elPadre->valor == elHijo->valor) { raiz_ = NULL;}
		else { elPadre->der = NULL; }
		delete elHijo;
	}
}

template <class T>
const T&  Conjunto<T>::minimo() const
{
	Nodo* actual = raiz_;

	while(actual->izq!=NULL){
			actual = actual->izq;
	}

	return actual->valor;
}

template <class T>
const T&  Conjunto<T>::maximo() const
{
	Nodo* actual = raiz_;

	while(actual->der!=NULL){
			actual = actual->der;
	}

	return actual->valor;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream& os) const {
	stack<Nodo*> pila;
	Nodo* next = raiz_;
	do {
		if (next != NULL) {
			//os << next -> valor << " "; //preorder
			pila.push(next);
			next = next -> izq;
		} else {
			next = pila.top(); pila.pop();
			os << next -> valor << " "; //inorder
			next = next -> der;
		}
		// y postorder?? Se puede con este esquema?
	} while (!pila.empty() or next != NULL);
	os << endl;
}

#endif // CONJUNTO_HPP_
