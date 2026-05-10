#include "sistemaCalculos.hpp"

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib> 
#include "json.hpp"
using namespace std;

void obtenerCoordenadas(PEDIDO& p) {

    using json = nlohmann::json;
    string comando = "python get_coords.py \"" + p.direccion + "\"";

    system(comando.c_str());

    ifstream archivo("transferencia.json");
    if (archivo.is_open()) {
        json datos;
        archivo >> datos;

        if (datos["status"] == "ok") {
            string latstr = datos["lat"];
            string lonstr = datos["lon"];
            p.latitud = stod(latstr);
            p.longitud = stod(lonstr);

        }
        else {
            cout << "Error: " << datos["message"] << std::endl;
            p.latitud = 0.00;
            p.longitud = 0.00;
        }
    }

}

void calcularDistancia(PEDIDO& p) {

    const double PI = 3.14159265358979323846;

    double latitudTienda = 25.7263663 * (PI / 180);
    double longitudTienda = -100.3123106 * (PI / 180);
    double latRad = p.latitud * (PI / 180);
    double lonRad = p.longitud * (PI / 180);

    double a = pow(sin((latitudTienda - latRad) / 2), 2) +
        (cos(latitudTienda) * cos(latRad) * pow(sin((longitudTienda - lonRad) / 2), 2));

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    p.distancia = 6371.0 * c;

}

void calcularCostoEnvio(PEDIDO& p, double subtotal) {

    string ans;
    p.costoEnvio = (2 * exp(0.225 * p.distancia)) - (0.1 * log(p.distancia + 1)) + 50;
    if (p.costoEnvio < 50) p.costoEnvio = 50;

    cout << " Deseas envio premium?(24 hrs, +35%): "; cin >> ans;
    cout << "+-----------------------------------+" << endl;
    if (ans == "si" || ans == "SI" || ans == "Si") p.costoEnvio *= 1.35;

    cout << " Deseas pagar seguro de envio?: "; cin >> ans;
    cout << "+-----------------------------------+" << endl;
    if (ans == "si" || ans == "SI" || ans == "Si") {
        
        double costoSeguro  = subtotal * 0.10; 
        p.costoEnvio += costoSeguro;
    
    }

}

bool validarTarjetaLuhn(const string& numeroTarjeta) {

    int suma = 0;
    bool esSegundo = false;

    for (int i = numeroTarjeta.length() - 1; i >= 0; i--) {

        if (numeroTarjeta[i] == ' ') continue;

        int digito = numeroTarjeta[i] - '0';

        if (esSegundo) {

            digito = digito * 2;
            if (digito > 9) {

                digito -= 9;

            }

        }

        suma += digito;
        esSegundo = !esSegundo;

    }

    return (suma % 10 == 0);

}

void elegirMetodoPago(PEDIDO& p) {

    int op;

    cout << " Elige tu metodo de pago" << endl << endl;
    cout << " 1 - Efectivo" << endl;
    cout << " 2 - Debito/Credito" << endl;
    cout << " Opcion: "; cin >> op;
    cout << "+-----------------------------------+" << endl;

    switch (op) {
        case 1: {
            p.metodoPago = "Efectivo";
            cout << " Pagaras al recibir el envio :)" << endl;
            cout << "+-----------------------------------+" << endl;
            break;
        }

        case 2: {
            string numeroTarejta, fecha, cvv;
            bool valido;
            p.metodoPago = "Debito/Credito";

            cout << " Datos de Tarjeta" << endl << endl;

            do {

                cout << " Numero: ";
                getline(cin >> ws, numeroTarejta);

                valido = validarTarjetaLuhn(numeroTarejta);

                if (valido == false) {

                    cout << " Numero de tarjeta no valido" << endl;
                    cout << " Presiona Enter para continuar...";
                    cin.ignore(10000, '\n');
                    cin.get();

                    for (int i = 0; i < 3; i++) {
                        cout << "\033[F";
                        cout << "\033[K";
                    }
                }

            } while (valido == false);

            cout << " Fecha de vencimiento: ";
            cin >> fecha;
            cout << " CVV: ";
            cin >> cvv;

            cout << endl << " Pago Realizado :D" << endl;
            cout << "+-----------------------------------+" << endl;
            break;
        }

    }

}

void generarTicket(PEDIDO& p) {


    ofstream archivoTicket("ticket.txt", ios::out);

    if (!archivoTicket.is_open()) {

        cout << "Error al abrir el archivo" << endl;
        return;

    }

    archivoTicket << "+-----------------------------------+" << endl;
    archivoTicket << "|         Resumen de Compra         |" << endl;
    archivoTicket << "+-----------------------------------+" << endl;
    archivoTicket << left << "|Nombre: " << p.nombre << setw(36) << "|" << endl;
    archivoTicket << left << "|Celular: " << p.celular << setw(36) << "|" << endl;
    archivoTicket << left << "|Email: " << p.email << setw(36) << "|" << endl;
    archivoTicket << left << "|Total:  " << p.costoTotal << setw(36) << "|" << endl;
    archivoTicket << left << "|Metodo de Pago: " << p.metodoPago << setw(36) << "|" << endl;

    archivoTicket.close();

}