/*
Modificar el programa anterior de manera que se puedan realizar búsquedas por Apellido y por nombre a la vez.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Persona {
    string nombre;
    string apellido;
    string dni;
};

void guardarDatos(const vector<Persona>& personas) {
    ofstream archivo("personas.txt", ios::app);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    for (const auto& persona : personas) {
        archivo << persona.nombre << " " << persona.apellido << " " << persona.dni << endl;
    }

    archivo.close();
}

void buscarPorApellidoYNombre(const string& apellido, const string& nombre) {
    ifstream archivo("personas.txt");
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string nombreArchivo, apellidoArchivo, dniArchivo;
    bool encontrado = false;

    while (archivo >> nombreArchivo >> apellidoArchivo >> dniArchivo) {
        if (apellidoArchivo == apellido && nombreArchivo == nombre) {
            cout << "Nombre: " << nombreArchivo << ", Apellido: " << apellidoArchivo << ", DNI: " << dniArchivo << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontro ninguna persona con el Apellido: " << apellido << " y Nombre: " << nombre << endl;
    }

    archivo.close();
}

int main() {
    vector<Persona> personas;
    int opcion;

    do {
        cout << "Menu:" << endl;
        cout << "1. Agregar persona" << endl;
        cout << "2. Buscar por Apellido y Nombre" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opcióo: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                Persona persona;
                cout << "Ingrese nombre: ";
                cin >> persona.nombre;
                cout << "Ingrese apellido: ";
                cin >> persona.apellido;
                cout << "Ingrese DNI: ";
                cin >> persona.dni;
                personas.push_back(persona);
                guardarDatos({persona});
                break;
            }
            case 2: {
                string apellido, nombre;
                cout << "Ingrese apellido: ";
                cin >> apellido;
                cout << "Ingrese nombre: ";
                cin >> nombre;
                buscarPorApellidoYNombre(apellido, nombre);
                break;
            }
            case 3:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción invalida. Intente nuevamente." << endl;
        }
    } while (opcion != 3);

    return 0;
}