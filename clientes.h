#pragma once
#include <mysql.h>
#include <iostream>
#include <string>
#include "conexionDB.h"


using namespace std;

class Cliente {
    // Atributos
private:
    int idCliente;
    string nombres;
    string apellidos;
    string nit;
    bool genero;
    string telefono;
    string correoElectronico;
    string fechaIngreso;

    // Constructor
public:
    Cliente() {}

    Cliente(int id, string nom, string ape, string n, bool gen, string tel, string correo, string ingreso) {
        idCliente = id;
        nombres = nom;
        apellidos = ape;
        nit = n;
        genero = gen;
        telefono = tel;
        correoElectronico = correo;
        fechaIngreso = ingreso;
    }

    // Métodos
    // set (modificar)
    void setIdCliente(int id) { idCliente = id; }
    void setNombres(string nom) { nombres = nom; }
    void setApellidos(string ape) { apellidos = ape; }
    void setNit(string n) { nit = n; }
    void setGenero(bool gen) { genero = gen; }
    void setTelefono(int tel) { telefono = tel; }
    void setCorreoElectronico(string correo) { correoElectronico = correo; }
    void setFechaIngreso(string ingreso) { fechaIngreso = ingreso; }

    // get (mostrar)
    int getIdCliente() { return idCliente; }
    string getNombres() { return nombres; }
    string getApellidos() { return apellidos; }
    string getNit() { return nit; }
    bool getGenero() { return genero; }
    string getTelefono() { return telefono; }
    string getCorreoElectronico() { return correoElectronico; }
    string getFechaIngreso() { return fechaIngreso; }

    // Métodos CRUD
    void crear() {
        int q_estado;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();

        time_t tiempoActual = time(nullptr);
        struct tm tiempoLocal;
        localtime_s(&tiempoLocal, &tiempoActual);
        char fechaIngreso[20];
        strftime(fechaIngreso, sizeof(fechaIngreso), "%Y-%m-%d %H:%M:%S", &tiempoLocal);

        if (cn.setConectar()) {
            string generoStr = genero ? "1" : "0";
            string insert = "INSERT INTO clientes(nombres, apellidos, nit, genero, telefono, correo_electronico, fechaingreso) VALUES('" + nombres + "', '" + apellidos + "', '" + nit + "', " + generoStr + ", '" + telefono + "', '" + correoElectronico + "', '" + fechaIngreso + "')";
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
            string consulta = "SELECT * FROM clientes";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.setConectar(), c);
            if (!q_estado) {
                resultado = mysql_store_result(cn.setConectar());
                cout << "------------------- Clientes -------------------" << endl;
                while (fila = mysql_fetch_row(resultado)) {
                    string generoStr = (fila[4] == "1") ? "Masculino" : "Femenino";
                    cout << "ID: " << fila[0] << ", Nombres: " << fila[1] << ", Apellidos: " << fila[2] << ", NIT: " << fila[3] << ", Genero: " << generoStr << ", Telefono: " << fila[5] << ", Correo Electronico: " << fila[6] << ", Fecha de Ingreso: " << fila[7] << endl;
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
            string generoStr = genero ? "1" : "0";
            string update = "UPDATE clientes SET nombres = '" + nombres + "', apellidos = '" + apellidos + "', nit = '" + nit + "', genero = " + generoStr + ", telefono = '" + telefono + "', correo_electronico = '" + correoElectronico + "', fechaingreso = '" + fechaIngreso + "' WHERE idCliente = " + to_string(id);
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
            string del = "DELETE FROM clientes WHERE idCliente = " + to_string(id);
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

