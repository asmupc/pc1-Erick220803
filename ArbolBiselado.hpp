#include <functional>
using namespace std;

template<class T>
class SPLNodo
{
public:
	T dato;
	SPLNodo* izq;
	SPLNodo* der;

	SPLNodo(T dato) {
		this->dato = dato;
		this->der = nullptr;
		this->izq = nullptr;
	}
	~SPLNodo();
	void setDato(T dato) {
		this->dato = dato;
	}
	void setIzq(SPLNodo<T>* izq) {
		this->izq = izq;
	}
	void setDer(SPLNodo<T>* der) {
		this->der = der;
	}
};

template<class T>
class ArbolSPL
{
public:
	ArbolSPL() {
		this->raiz = nullptr;
		this->comparar = [](T a, T b)->int {
			if (a < b) {
				return 1;
			}
			else if (a > b) {
				return -1;
			}
			else {
				return 0;
			}
		};
	}
	~ArbolSPL();
	void insertar(T dato) {
		if (_insertar(dato, this->raiz)) {
			cout << "Dato insertado exitosamente." << endl;
		}
		else {
			cout << "Hubo un error." << endl;
		}
	}
	void buscar(T dato) {
		if (_buscar(dato, this->raiz)) {
			moverNodoARaiz(dato, this->raiz);
		}
	}
	void eliminar(T dato) {
		if (_eliminar(dato)) {
			cout << "Dato eliminado exitosamente." << endl;
		}
		else {
			cout << "Hubo un error." << endl;
		}
	}
	void preOrden() {
		_preOrden(this->raiz);
	}
	void enOrden() {
		_enOrden(this->raiz);
	}
	void postOrden() {
		_postOrden(this->raiz);
	}
private:
	SPLNodo<T>* raiz;
	typedef function<int(T, T)> Comp; //Lambda
	Comp comparar; //criterio de comparación
	void zig(SPLNodo<T>*& nodo) {
		SPLNodo<T>* aux = nodo;
		nodo = nodo->izq;
		aux->izq = nodo->der;
		nodo->der = aux;
	}
	void zigZig(SPLNodo<T>*& nodo) {
		zig(nodo);
		zig(nodo);
	}
	void zigZag(SPLNodo<T>*& nodo) {
		zag(nodo->izq);
		zig(nodo);
	}
	void zag(SPLNodo<T>*& nodo) {
		SPLNodo<T>* aux = nodo;
		nodo = nodo->der;
		aux->der = nodo->izq;
		nodo->izq = aux;
	}
	void zagZag(SPLNodo<T>*& nodo) {
		zag(nodo);
		zag(nodo);
	}
	void zagZig(SPLNodo<T>*& nodo) {
		zig(nodo->der);
		zag(nodo);
	}
	void rotaciones(T dato, SPLNodo<T>*& nodo) {
		if (nodo->dato > dato) {
			if (nodo->izq->dato == dato) {
				zig(nodo);
			}
			else if (nodo->izq->dato > dato && nodo->izq->izq->dato == dato) {
				zigZig(nodo);
			}
			else if (nodo->izq->dato < dato && nodo->izq->der->dato == dato) {
				zigZag(nodo);
			}
			else {
				rotaciones(dato, nodo->izq);
			}
		}
		else if (nodo->dato < dato) {
			if (nodo->der->dato == dato) {
				zag(nodo);
			}
			else if (nodo->der->dato > dato && nodo->der->izq->dato == dato) {
				zagZig(nodo);
			}
			else if (nodo->der->dato < dato && nodo->der->der->dato == dato) {
				zagZag(nodo);
			}
			else {
				rotaciones(dato, nodo->der);
			}
		}
	}
	void moverNodoARaiz(T dato, SPLNodo<T>*& nodo) {
		while (nodo->dato != dato) {
			rotaciones(dato, nodo);
		}
	}
	bool _insertar(T dato, SPLNodo<T>*& nodo) {
		if (nodo == nullptr) {
			nodo = new SPLNodo<T>(dato);
			return true;
		}
		else {
			int r = comparar(dato, nodo->dato);
			if (r == 0) return false;
			else if (r < 0) {
				return _insertar(dato, nodo->der);
			}
			else {
				return _insertar(dato, nodo->izq);
			}
		}

		moverNodoARaiz(dato, this->raiz);
	}
	bool _buscar(T dato, SPLNodo<T>* nodo) {
		if (nodo != nullptr) {
			if (nodo->dato == dato) {
				return true;
			}
			else if (nodo->dato > dato) {
				return _buscar(dato, nodo->izq);
			}
			else if (nodo->dato < dato) {
				return _buscar(dato, nodo->der);
			}
		}
		return false;
	}
	T obtenerMayorHijo(SPLNodo<T>*& nodo) {
		if (nodo->der == nullptr) {
			return nodo->dato;
		}

		return obtenerMayorHijo(nodo->der);
	}
	bool _eliminar(T dato) {
		if (!_buscar(dato, this->raiz)) {
			return false;
		}
		moverNodoARaiz(dato, this->raiz);
		if (this->raiz->izq == nullptr && this->raiz->der == nullptr) {
			this->raiz = nullptr;
		}
		else if (this->raiz->izq != nullptr && this->raiz->der != nullptr) {
			T aux = obtenerMayorHijo(raiz->izq);

			if (aux != this->raiz->izq->dato) {
				moverNodoARaiz(aux, this->raiz->izq);
			}
			this->raiz->izq->der = this->raiz->der;
			this->raiz = this->raiz->izq;
		}
		else if (this->raiz->izq != nullptr) {
			this->raiz = this->raiz->izq;
		}
		else {
			this->raiz = this->raiz->der;
		}

		return true;
	}
	void _preOrden(SPLNodo<T>* nodo) {
		if (nodo == nullptr) return;
		cout << nodo->dato << " ";
		_preOrden(nodo->izq);
		_preOrden(nodo->der);
	}
	void _enOrden(SPLNodo<T>* nodo) {
		if (nodo == nullptr) return;
		_enOrden(nodo->izq);
		cout << nodo->dato << " ";
		_preOrden(nodo->der);
	}
	void _postOrden(SPLNodo<T>* nodo) {
		if (nodo == nullptr) return;
		_postOrden(nodo->izq);
		_postOrden(nodo->der);
		cout << nodo->dato << " ";
	}
};