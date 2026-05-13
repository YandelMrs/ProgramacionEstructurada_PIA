#include "sistemaEnvio.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <regex>
using namespace std;

void cargarCatalogo(vector<PRODUCTO>& catalogo) {

    PRODUCTO temp;
    ifstream archivo("catalogo.txt", ios::in);

    if (!archivo.is_open()) {

        cout << "No se pudo caragar el catalogo :(" << endl;
        return;

    }
    while (archivo >> temp.id >> temp.nombre >> temp.precio >> temp.marca) {

        catalogo.push_back(temp);

    }

    archivo.close();

    const int columnas = 3;
    const int ancho = 38;

    cout << "=================================== PRODUCTOS A LA VENTA ===================================" << endl;

    for (int i = 0; i < catalogo.size(); i += columnas) {
        int fin = min(i + columnas, (int)catalogo.size());

        for (int j = i; j < fin; j++) {
            cout << "+" << string(ancho - 2, '-') << "+ ";
        }
        cout << endl;

        for (int j = i; j < fin; j++) {
            cout << "| " << left << setw(ancho - 4)
                << "[" + to_string(catalogo[j].id) + "] " + catalogo[j].nombre
                << " | ";
        }
        cout << endl;

        for (int j = i; j < fin; j++) {
            cout << "| " << left << setw(ancho - 4)
                << " "
                << " | ";
        }
        cout << endl;

        for (int j = i; j < fin; j++) {
            cout << "| " << left << setw(ancho - 4)
                << ("$" + to_string((int)catalogo[j].precio))
                << " | ";
        }
        cout << endl;

        for (int j = i; j < fin; j++) {
            cout << "| " << left << setw(ancho - 4)
                << catalogo[j].marca
                << " | ";
        }
        cout << endl;

        for (int j = i; j < fin; j++) {
            cout << "| " << left << setw(ancho - 4)
                << " "
                << " | ";
        }
        cout << endl;

        for (int j = i; j < fin; j++) {
            cout << "| " << left << setw(ancho - 4)
                << "+ Agregar al Carrito"
                << " | ";
        }
        cout << endl;

        for (int j = i; j < fin; j++) {
            cout << "+" << string(ancho - 2, '-') << "+ ";
        }
        cout << "\n\n";
    }

}

void buscarProducto(vector<PRODUCTO>& catalogo, int& lineas) {

    string productob;

    cout << "+-- BUSCAR PRODUCTO --------------------------------------------------+" << endl;
    cout << "| Producto:                                                           |\033[59D"; cin >> productob;
    cout << "+---------------------------------------------------------------------+" << endl;
    cout << "| Productos Encontrados                                               |" << endl;
    cout << "+---------------------------------------------------------------------+" << endl;

    regex patronBusqueda(productob, regex_constants::icase);
    bool encontrado = false;
    for (int i = 0; i < catalogo.size(); i++) {

        if (regex_search(catalogo[i].nombre, patronBusqueda)) {

            lineas += 2;
            encontrado = true;
            cout << "|" << left << setw(37) << catalogo[i].nombre
                << "|" << left << setw(15) << catalogo[i].marca
                << "|" << left << setw(15) << fixed << setprecision(2) << catalogo[i].precio << "|" << endl;
            cout << "+---------------------------------------------------------------------+" << endl;

        }

    }
    if (encontrado == true) cout << endl;
    if (encontrado == false) {

        lineas += 2;
        cout << "|                   No se encontro ningun producto!                   |" << endl;
        cout << "+---------------------------------------------------------------------+" << endl;
        cout << endl;

    }

}

void mostrarCarrito(double& subtotal, vector<string> productos, vector<PRODUCTO>& catalogo) {

    cout << "+-- CARRITO DE COMPRAS -------------------------------------+" << endl;
    cout << "|         Producto          |     Marca     |     Precio    |" << endl;
    cout << "+-----------------------------------------------------------+" << endl;
    for (int i = 0; i < productos.size(); i++) {
        for (int j = 0; j < catalogo.size(); j++) {

            if (productos[i] == catalogo[j].nombre) {

                cout << "|" << left << setw(27) << catalogo[j].nombre
                    << "|" << left << setw(15) << catalogo[j].marca
                    << "|" << left << setw(15) << fixed << setprecision(2) << catalogo[j].precio << "|" << endl;
                cout << "+-----------------------------------------------------------+" << endl;

            }

        }
    }
    cout << "|" << right << setw(44) << "Subtotal: " << left << setw(15) << subtotal  << "|" << endl;
    cout << "+-----------------------------------------------------------+" << endl;
    cout << endl;

}