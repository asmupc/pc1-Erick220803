#include<iostream>
using namespace std;

template <typename T>
class CNodo {
private:
    T dato;
    CNodo* siguiente;
public:
    CNodo(T dato, CNodo* siguiente) {
        this->dato = dato;
        this->siguiente = siguiente;
    }
    ~CNodo() {
    }
    T getDato() {
        return dato;
    }
    CNodo* getSiguiente() {
        return siguiente;
    }
    void setDato(T dato) {
        this->dato = dato;
    }
    void setSiguiente(CNodo* siguiente) {
        this->siguiente = siguiente;
    }
};

template <typename T>
class CListaSimple {
private:
    int tamanio;
    CNodo<T>* inicio;
public:
    CListaSimple() {
        this->tamanio = 0;
        this->inicio = nullptr;
    }
    ~CListaSimple() {
    }
    int getTamanio() {
        return tamanio;
    }
    CNodo<T>* getInicio() {
        return inicio;
    }
    void setTamanio(int tamanio) {
        this->tamanio = tamanio;
    }
    void setInicio(CNodo<T>* inicio) {
        this->inicio = inicio;
    }
    void agregarAlInicio(T nuevoValor) {
        CNodo<T>* nuevoNodo = new CNodo<T>(nuevoValor, this->inicio);
        this->inicio = nuevoNodo;
        this->tamanio++;
    }
    void agregarAlFinal(T nuevoValor) {
        CNodo<T>* nuevoNodo = new CNodo<T>(nuevoValor, nullptr);
        if (this->inicio) //verificar sis  la lista esta vacia
        {
            CNodo<T>* aux = this->inicio; //iniclaizamos en el primer nodo
            while (aux->getSiguiente())
            {

                aux = aux->getSiguiente();
            }
            aux->setSiguiente(nuevoNodo);
        }
        else { //lista vacia
            this->inicio = nuevoNodo;
        }
        this->tamanio++;
    }

    void agregaPorIndice(int indice, T nuevoValor) {
        if (indice >= 0 && indice <= this->tamanio) {
            if (indice == 0) //si el indice es el inicio de la lista
            {
                agregarAlInicio(nuevoValor);
            }
            else if (indice == this->tamanio) { //si el indice es el final de la lista
                agregarAlFinal(nuevoValor);
            }
            else { //si el indice no es ni el inicio ni el final
                CNodo<T>* actual = this->inicio;
                CNodo<T>* previo;

                for (int i = 0; i < indice; i++)
                {
                    previo = actual;  //se va recorriendo la lista
                    actual = actual->getNext(); //se va recorriendo la lista
                }

                CNodo<T>* nuevoNodo = new CNodo<T>(nuevoValor, actual);
                previo->setNext(nuevoNodo);
                this->tamanio++;
            }

        }
        else {
            cout << "El índice es mayor al tamaño de la lista o menor a 0.";
        }
    }
    void eliminarAlInicio() {
        if (tamanio > 0) { //si la lista tiene algo dentro
            CNodo<T>* aux = inicio;
            inicio = inicio->getSiguiente();
            delete aux;
            tamanio--;
        }
    }
    void eliminarAlFinal() {
        if (tamanio>0) { //si hay algo en la lista
            CNodo<T>* actual = this->inicio;
            CNodo<T>* previo = nullptr;
            while (actual->getSiguiente())
            {
                previo = actual;
                actual = actual->getSiguiente();
            }
            if (actual == this->inicio) { 
                this->inicio = this->inicio->getSiguiente();
                delete actual;
                this->tamanio--;
            }
            else {
                previo->setSiguiente(nullptr);
                delete actual;
                this->tamanio--;
            }
        }
    }
    void vaciarLista() {
        inicio = nullptr;
        setTamanio(0);
    }
    bool verificarExistencia(T elemento) {
        CNodo<T>* aux = inicio;
        bool resultado = false;

        while (aux != nullptr) {
            if (aux->getDato()==elemento) {
                resultado = true;
            }
            aux = aux->getSiguiente();
        }
        return resultado;
    }
    void imprimeDatos() {
        CNodo<T>* aux = this->inicio; //aux actua como un iterador
        while (aux != nullptr)
        {
            cout << aux->getDato() << " ";
            aux = aux->getSiguiente();//apuntado elemento a alemento
            cout << endl;
        }
    }
};
