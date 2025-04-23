/*
Realizar un programa en el cual se ingresen los siguientes datos Nombre, Apellido y DNI
Crear un menú donde se ingresen los datos y los guarde en un archivo
Otro ítem donde se pueda realizar una búsqueda por DNI y devuelva los datos de Nombre y apellido
Salir del mismo 

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

void buscarPorDNI(const string& dni) {
    ifstream archivo("personas.txt");
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string nombre, apellido, dniArchivo;
    bool encontrado = false;

    while (archivo >> nombre >> apellido >> dniArchivo) {
        if (dniArchivo == dni) {
            cout << "Nombre: " << nombre << ", Apellido: " << apellido << ", DNI: " << dniArchivo << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontró ninguna persona con el DNI: " << dni << endl;
    }

    archivo.close();
}

int main() {
    vector<Persona> personas;
    int opcion;

    do {
        cout << "Menu:" << endl;
        cout << "1. Ingresar datos" << endl;
        cout << "2. Buscar por DNI" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opcion: ";
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
                string dni;
                cout << "Ingrese el DNI a buscar: ";
                cin >> dni;
                buscarPorDNI(dni);
                break;
            }
            case 3:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcion != 3);

    system("pause");
    return 0;
}
