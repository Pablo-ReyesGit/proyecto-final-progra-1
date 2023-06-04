#pragma once
#include <mysql.h>
#include <iostream>
#include <string>
#include "conexionDB.h"

using namespace std;

class Puesto {
    // Atributos
private:
    int idPuesto;
    string puesto;

public:
    // Constructor
    Puesto() {}

    Puesto(int id, string p) {
        idPuesto = id;
        puesto = p;
    }

    // Métodos
    // set (modificar)
    void setIdPuesto(int id) { idPuesto = id; }
    void setPuesto(string p) { puesto = p; }

    // get (mostrar)
    int getIdPuesto() { return idPuesto; }
    string getPuesto() { return puesto; }

    // Métodos CRUD
    void crear() {
        int q_estado;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.setConectar()) {
            string insert = "INSERT INTO puestos(puesto) VALUES('" + puesto + "')";
            const char* i = insert.c_str();
            q_estado = mysql_query(cn.setConectar(), i);
            if (!q_estado) {
                cout << "Ingreso exitoso..." << endl;
            }
            else {
                cout << "Error al ingresar la informacion: " << mysql_error(cn.setConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexion ---" << endl;
        }
        cn.cerrar_conexion();
    }

    void leer() {
        int q_estado;
        ConexionBD cn = ConexionBD();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrir_conexion();
        if (cn.setConectar()) {
            string consulta = "SELECT * FROM puestos";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.setConectar(), c);
            if (!q_estado) {
                resultado = mysql_store_result(cn.setConectar());
                cout << "------------------- Puestos -------------------" << endl;
                while (fila = mysql_fetch_row(resultado)) {
                    cout << "ID: " << fila[0] << ", Puesto: " << fila[1] << endl;
                }
            }
            else {
                cout << "Error al realizar la consulta: " << mysql_error(cn.setConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexion ---" << endl;
        }
        cn.cerrar_conexion();
    }

    void actualizar(int id) {
        int q_estado;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.setConectar()) {
            string update = "UPDATE puestos SET puesto = '" + puesto + "' WHERE idPuesto = " + to_string(id);
            const char* u = update.c_str();
            q_estado = mysql_query(cn.setConectar(), u);
            if (!q_estado) {
                cout << "Actualizacion exitosa..." << endl;
            }
            else {
                cout << "Error al actualizar la informacion: " << mysql_error(cn.setConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexion ---" << endl;
        }
        cn.cerrar_conexion();
    }

    void eliminar(int id) {
        int q_estado;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.setConectar()) {
            string del = "DELETE FROM puestos WHERE idPuesto = " + to_string(id);
            const char* d = del.c_str();
            q_estado = mysql_query(cn.setConectar(), d);
            if (!q_estado) {
                cout << "Eliminacion exitosa..." << endl;
            }
            else {
                cout << "Error al eliminar la informacion: " << mysql_error(cn.setConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexion ---" << endl;
        }
        cn.cerrar_conexion();
    }
};
