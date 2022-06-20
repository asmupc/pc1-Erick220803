#include<iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

void imprimir(string e) {
	cout << " " << e;
}

CListaSimple<string>* folders = new CListaSimple<string>();
CListaSimple<string>* contrasenias = new CListaSimple<string>();
CListaSimple<string>* detallesContrasenias = new CListaSimple<string>();
CVector<string>* urls = new CVector<string>();
CVector<string>* usuarios = new CVector<string>();
CVector<string>* claves = new CVector<string>();
CVector<string>* notasT = new CVector<string>();
CPila<string>* historial = new CPila<string>();
CPila<string>* historialUsuarios = new CPila<string>();
CPila<string>* historialURLs = new CPila<string>();
CPila<string>* historialClaves = new CPila<string>();
ArbolBB<string>* datosAutogenerados = new ArbolBB<string>(imprimir);

void intercambiar(string& a, string& b) {
	string aux = a;
	a = b;
	b = aux;
}

void selectionSort(vector<string>& arreglo) {
	int indiceMenor;
	for (int i = 0; i < arreglo.size() - 1; i++) {
		indiceMenor = i;
		for (int j = i + 1; j < arreglo.size(); j++) {
			if (arreglo[j] < arreglo[indiceMenor]) {
				indiceMenor = j;
			}
		}
		intercambiar(arreglo[i], arreglo[indiceMenor]);
	}
}

void insertionSort(vector<string>& arreglo) {
	for (int i = 1; i < arreglo.size(); i++) {
		int j = i;
		string aux = arreglo[i];
		while (j > 0 && aux < arreglo[j - 1]) {
			arreglo[j] = arreglo[j - 1];
			j--;
		}
		arreglo[j] = aux;
	}
}

int particion(vector<string>& arreglo, int inicio, int final) {
	string pivote = arreglo[inicio];
	int i = inicio + 1;
	for (int j = i; j <= final; j++) {
		if (arreglo[j] < pivote) {
			intercambiar(arreglo[i], arreglo[j]);
			i++;
		}
	}
	intercambiar(arreglo[inicio], arreglo[i - 1]);
	return i - 1; //pivote
}

void quickSort(vector<string>& arreglo, int inicio, int fin) {
	if (inicio < fin) {
		int pivote = particion(arreglo, inicio, fin);
		quickSort(arreglo, inicio, pivote - 1);
		quickSort(arreglo, pivote + 1, fin);
	}
}

string quickselect(vector<string>& arreglo, int inicio, int fin, int k) {
	if (inicio == fin) return arreglo[inicio];
	int q = particion(arreglo, inicio, fin);
	int l = q - inicio + 1;
	if (k == l)
		return arreglo[q];
	else if (k < l) {
		return quickselect(arreglo, inicio, q - 1, k);
	}
	else {
		return quickselect(arreglo, q + 1, fin, k - l);
	}
}

const int RUN = 64;

int min(int x, int y) {
	if (x < y) {
		return x;
	}
	else {
		return y;
	}
}

void insertionSort(int* array, int start_index, int end_index)
{
	for (int i = start_index + 1, j, temp; i <= end_index; i++) {
		temp = array[i];
		j = i - 1;

		while (j >= 0 && temp <= array[j]) {
			array[j + 1] = array[j];
			j = j - 1;
		}
		array[j + 1] = temp;
	}
}

void merge(int* array, int start_index, int mid, int end_index)
{
	int i, j, k;
	int left_size = mid - start_index + 1;
	int right_size = end_index - mid;
	int left_array[left_size], right_array[right_size];

	for (int i = 0; i < left_size; i++) {
		left_array[i] = array[start_index + i];
	}

	for (int j = 0; j < right_size; j++) {
		right_array[j] = array[mid + 1 + j];
	}
	i = 0, j = 0, k = start_index;

	for (; i < left_size && j < right_size; k++) {
		if (left_array[i] <= right_array[j]) {
			array[k] = left_array[i];
			i++;
		}
		else {
			array[k] = right_array[j];
			j++;
		}
	}
	for (; i < left_size; i++, k++) {
		array[k] = left_array[i];
	}
	for (; j < right_size; j++, k++) {
		array[k] = right_array[j];
	}
}

