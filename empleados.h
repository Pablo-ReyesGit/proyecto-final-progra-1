
#pragma once
#include <mysql.h>
#include <iostream>
#include <string>
#include "conexionDB.h"

using namespace std;
class empleados
{
        // Atributos
    private:
        int id_empleado, id_puesto;
        string nombres, apellidos, direccion, telefono, DPI, fecha_nacimineto, fecha_nicio_labores, fecha_ingreso;
        bool genero;

        // Constructor
    public:
        empleados() {}

        empleados(int id, string nom, string ape, string dir, string tel, string dpi, bool gen,string fn,int idP, string fiv, string fi) {
            id_empleado = id;
            nombres = nom;
            apellidos = ape;
            direccion = dir;
            telefono = tel;
            DPI = dpi;
            genero = gen;
            fecha_nacimineto = fn;
            id_puesto = idP;
            fecha_nicio_labores = fiv;
            fecha_ingreso = fi;
        }

        // Métodos
        // set (modificar)
        void setIdEmpleado(int id) { id_empleado = id; }
        void setNombres(string nom) { nombres = nom; }
        void setApellido(string ape) { apellidos = ape; }
        void setDireccion(string dir) { direccion = dir; }
        void setTelefono(string tel) { telefono = tel; }
        void setDPI(string dpi) { DPI = dpi; }
        void setGenero(bool gen) { genero = gen; }
        void setFecha_nacimiento(string fn) { fecha_nacimineto = fn; }
        void setIdPuesto(int idP) { id_puesto = idP; }
        void setFecha_inicio_labores(string fiv) { fecha_nicio_labores = fiv; }
        void setFecha_ingreso(string fi) { fecha_ingreso = fi; }

        // get (mostrar)
        int getIdEmpleado() { return id_empleado; }
        string getNombres() { return nombres; }
        string getApellidos() { return apellidos; }
        string getDireccion() { return direccion; }
        string getTelefono() { return telefono; }
        string getDPI() { return DPI; }
        bool getGenero() { return genero; }
        string getFecha_nacimiento() { return fecha_nacimineto; }
        int getIdPuesto() { return id_puesto; }
        string getFecha_inicio_labores() { return fecha_nicio_labores; }
        string getFecha_Ingreso() { return fecha_ingreso; }

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
                string gene = to_string(genero);
                string idPuestos = to_string(id_puesto);
                string insert = "INSERT INTO proveedores(proveedor, nit, direccion, telefono) VALUES('" + nombres + "', '" + apellidos + "', '" + direccion + "', '" + telefono + "')" + DPI + "')" + gene + "')" + fecha_nacimineto + "')" + idPuestos + "')" + fecha_nicio_labores + "')" + fechaIngreso + "')";
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
                        cout << "ID: " << fila[0] << ", nombres: " << fila[1] << ", apellidos: " << fila[2] << ", Direccion: " << fila[3] << ", Telefono: " << fila[4] << ", DPI: " << fila[5] << ", Genero: " << fila[6] << ", fecha de nacimiento: " << fila[6] << ", Id puesto: " << fila[7] << ", fecha de inico de labores: " << fila[8] << ", fecha de ingreso: " << fila[9] << endl;
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
                string gene = to_string(genero);
                string idPuestos = to_string(id_puesto);
                string update = "UPDATE proveedores SET nombre = '" + nombres + "', apellido = '" + apellidos + "', direccion = '" + direccion + "', telefono = '" + telefono + "', DIP = '" + DPI + "', genero = '" + gene + "', fecha_nacimiento = '" + fecha_nacimineto + "', id_puesto = '" + idPuestos + "', fecha_inicio_labores = '" + fecha_nicio_labores + "', fecha_ingreso = '" + fecha_ingreso + "' WHERE idEmpleados = " + to_string(id);
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
                string del = "DELETE FROM empleados WHERE idEmpleados = " + to_string(id);
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