#include <iostream>
using namespace std;

template<class T>
class HashEntidad {
private:
	T key;
	T value;
public:
	HashEntidad(T key, T value) {
		this->key = key;
		this->value = value;
	}
	T getKey() { return key; }
	T getValue() { return value; }
	void imprimirHashEntidad() {
		cout << key << "," << value << endl;
	}
};

template <class T>
class HashTabla {
private:
	HashEntidad<T>** tabla;
	long numElementos;
	long TABLE_SIZE;
	int deStringAInt(T palabra) {
		int valor = 0;

		for (int i = 0; i < palabra.size(); i++) {
			valor += palabra[i];
		}

		return valor;
	}
public:
	HashTabla(long TABLE_SIZE) {
		this->TABLE_SIZE = TABLE_SIZE;
		tabla = new HashEntidad<T> *[TABLE_SIZE];
		for (long i = 0; i < TABLE_SIZE; ++i) {
			tabla[i] = nullptr;
		}
		numElementos = 0;

	}
	~HashTabla()
	{
		for (long i = 0; i < TABLE_SIZE; ++i) {
			if (tabla[i] != nullptr) {
				delete tabla[i];
			}
		}
		delete[] tabla;
	}
	//Direccionamiento según Prueba Lineal
	void insertar(T key, T value) {
		//Hash prima
		int base, step, hash;
		//validar si la tabla está llena
		if (numElementos == TABLE_SIZE) cout << "La tabla esta llena.\n";
		//Función Hash1
		base = deStringAInt(key) % TABLE_SIZE;
		hash = base;
		//constante para Hash2
		step = 0;
		while (tabla[hash] != nullptr)
		{
			//Función Hash2
			hash = (base + step) % TABLE_SIZE;
			step++;
		}
		//almacenarlo en la tabla
		tabla[hash] = new HashEntidad<T>(key, value);
		numElementos++;
	}
	long size() {
		return TABLE_SIZE;
	}
	long sizeactual() {
		return numElementos;
	}
	T obtener(T key) {
		long step = 0;
		long i, base;
		i = base = deStringAInt(key) % TABLE_SIZE; //hash1 es = a hash2 cuando step=0;
		string error = "No se encontro.\n";
		while (true)
		{
			if (tabla[i] == nullptr)return error;
			else if (tabla[i]->getKey() == key) {
				return tabla[i]->getValue();
			}
			else step++;

			i = (base + step) % TABLE_SIZE;
		}
	}
	HashEntidad<T>** getTabla() {
		return tabla;
	}
	void imprimirHT() {
		for (long i = 0; i < TABLE_SIZE; ++i) {
			cout << "POSICION " << i << ": ";
			tabla[i]->imprimirHashEntidad();
		}
	}
};