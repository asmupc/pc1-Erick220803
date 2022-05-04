#include <iostream>
using namespace std;

template<typename T>
class CNodoP
{
public:
	CNodoP(T dato, CNodoP* siguiente) {
		this->dato = dato;
		this->siguiente = siguiente;
	}
	~CNodoP() {
	}
	T getDato() {
		return dato;
	}
	CNodoP* getSiguiente() {
		return siguiente;
	}
	void setDato(T dato) {
		this->dato = dato;
	}
	void setSiguiente(CNodoP* siguiente) {
		this->siguiente = siguiente;
	}

private:
	T dato;
	CNodoP* siguiente;
};

template<typename T>
class CPila
{
public:
	CPila() {
		this->tamanio = 0;
		this->top = nullptr;
		this->llena = false;
	}
	~CPila() {
	}
	int getTamanio() {
		return tamanio;
	}
	bool getLlena() {
		return llena;
	}
	CNodoP<T>* getTop() {
		return top;
	}
	void setTamanio(int tamanio) {
		this->tamanio = tamanio;
	}
	void setLlena(bool llena) {
		this->llena = llena;
	}
	void setTop(CNodoP<T>* top) {
		this->top = top;
	}
	bool full() {
		if (this->tamanio>0)
		{
			this->llena = true;
		}
		return llena;
	}
	bool empty() {
		if (this->tamanio == 0) {
			this->llena = false;
		}
		return llena;
	}
	void push(T nuevoValor) {
		CNodoP<T>* nuevoNodo = new CNodoP<T>(nuevoValor, this->top);
		this->top = nuevoNodo;
		this->tamanio++;
	}
	void pop() {
		if (full() == true) {
			CNodoP<T>* aux = this->top;
			this->top = aux->getSiguiente();
			delete aux;
			this->tamanio--;
		}
		else {
			cout << "La lista esta vacia";
		}
	}
	void seek() {
		cout << this->top->getDato() << endl;
	}
	void imprimirPila() {
		CNodoP<T>* aux = this->top;

		while (aux!=nullptr)
		{
			cout << aux->getDato() << " ";
			aux = aux->getSiguiente();
		}
		cout << endl;
	}
	
private:
	int tamanio;
	bool llena;
	CNodoP<T>* top;
};