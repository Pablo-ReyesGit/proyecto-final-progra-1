#pragma once
#include <mysql.h>
#include <iostream>
#include <string>
#include "conexionDB.h"
#include "producto.h"

using namespace std;

class Producto {
    // Atributos
private:
    int idProducto, idMarca, existencia;
    string producto, descripcion, imagen;
    double precio_costo, precio_venta;
    string fecha_ingreso;

public:
    // Constructor
    Producto() {}

    Producto(int id, string prod, int idM, string desc, string img, double costo, double venta, int exist, string fecha) {
        idProducto = id;
        producto = prod;
        idMarca = idM;
        descripcion = desc;
        imagen = img;
        precio_costo = costo;
        precio_venta = venta;
        existencia = exist;
        fecha_ingreso = fecha;
    }

    // Métodos
    // set (modificar)
    void setIdProducto(int id) { idProducto = id; }
    void setProducto(string prod) { producto = prod; }
    void setIdMarca(int idM) { idMarca = idM; }
    void setDescripcion(string desc) { descripcion = desc; }
    void setImagen(string img) { imagen = img; }
    void setPrecioCosto(double costo) { precio_costo = costo; }
    void setPrecioVenta(double venta) { precio_venta = venta; }
    void setExistencia(int exist) { existencia = exist; }
    void setFechaIngreso(string fecha) { fecha_ingreso = fecha; }

    // get (mostrar)
    int getIdProducto() { return idProducto; }
    string getProducto() { return producto; }
    int getIdMarca() { return idMarca; }
    string getDescripcion() { return descripcion; }
    string getImagen() { return imagen; }
    double getPrecioCosto() { return precio_costo; }
    double getPrecioVenta() { return precio_venta; }
    int getExistencia() { return existencia; }
    string getFechaIngreso() { return fecha_ingreso; }

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
            string insert = "INSERT INTO productos(producto, idMarca, descripcion, imagen, precio_costo, precio_venta, existencia, fecha_ingreso) VALUES('" + producto + "', " + to_string(idMarca) + ", '" + descripcion + "', '" + imagen + "', " + to_string(precio_costo) + ", " + to_string(precio_venta) + ", " + to_string(existencia) + ", '" + fechaIngreso + "')";
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
            string consulta = "SELECT * FROM productos";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.setConectar(), c);
            if (!q_estado) {
                resultado = mysql_store_result(cn.setConectar());
                cout << "------------------- Productos -------------------" << endl;
                while (fila = mysql_fetch_row(resultado)) {
                    cout << "ID: " << fila[0] << ", Producto: " << fila[1] << ", ID Marca: " << fila[2] << ", Descripcion: " << fila[3] << ", Imagen: " << fila[4] << ", Precio Costo: " << fila[5] << ", Precio Venta: " << fila[6] << ", Existencia: " << fila[7] << ", Fecha Ingreso: " << fila[8] << endl;
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
            string update = "UPDATE productos SET producto = '" + producto + "', idMarca = " + to_string(idMarca) + ", descripcion = '" + descripcion + "', imagen = '" + imagen + "', precio_costo = " + to_string(precio_costo) + ", precio_venta = " + to_string(precio_venta) + ", existencia = " + to_string(existencia) + ", fecha_ingreso = '" + fecha_ingreso + "' WHERE idProducto = " + to_string(id);
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
            string del = "DELETE FROM productos WHERE idProducto = " + to_string(id);
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

