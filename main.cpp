#include <iostream>
#include"conexionDB.h"
#include"clientes.h"
#include"marcas.h"
#include"producto.h"
#include"puestos.h"
#include"empleados.h"
#include"proveedores.h"
#include"VentasMaestro_Detalle.h"
#include"ComprasMaestro_Detalle.h"
#include"arduino.h"
using namespace std;

void mainclientes();
void mainmarcas();
void mainPuestos();
void mainProducto();
void mainEmpleado();
void mainProveedores();
void mainventas();
void mainCompras();
void mainArduino();
int main()
{
    int respuesta;
    do {
        cout << "1 = clientes" << endl;
        cout << "2 = marcas" << endl;
        cout << "3 = puestos" << endl;
        cout << "4 = producto" << endl;
        cout << "5 = empleados" << endl;
        cout << "6 = proveedores" << endl;
        cout << "7 = compras" << endl;
        cout << "8 = ventas" << endl;
        cout << "9 = arduino" << endl;
        cout << "10 = salir" << endl;
        cin >> respuesta;
        switch (respuesta) {
        case 1:
            mainclientes();
        break;
        case 2:
            mainmarcas();
        break;
        case 3:
            mainPuestos();
        break;
        case 4:
            mainProducto();
        break;
        case 5:
            mainEmpleado();
        break;
        case 6:
            mainProveedores();
        break;
        case 7:
            mainCompras();
        break;
        case 8:
            mainventas();
        break;
        case 9:
            mainArduino();
        break;
        case 10:
            cout << "saliendo del programa" << endl;
            return 0;
        break;
        default:
            cout << "ingrese una opcion valida" << endl;
        break;
        }
    } while (respuesta != 10);
}
void mainclientes() {
    int opcion;
    Cliente cliente;

    do {
        cout << "---- CRUD de Clientes ----" << endl;
        cout << "1. Crear cliente" << endl;
        cout << "2. Leer clientes" << endl;
        cout << "3. Actualizar cliente" << endl;
        cout << "4. Eliminar cliente" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;
        string nit, nombre, apellido, direccion, fecha_ingreso, CorreoE;
        int telefono = 0;
        bool genero;

        switch (opcion) {
        case 1:
            //datos de ingreso nuevo
            cin.ignore();
            cout << "ingrese nombres:" << endl;
            getline(cin, nombre);
            cout << "ingrese apellidos:" << endl;
            getline(cin, apellido);
            cout << "ingrese NIT:" << endl;
            getline(cin, nit);
            cout << "ingrese Genero:" << endl;
            cout << "0 masculino, 1 Femenino:" << endl;
            cin >> genero;
            cout << "ingrese telefono:" << endl;
            cin >> telefono;
            cin.ignore();
            cout << "ingrese fecha de correo electronico:" << endl;
            getline(cin, CorreoE);
            cliente.setNombres(nombre);
            cliente.setApellidos(apellido);
            cliente.setNit(nit);
            cliente.setGenero(genero);
            cliente.setTelefono(telefono);

            cliente.crear();
            break;
        case 2:
            cliente.leer();
            break;
        case 3:
            int id;
            cout << "Ingrese el ID del cliente a actualizar: ";
            cin >> id;
            cliente.actualizar(id);
            break;
        case 4:
            int idEliminar;
            cout << "Ingrese el ID del cliente a eliminar: ";
            cin >> idEliminar;
            cliente.eliminar(idEliminar);
            break;
        case 5:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opción inválida. Intente nuevamente." << endl;
            break;
        }

        cout << endl;
    } while (opcion != 5);
}

