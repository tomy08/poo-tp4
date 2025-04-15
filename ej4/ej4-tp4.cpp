/*
Modificar dicho programa de manera que me muestre los datos de manera ordenada
Según se desee por nombre y apellido o por DNI
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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

void mostrarDatosOrdenadosPorNombreYApellido() {
    ifstream archivo("personas.txt");
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    vector<Persona> personas;
    string nombre, apellido, dni;

    while (archivo >> nombre >> apellido >> dni) {
        personas.push_back({nombre, apellido, dni});
    }

    archivo.close();

    sort(personas.begin(), personas.end(), [](const Persona& a, const Persona& b) {
        if (a.apellido == b.apellido) {
            return a.nombre < b.nombre;
        }
        return a.apellido < b.apellido;
    });

    cout << "Personas ordenadas por Nombre y Apellido:" << endl;
    for (const auto& persona : personas) {
        cout << "Nombre: " << persona.nombre << ", Apellido: " << persona.apellido << ", DNI: " << persona.dni << endl;
    }
}
void mostrarDatosOrdenadosPorDNI() {
    ifstream archivo("personas.txt");
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    vector<Persona> personas;
    string nombre, apellido, dni;

    while (archivo >> nombre >> apellido >> dni) {
        personas.push_back({nombre, apellido, dni});
    }

    archivo.close();

    sort(personas.begin(), personas.end(), [](const Persona& a, const Persona& b) {
        return a.dni < b.dni;
    });

    cout << "Personas ordenadas por DNI:" << endl;
    for (const auto& persona : personas) {
        cout << "Nombre: " << persona.nombre << ", Apellido: " << persona.apellido << ", DNI: " << persona.dni << endl;
    }
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
        cout << "1. Agregar persona" << endl;
        cout << "2. Buscar por Apellido y Nombre" << endl;
        cout << "3. Buscar por DNI" << endl;
        cout << "4. Mostrar datos ordenados por Nombre y Apellido" << endl;
        cout << "5. Mostrar datos ordenados por DNI" << endl;
        cout << "6. Salir" << endl;
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

                if (validarDNI(persona.dni) && validarNombreYApellido(persona.nombre, persona.apellido)) {
                    personas.push_back(persona);
                    guardarDatos(personas);
                    cout << "Persona agregada exitosamente." << endl;
                } else {
                    cout << "El DNI o el Nombre y Apellido ya existen." << endl;
                }
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
            case 3: {
                string dni;
                cout << "Ingrese DNI: ";
                cin >> dni;
                buscarPorDNI(dni);
                break;
            }
            case 4:
                mostrarDatosOrdenadosPorNombreYApellido();
                break;
            case 5:
                mostrarDatosOrdenadosPorDNI();
                break;
            case 6:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opcion != 6);

    return 0;
}