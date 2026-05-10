#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
#include "sistemaEnvio.hpp"
#include "sistemaCalculos.hpp"
using namespace std;

void ocultarAcciones(int cantLineas, bool extraLinea = false) {
 
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

    cout << "==================================" << endl;
    cout << "           MENU VIRTUAL           " << endl;
    cout << "==================================" << endl;
    cout << "       1 - Agregar Producto       " << endl;
    cout << "       2 - Eliminar Producto      " << endl;
    cout << "       3 - Buscar Producto        " << endl;
    cout << "       4 - Mostrar Carrito        " << endl;
    cout << "       5 - Hacer Pedido           " << endl;
    cout << "==================================" << endl;

    do {

        cout << "Opcion: "; cin >> op;
        cout << endl;

        switch (op) {
            case 1: {
                carritoUser.agregarAlCarrito(catalogo);
                break;
            }

            case 2: {
                carritoUser.eliminarDelCarrito();
                break;
            }

            case 3: {
                buscarProducto(catalogo, carritoUser.condicion);
                break;
            }

            case 4: {
                mostrarCarrito(carritoUser.subtotal, carritoUser.productos, catalogo);
                break;
            }

        }

        cout << "\nPresiona Enter para continuar...";
        cin.ignore();
        cin.get();

        if (op == 1 || op == 2) {
            ocultarAcciones(12);

        } else if (op == 3) {
            if (carritoUser.condicion == true) ocultarAcciones(16);
            if (carritoUser.condicion == false) ocultarAcciones(12);

        }
        else if (op == 4) {
            ocultarAcciones(carritoUser.productos.size() + 10);

        }

    } while (op != 5);

    PEDIDO pedidoUser;

    cout << endl;
    cout << "+-----------------------------------+" << endl;
    cout << "|           HACER PEDIDO!           |" << endl;
    cout << "+-----------------------------------+" << endl;
    cout << " Informacion Personal" << endl << endl;
    cout << " Ingresa nombre: "; cin >> pedidoUser.nombre;
    cout << " Ingresa celuar: "; cin >> pedidoUser.celular;
    cout << " Ingresa email: "; cin >> pedidoUser.email;
    cout << "+-----------------------------------+" << endl;
    getchar();
    cout << " Direccion de Envio" << endl << endl;
    cout << " Ingresa direccion: "; getline(cin, pedidoUser.direccion);
    cout << " Ingresa referenias: "; cin >> pedidoUser.referencias;
    cout << "+-----------------------------------+" << endl;

    obtenerCoordenadas(pedidoUser);
    calcularDistancia(pedidoUser);
    calcularCostoEnvio(pedidoUser, carritoUser.subtotal);
    pedidoUser.costoTotal = pedidoUser.costoEnvio + carritoUser.subtotal;
    elegirMetodoPago(pedidoUser);

    generarTicket(pedidoUser);

    return 0;

}