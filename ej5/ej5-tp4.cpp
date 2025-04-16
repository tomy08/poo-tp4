/*
Guardar Los cambios en un archivo con nombre pertinente sin modificar el original
y pudiendo tener acceso a los mismos
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    string archivoOriginal, archivoNuevo;
    vector<string> lineas;

    cout << "Nombre del archivo original (.txt): ";
    getline(cin, archivoOriginal);

    ifstream entrada(archivoOriginal);
    if (!entrada) {
        cout << "No se pudo abrir el archivo.\n";
        return 1;
    }

    string linea;
    while (getline(entrada, linea)) {
        lineas.push_back(linea);
    }
    entrada.close();

    bool continuar = true;
    while (continuar) {
        cout << "\nContenido actual del archivo:\n";
        for (size_t i = 0; i < lineas.size(); ++i) {
            cout << i + 1 << ": " << lineas[i] << '\n';
        }

        int numLinea;
        cout << "\nIngrese el número de línea a modificar: ";
        cin >> numLinea;
        cin.ignore();

        if (numLinea < 1 || numLinea > lineas.size()) {
            cout << "Número de línea inválido.\n";
        } else {
            string nuevoTexto;
            cout << "Nuevo texto para la línea " << numLinea << ": ";
            getline(cin, nuevoTexto);
            lineas[numLinea - 1] = nuevoTexto;
        }

        string respuesta;
        cout << "\n¿Desea modificar otra línea? (s/n): ";
        getline(cin, respuesta);
        if (respuesta != "s" && respuesta != "S") {
            continuar = false;
        }
    }

    cout << "\nNombre del nuevo archivo para guardar los cambios: ";
    getline(cin, archivoNuevo);

    ofstream salida(archivoNuevo);
    if (!salida) {
        cout << "No se pudo crear el archivo.\n";
        return 1;
    }

    for (const auto& l : lineas) {
        salida << l << '\n';
    }

    cout << "Archivo guardado como: " << archivoNuevo << endl;

    return 0;
}