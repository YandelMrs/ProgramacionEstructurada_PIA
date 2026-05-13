#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct PRODUCTO {

    int id;
    string nombre;
    double precio;
    string marca;

};

struct CARRITO {

    vector<string> productos;
    double subtotal = 0;
    int cantLineas = 9;

    void agregarAlCarrito(vector<PRODUCTO> catalogo) {

        string producto;

        cout << "+-- AGERGAR PRODUCTO -----------------------------+" << endl;
        cout << "| Producto:                                       |\033[39D"; cin >> producto;
        cout << "+-------------------------------------------------+" << endl;
        
        bool encontrado = false;
        for (int i = 0; i < catalogo.size(); i++) {

            if (producto == catalogo[i].nombre) {

                productos.push_back(producto);
                subtotal += catalogo[i].precio;
                encontrado = true;
                cout << "|               Producto Agregado :D              |" << endl;
                cout << "+-------------------------------------------------+" << endl;
                cout << endl;
                break;

            }

        }
        if (encontrado == false) {

            cout << "|             Producto no encontrado!             |" << endl;
            cout << "+-------------------------------------------------+" << endl;
            cout << endl;

        }


    }

    void eliminarDelCarrito(vector<PRODUCTO> catalogo) {

        string producto;

        if (productos.empty()) {

            cout << "+-- ELIMINAR PRODUCTO ----------------------------+" << endl;
            cout << "| Producto:                                       |" << endl;
            cout << "+-------------------------------------------------+" << endl;
            cout << "|               Carrito esta vacio!               |" << endl;
            cout << "+-------------------------------------------------+" << endl;
            cout << endl;
            return;

        }

        cout << "+-- ELIMINAR PRODUCTO ----------------------------+" << endl;
        cout << "| Producto:                                       |\033[39D"; cin >> producto;
        cout << "+-------------------------------------------------+" << endl;

        bool encontrado = false;
        for (int i = 0; i < productos.size(); i++) {

            if (producto == productos[i]) {

                for (int j = 0; j < catalogo.size(); j++) {

                    if (productos[i] == catalogo[j].nombre) {

                        productos.erase(productos.begin() + i);
                        subtotal -= catalogo[j].precio;
                        encontrado = true;
                        break;
                    }

                }
                cout << "|              Producto Eliminado :(              |" << endl;
                cout << "+-------------------------------------------------+" << endl;
                cout << endl;
                break;

            }

        }
        if (encontrado == false) {
        
            cout << "|         Producto no esta en el carrito!         |" << endl;
            cout << "+-------------------------------------------------+" << endl;
            cout << endl;
        
        }

    }

};

void cargarCatalogo(vector<PRODUCTO>& catalogo);
void buscarProducto(vector<PRODUCTO>& catalogo, int& lineas);
void mostrarCarrito(double& subtotal, vector<string> productos, vector<PRODUCTO>& catalogo);