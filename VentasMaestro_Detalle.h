#pragma once
#include <mysql.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "conexionDB.h"

using namespace std;

class Ventas {
private:
    int idVenta, noFactura, idCliente, idEmpleado;
    string serie, fechaFactura, fechaIngreso;
public:
    Ventas() {}

    Ventas(int id, int factura, string ser, string fecha, int cliente, int empleado, string ingreso) {
        idVenta = id;
        noFactura = factura;
        serie = ser;
        fechaFactura = fecha;
        idCliente = cliente;
        idEmpleado = empleado;
        fechaIngreso = ingreso;
    }

    void setIdVenta(int id) { idVenta = id; }
    void setNoFactura(int factura) { noFactura = factura; }
    void setSerie(string ser) { serie = ser; }
    void setFechaFactura(string fecha) { fechaFactura = fecha; }
    void setIdCliente(int cliente) { idCliente = cliente; }
    void setIdEmpleado(int empleado) { idEmpleado = empleado; }
    void setFechaIngreso(string ingreso) { fechaIngreso = ingreso; }

    int getIdVenta() { return idVenta; }
    int getNoFactura() { return noFactura; }
    string getSerie() { return serie; }
    string getFechaFactura() { return fechaFactura; }
    int getIdCliente() { return idCliente; }
    int getIdEmpleado() { return idEmpleado; }
    string getFechaIngreso() { return fechaIngreso; }



