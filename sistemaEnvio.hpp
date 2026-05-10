#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct PRODUCTO {

    string nombre;
    double precio;
    string marca;

};

struct CARRITO {

    vector<string> productos;
    double subtotal;
    bool condicion;

    void agregarAlCarrito(vector<PRODUCTO> catalogo) {

        string producto;

        cout << "==================================" << endl;
        cout << "  Agrega un producto al carrito!  " << endl;
        cout << "==================================" << endl;
        cout << "Anadir: "; cin >> producto;
        
        bool encontrado = false;
        for (int i = 0; i < catalogo.size(); i++) {

            if (producto == catalogo[i].nombre) {

                productos.push_back(producto);
                encontrado = true;
                cout << "==================================" << endl;
                cout << "       Producto agregado :D       " << endl;
                cout << "==================================" << endl;
                cout << endl;
                break;

            }

        }
        if (encontrado == false) {

            cout << "==================================" << endl;
            cout << " Producto no esta en el catalogo! " << endl;
            cout << "==================================" << endl;
            cout << endl;

        }


    }

    void eliminarDelCarrito() {

        string producto;

        if (productos.empty()) {

            cout << "==================================" << endl;
            cout << "     Advertencia: Carrito vacio   " << endl;
            cout << "==================================" << endl;
            cout << endl;
            return;

        }

        cout << "==================================" << endl;
        cout << "        Eliminar producto!        " << endl;
        cout << "==================================" << endl;
        cout << "Eliminar: "; cin >> producto;

        bool encontrado = false;
        for (int i = 0; i < productos.size(); i++) {

            if (producto == productos[i]) {

                productos.erase(productos.begin() + i);
                encontrado = true;
                cout << "==================================" << endl;
                cout << "       Producto eliminado :(      " << endl;
                cout << "==================================" << endl;
                cout << endl;
                break;

            }

        }
        if (encontrado == false) {
        
            cout << "==================================" << endl;
            cout << "  Producto no esta en el carrito  " << endl;
            cout << "==================================" << endl;
            cout << endl;
        
        }

    }

};

void cargarCatalogo(vector<PRODUCTO>& catalogo);
void buscarProducto(vector<PRODUCTO>& catalogo, bool& condition);
void mostrarCarrito(double& subtotal, vector<string> productos, vector<PRODUCTO>& catalogo);