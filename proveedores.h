#pragma once
#include <mysql.h>
#include <iostream>
#include <string>
#include "conexionDB.h"

using namespace std;

class Proveedor  {
    // Atributos
private:
    int idProveedor;
    string proveedor;
    string nit;
    string direccion;
    string telefono;

    // Constructor
public:
    Proveedor() {}

    Proveedor(int id, string prov, string n, string dir, string tel) {
        idProveedor = id;
        proveedor = prov;
        nit = n;
        direccion = dir;
        telefono = tel;
    }

    // Métodos
    // set (modificar)
    void setIdProveedor(int id) { idProveedor = id; }
    void setProveedor(string prov) { proveedor = prov; }
    void setNit(string n) { nit = n; }
    void setDireccion(string dir) { direccion = dir; }
    void setTelefono(string tel) { telefono = tel; }

    // get (mostrar)
    int getIdProveedor() { return idProveedor; }
    string getProveedor() { return proveedor; }
    string getNit() { return nit; }
    string getDireccion() { return direccion; }
    string getTelefono() { return telefono; }

    // Métodos CRUD
    void crear() {
        int q_estado;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.setConectar()) {
            string insert = "INSERT INTO proveedores(proveedor, nit, direccion, telefono) VALUES('" + proveedor + "', '" + nit + "', '" + direccion + "', '" + telefono + "')";
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
            string consulta = "SELECT * FROM proveedores";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.setConectar(), c);
            if (!q_estado) {
                resultado = mysql_store_result(cn.setConectar());
                cout << "------------------- Proveedores -------------------" << endl;
                while (fila = mysql_fetch_row(resultado)) {
                    cout << "ID: " << fila[0] << ", Proveedor: " << fila[1] << ", NIT: " << fila[2] << ", Direccion: " << fila[3] << ", Telefono: " << fila[4] << endl;
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
            string update = "UPDATE proveedores SET proveedor = '" + proveedor + "', nit = '" + nit + "', direccion = '" + direccion + "', telefono = '" + telefono + "' WHERE idProveedore = " + to_string(id);
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
            string del = "DELETE FROM proveedores WHERE idProveedore = " + to_string(id);
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