void mainmarcas() {
    int opcion;
    int id;
    string nombreMarca;
    Marca marca;

    do {
        cout << "---- CRUD de Marcas ----" << endl;
        cout << "1. Crear marca" << endl;
        cout << "2. Leer marcas" << endl;
        cout << "3. Actualizar marca" << endl;
        cout << "4. Eliminar marca" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Ingrese el ID de la marca: ";
            cin >> id;
            marca.setIdMarca(id);
            cout << "Ingrese el nombre de la marca: ";
            cin.ignore();
            getline(cin, nombreMarca);
            marca.setMarca(nombreMarca);
            marca.crear();
            break;
        case 2:
            marca.leer();
            break;
        case 3:
            int idActualizar;
            cout << "Ingrese el ID de la marca a actualizar: ";
            cin >> idActualizar;
            cout << "Ingrese el nuevo nombre de la marca: ";
            cin.ignore(); 
            getline(cin, nombreMarca);
            marca.actualizar(idActualizar);
            break;
        case 4:
            int idEliminar;
            cout << "Ingrese el ID de la marca a eliminar: ";
            cin >> idEliminar;
            marca.eliminar(idEliminar);
            break;
        case 5:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opción inválida. Intente nuevamente." << endl;
            break;
        }

        cout << endl;
    } while (opcion != 5);
}

void mainProducto() {
    Producto producto;
    int opcion = 0;

    while (opcion != 5) {
        cout << "----- MENU -----" << endl;
        cout << "1. Crear producto" << endl;
        cout << "2. Leer productos" << endl;
        cout << "3. Actualizar producto" << endl;
        cout << "4. Eliminar producto" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: {
            int id;
            string nombre, descripcion, imagen;
            int idMarca, existencia;
            double precioCosto, precioVenta;

            cout << "Ingrese los datos del producto:" << endl;
            cout << "ID: ";
            cin >> id;
            cin.ignore();
            cout << "Nombre: ";
            getline(cin, nombre);
            cout << "ID de Marca: ";
            cin >> idMarca;
            cin.ignore();
            cout << "Descripción: ";
            getline(cin, descripcion);
            cout << "Imagen: ";
            getline(cin, imagen);
            cout << "Precio de Costo: ";
            cin >> precioCosto;
            cout << "Precio de Venta: ";
            cin >> precioVenta;
            cout << "Existencia: ";
            cin >> existencia;
            cin.ignore();

            producto.setIdProducto(id);
            producto.setProducto(nombre);
            producto.setIdMarca(idMarca);
            producto.setDescripcion(descripcion);
            producto.setImagen(imagen);
            producto.setPrecioCosto(precioCosto);
            producto.setPrecioVenta(precioVenta);
            producto.setExistencia(existencia);

            producto.crear();
            break;
        }

        case 2:
            producto.leer();
            break;

        case 3: {
            int idActualizar;
            cout << "Ingrese el ID del producto a actualizar: ";
            cin >> idActualizar;
            cin.ignore();
            int id;
            string nombre, descripcion, imagen;
            int idMarca, existencia;
            double precioCosto, precioVenta;

            cout << "Ingrese los datos del producto:" << endl;
            cout << "ID: ";
            cin >> id;
            cin.ignore();
            cout << "Nombre: ";
            getline(cin, nombre);
            cout << "ID de Marca: ";
            cin >> idMarca;
            cin.ignore();
            cout << "Descripción: ";
            getline(cin, descripcion);
            cout << "Imagen: ";
            getline(cin, imagen);
            cout << "Precio de Costo: ";
            cin >> precioCosto;
            cout << "Precio de Venta: ";
            cin >> precioVenta;
            cout << "Existencia: ";
            cin >> existencia;
            cin.ignore();

            producto.setIdProducto(id);
            producto.setProducto(nombre);
            producto.setIdMarca(idMarca);
            producto.setDescripcion(descripcion);
            producto.setImagen(imagen);
            producto.setPrecioCosto(precioCosto);
            producto.setPrecioVenta(precioVenta);
            producto.setExistencia(existencia);

            producto.actualizar(idActualizar);
            break;
        }

        case 4: {
            int idEliminar;
            cout << "Ingrese el ID del producto a eliminar: ";
            cin >> idEliminar;
            cin.ignore();
            producto.eliminar(idEliminar);
            break;
        }

        case 5:
            cout << "Saliendo del programa..." << endl;
            break;

        default:
            cout << "Opción inválida. Intente nuevamente." << endl;
            break;
        }

        cout << endl;
    }
}

