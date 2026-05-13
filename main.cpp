#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
#include "sistemaEnvio.hpp"
#include "sistemaCalculos.hpp"
using namespace std;

void ocultarAcciones(int cantLineas) {

    for (int i = 0; i < cantLineas; i++) {
        cout << "\033[F";
        cout << "\033[K";
    }

    cout.flush();
}

int main() {

    vector<PRODUCTO> catalogo;

    cargarCatalogo(catalogo);

    CARRITO carritoUser;
    int op;
    bool extraLinea = false;

    cout << "+-------------------------------------------------+" << endl;
    cout << "|                   MENU VIRTUAL                  |" << endl;
    cout << "+-------------------------------------------------+" << endl;
    cout << "|  [1] Agregar Producto    [2] Eliminar Producto  |" << endl;
    cout << "|  [3] Buscar Producto     [4] Mostrar Carrito    |" << endl;
    cout << "|  [5] Hacer Pedido                               |" << endl;
    cout << "+-------------------------------------------------+" << endl;

    do {

        cout << "> Selecciona una opcion: "; cin >> op;
        if (op != 1 && op != 2 && op != 3 && op != 4 && op != 5) {

            extraLinea = true;
            ocultarAcciones(1);
            do {

                cout << "/Error.(Opcion Invalida)" << endl;
                cout << "> Selecciona una opcion valida: "; cin >> op;
                if (op != 1 && op != 2 && op != 3 && op != 4 && op != 5) {
                    ocultarAcciones(2);
                }

            } while (op != 1 && op != 2 && op != 3 && op != 4 && op != 5);

        }
        cout << endl;

        switch (op) {
            case 1: {
                carritoUser.agregarAlCarrito(catalogo);
                break;
            }

            case 2: {
                carritoUser.eliminarDelCarrito(catalogo);
                break;
            }

            case 3: {
                buscarProducto(catalogo, carritoUser.cantLineas);
                break;
            }

            case 4: {
                mostrarCarrito(carritoUser.subtotal, carritoUser.productos, catalogo);
                break;
            }

        }

        cout << "[Enter] para volver al menu...";
        cin.ignore();
        cin.get();

        if (op == 1 || op == 2) {
            ocultarAcciones(9);

        } else if (op == 3) {
            if (carritoUser.cantLineas > 9) ocultarAcciones(carritoUser.cantLineas);
            if (carritoUser.cantLineas == 9) ocultarAcciones(9);

        }
        else if (op == 4) {
            ocultarAcciones((carritoUser.productos.size()*2) + 9);

        }
        if (extraLinea == true) {
            ocultarAcciones(1);
            extraLinea = false;
        }

    } while (op != 5);

    PEDIDO pedidoUser;
    string confirmar;

    cout << endl;
    cout << "+-------------------------------------------------+" << endl;
    cout << "|                  HACER PEDIDO!                  |" << endl;
    cout << "+-------------------------------------------------+" << endl;
    do {

        cout << "| Informacion Personal                            |" << endl;
        cout << "|                                                 |" << endl;
        cout << "| Nombre:                                         |\033[41D"; getline(cin, pedidoUser.nombre);
        cout << "| Celular:                                        |\033[40D"; getline(cin, pedidoUser.celular);
        cout << "| Email:                                          |\033[42D"; getline(cin, pedidoUser.email);
        cout << "|                                                 |" << endl;
        cout << "| Los datos son correctos?(si/no):                |\033[15D"; getline(cin, confirmar);
        if (confirmar == "no" || confirmar == "NO" || confirmar == "No") {
            ocultarAcciones(7);
        }

    } while (confirmar == "no" || confirmar == "NO" || confirmar == "No");
    cout << "+-------------------------------------------------+" << endl;
    do {

        cout << "| Direccion de Envio                              |" << endl;
        cout << "|                                                 |" << endl;
        cout << "| Calle:                                          |\033[42D"; getline(cin, pedidoUser.calle);
        cout << "| Numero:                                         |\033[41D"; getline(cin, pedidoUser.numero);
        cout << "| Colonia:                                        |\033[40D"; getline(cin, pedidoUser.colonia);
        cout << "| Municipio:                                      |\033[38D"; getline(cin, pedidoUser.municipio);
        cout << "| Estado:                                         |\033[41D"; getline(cin, pedidoUser.estado);
        cout << "| Codigo Postal:                                  |\033[34D"; getline(cin, pedidoUser.cp);
        cout << "| Referencias:                                    |\033[36D"; getline(cin, pedidoUser.referencias);
        cout << "|                                                 |" << endl;
        cout << "| Los datos son correctos?(si/no):                |\033[15D"; getline(cin, confirmar);
        if (confirmar == "no" || confirmar == "NO" || confirmar == "No") {
            ocultarAcciones(11);
        }

    } while (confirmar == "no" || confirmar == "NO" || confirmar == "No");
    cout << "+-------------------------------------------------+" << endl;

    pedidoUser.direccion = pedidoUser.calle + " " + 
        pedidoUser.numero + ", " + 
        pedidoUser.colonia + ", " + 
        pedidoUser.municipio + ", " + 
        pedidoUser.cp;

    obtenerCoordenadas(pedidoUser);
    calcularDistancia(pedidoUser);
    calcularCostoEnvio(pedidoUser, carritoUser.subtotal);
    pedidoUser.costoTotal = pedidoUser.costoEnvio + carritoUser.subtotal;
    elegirMetodoPago(pedidoUser);

    generarTicket(pedidoUser, carritoUser.productos);

    return 0;

}