void timsort(int* array, int size) {
	for (int i = 0; i < size; i = i + RUN) {
		insertionSort(array, i, min((i + RUN - 1), (size - 1)));
	}

	for (int n = RUN; n < size; n *= 2) {
		for (int start_index = 0; start_index < size; start_index += 2 * n) {
			int mid = start_index + n - 1;
			int end_index = min((start_index + 2 * n - 1), (size - 1));

			if (mid < end_index) {
				merge(array, start_index, mid, end_index);
			}
		}
	}
}

void imprimirArreglo(vector<string>arreglo) {
	for (int i = 0; i < arreglo.size(); i++) {
		cout << arreglo[i] << " ";
	}
	cout << endl;
}

void imprimirArreglo2(vector<string>arreglo, int k) {
	string e = quickselect(arreglo, 0, arreglo.size() - 1, k);
	cout << "El kesimo elemento es: " << e;

}

void menu();

void agregarEspecificacionesContrasenia(string nombre) {
	ofstream archivo;
	string url;
	string usuario;
	string contrasenia;
	string notas;

	cout << "Escriba la url de la pagina web: ";
	cin >> url;
	urls->agregarAlFinal(url);
	historialURLs->push("Se agrego la URL " + url);
	cout << "Escriba el usuario ligado a la contrase�a: ";
	cin >> usuario;
	usuarios->agregarAlFinal(usuario);
	historialUsuarios->push("Se agrego el usuario " + usuario);
	cout << "Escriba la contrasenia que desea guardar: ";
	cin >> contrasenia;
	historialClaves->push("Se agrego la contrasenia " + contrasenia);
	claves->agregarAlFinal(contrasenia);
	cout << "Escriba una nota para recordar la contrasenia (separando palabras con _ ): ";
	cin >> notas;
	notasT->agregarAlFinal(notas);

	archivo.open(nombre + ".txt", ios::app);

	if (archivo.is_open()) {
		archivo << url << endl;
		archivo << usuario << endl;
		archivo << contrasenia << endl;
		archivo << notas;

		archivo.close();
	}

	historial->push("Se agrego los detalles de una contrasenia.");
}

void agregarContrasenia(string nombreFolder) {
	ofstream archivo;
	string nombre;
	
	cout << "Escriba el nombre con el que desea guardar la contrasenia: ";
	cin >> nombre;

	archivo.open(nombreFolder + ".txt", ios::app);

	if (archivo.is_open()) {
		archivo << nombre << endl;

		archivo.close();
	}
	
	agregarEspecificacionesContrasenia(nombre);

	historial->push("Se agrego una contrasenia.");
}

void buscarClaves() {
	int k;
	cout << "ingrese posicion: " << endl;
	cin >> k;
	vector<string> arreglo = claves->getVector();
	cout << endl;
	quickselect(arreglo, 0, arreglo.size() - 1, k);
	imprimirArreglo2(arreglo, k);
	cout << endl;
}

void verContrasenias(string nombreFolder) {
	ifstream archivo;
	string texto;

	archivo.open(nombreFolder + ".txt", ios::in);

	if (archivo.is_open())
	{
		while (!archivo.eof())
		{
			//leeemos linea por linea
			getline(archivo, texto);
			contrasenias->agregarAlFinal(texto);
		}
		contrasenias->imprimeDatos();
	}
	else {
		cout << "\nEl archivo no existe";
	}
	contrasenias->vaciarLista();

	historial->push("Se vio la lista de contrasenias de un folder.");
}