    void crear() {
        int q_estado;
        srand(time(0));
        int No_factura = 1 + (rand() % 10000);
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();

        time_t tiempoActual = time(nullptr);
        struct tm tiempoLocal;
        localtime_s(&tiempoLocal, &tiempoActual);
        char fechaIngreso[20];
        strftime(fechaIngreso, sizeof(fechaIngreso), "%Y-%m-%d %H:%M:%S", &tiempoLocal);

        time_t tiempoFactura = time(nullptr);
        struct tm tiempoFacturaLocal;
        localtime_s(&tiempoFacturaLocal, &tiempoFactura);
        char fechaFactura[11];
        strftime(fechaFactura, sizeof(fechaFactura), "%Y-%m-%d", &tiempoFacturaLocal);
        if (cn.setConectar()) {
            string insert = "INSERT INTO ventas (nofactura, serie, fechafactura, idcliente, idempleado, fechaingreso) VALUES (" + to_string(No_factura) + ", '" + serie + "', '" + fechaFactura + "', " + to_string(idCliente) + ", " + to_string(idEmpleado) + ", '" + fechaIngreso + "')";

            const char* i = insert.c_str();
            q_estado = mysql_query(cn.setConectar(), i);
            if (!q_estado) {
                cout << "Ingreso exitoso en la tabla 'ventas'..." << endl;
                int idVentaInsertada = mysql_insert_id(cn.setConectar());
                ingresarDetalle(idVentaInsertada);
                factura(idVentaInsertada);
            }
            else {
                cout << "Error al ingresar la información en la tabla 'ventas': " << mysql_error(cn.setConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexión ---" << endl;
        }
        cn.cerrar_conexion();
    }

    void ingresarDetalle(int idVenta) {
        int id_producto=0, cantidad=0, precio=0;
        int q_estado;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        char res;
        if (cn.setConectar()) {
            string insert = "INSERT INTO ventas_detalle (idVenta, idProducto, cantidad, precio_unitario) VALUES ";
            do {
                cout << "ingrese el ID producto" << endl;
                cin >> id_producto;
                cout << "ingrese la cantidad" << endl;
                cin >> cantidad;
                cout << "ingrese el precio" << endl;
                cin >> precio;
                insert += "("+to_string(idVenta) + ", " + to_string(id_producto) + ", " + to_string(cantidad) + ", " + to_string(precio) + ") ";
                cout << "aun hay mas detalles(s/n)" << endl;
                cin >> res;
            } while (res == 's' || res == 'S');

            const char* i = insert.c_str();
            q_estado = mysql_query(cn.setConectar(), i);
            if (!q_estado) {
                cout << "Ingreso exitoso en la tabla 'ventas_detalle'..." << endl;
            }
            else {
                cout << "Error al ingresar la información en la tabla 'ventas_detalle': " << mysql_error(cn.setConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexión ---" << endl;
        }
        cn.cerrar_conexion();
    }

    void leer() {
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.setConectar()) {
            string consulta = "SELECT * FROM ventas";
            const char* c = consulta.c_str();
            mysql_query(cn.setConectar(), c);
            MYSQL_RES* resultado = mysql_store_result(cn.setConectar());

            if (resultado) {
                MYSQL_ROW fila;
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << "------------------- Ventas -------------------" << endl;
                    cout << "IdVenta: " << fila[0] << ", No. Factura: " << fila[1] << ", Serie: " << fila[2] << ", Fecha Factura: " << fila[3] << ", Id Empleado: " << fila[4] << ", Fecha Ingreso: " << fila[5] << endl;

                    int idVenta = atoi(fila[0]);
                    mostrarDetalles(idVenta, cn);
                    cout << "-----------------------" << endl;
                }
                mysql_free_result(resultado);
            }
            else {
                cout << "Error al consultar la tabla 'ventas': " << mysql_error(cn.setConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexión ---" << endl;
        }
        cn.cerrar_conexion();
    }

    void factura(int idVenta) {
        ConexionBD cn;
        cn.abrir_conexion();

        if (cn.setConectar()) {
            string consulta = "SELECT e.idVenta, e.nofactura, e.fechafactura, c.nombres, c.apellidos, c.nit "
                "FROM ventas AS e "
                "INNER JOIN clientes AS c ON e.idcliente = c.idClientes "
                "WHERE e.idVenta = " + to_string(idVenta) + ";";

            const char* c = consulta.c_str();
            mysql_query(cn.setConectar(), c);
            MYSQL_RES* resultado = mysql_store_result(cn.setConectar());

            if (resultado) {
                MYSQL_ROW fila;
                if ((fila = mysql_fetch_row(resultado))) {
                    cout << "------------------- Factura -------------------" << endl;
                    cout << "Número de factura: " << fila[1] << ", fecha: " << fila[2] << ", cliente: " << fila[3] << " " << fila[4] << ", nit: " << fila[5] << endl;

                    mostrarDetalles(idVenta, cn);

                    cout << "-----------------------" << endl;
                }
                else {
                    cout << "No se encontró la venta con el idVenta: " << idVenta << endl;
                }
                mysql_free_result(resultado);
            }
            else {
                cout << "Error al consultar la tabla 'ventas': " << mysql_error(cn.setConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexión ---" << endl;
        }

        cn.cerrar_conexion();
    }


    void mostrarDetalles(int idVenta, ConexionBD& cn) {
        if (cn.setConectar()) {
            string consulta = "SELECT * FROM ventas_detalle WHERE idventa = " + to_string(idVenta);
            const char* c = consulta.c_str();
            mysql_query(cn.setConectar(), c);
            MYSQL_RES* resultado = mysql_store_result(cn.setConectar());

            if (resultado) {
                MYSQL_ROW fila;
                cout << "detalles de la compra" << endl;
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << "IdVentaDetalle: " << fila[0] << ", IdVenta: " << fila[1] << ", Cantidad: " << fila[2] << ", Precio Unitario: $ " << fila[3] << endl;
                }
                mysql_free_result(resultado);
            }
            else {
                cout << "Error al consultar la tabla 'ventas_detalle': " << mysql_error(cn.setConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexión ---" << endl;
        }
    }

    void actualizar() {
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.setConectar()) {
            int idVentaActualizacion;
            cout << "Ingrese el ID de la venta a actualizar: ";
            cin >> idVentaActualizacion;

            string consulta = "SELECT * FROM ventas WHERE idVenta = " + to_string(idVentaActualizacion);
            const char* c = consulta.c_str();
            mysql_query(cn.setConectar(), c);
            MYSQL_RES* resultado = mysql_store_result(cn.setConectar());

            if (resultado) {
                MYSQL_ROW fila;
                if ((fila = mysql_fetch_row(resultado))) {
                    int idVenta = stoi(fila[0]);
                    int noFactura = stoi(fila[1]);
                    string serie = fila[2];
                    string fechaFactura = fila[3];
                    int idCliente = stoi(fila[4]);
                    int idEmpleado = stoi(fila[5]);
                    string fechaIngreso = fila[6];

                    cout << "\nIngrese los nuevos datos de la venta:" << endl;
                    cout << "No. Factura: ";
                    cin >> noFactura;
                    cout << "Serie: ";
                    cin >> serie;
                    cout << "Fecha Factura: ";
                    cin >> fechaFactura;
                    cout << "ID Cliente: ";
                    cin >> idCliente;
                    cout << "ID Empleado: ";
                    cin >> idEmpleado;
                    cout << "Fecha Ingreso: ";
                    cin >> fechaIngreso;

                    string update = "UPDATE ventas SET nofactura = " + to_string(noFactura) + ", serie = '" + serie + "', fechafactura = '" + fechaFactura + "', idcliente = " + to_string(idCliente) + ", idempleado = " + to_string(idEmpleado) + ", fechaingreso = '" + fechaIngreso + "' WHERE idVenta = " + to_string(idVenta);
                    const char* u = update.c_str();
                    int q_estado = mysql_query(cn.setConectar(), u);

                    if (!q_estado) {
                        cout << "\nActualización exitosa en la tabla 'ventas'." << endl;
                        actualizarDetalles(idVenta);
                    }
                    else {
                        cout << "Error al actualizar la información en la tabla 'ventas': " << mysql_error(cn.setConectar()) << endl;
                    }
                }
                else {
                    cout << "No se encontró una venta con el ID proporcionado." << endl;
                }
            }
            else {
                cout << "Error al consultar la tabla 'ventas': " << mysql_error(cn.setConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexión ---" << endl;
        }
        cn.cerrar_conexion();
    }

    void actualizarDetalles(int idVenta) {
        int id_producto, cantidad, precio;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.setConectar()) {
            string consulta = "SELECT * FROM ventas_detalle WHERE idVenta = " + to_string(idVenta);
            const char* c = consulta.c_str();
            mysql_query(cn.setConectar(), c);
            MYSQL_RES* resultado = mysql_store_result(cn.setConectar());

            if (resultado) {
                MYSQL_ROW fila;
                int id_ventas_detalle;
                cout << "ingrese el ID venta detalles que quiera actualizar" << endl;
                cin >> id_ventas_detalle;
                while ((fila = mysql_fetch_row(resultado))) {
                    // Solicitar nuevos datos para actualizar
                    cout << "\nIngrese los nuevos datos del detalle:" << endl;
                    cout << "ID Producto: ";
                    cin >> id_producto;
                    cout << "Cantidad: ";
                    cin >> cantidad;
                    cout << "Precio Unitario: ";
                    cin >> precio;

                    string updateDetalle = "UPDATE ventas_detalle SET idProducto = " + to_string(id_producto) + ", cantidad = " + to_string(cantidad) + ", precio_unitario = " + to_string(precio) + " WHERE idventa_detalle = " + to_string(id_ventas_detalle);
                    const char* u = updateDetalle.c_str();
                    int q_estado = mysql_query(cn.setConectar(), u);

                    if (q_estado) {
                        cout << "Error al actualizar la información en la tabla 'ventas_detalle': " << mysql_error(cn.setConectar()) << endl;
                        return;
                    }
                }
                cout << "\nActualización exitosa en la tabla 'ventas_detalle'." << endl;
            }
            else {
                cout << "Error al consultar la tabla 'ventas_detalle': " << mysql_error(cn.setConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexión ---" << endl;
        }
        cn.cerrar_conexion();
    }

    void eliminar() {
        int idVenta;
        cout << "Ingrese el ID de la venta que desea eliminar: ";
        cin >> idVenta;

        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.setConectar()) {
            string consulta = "SELECT * FROM ventas WHERE idVenta = " + to_string(idVenta);
            const char* c = consulta.c_str();
            mysql_query(cn.setConectar(), c);
            MYSQL_RES* resultado = mysql_store_result(cn.setConectar());

            if (resultado) {
                int numFilas = mysql_num_rows(resultado);
                if (numFilas > 0) {
                    // Eliminar registro de la tabla ventas
                    string deleteVenta = "DELETE FROM ventas WHERE idVenta = " + to_string(idVenta);
                    const char* d = deleteVenta.c_str();
                    int q_estado = mysql_query(cn.setConectar(), d);

                    if (q_estado == 0) {
                        cout << "Eliminación exitosa en la tabla 'ventas'." << endl;
                        eliminarDetalles(idVenta);
                    }
                    else {
                        cout << "Error al eliminar la información en la tabla 'ventas': " << mysql_error(cn.setConectar()) << endl;
                    }
                }
                else {
                    cout << "No se encontró una venta con el ID proporcionado." << endl;
                }
            }
            else {
                cout << "Error al consultar la tabla 'ventas': " << mysql_error(cn.setConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexión ---" << endl;
        }
        cn.cerrar_conexion();
    }

    void eliminarDetalles(int idVenta) {
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.setConectar()) {
            string deleteDetalles = "DELETE FROM ventas_detalle WHERE idVenta = " + to_string(idVenta);
            const char* d = deleteDetalles.c_str();
            int q_estado = mysql_query(cn.setConectar(), d);

            if (q_estado == 0) {
                cout << "Eliminación exitosa en la tabla 'ventas_detalle'." << endl;
            }
            else {
                cout << "Error al eliminar la información en la tabla 'ventas_detalle': " << mysql_error(cn.setConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexión ---" << endl;
        }
        cn.cerrar_conexion();
    }
};