class NRNodo
{
public:
	NRNodo(int dato) {
		this->dato = dato;
		this->color = "rojo";
	}
	~NRNodo();

	int getDato() {
		return this->dato;
	}
	string getColor() {
		return this->color;
	}
	NRNodo* getIzq() {
		return this->izq;
	}
	NRNodo* getDer() {
		return this->der;
	}
	NRNodo* getPadre() {
		return this->padre;
	}
	void setDato(int dato) {
		this->dato = dato;
	}
	void setColor(string color) {
		this->color = color;
	}
	void setIzq(NRNodo* izq) {
		this->izq = izq;
	}
	void setDer(NRNodo* der) {
		this->der = der;
	}
	void setPadre(NRNodo* padre) {
		this->padre = padre;
	}
private:
	int dato;
	string color;
	NRNodo* izq;
	NRNodo* der;
	NRNodo* padre;
};

class ArbolNR
{
public:
	ArbolNR() {
		this->raiz = nullptr;
	}
	~ArbolNR();
	void inOrderTraversal(NRNodo* nodo) {
		if (nodo->getIzq() != nullptr) {
			inOrderTraversal(nodo->getIzq());
		}
		cout << nodo->getDato() << endl;
		if (nodo->getDer() != nullptr) {
			inOrderTraversal(nodo->getDer());
		}
	}
	void traverse() {
		if (raiz = nullptr) {
			inOrderTraversal(raiz);
		}
	}
	NRNodo* insertarEnArbol(NRNodo* raiz, NRNodo* nodo) {
		if (raiz == nullptr) {
			return nodo;
		}
		if (nodo->getDato() < raiz->getDato()) {
			raiz->setIzq(insertarEnArbol(raiz->getIzq(), nodo));
			raiz->getIzq()->setPadre(raiz);
		}
		else if (nodo->getDato() > raiz->getDato()) {
			raiz->setDer(insertarEnArbol(raiz->getDer(), nodo));
			raiz->setPadre(raiz);
		}

		return nullptr;
	}
	void rotacionDerecha(NRNodo* nodo) {
		cout << "Rotando a la derecha en el nodo" << nodo->getDato() << endl;
		NRNodo* auxIzq = nodo->getIzq();
		nodo->setIzq(auxIzq->getDer());

		if (nodo->getIzq() != nullptr) {
			nodo->getIzq()->setPadre(nodo);
		}

		auxIzq->setPadre(nodo->getPadre());

		if (auxIzq->getPadre() == nullptr) {
			raiz = auxIzq;
		}
		else if (nodo == nodo->getPadre()->getIzq()) {
			nodo->getPadre()->setIzq(auxIzq);
		}
		else {
			nodo->getPadre()->setDer(auxIzq);
		}

		auxIzq->setDer(nodo);
		nodo->setPadre(auxIzq);
	}
	void rotacionIzquierda(NRNodo* nodo) {
		cout << "Rotando a la izquierda en el nodo" << nodo->getDato() << endl;
		NRNodo* auxDer = nodo->getDer();
		nodo->setDer(auxDer->getIzq());

		if (nodo->getDer() != nullptr) {
			nodo->getDer()->setPadre(nodo);
		}

		auxDer->setPadre(nodo->getPadre());

		if (auxDer->getPadre() == nullptr) {
			raiz = auxDer;
		}
		else if (nodo == nodo->getPadre()->getIzq()) {
			nodo->getPadre()->setIzq(auxDer);
		}
		else {
			nodo->getPadre()->setDer(auxDer);
		}

		auxDer->setIzq(nodo);
		nodo->setPadre(auxDer);
	}
	void arreglarViolaciones(NRNodo* nodo) {
		NRNodo* padre = nullptr;
		NRNodo* abuelo = nullptr;

		while (nodo != raiz && nodo->getColor() != "negro" && nodo->getPadre()->getColor() == "rojo") {
			padre = nodo->getPadre();
			abuelo = nodo->getPadre()->getPadre();

			if (padre == abuelo->getIzq()) {
				NRNodo* tio = abuelo->getDer();

				if (tio != nullptr && tio->getColor() == "rojo") {
					abuelo->setColor("rojo");
					padre->setColor("negro");
					tio->setColor("negro");
					nodo = abuelo;
				}
				else {
					if (nodo == padre->getDer()) {
						rotacionIzquierda(padre);
						nodo = padre;
						padre = nodo->getPadre();
					}

					rotacionDerecha(abuelo);
					string auxcolor = padre->getColor();
					padre->setColor(abuelo->getColor());
					abuelo->setColor(auxcolor);
					nodo = padre;
				}
			}
			else {
				NRNodo* tio = abuelo->getIzq();

				if (tio != nullptr && tio->getColor() == "rojo") {
					abuelo->setColor("rojo");
					padre->setColor("negro");
					tio->setColor("negro");
					nodo = abuelo;
				}
				else {
					if (nodo == padre->getIzq()) {
						rotacionDerecha(padre);
						nodo = padre;
						padre = nodo->getPadre();
					}

					rotacionIzquierda(abuelo);
					string auxcolor = padre->getColor();
					padre->setColor(abuelo->getColor());
					abuelo->setColor(auxcolor);
					nodo = padre;
				}
			}
		}

		if (raiz->getColor() == "rojo") {
			raiz->setColor("negro");
		}
	}
	void insertar(int dato) {
		NRNodo* nodo = new NRNodo(dato);

		raiz = insertarEnArbol(raiz, nodo);

		arreglarViolaciones(nodo);
	}
private:
	NRNodo* raiz;
};

int main()
{
	ArbolNR* arbol = new ArbolNR();
	arbol->insertar(10);
	arbol->insertar(20);
	arbol->insertar(30);
	//cout << "Hello World!\n";
}