void verDetallesContrasenia() {
	ifstream archivo;
	string texto;
	string nombre;

	cout << "Ingrese el nombre de la contrasenia de la cual desea conocer las especificaciones: ";
	cin >> nombre;

	archivo.open(nombre + ".txt", ios::in);

	if (archivo.is_open())
	{
		while (!archivo.eof())
		{
			//leeemos linea por linea
			getline(archivo, texto);
			detallesContrasenias->agregarAlFinal(texto);
		}
		cout << "\nURL USUARIO CONTRASENIA NOTAS\n";
		detallesContrasenias->imprimeDatos();
	}
	else {
		cout << "\nEl archivo no existe";
	}
	detallesContrasenias->vaciarLista();

	historial->push("Se vieron los detalles de una contrasenia.");
}

void verURLs() {
	cout << "\nUrls:\n";
	urls->imprimirVector();
	menu();

	historial->push("Se vieron las URLs.");
}

void verUsuarios() {
	cout << "\nUsuarios:\n";
	usuarios->imprimirVector();
	menu();

	historial->push("Se vieron los usuarios.");
}

void verClaves() {
	cout << "\nClaves:\n";
	claves->imprimirVector();
	menu();

	historial->push("Se vieron las claves.");
}

void verNotas() {
	cout << "\nNotas:\n";
	notasT->imprimirVector();
	menu();

	historial->push("Se vieron las notas.");
}

void ingresarAFolder() {
	string folderElegido;
	string texto;
	int eleccion;
	ofstream archivo1;
	ifstream archivo2;

	cout << "Ingrese el nombre del folder al que desea ingresar: ";
	cin >> folderElegido;

	archivo2.open("folderes.txt", ios::in);
	if (archivo2.is_open())
	{
		if (folders->getTamanio() == 0) { //si la lista est� vac�a
			while (!archivo2.eof())
			{
				//leeemos linea por linea
				getline(archivo2, texto);
				folders->agregarAlFinal(texto);
			}
		}
		archivo2.close();
	}

	if (folders->verificarExistencia(folderElegido)==true) {
		archivo1.open(folderElegido + ".txt", ios::app);

		cout << "\n\tElija una opcion:\n";
		cout << "1) Agregar contrasenia\n";
		cout << "2) Ver contrasenias guardadas\n";
		cout << "3) Ver detalles de contrasenia\n";
		cin >> eleccion;

		switch (eleccion)
		{
		case 1:
			agregarContrasenia(folderElegido);
			menu();
			break;
		case 2:
			verContrasenias(folderElegido);
			menu();
			break;
		case 3:
			verDetallesContrasenia();
			menu();
			break;
		default:
			break;
		}
	}
	else {
		cout << "El folder elegido no existe.";
	}

	historial->push("Se ingreso a un folder.");
}

void crearFolder() {
	ofstream archivo;
	string nuevoFolder;

	cout << "Ingrese el nombre del nuevo folder: ";
	cin >> nuevoFolder;
	
	archivo.open("folderes.txt", ios::app);

	if (archivo.is_open()) {
		archivo << nuevoFolder << endl;

		archivo.close();
	}

	folders->agregarAlFinal(nuevoFolder);

	cout << "Folder creado con exito.";

	historial->push("Se creo un folder.");
}

void verFolderes() {
	ifstream archivo;
	string texto;

	archivo.open("folderes.txt", ios::in);
	if (archivo.is_open())
	{
		if (folders->getTamanio() == 0) { //si la lista est� vac�a
			while (!archivo.eof())
			{
				//leeemos linea por linea
				getline(archivo, texto);
				folders->agregarAlFinal(texto);
			}
			folders->imprimeDatos();
		}
		else { //si la lista ya tiene elementos
			folders->imprimeDatos();
		}
		archivo.close();
	}

	historial->push("Se vieron los folderes.");
}

void ordenarUrls() {
	vector<string> arreglo1 = urls->getVector();
	cout << endl;
	selectionSort(arreglo1);
	imprimirArreglo(arreglo1);
	cout << endl;
}

