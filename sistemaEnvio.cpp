#include "sistemaEnvio.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

void cargarCatalogo(vector<PRODUCTO>& catalogo) {

    PRODUCTO temp;
    ifstream archivo("catalogo.txt", ios::in);

    if (!archivo.is_open()) {

        cout << "No se pudo caragar el catalogo :(" << endl;
        return;

    }
    while (archivo >> temp.nombre >> temp.precio >> temp.marca) {

        catalogo.push_back(temp);

    }

    archivo.close();

    const int columnas = 3;
    const int ancho = 30;

    cout << "=================================== PRODUCTOS A LA VENTA ===================================" << endl;

    for (int i = 0; i < catalogo.size(); i += columnas) {
        int fin = min(i + columnas, (int)catalogo.size());

        for (int j = i; j < fin; j++) {
            cout << "+" << string(ancho - 2, '-') << "+ ";
        }
        cout << endl;

        for (int j = i; j < fin; j++) {
            cout << "| " << left << setw(ancho - 4)
                << ("Producto: " + catalogo[j].nombre)
                << " | ";
        }
        cout << endl;

        for (int j = i; j < fin; j++) {
            cout << "| " << left << setw(ancho - 4)
                << ("Precio: $" + to_string((int)catalogo[j].precio))
                << " | ";
        }
        cout << endl;

        for (int j = i; j < fin; j++) {
            cout << "| " << left << setw(ancho - 4)
                << ("Marca: " + catalogo[j].marca)
                << " | ";
        }
        cout << endl;

        for (int j = i; j < fin; j++) {
            cout << "+" << string(ancho - 2, '-') << "+ ";
        }
        cout << "\n\n";
    }

}

void buscarProducto(vector<PRODUCTO>& catalogo, bool& condicion) {

    string productob;

    cout << "==================================" << endl;
    cout << "       Buscador de productos      " << endl;
    cout << "==================================" << endl;
    cout << "Buscar: "; cin >> productob;

    bool encontrado = false;
    for (int i = 0; i < catalogo.size(); i++) {

        if (productob == catalogo[i].nombre) {

            cout << "==================================" << endl;
            cout << "       Producto encontrado!       " << endl;
            cout << "==================================" << endl;
            cout << left << setw(17) << "Producto:" << left << setw(18) << catalogo[i].nombre << endl;
            cout << left << setw(17) << "Precio:" << left << setw(18) << catalogo[i].precio << endl;
            cout << left << setw(17) << "Marca:" << left << setw(18) << catalogo[i].marca << endl;
            cout << "==================================" << endl;
            cout << endl;
            encontrado = true;
            break;

        }

    }
    if (encontrado == false) {
    
        cout << "==================================" << endl;
        cout << "    Producto no encontrado :(     " << endl;
        cout << "==================================" << endl;
        cout << endl;

    }

    condicion = encontrado;

}

void mostrarCarrito(double& subtotal, vector<string> productos, vector<PRODUCTO>& catalogo) {

    subtotal = 0;

    cout << ">>>>>>>>>>>>> CARRITO <<<<<<<<<<<<<" << endl;
    cout << "-----------------------------------" << endl;
    for (int i = 0; i < productos.size(); i++) {
        for (int j = 0; j < catalogo.size(); j++) {

            if (productos[i] == catalogo[j].nombre) {

                cout << left << setw(18) << catalogo[j].nombre << left << setw(17) << catalogo[j].precio << endl;
                subtotal += catalogo[j].precio;

            }

        }
    }
    cout << "-----------------------------------" << endl;
    cout << left << setw(18) << "Subtotal: " << left << setw(17) << subtotal << endl;
    cout << ">>>>>>>>> TICKET TEMPORAL <<<<<<<<<" << endl;
    cout << endl;

}