void mainPuestos() {
    int opcion;
    int id;

    do {
        cout << "----- Menu -----" << endl;
        cout << "1. Crear puesto" << endl;
        cout << "2. Leer puestos" << endl;
        cout << "3. Actualizar puesto" << endl;
        cout << "4. Eliminar puesto" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string puesto;

            cout << "Ingrese el nombre del puesto: ";
            cin.ignore();
            getline(cin, puesto);

            Puesto nuevoPuesto;
            nuevoPuesto.setPuesto(puesto);
            nuevoPuesto.crear();
            break;
        }
        case 2: {
            Puesto puesto;
            puesto.leer();
            break;
        }
        case 3: {
            cout << "Ingrese el ID del puesto a actualizar: ";
            cin >> id;

            string puesto;

            cout << "Ingrese el nuevo nombre del puesto: ";
            cin.ignore();
            getline(cin, puesto);

            Puesto puestoActualizar;
            puestoActualizar.setPuesto(puesto);
            puestoActualizar.actualizar(id);
            break;
        }
        case 4: {
            cout << "Ingrese el ID del puesto a eliminar: ";
            cin >> id;

            Puesto puestoEliminar;
            puestoEliminar.eliminar(id);
            break;
        }
        case 0: {
            cout << "Saliendo del programa..." << endl;
            break;
        }
        default: {
            cout << "Opcion no valida. Intente nuevamente." << endl;
            break;
        }
        }
    } while (opcion != 0);
}


void mainEmpleado() {
    int opcion;
    empleados empleado;

    do {
        cout << "---- CRUD de Empleados ----" << endl;
        cout << "1. Crear empleado" << endl;
        cout << "2. Leer empleados" << endl;
        cout << "3. Actualizar empleado" << endl;
        cout << "4. Eliminar empleado" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
        {
            string nombre, apellido, direccion, telefono, DPI, fecha_nacimiento, fecha_inicio_labores, fecha_ingreso;
            bool genero;
            int id_puesto;
            cin.ignore();
            cout << "Ingrese nombres: " << endl;
            getline(cin, nombre);
            cout << "Ingrese apellidos: " << endl;
            getline(cin, apellido);
            cout << "Ingrese dirección: " << endl;
            getline(cin, direccion);
            cout << "Ingrese teléfono: " << endl;
            getline(cin, telefono);
            cout << "Ingrese DPI: " << endl;
            getline(cin, DPI);
            cout << "Ingrese género (0 masculino, 1 femenino): " << endl;
            cin >> genero;
            cin.ignore();
            cout << "Ingrese fecha de nacimiento: " << endl;
            getline(cin, fecha_nacimiento);
            cout << "Ingrese ID de puesto: " << endl;
            cin >> id_puesto;
            cin.ignore();
            cout << "Ingrese fecha de inicio de labores: " << endl;
            getline(cin, fecha_inicio_labores);
            cout << "Ingrese fecha de ingreso: " << endl;
            getline(cin, fecha_ingreso);

            empleado.setNombres(nombre);
            empleado.setApellido(apellido);
            empleado.setDireccion(direccion);
            empleado.setTelefono(telefono);
            empleado.setDPI(DPI);
            empleado.setGenero(genero);
            empleado.setFecha_nacimiento(fecha_nacimiento);
            empleado.setIdPuesto(id_puesto);
            empleado.setFecha_inicio_labores(fecha_inicio_labores);
            empleado.setFecha_ingreso(fecha_ingreso);

            empleado.crear();
            break;
        }

        case 2:
            empleado.leer();
            break;

        case 3:
        {
            int id;
            cout << "Ingrese el ID del empleado a actualizar: ";
            cin >> id;
            string nombre, apellido, direccion, telefono, DPI, fecha_nacimiento, fecha_inicio_labores, fecha_ingreso;
            bool genero;
            int id_puesto;
            cin.ignore();
            cout << "Ingrese nombres: " << endl;
            getline(cin, nombre);
            cout << "Ingrese apellidos: " << endl;
            getline(cin, apellido);
            cout << "Ingrese dirección: " << endl;
            getline(cin, direccion);
            cout << "Ingrese teléfono: " << endl;
            getline(cin, telefono);
            cout << "Ingrese DPI: " << endl;
            getline(cin, DPI);
            cout << "Ingrese género (0 masculino, 1 femenino): " << endl;
            cin >> genero;
            cin.ignore();
            cout << "Ingrese fecha de nacimiento: " << endl;
            getline(cin, fecha_nacimiento);
            cout << "Ingrese ID de puesto: " << endl;
            cin >> id_puesto;
            cin.ignore();
            cout << "Ingrese fecha de inicio de labores: " << endl;
            getline(cin, fecha_inicio_labores);

            empleado.setNombres(nombre);
            empleado.setApellido(apellido);
            empleado.setDireccion(direccion);
            empleado.setTelefono(telefono);
            empleado.setDPI(DPI);
            empleado.setGenero(genero);
            empleado.setFecha_nacimiento(fecha_nacimiento);
            empleado.setIdPuesto(id_puesto);
            empleado.setFecha_inicio_labores(fecha_inicio_labores);
            empleado.setFecha_ingreso(fecha_ingreso);

            empleado.actualizar(id);
            break;
        }

        case 4:
        {
            int idEliminar;
            cout << "Ingrese el ID del empleado a eliminar: ";
            cin >> idEliminar;
            empleado.eliminar(idEliminar);
            break;
        }

        case 5:
            cout << "Saliendo del programa..." << endl;
            break;

        default:
            cout << "Opción inválida. Intente nuevamente." << endl;
            break;
        }

    } while (opcion != 5);
}

