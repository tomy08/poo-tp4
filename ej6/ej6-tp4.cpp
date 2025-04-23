/*
Realizar un programa que realice las siguientes acciones
- Guarde el registro del nombre y el puntaje de un jugador (solicitando el ingreso de los datos del usuario)
- Muestre el resultado de los 10 mejores jugadores ordenados por mayor puntaje.
- Realice y muestre una búsqueda de un Nombre y devuelva sus resultados
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Jugador {
    string nombre;
    int puntaje;
};

void guardarDatos(const vector<Jugador>& jugadores) {
    ofstream archivo("jugadores.txt", ios::app);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    for (const auto& jugador : jugadores) {
        archivo << jugador.nombre << " " << jugador.puntaje << endl;
    }

    archivo.close();
}

void mostrarMejoresJugadores() {
    ifstream archivo("jugadores.txt");
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    vector<Jugador> jugadores;
    Jugador jugador;

    while (archivo >> jugador.nombre >> jugador.puntaje) {
        jugadores.push_back(jugador);
    }

    archivo.close();

    // Ordenar los jugadores por puntaje de mayor a menor
    sort(jugadores.begin(), jugadores.end(), [](const Jugador& a, const Jugador& b) {
        return a.puntaje > b.puntaje;
    });

    cout << "Los 10 mejores jugadores son:" << endl;
    for (size_t i = 0; i < min(jugadores.size(), size_t(10)); ++i) {
        cout << "Nombre: " << jugadores[i].nombre << ", Puntaje: " << jugadores[i].puntaje << endl;
    }
}


void buscarPorNombre(const string& nombre) {
    ifstream archivo("jugadores.txt");
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    Jugador jugador;
    bool encontrado = false;

    while (archivo >> jugador.nombre >> jugador.puntaje) {
        if (jugador.nombre == nombre) {
            cout << "Nombre: " << jugador.nombre << ", Puntaje: " << jugador.puntaje << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontró ningún jugador con el nombre: " << nombre << endl;
    }

    archivo.close();
}

int main() {
    vector<Jugador> jugadores;
    int opcion;

    do {
        cout << "Menu:" << endl;
        cout << "1. Ingresar datos" << endl;
        cout << "2. Mostrar mejores jugadores" << endl;
        cout << "3. Buscar por nombre" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                Jugador jugador;
                cout << "Ingrese nombre: ";
                cin >> jugador.nombre;
                cout << "Ingrese puntaje: ";
                cin >> jugador.puntaje;
                jugadores.push_back(jugador);
                guardarDatos({jugador});
                break;
            }
            case 2:
                mostrarMejoresJugadores();
                break;
            case 3: {
                string nombre;
                cout << "Ingrese el nombre a buscar: ";
                cin >> nombre;
                buscarPorNombre(nombre);
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