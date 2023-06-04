#pragma once
#include <iostream>
#include<mysql.h>

using namespace std;

class ConexionBD
{
private:
	MYSQL* conectar;
public:
	void abrir_conexion() {
		conectar = mysql_init(0);
		conectar = mysql_real_connect(conectar, "localhost", "root", "pablo123,reyesSQL", "db_ventas", 3306, NULL, 0);

	}

	MYSQL* setConectar() {
		return conectar;
	}
	void cerrar_conexion() {
		mysql_close(conectar);
	}

};

