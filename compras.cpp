#pragma once
#include <mysql.h>
#include <iostream>
#include <string>
#include "conexionDB.h"

using namespace std;

class Compras {
private:
    int idCompra, noOrdenCompra, idProveedor;
    string fechaOrden, fechaIngreso;

    int id_producto, cantidad, precio;
public:
    Compras() {}

    Compras(int id, int noOrden, int idProv, string fechaOrd, string fechaIng) {
        idCompra = id;
        noOrdenCompra = noOrden;
        idProveedor = idProv;
        fechaOrden = fechaOrd;
        fechaIngreso = fechaIng;
    }

    void setIdCompra(int id) { idCompra = id; }
    void setNoOrdenCompra(int noOrden) { noOrdenCompra = noOrden; }
    void setIdProveedor(int idProv) { idProveedor = idProv; }
    void setFechaOrden(string fechaOrd) { fechaOrden = fechaOrd; }
    void setFechaIngreso(string fechaIng) { fechaIngreso = fechaIng; }

    int getIdCompra() { return idCompra; }
    int getNoOrdenCompra() { return noOrdenCompra; }
    int getIdProveedor() { return idProveedor; }
    string getFechaOrden() { return fechaOrden; }
    string getFechaIngreso() { return fechaIngreso; }

    void crear() {
        int q_estado;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.setConectar()) {
            string insert = "INSERT INTO compras (no_orden_compra, idproveedor, fecha_orden, fechaingreso) VALUES (" + to_string(noOrdenCompra) + ", " + to_string(idProveedor) + ", '" + fechaOrden + "', '" + fechaIngreso + "')";
            const char* i = insert.c_str();
            q_estado = mysql_query(cn.setConectar(), i);
            if (!q_estado) {
                cout << "Ingreso exitoso en la tabla 'compras'..." << endl;
                int idCompraInsertada = mysql_insert_id(cn.setConectar());
                ingresarDetalle(idCompraInsertada);
            }
            else {
                cout << "Error al ingresar la información en la tabla 'compras': " << mysql_error(cn.setConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexión ---" << endl;
        }
        cn.cerrar_conexion();
    }

    void ingresarDetalle(int idCompra) {
        int idProducto, cantidad;
        double precioCostoUnitario;
        int q_estado;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        char res;
        if (cn.setConectar()) {
            string insert = "INSERT INTO ventas_detalle (idcompra, idproducto, cantidad, precio_costo_unitario) VALUES ";
            do {
                insert += "(" + to_string(idCompra) + ", " + to_string(idProducto) + ", " + to_string(cantidad) + ", " + to_string(precioCostoUnitario) + "), ";
                cout << "¿Aún hay más detalles? (s/n): ";
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
            string consulta = "SELECT * FROM compras";
            const char* c = consulta.c_str();
            mysql_query(cn.setConectar(), c);
            MYSQL_RES* resultado = mysql_store_result(cn.setConectar());

            if (resultado) {
                MYSQL_ROW fila;
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << "------------------- Compras -------------------" << endl;
                    cout << "idCompra: " << fila[0] << ", no_orden_compra: " << fila[1] << ", idproveedor: " << fila[2] << ", fecha_orden: " << fila[3] << ", fechaingreso: " << fila[4] << endl;

                    mostrarDetalles(atoi(fila[0]));
                    cout << "-----------------------" << endl;
                }
            }
            else {
                cout << "Error al consultar la tabla 'compras': " << mysql_error(cn.setConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexión ---" << endl;
        }
        cn.cerrar_conexion();
    }

    void mostrarDetalles(int idCompra) {
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.setConectar()) {
            string consulta = "SELECT * FROM ventas_detalle WHERE idcompra = " + to_string(idCompra);
            const char* c = consulta.c_str();
            mysql_query(cn.setConectar(), c);
            MYSQL_RES* resultado = mysql_store_result(cn.setConectar());

            if (resultado) {
                MYSQL_ROW fila;
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << "idcompra_detalle: " << fila[0] << ", idcompra: " << fila[1] << ", idproducto:" << fila[2] << ", cantidad: " << fila[3] << ", precio_costo_unitario: " << fila[4] << endl;
                }
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

    void actualizar() {
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.setConectar()) {
            int idVentaActualizacion;
            cout << "Ingrese el ID de la venta a actualizar: ";
            cin >> idVentaActualizacion;

            string consulta = "SELECT * FROM compras WHERE idCompra = " + to_string(idVentaActualizacion);
            const char* c = consulta.c_str();
            mysql_query(cn.setConectar(), c);
            MYSQL_RES* resultado = mysql_store_result(cn.setConectar());

            if (resultado) {
                MYSQL_ROW fila;
                if ((fila = mysql_fetch_row(resultado))) {
                    int idCompra = stoi(fila[0]);
                    int no_orden_compra = stoi(fila[1]);
                    int idproveedor = stoi(fila[2]);
                    string fecha_orden = fila[3];
                    string fechaingreso = fila[4];

                    cout << "\nIngrese los nuevos datos de la compra:" << endl;
                    cout << "No. Orden Compra: ";
                    cin >> no_orden_compra;
                    cout << "ID Proveedor: ";
                    cin >> idproveedor;
                    cout << "Fecha Orden: ";
                    cin >> fecha_orden;
                    cout << "Fecha Ingreso: ";
                    cin >> fechaingreso;

                    string update = "UPDATE compras SET no_orden_compra = " + to_string(no_orden_compra) + ", idproveedor = " + to_string(idproveedor) + ", fecha_orden = '" + fecha_orden + "', fechaingreso = '" + fechaingreso + "' WHERE idCompra = " + to_string(idCompra);
                    const char* u = update.c_str();
                    int q_estado = mysql_query(cn.setConectar(), u);

                    if (!q_estado) {
                        cout << "\nActualización exitosa en la tabla 'compras'." << endl;
                        actualizarDetalles(idCompra);
                    }
                    else {
                        cout << "Error al actualizar la información en la tabla 'compras': " << mysql_error(cn.setConectar()) << endl;
                    }
                }
                else {
                    cout << "No se encontró una compra con el ID proporcionado." << endl;
                }
            }
            else {
                cout << "Error al consultar la tabla 'compras': " << mysql_error(cn.setConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexión ---" << endl;
        }
        cn.cerrar_conexion();
    }

    void actualizarDetalles(int idCompra) {
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.setConectar()) {
            string consulta = "SELECT * FROM ventas_detalle WHERE idcompra = " + to_string(idCompra);
            const char* c = consulta.c_str();
            mysql_query(cn.setConectar(), c);
            MYSQL_RES* resultado = mysql_store_result(cn.setConectar());

            if (resultado) {
                MYSQL_ROW fila;
                int idVentaDetalle;
                cout << "Ingrese el ID del detalle de compra que desea actualizar: ";
                cin >> idVentaDetalle;
                while ((fila = mysql_fetch_row(resultado))) {
                    // Solicitar nuevos datos para actualizar
                    int idcompra_detalle = stoi(fila[0]);
                    int idproducto = stoi(fila[2]);
                    int cantidad = stoi(fila[3]);
                    double precio_costo_unitario = stod(fila[4]);

                    cout << "\nIngrese los nuevos datos del detalle:" << endl;
                    cout << "ID Producto: ";
                    cin >> idproducto;
                    cout << "Cantidad: ";
                    cin >> cantidad;
                    cout << "Precio Costo Unitario: ";
                    cin >> precio_costo_unitario;

                    string updateDetalle = "UPDATE ventas_detalle SET idproducto = " + to_string(idproducto) + ", cantidad = " + to_string(cantidad) + ", precio_costo_unitario = " + to_string(precio_costo_unitario) + " WHERE idcompra_detalle = " + to_string(idVentaDetalle);
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
        int idCompra;
        cout << "Ingrese el ID de la compra que desea eliminar: ";
        cin >> idCompra;

        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.setConectar()) {
            string consulta = "SELECT * FROM compras WHERE idCompra = " + to_string(idCompra);
            const char* c = consulta.c_str();
            mysql_query(cn.setConectar(), c);
            MYSQL_RES* resultado = mysql_store_result(cn.setConectar());

            if (resultado) {
                int numFilas = mysql_num_rows(resultado);
                if (numFilas > 0) {
                    // Eliminar registro de la tabla compras
                    string deleteCompra = "DELETE FROM compras WHERE idCompra = " + to_string(idCompra);
                    const char* d = deleteCompra.c_str();
                    int q_estado = mysql_query(cn.setConectar(), d);

                    if (q_estado == 0) {
                        cout << "Eliminación exitosa en la tabla 'compras'." << endl;
                        eliminarDetalles(idCompra);
                    }
                    else {
                        cout << "Error al eliminar la información en la tabla 'compras': " << mysql_error(cn.setConectar()) << endl;
                    }
                }
                else {
                    cout << "No se encontró una compra con el ID proporcionado." << endl;
                }
            }
            else {
                cout << "Error al consultar la tabla 'compras': " << mysql_error(cn.setConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexión ---" << endl;
        }
        cn.cerrar_conexion();
    }

    void eliminarDetalles(int idCompra) {
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.setConectar()) {
            string deleteDetalles = "DELETE FROM compras_detalle WHERE idCompra = " + to_string(idCompra);
            const char* d = deleteDetalles.c_str();
            int q_estado = mysql_query(cn.setConectar(), d);

            if (q_estado == 0) {
                cout << "Eliminación exitosa en la tabla 'compras_detalle'." << endl;
            }
            else {
                cout << "Error al eliminar la información en la tabla 'compras_detalle': " << mysql_error(cn.setConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexión ---" << endl;
        }
        cn.cerrar_conexion();
    }
};