void mainProveedores() {
    int opcion;
    Proveedor proveedor;

    do {
        // Mostrar el menú de opciones
        cout << "----- MENU -----" << endl;
        cout << "1. Crear proveedor" << endl;
        cout << "2. Leer proveedores" << endl;
        cout << "3. Actualizar proveedor" << endl;
        cout << "4. Eliminar proveedor" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string prov, n, dir, tel;

            // Obtener los datos del proveedor
            cout << "Ingrese el nombre del proveedor: ";
            getline(cin, prov);
            cout << "Ingrese el NIT: ";
            getline(cin, n);
            cout << "Ingrese la direccion: ";
            getline(cin, dir);
            cout << "Ingrese el telefono: ";
            getline(cin, tel);

            // Establecer los datos del proveedor
            proveedor.setProveedor(prov);
            proveedor.setNit(n);
            proveedor.setDireccion(dir);
            proveedor.setTelefono(tel);

            // Crear el proveedor
            proveedor.crear();
            break;
        }
        case 2:
            // Leer proveedores
            proveedor.leer();
            break;
        case 3: {
            int id;
            string prov, n, dir, tel;

            // Obtener el ID del proveedor a actualizar
            cout << "Ingrese el ID del proveedor a actualizar: ";
            cin >> id;

            // Obtener los nuevos datos del proveedor
            cout << "Ingrese el nuevo nombre del proveedor: ";
            getline(cin, prov);
            cout << "Ingrese el nuevo NIT: ";
            getline(cin, n);
            cout << "Ingrese la nueva direccion: ";
            getline(cin, dir);
            cout << "Ingrese el nuevo telefono: ";
            getline(cin, tel);

            // Establecer los nuevos datos del proveedor
            proveedor.setProveedor(prov);
            proveedor.setNit(n);
            proveedor.setDireccion(dir);
            proveedor.setTelefono(tel);

            // Actualizar el proveedor
            proveedor.actualizar(id);
            break;
        }
        case 4: {
            int id;

            // Obtener el ID del proveedor a eliminar
            cout << "Ingrese el ID del proveedor a eliminar: ";
            cin >> id;

            // Eliminar el proveedor
            proveedor.eliminar(id);
            break;
        }
        case 5:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
        }

        cout << endl;

    } while (opcion != 5);
}

