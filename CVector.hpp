#include<iostream>
#include <vector>
using namespace std;

template<typename T>
class CVector
{
public:
	CVector() {
		this->tamanio = 0;
	}
	~CVector() {
	}
	
	vector<T>getVector() {
		return vector;
	}
	void setVector(vector<T> &vector) {
		this->vector = vector;
	}
	int getTamanio() {
		return tamanio;
	}
	void setTamanio(int tamanio) {
		this->tamanio = tamanio;
	}
	//COMPORTAMIENTOS
	void agregarAlInicio(T nuevoValor) {
		vector.insert(vector.begin(), nuevoValor);
	}
	void agregarAlFinal(T nuevoValor) {
		vector.push_back(nuevoValor);
	}
	void agregarEnPosicion(T nuevoValor,int posicion) {
		vector.insert(vector.begin() + posicion, nuevoValor);
	}
	void eliminarAlInicio() {
		vector.erase(vector.begin());
	}
	void eliminarAlFinal() {
		vector.pop_back();
	}
	void eliminarEnPosicion(int posicion) {
		vector.erase(vector.begin() + posicion);
	}
	void vaciarVector() {
		vector.erase(vector.begin(), vector.end());
	}
	void imprimirVector() {
		for (int i = 0; i < vector.size(); i++) {
			cout << vector.at(i) << endl;
		}
		/*auto a = [](T elemento) {
			cout << elemento;
		};
		for each (vector.begin(), vector.end(), a);*/
	}
	
private:
	vector<T> vector;
	int tamanio;
};