void ordenarUsuarios() {
	vector<string> arreglo = usuarios->getVector();
	cout << endl;
	insertionSort(arreglo);
	imprimirArreglo(arreglo);
	cout << endl;
}

void ordenarClaves() {
	vector<string> arreglo = claves->getVector();
	cout << endl;
	quickSort(arreglo,0,arreglo.size()-1);
	imprimirArreglo(arreglo);
	cout << endl;
}

string generarPalabra() {
	char a;
	string b;

	for (int i = 0; i < 4; i++) {
		a = 97 + rand() % (122 - 97);
		b += a;
	}

	return b;
}

void autoGenerador(ArbolBB<string>* &datosAutogenerados) {
	string carpetaAutogenerada = "D:/Ciclo 4 Ingenier�a de Software/Algoritmos y estructuras de datos/PC1/PC1 Grupo 6/PC1 Grupo 6/Archivos autogenerados";
	string redesSociales = carpetaAutogenerada + "/Redes sociales";

	if (_mkdir(carpetaAutogenerada.c_str()) == 0) {

		if (_mkdir(redesSociales.c_str())==0) {
			ofstream archivo;
			archivo.open(redesSociales + "/Redes_sociales.txt", ios::app);
			string palabra = "";

			if (archivo.is_open()) {

				for (int i = 0; i < 1000000; i++) {
					palabra = generarPalabra();
					archivo << palabra << endl;
					datosAutogenerados->insertar(palabra);
				}

				archivo.close();
			}

			
			
		}
	}
	datosAutogenerados->enOrden();
}

void menu() {
	int eleccion;

	cout << "\n\tMenu\n";
	cout << "1) Ingresar a folder.\n";
	cout << "2) Crear folder.\n";
	cout << "3) Ver folderes.\n";
	cout << "4) Ver todas las URLs guardadas en los folderes.\n";
	cout << "5) Ver todos los usuarios guardados en los folder.\n";
	cout << "6) Ver todas las claves guardadas en los folder.\n";
	cout << "7) Ver todas las notas guardadas en los folder.\n";
	cout << "8) Ver las URLs guardadas organizadas alfabeticamente.\n";
	cout << "9) Ver los usuarios guardados organizados alfabeticamente.\n";
	cout << "10) Ver las claves guardadas organizadas alfabeticamente.\n";
	cout << "11) Ver historial general.\n";
	cout << "12) Ver historial de URLs.\n";
	cout << "13) Ver historial de usuarios.\n";
	cout << "14) Ver historial de claves.\n";
	cout << "15) Generar datos automaticamente\n";
	cout << "16) Buscar clave en posicion k\n";
	cout << "17) Salir\n";
	cout << "\nIngrese una opcion: ";
	cin >> eleccion;

	switch (eleccion)
	{
	case 1:
		ingresarAFolder();
		break;
	case 2:
		crearFolder();
		menu();
		break;
	case 3:
		verFolderes();
		menu(); 
		break;
	case 4:
		verURLs();
		menu();
		break;
	case 5:
		verUsuarios();
		menu();
		break;
	case 6:
		verClaves();
		menu();
		break;
	case 7:
		verNotas();
		menu();
		break;
	case 8:
		ordenarUrls();
		menu();
		break;
	case 9:
		ordenarUsuarios();
		menu();
		break;
	case 10:
		ordenarClaves();
		menu();
		break;
	case 11:
		historial->imprimirPila();
		menu();
		break;
	case 12:
		historialURLs->imprimirPila();
		menu();
		break;
	case 13:
		historialUsuarios->imprimirPila();
		menu();
		break;
	case 14:
		historialClaves->imprimirPila();
		menu();
		break;
	case 15:
		autoGenerador(datosAutogenerados);
		break;
	case 16:
		buscarClaves();
		break;
	case 17:
		exit(0);
		break;
	default:
		break;
	}
}