void mainventas() {
    int opcion;
    Ventas ventas;
    int noFactura, idCliente, idEmpleado;
    string serie, fechaFactura, fechaIngreso;

    do {
        cout << "------------------- Menú -------------------" << endl;
        cout << "1. Crear una venta" << endl;
        cout << "2. Leer ventas" << endl;
        cout << "3. Actualizar una venta" << endl;
        cout << "4. Eliminar una venta" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1: 
            cout << "\nIngrese los datos de la venta:" << endl;
            cout << "Serie: ";
            cin >> serie;
            cout << "NIt del Cliente: ";
            cin >> idCliente;
            cout << "ID Empleado: ";
            cin >> idEmpleado;

            ventas.setSerie(serie);
            ventas.setIdCliente(idCliente);
            ventas.setIdEmpleado(idEmpleado);

            ventas.crear();
            break;
        case 2:
            ventas.leer();
            break;
        case 3:
            int idVentas;
            cout << "Ingrese el ID de la venta a actualizar: ";
            cin >> idVentas;

            ventas.setIdVenta(idVentas);

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

            ventas.setNoFactura(noFactura);
            ventas.setSerie(serie);
            ventas.setFechaFactura(fechaFactura);
            ventas.setIdCliente(idCliente);
            ventas.setIdEmpleado(idEmpleado);
            ventas.setFechaIngreso(fechaIngreso);

            ventas.actualizar();
            break;
        case 4:
            int id;

            // Obtener el ID del proveedor a eliminar
            cout << "Ingrese el ID la venta a eliminar: ";
            cin >> id;
            ventas.eliminar();
            break;
        case 5:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opción inválida. Intente nuevamente." << endl;
            break;
            }
        } while (opcion != 5);
    }
void mainCompras() {
    int opcion;
    Compras compras;
    int idCompra, noOrdenCompra, idProveedor;
    string fechaOrden, fechaIngreso;

    do {
        cout << "------------------- Menú -------------------" << endl;
        cout << "1. Crear una compra" << endl;
        cout << "2. Leer compras" << endl;
        cout << "3. Actualizar una compra" << endl;
        cout << "4. Eliminar una compra" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "\nIngrese los datos de la compra:" << endl;
            cout << "ID Compra: ";
            cin >> idCompra;
            cout << "No. Orden de Compra: ";
            cin >> noOrdenCompra;
            cout << "ID Proveedor: ";
            cin >> idProveedor;
            cout << "Fecha de Orden: ";
            cin >> fechaOrden;
            cout << "Fecha de Ingreso: ";
            cin >> fechaIngreso;

            compras.setIdCompra(idCompra);
            compras.setNoOrdenCompra(noOrdenCompra);
            compras.setIdProveedor(idProveedor);
            compras.setFechaOrden(fechaOrden);
            compras.setFechaIngreso(fechaIngreso);

            compras.crear();
            break;
        case 2:
            compras.leer();
            break;
        case 3:
            int idCompraActualizar;
            cout << "Ingrese el ID de la compra a actualizar: ";
            cin >> idCompraActualizar;

            compras.setIdCompra(idCompraActualizar);

            cout << "\nIngrese los nuevos datos de la compra:" << endl;
            cout << "No. Orden de Compra: ";
            cin >> noOrdenCompra;
            cout << "ID Proveedor: ";
            cin >> idProveedor;
            cout << "Fecha de Orden: ";
            cin >> fechaOrden;
            cout << "Fecha de Ingreso: ";
            cin >> fechaIngreso;

            compras.setNoOrdenCompra(noOrdenCompra);
            compras.setIdProveedor(idProveedor);
            compras.setFechaOrden(fechaOrden);
            compras.setFechaIngreso(fechaIngreso);

            compras.actualizar();
            break;
        case 4:
            int idCompraEliminar;

            // Obtener el ID de la compra a eliminar
            cout << "Ingrese el ID de la compra a eliminar: ";
            cin >> idCompraEliminar;
            compras.setIdCompra(idCompraEliminar);
            compras.eliminar();
            break;
        case 5:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opción inválida. Intente nuevamente." << endl;
            break;
        }
    } while (opcion != 5);
}

void mainArduino() {
    int res = 0;
    cout << "1 = encender" << endl;
    cout << "2 = salir" << endl;
    cout << "elija una opcion" << endl;
    cin >> res;
    arduino Arduino;
    do {
        switch (res) {
        case 1:
            Arduino.setup();
            Arduino.loop();
        break;
        default:
            cout << "ingrese una opcion valida" << endl;
        break;
        }
    } while (res != 2);
}
