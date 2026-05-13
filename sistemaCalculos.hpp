#pragma once

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib> 
#include "json.hpp"
using namespace std;

struct PEDIDO {

    string nombre;
    string celular;
    string email;

    string calle;
    string numero;
    string colonia;
    string municipio;
    string estado;
    string cp;

    string direccion;
    string referencias;
    double latitud;
    double longitud;
    double distancia;

    string metodoPago;
    double costoEnvio;
    double costoTotal;

};

void obtenerCoordenadas(PEDIDO& p);
void calcularDistancia(PEDIDO& p);
void calcularCostoEnvio(PEDIDO& p, double subtotal);
bool validarTarjetaLuhn(const string& numeroTarjeta);
void elegirMetodoPago(PEDIDO& p);
void generarTicket(PEDIDO& p, vector<string> productos);