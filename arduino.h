#pragma once
#include<iostream>
#define rele 12
#define boton 2
using namespace std;

class arduino {
private:
	int on = 1;       // Variable encendido
	int valorboton;       // Variable para almacenar lectura de boton
	int memoria = 0;        // Variable para saber el estado de programa
	int valanterior = 0;      // Variable de almacenamiento estado anterior de boton

public:
	arduino() {}

	arduino(int o, int valbot, int mem, int alante) {
		on = o;
		valorboton = valbot;
		memoria = mem;
		valanterior = alante;
	}

	void setup() {

	}

	// Control de la cinta transportadora

	void loop() {

		
		}
};