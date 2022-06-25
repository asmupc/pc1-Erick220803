#include<iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

void imprimir(string e) {
	cout << endl << e;
}

CListaSimple<string>* folders = new CListaSimple<string>();
CListaSimple<string>* contrasenias = new CListaSimple<string>();
CListaSimple<string>* detallesContrasenias = new CListaSimple<string>();
CVector<string>* urls = new CVector<string>();
CVector<string>* usuarios = new CVector<string>();
CVector<string>* claves = new CVector<string>();
CVector<string>* notasT = new CVector<string>();
CVector<string>* historialNotas = new CVector<string>();
CPila<string>* historial = new CPila<string>();
CPila<string>* historialUsuarios = new CPila<string>();
CPila<string>* historialURLs = new CPila<string>();
CPila<string>* historialClaves = new CPila<string>();
ArbolBB<string>* abbUsuarios = new ArbolBB<string>(imprimir);
ArbolBB<string>* abbClaves = new ArbolBB<string>(imprimir);
ArbolSPL<string>* asplUrls = new ArbolSPL<string>();
ArbolSPL<string>* asplNotas = new ArbolSPL<string>();

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

void merge(vector<string>& arreglo, int inicio, int mitad, int final) {
	int i, j, k;
	int elementosIzq = mitad - inicio + 1;
	int elementosDer = final - mitad;

	vector<string>izquierda(elementosIzq);
	vector<string>derecha(elementosDer);

	for (int i = 0; i < elementosIzq; i++) {
		izquierda[i] = arreglo[inicio + i];
	}
	for (int j = 0; j < elementosDer; j++) {
		derecha[j] = arreglo[mitad + 1 + j];
	}

	i = 0;
	j = 0;
	k = inicio;

	while (i < elementosIzq && j < elementosDer) {
		if (izquierda[i] <= derecha[j]) {
			arreglo[k] = izquierda[i];
			i++;
		}
		else {
			arreglo[k] = derecha[j];
			j++;
		}
		k++;
	}

	while (j < elementosDer) {
		arreglo[k] = derecha[j];
		j++;
		k++;
	}

	while (i < elementosIzq) {
		arreglo[k] = izquierda[i];
		i++;
		k++;
	}

}

void mergeSort(vector<string>& arreglo, int inicio, int final) {
	if (inicio < final) {
		int mitad = inicio + (final - inicio) / 2;
		mergeSort(arreglo, inicio, mitad);
		mergeSort(arreglo, mitad + 1, final);
		merge(arreglo, inicio, mitad, final);
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
	asplUrls->insertar(url);
	cout << "Escriba el usuario ligado a la contraseña: ";
	cin >> usuario;
	usuarios->agregarAlFinal(usuario);
	historialUsuarios->push("Se agrego el usuario " + usuario);
	abbUsuarios->insertar(usuario);
	cout << "Escriba la contrasenia que desea guardar: ";
	cin >> contrasenia;
	historialClaves->push("Se agrego la contrasenia " + contrasenia);
	claves->agregarAlFinal(contrasenia);
	abbClaves->insertar(contrasenia);
	cout << "Escriba una nota para recordar la contrasenia (separando palabras con _ ): ";
	cin >> notas;
	notasT->agregarAlFinal(notas);
	historialNotas->agregarAlFinal(notas);
	asplNotas->insertar(notas);

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
	imprimirArreglo(arreglo);
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
		if (folders->getTamanio() == 0) { //si la lista está vacía
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
		if (folders->getTamanio() == 0) { //si la lista está vacía
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

void ordenarNotas() {
	vector<string> arreglo = historialNotas->getVector();
	cout << endl;
	//quickSort(arreglo, 0, arreglo.size() - 1);
	mergeSort(arreglo, 0, arreglo.size() - 1);
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

void autoGenerador() {
	string carpetaAutogenerada = "D:/Ciclo 4 Ingeniería de Software/Algoritmos y estructuras de datos/PC1/PC1 Grupo 6/PC1 Grupo 6/Archivos autogenerados";
	string redesSociales = carpetaAutogenerada + "/Redes sociales";
	HashTabla<string>* autogenerados = new HashTabla<string>(1000000);
	if (_mkdir(carpetaAutogenerada.c_str()) == 0) {

		if (_mkdir(redesSociales.c_str())==0) {
			ofstream archivo;
			archivo.open(redesSociales + "/Redes_sociales.txt", ios::app);
			string palabra1 = "";
			string palabra2 = "";

			if (archivo.is_open()) {

				for (long i = 0; i < 1000000; i++) {
					palabra1 = generarPalabra();
					palabra2 = generarPalabra();
					//archivo << palabra1 << endl;
					autogenerados->insertar(palabra1, palabra2);
				}

				archivo.close();
			}
		}
	}
	autogenerados->imprimirHT();
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
	cout << "10) Ver las claves guardadas organizadas alfabeticamente (quicksort).\n";
	cout << "11) Ver las notas guardadas organizadas alfabeticamente (mergesort).\n";
	cout << "12) Ver historial general.\n";
	cout << "13) Ver historial de URLs.\n";
	cout << "14) Ver historial de usuarios.\n";
	cout << "15) Ver historial de claves.\n";
	cout << "16) Generar datos automaticamente\n";
	cout << "17) Buscar clave en posicion (quickselect)\n";
	cout << "18) Ver URLs enOrden (Arbol SPL)\n";
	cout << "19) Ver usuarios enOrden (Arbol BB)\n";
	cout << "20) Ver claves postOrden (Arbol BB)\n";
	cout << "21) Ver notas preOrden (Arbol SPL)\n";
	cout << "22) Salir\n";
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
		ordenarNotas();
		menu();
		break;
	case 12:
		historial->imprimirPila();
		menu();
		break;
	case 13:
		historialURLs->imprimirPila();
		menu();
		break;
	case 14:
		historialUsuarios->imprimirPila();
		menu();
		break;
	case 15:
		historialClaves->imprimirPila();
		menu();
		break;
	case 16:
		autoGenerador();
		menu();
		break;
	case 17:
		buscarClaves();
		menu();
		break;
	case 18:
		asplUrls->enOrden();
		menu();
		break;
	case 19:
		abbUsuarios->enOrden();
		menu();
		break;
	case 20:
		abbClaves->postOrden();
		menu();
		break;
	case 21:
		asplNotas->preOrden();
		menu();
		break;
	case 22:
		exit(0);
		break;
	default:
		break;
	}
}