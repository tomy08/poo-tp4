/*
Agregar validación de datos de manera que no se repitan cuando sea necesario.
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


bool validarDNI(const string& dni) {
    ifstream archivo("personas.txt");
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }

    string nombre, apellido, dniArchivo;
    while (archivo >> nombre >> apellido >> dniArchivo) {
        if (dniArchivo == dni) {
            archivo.close();
            return false; 
        }
    }

    archivo.close();
    return true; 
}

bool validarNombreYApellido(const string& nombre, const string& apellido) {
    ifstream archivo("personas.txt");
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }

    string nombreArchivo, apellidoArchivo, dniArchivo;
    while (archivo >> nombreArchivo >> apellidoArchivo >> dniArchivo) {
        if (apellidoArchivo == apellido && nombreArchivo == nombre) {
            archivo.close();
            return false; 
        }
    }

    archivo.close();
    return true; 
}

int main() {
    vector<Persona> personas;
    int opcion;

    do {
        cout << "Menu:" << endl;
        cout << "1. Agregar Persona" << endl;
        cout << "2. Buscar por Apellido y Nombre" << endl;
        cout << "3. Buscar por DNI" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                Persona persona;
                cout << "Ingrese el nombre: ";
                cin >> persona.nombre;
                cout << "Ingrese el apellido: ";
                cin >> persona.apellido;
                cout << "Ingrese el DNI: ";
                cin >> persona.dni;

                if (validarDNI(persona.dni) && validarNombreYApellido(persona.nombre, persona.apellido)) {
                    personas.push_back(persona);
                    guardarDatos(personas);
                    cout << "Persona guardada exitosamente." << endl;
                } else {
                    cout << "El DNI o el Nombre y Apellido ya existen." << endl;
                }
                break;
            }
            case 2: {
                string apellido, nombre;
                cout << "Ingrese el apellido: ";
                cin >> apellido;
                cout << "Ingrese el nombre: ";
                cin >> nombre;
                buscarPorApellidoYNombre(apellido, nombre);
                break;
            }
            case 3: {
                string dni;
                cout << "Ingrese el DNI: ";
                cin >> dni;
                buscarPorDNI(dni);
                break;
            }
            case 4:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente." << endl;
        }
    } while (opcion != 4);

    return 0;
}