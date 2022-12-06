#include <iostream>
#include <cstring>
#include <limits>
#include <vector>
#include "../model/Entities.h"
#include "../controller/Controller.h"
using namespace std;

// void IngresarRegistro();
// void ModificarRegistro();
// void EliminarRegistro();

void IngresarProducto(Producto producto);
void IngresarProveedor(Proveedor proveedor);
void IngresarCompra(Compra compra);
void IngresarFactura(Factura factura);
void IngresarCliente(Cliente cliente);
void ModificarProducto(int id);
void ModificarProveedor(int id);
void ModificarCompra(int id);
void ModificarFactura(int id);
void ModificarCliente(int id);
void Listar(int item);
FilePaths paths;

Controller<Producto> productoController = *new Controller<Producto>(paths.db_productos);
Controller<Proveedor> proveedorController = *new Controller<Proveedor>(paths.db_proveedores);
Controller<Compra> compraController = *new Controller<Compra>(paths.db_compras);
Controller<Factura> facturaController = *new Controller<Factura>(paths.db_facturas);
Controller<Cliente> clienteController = *new Controller<Cliente>(paths.db_clientes);

void IngresarRegistro()
{
    system("cls");
    cout << "1. Ingresar Producto." << endl;
    cout << "2. Ingresar Proveedor." << endl;
    cout << "3. Ingresar Compra." << endl;
    cout << "4. Ingresar Factura." << endl;
    cout << "5. Ingresar Cliente." << endl;

    Producto producto;
    Proveedor proveedor;
    Compra compra;
    Factura factura;
    Cliente cliente;

    int opt;
    cin >> opt;

    switch (opt)
    {
    case 1:
    {
        IngresarProducto(producto);
        break;
    }
    case 2:
    {
        IngresarProveedor(proveedor);
        break;
    }
    case 3:
    {
        IngresarCompra(compra);
        break;
    }
    case 4:
    {
        IngresarFactura(factura);
        break;
    }
    case 5:
    {
        IngresarCliente(cliente);
        break;
    }
    default:
    {
        system("cls");
        cout << "Intente de nuevo." << endl;
        system("pause");
        system("cls");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }
    }
}

// template <typename T, typename C>
void IngresarProducto(Producto producto)
{
    cout << "1. Ingresa id del producto: ";
    cin >> producto.id;
    cin.ignore();

    int id = producto.id;
    bool exists = productoController.Search(producto);
    while (exists)
    {
        cout << "El id: " << id << " ya existe." << endl;
        cout << "Ingresa otro id por favor: ";
        cin >> producto.id;
        cin.ignore();
        id = producto.id;
        exists = productoController.Search(producto);
    }

    cout << "Ingresar id del Proveedor: ";
    cin >> producto.id_proveedor;
    cin.ignore();

    // Verificar que el producto existe.
    // int aux = producto.id_proveedor;
    int aux = producto.id_proveedor;
    Proveedor proveedor;
    proveedor.id = aux;
    exists = proveedorController.Search(proveedor);
    while (!exists)
    {
        cout << "El id: " << aux << " del proveedor no existe." << endl;
        cout << "Desea ingresar el proveedor? (S/n)";
        char decision[1];
        cin >> decision;
        if (tolower(decision[0]) == 115 /* 's' */)
        {
            // @TODO Por alguna razon se pierde el scope
            proveedor.id = aux;
            IngresarProveedor(proveedor);
        }
        else
        {
            cout << "Verifique el id e ingrese nuevamente por favor: ";
            cin >> producto.id_proveedor;
            proveedor.id = producto.id_proveedor;
            cin.ignore();
        }
        exists = proveedorController.Search(proveedor);
    }

    cout << "Ingresar stock minimo: ";
    cin >> producto.stock_min;
    cout << "Ingresar stock: ";
    cin >> producto.stock;
    cin.ignore();

    while (producto.stock_min < producto.stock)
    {
        cout << "El stock actual no puede ser menor que el stock minimo." << endl;
        cout << "Ingresa otra cantidad de stock por favor: ";
        cin >> producto.stock;
        cin.ignore();
    }
    cout << "Ingresa precio: ";
    cin >> producto.precio;
    cin.ignore();

    cout << "Ingresa descripcion: ";
    cin.getline(producto.descripcion, sizeof(producto.descripcion));

    if (productoController.Write(producto))
    {
        cout << "Producto creado correctamente." << endl;
        system("pause");
    }
}

// template <typename T>
void IngresarProveedor(Proveedor proveedor)
{
    cout << "1. Ingrese id del proveedor: ";
    cin >> proveedor.id;
    cin.ignore();

    bool exists = proveedorController.Search(proveedor);
    while (exists)
    {
        cout << "El id: " << proveedor.id << " ya existe." << endl;
        cout << "Ingrese otro id por favor: ";
        cin >> proveedor.id;
        cin.ignore();
        exists = proveedorController.Search(proveedor);
    }

    cout << "Ingrese nombre del Proveedor: ";
    cin.getline(proveedor.nombre, sizeof(proveedor.nombre));

    cout << "Ingrese telefono del proveedor: ";
    cin.getline(proveedor.telefono, sizeof(proveedor.telefono));

    if (proveedorController.Write(proveedor))
    {
        cout << "Proveedor creado correctamente." << endl;
        system("pause");
    }
}

// template <typename T, typename C>
void IngresarCompra(Compra compra)
{
    cout << "1. Ingrese id de la compra: ";
    cin >> compra.id;
    cin.ignore();

    bool exists = compraController.Search(compra);
    while (exists)
    {
        cout << "El id: " << compra.id << " ya existe." << endl;
        cout << "Ingrese otro id por favor: ";
        cin >> compra.id;
        cin.ignore();
        exists = compraController.Search(compra);
    }

    cout << "Ingrese id del Producto de la compra: ";
    cin >> compra.id_producto;
    cin.ignore();

    // Verificar que el producto existe.
    int aux = compra.id_producto;
    Producto producto;
    producto.id = aux;

    exists = productoController.Search(producto);
    while (!exists)
    {
        cout << "El id: " << aux << " del producto no existe." << endl;
        cout << "Desea ingresar el producto? (S/n)";
        char decision[1];
        cin >> decision;
        if (tolower(decision[0]) == 115 /* 's' */)
        {
            // @TODO Por alguna razon se pierde el scope
            producto.id = aux;
            IngresarProducto(producto);
        }
        else
        {
            cout << "Verifique el id e ingrese nuevamente por favor: ";
            cin >> compra.id_producto;
            cin.ignore();

            producto.id = compra.id_producto;
        }
        exists = productoController.Search(producto);
    }

    cout << "Ingrese id de la factura: ";
    cin >> compra.id_factura;
    cin.ignore();

    // Verificar que la factura existe.
    aux = compra.id_factura;
    Factura factura;
    factura.id = aux;

    exists = facturaController.Search(factura);
    while (!exists)
    {
        cout << "El id: " << aux << " de la factura no existe." << endl;
        cout << "Desea ingresar la factura? (S/n)";
        char decision[1];
        cin >> decision;
        if (tolower(decision[0]) == 115 /* 's' */)
        {
            // @TODO Por alguna razon se pierde el scope
            factura.id = aux;
            IngresarFactura(factura);
        }
        else
        {
            cout << "Verifique el id e ingrese nuevamente por favor: ";
            cin >> compra.id_factura;
            cin.ignore();

            factura.id = compra.id_producto;
        }
        exists = facturaController.Search(factura);
    }

    productoController.Read(producto);
    cout << "Recuerde no ingresa una cantidad de compra mayor al stock actual: " << producto.stock << endl;
    cout << "Ingrese cantidad de la compra: ";
    cin >> compra.cantidad;
    cin.ignore();

    while (compra.cantidad > producto.stock)
    {
        cout << "La cantidad de compra no puede ser mayor que la cantidad en stock." << endl;
        cout << "Ingresa otra cantidad por favor: ";
        cin >> compra.cantidad;
        cin.ignore();
    }
    // Restar del stock de productos
    producto.stock -= compra.cantidad;
    productoController.Modify(producto);

    if (compraController.Write(compra))
    {
        cout << "Compra creada correctamente." << endl;
        system("pause");
    }
}

// template <typename T, typename C>
void IngresarFactura(Factura factura)
{
    cout << "1. Ingrese id de la factura: ";
    cin >> factura.id;
    cin.ignore();

    bool exists = facturaController.Search(factura);
    while (exists)
    {
        cout << "El id: " << factura.id << " ya existe." << endl;
        cout << "Ingrese otro id por favor: ";
        cin >> factura.id;
        cin.ignore();
        exists = facturaController.Search(factura);
    }

    cout << "Ingrese id del cliente: ";
    cin >> factura.id_cliente;
    cin.ignore();

    // Verificar que el cliente existe.
    int aux = factura.id_cliente;
    Cliente cliente;
    cliente.id = aux;

    exists = clienteController.Search(cliente);
    while (!exists)
    {
        cout << "El id: " << aux << " del cliente no existe." << endl;
        cout << "Desea ingresar el cliente? (S/n)";
        char decision[1];
        cin >> decision;
        if (tolower(decision[0]) == 115 /* 's' */)
        {
            // @TODO Por alguna razon se pierde el scope
            cliente.id = aux;
            IngresarCliente(cliente);
        }
        else
        {
            cout << "Verifique el id e ingrese nuevamente por favor: ";
            cin >> factura.id_cliente;
            cin.ignore();

            cliente.id = factura.id_cliente;
        }
        exists = clienteController.Search(cliente);
    }

    cout << "Ingrese la fecha de la factura: ";
    cin.getline(factura.fecha, sizeof(factura.fecha));

    if (facturaController.Write(factura))
    {
        cout << "Factura creada correctamente." << endl;
        system("pause");
    }
}

// template <typename T>
void IngresarCliente(Cliente cliente)
{
    cout << "1. Ingrese id del cliente: ";
    cin >> cliente.id;
    cin.ignore();

    bool exists = clienteController.Search(cliente);
    while (exists)
    {
        cout << "El id: " << cliente.id << " ya existe." << endl;
        cout << "Ingrese otro id por favor: ";
        cin >> cliente.id;
        cin.ignore();
        exists = clienteController.Search(cliente);
    }

    cout << "Ingrese nombre del cliente: ";
    cin.getline(cliente.nombre, sizeof(cliente.nombre));

    cout << "Ingrese direccion del cliente: ";
    cin.getline(cliente.direccion, sizeof(cliente.direccion));

    cout << "Ingrese telefono del cliente: ";
    cin.getline(cliente.telefono, sizeof(cliente.telefono));

    if (clienteController.Write(cliente))
    {
        cout << "Cliente creado correctamente." << endl;
        system("pause");
    }
}

void ModificarRegistro()
{
    system("cls");
    cout << "1. Modificar Producto." << endl;
    cout << "2. Modificar Proveedor." << endl;
    cout << "3. Modificar Compra." << endl;
    cout << "4. Modificar Factura." << endl;
    cout << "5. Modificar Cliente." << endl;

    Producto producto;
    Proveedor proveedor;
    Compra compra;
    Factura factura;
    Cliente cliente;

    int opt;
    cin >> opt;
    cin.ignore();

    Listar(opt);
    int id;
    cout << "Ingresa el id del registro a modificar: " << endl;
    cin >> id;
    cin.ignore();

    switch (opt)
    {
    case 1:
    {
        producto.id = id;
        ModificarProducto(id);
        break;
    }
    case 2:
    {
        proveedor.id = id;
        ModificarProveedor(id);
        break;
    }
    case 3:
    {
        compra.id = id;
        ModificarCompra(id);
        break;
    }
    case 4:
    {
        factura.id = id;
        ModificarFactura(id);
        break;
    }
    case 5:
    {
        cliente.id = id;
        ModificarCliente(id);
        break;
    }
    default:
    {
        system("cls");
        cout << "Intente de nuevo." << endl;
        system("pause");
        system("cls");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }
    }
}

void ModificarProducto(int id)
{
    Producto producto;
    producto.id = id;
    productoController.Read(producto);
    bool modifying = true;
    bool hasModified = false;

    cout << "Ingrese el campo a modificar." << endl;
    cout << "1. Modificar id proveedor: " << producto.id_proveedor << endl;
    cout << "2. Modificar stock: " << producto.stock << endl;
    cout << "3. Modificar precio: " << producto.precio << endl;
    cout << "4. Modificar descripcion: " << producto.descripcion << endl;
    cout << "5. Modificar stock_min: " << producto.stock_min << endl;
    cout << "6. Salir." << producto.stock_min << endl;
    while (modifying)
    {
        int opt;
        cin >> opt;
        cin.ignore();

        switch (opt)
        {
        case 1:
        {
            cout << "Ingrese el nuevo id de proveedor: " << endl;
            cin >> producto.id_proveedor;
            cin.ignore();

            // Verificar que el proveedor existe.
            int aux = producto.id_proveedor;
            Proveedor proveedor;
            proveedor.id = aux;
            bool exists = proveedorController.Search(proveedor);
            while (!exists)
            {
                cout << "El id: " << aux << " del proveedor no existe." << endl;
                cout << "Desea ingresar el proveedor? (S/n)";
                char decision[1];
                cin >> decision;
                if (tolower(decision[0]) == 115 /* 's' */)
                {
                    // @TODO Por alguna razon se pierde el scope
                    proveedor.id = aux;
                    IngresarProveedor(proveedor);
                }
                else
                {
                    cout << "Verifique el id e ingrese nuevamente por favor: ";
                    cin >> producto.id_proveedor;
                    proveedor.id = producto.id_proveedor;
                    cin.ignore();
                }
                exists = proveedorController.Search(proveedor);
            }
            hasModified = true;
            break;
        }
        case 2:
        {
            cout << "Ingrese el nuevo stock: " << endl;
            cin >> producto.stock;
            cin.ignore();
            while (producto.stock > producto.stock_min)
            {
                cout << "El stock actual es mayor que el stock minimo." << endl;
                cout << "Desea aumentar el stock minimo? (S/n)";
                char decision[1];
                cin >> decision;
                if (tolower(decision[0]) == 115 /* 's' */)
                {
                    cout << "Ingrese el nuevo stock minimo: ";
                    cin >> producto.stock_min;
                    hasModified = true;
                }
                else
                {
                    cout << "Verifique el stock e ingrese nuevamente por favor: ";
                    cin >> producto.stock;
                    cin.ignore();
                }
            }
            hasModified = true;
            break;
        }
        case 3:
        {
            cout << "Ingrese el nuevo precio: " << endl;
            cin >> producto.precio;
            cin.ignore();
            hasModified = true;
            break;
        }
        case 4:
        {
            cout << "Ingrese la nueva descripcion: " << endl;
            cin.getline(producto.descripcion, sizeof(producto.descripcion));
            hasModified = true;
            break;
        }
        case 5:
        {
            cout << "Ingrese el nuevo stock_min: " << endl;
            cin >> producto.stock_min;
            cin.ignore();
            while (producto.stock_min < producto.stock)
            {
                cout << "El stock minimo es menor que el stock actual." << endl;
                cout << "Desea aumentar el stock minimo? (S/n)";
                char decision[1];
                cin >> decision;
                if (tolower(decision[0]) == 115 /* 's' */)
                {
                    cout << "Ingrese el nuevo stock minimo: ";
                    cin >> producto.stock_min;
                    hasModified = true;
                }
                else
                {
                    cout << "Verifique el stock minimo e ingrese nuevamente por favor: ";
                    cin >> producto.stock_min;
                    cin.ignore();
                }
            }
            hasModified = true;
            break;
        }
        case 6:
        {
            modifying = false;
            break;
        }
        default:
        {
            system("cls");
            cout << "Intente de nuevo." << endl;
            system("pause");
            system("cls");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        }
    }
    if (hasModified)
        productoController.Modify(producto);
}
void ModificarProveedor(int id)
{
    Proveedor proveedor;
    proveedor.id = id;
    proveedorController.Read(proveedor);
    bool modifying = true;
    bool hasModified = false;

    cout << "Ingrese el campo a modificar." << endl;
    cout << "1. Modificar nombre del proveedor: " << proveedor.nombre << endl;
    cout << "2. Modificar telefono del proveedor: " << proveedor.telefono << endl;
    cout << "3. Salir." << endl;
    while (modifying)
    {
        int opt;
        cin >> opt;
        cin.ignore();

        switch (opt)
        {
        case 1:
        {
            cout << "Ingrese el nuevo nombre del proveedor: " << endl;
            cin.getline(proveedor.nombre, sizeof(proveedor.nombre));
            hasModified = true;
            break;
        }
        case 2:
        {
            cout << "Ingrese el nuevo telefono del proveedor: " << endl;
            cin.getline(proveedor.telefono, sizeof(proveedor.telefono));
            hasModified = true;
            break;
        }
        case 3:
        {
            modifying = false;
            break;
        }
        default:
        {
            system("cls");
            cout << "Intente de nuevo." << endl;
            system("pause");
            system("cls");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        }
    }
    if (hasModified)
        proveedorController.Modify(proveedor);
}
void ModificarCompra(int id)
{
    Compra compra;
    compra.id = id;
    compraController.Read(compra);
    bool modifying = true;
    bool hasModified = false;

    cout << "Ingrese el campo a modificar." << endl;
    cout << "1. Modificar id del producto de la compra: " << compra.id_producto << endl;
    cout << "2. Modificar id de la factura de la compra: " << compra.id_factura << endl;
    cout << "3. Modificar cantidad de compra: " << compra.cantidad << endl;
    cout << "4. Salir." << endl;

    while (modifying)
    {
        int opt;
        cin >> opt;
        cin.ignore();

        switch (opt)
        {
        case 1:
        {
            cout << "Ingrese el nuevo id de producto de la compra: " << endl;
            cin >> compra.id_producto;
            cin.ignore();

            // Verificar que el producto existe.
            int aux = compra.id_producto;
            Producto producto;
            producto.id = aux;

            bool exists = productoController.Search(producto);
            while (!exists)
            {
                cout << "El id: " << aux << " del producto no existe." << endl;
                cout << "Desea ingresar el producto? (S/n)";
                char decision[1];
                cin >> decision;
                if (tolower(decision[0]) == 115 /* 's' */)
                {
                    // @TODO Por alguna razon se pierde el scope
                    producto.id = aux;
                    IngresarProducto(producto);
                }
                else
                {
                    cout << "Verifique el id e ingrese nuevamente por favor: ";
                    cin >> compra.id_producto;
                    cin.ignore();

                    producto.id = compra.id_producto;
                }
                exists = productoController.Search(producto);
            }
            hasModified = true;
            break;
        }
        case 2:
        {
            cout << "Ingrese el nuevo id de la factura de la compra: " << endl;
            cin >> compra.id_factura;
            cin.ignore();
            // Verificar que la factura existe.
            int aux = compra.id_factura;
            Factura factura;
            factura.id = aux;

            bool exists = facturaController.Search(factura);
            while (!exists)
            {
                cout << "El id: " << aux << " de la factura no existe." << endl;
                cout << "Desea ingresar la factura? (S/n)";
                char decision[1];
                cin >> decision;
                if (tolower(decision[0]) == 115 /* 's' */)
                {
                    // @TODO Por alguna razon se pierde el scope
                    factura.id = aux;
                    IngresarFactura(factura);
                }
                else
                {
                    cout << "Verifique el id e ingrese nuevamente por favor: ";
                    cin >> compra.id_factura;
                    cin.ignore();

                    factura.id = compra.id_producto;
                }
                exists = facturaController.Search(factura);
            }
            hasModified = true;
            break;
        }
        case 3:
        {
            Producto producto;
            producto.id = compra.id_producto;
            productoController.Read(producto);
            cout << "Recuerde no ingresa una cantidad de compra mayor al stock actual: " << producto.stock << endl;
            cout << "Ingrese la nueva cantidad de compra: " << endl;
            cin >> compra.cantidad;
            cin.ignore();

            while (compra.cantidad > producto.stock)
            {
                cout << "La cantidad de compra no puede ser mayor a la cantidad en stock." << endl;
                cout << "Ingresa otra cantidad por favor: ";
                cin >> compra.cantidad;
                cin.ignore();
            }
            hasModified = true;
            break;
        }
        case 4:
        {
            modifying = false;
            break;
        }
        default:
        {
            system("cls");
            cout << "Intente de nuevo." << endl;
            system("pause");
            system("cls");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        }
    }
    if (hasModified)
        compraController.Modify(compra);
}
void ModificarFactura(int id)
{
    Factura factura;
    factura.id = id;
    facturaController.Read(factura);
    bool modifying = true;
    bool hasModified = false;

    cout << "Ingrese el campo a modificar." << endl;
    cout << "1. Modificar id del cliente de la factura: " << factura.id_cliente << endl;
    cout << "2. Modificar fecha de la factura: " << factura.fecha << endl;
    cout << "3. Salir." << endl;

    while (modifying)
    {
        int opt;
        cin >> opt;
        cin.ignore();

        switch (opt)
        {
        case 1:
        {
            cout << "Ingrese el nuevo id de cliente de la factura: " << endl;
            cin >> factura.id_cliente;
            cin.ignore();
            // Verificar que el cliente existe.
            int aux = factura.id_cliente;
            Cliente cliente;
            cliente.id = aux;

            bool exists = clienteController.Search(cliente);
            while (!exists)
            {
                cout << "El id: " << aux << " del cliente no existe." << endl;
                cout << "Desea ingresar el cliente? (S/n)";
                char decision[1];
                cin >> decision;
                if (tolower(decision[0]) == 115 /* 's' */)
                {
                    // @TODO Por alguna razon se pierde el scope
                    cliente.id = aux;
                    IngresarCliente(cliente);
                }
                else
                {
                    cout << "Verifique el id e ingrese nuevamente por favor: ";
                    cin >> factura.id_cliente;
                    cin.ignore();

                    cliente.id = factura.id_cliente;
                }
                exists = clienteController.Search(cliente);
            }

            hasModified = true;
            break;
        }
        case 2:
        {
            cout << "Ingrese la nueva fecha de la factura: " << endl;
            cin.getline(factura.fecha, sizeof(factura.fecha));
            hasModified = true;
            break;
        }
        case 3:
        {
            modifying = false;
            break;
        }
        default:
        {
            system("cls");
            cout << "Intente de nuevo." << endl;
            system("pause");
            system("cls");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        }
    }
    if (hasModified)
        facturaController.Modify(factura);
}
void ModificarCliente(int id)
{
    Cliente cliente;
    cliente.id = id;
    clienteController.Read(cliente);
    bool modifying = true;
    bool hasModified = false;

    cout << "Ingrese el campo a modificar." << endl;
    cout << "1. Modificar el nombre del cliente: " << cliente.nombre << endl;
    cout << "2. Modificar la direccion del cliente: " << cliente.direccion << endl;
    cout << "3. Modificar el telefono del cliente: " << cliente.telefono << endl;
    cout << "4. Salir." << endl;

    while (modifying)
    {
        int opt;
        cin >> opt;
        cin.ignore();

        switch (opt)
        {
        case 1:
        {
            cout << "Ingrese el nuevo nombre del cliente: " << endl;
            cin.getline(cliente.nombre, sizeof(cliente.nombre));
            hasModified = true;
            break;
        }
        case 2:
        {
            cout << "Ingrese la nueva direccion del cliente: " << endl;
            cin.getline(cliente.direccion, sizeof(cliente.direccion));
            hasModified = true;
            break;
        }
        case 3:
        {
            cout << "Ingrese el nuevo telefono del cliente: " << endl;
            cin.getline(cliente.telefono, sizeof(cliente.telefono));
            hasModified = true;
            break;
        }
        case 4:
        {
            modifying = false;
            break;
        }
        default:
        {
            system("cls");
            cout << "Intente de nuevo." << endl;
            system("pause");
            system("cls");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        }
    }
    if (hasModified)
        clienteController.Modify(cliente);
}

// template <typename T>
void EliminarRegistro()
{
    system("cls");
    cout << "1. Eliminar Producto." << endl;
    cout << "2. Eliminar Proveedor." << endl;
    cout << "3. Eliminar Compra." << endl;
    cout << "4. Eliminar Factura." << endl;
    cout << "5. Eliminar Cliente." << endl;

    int opt;
    cin >> opt;
    cin.ignore();

    switch (opt)
    {
    case 1:
    {
        // vector<Producto> v_productos = productoController.GetAll();
        // vector<Proveedor> v_proveedores = proveedorController.GetAll();

        // for (int i = 0; i < v_productos.size(); i++)
        // {
        //     // char *prov;
        //     // for (int j = 0; j < v_proveedores.size(); j++)
        //     // {
        //     //     if (v_proveedores[j].id == v_productos[i].id_proveedor)
        //     //     {
        //     //         strcpy(prov, (char *)v_proveedores[j].nombre);
        //     //     }
        //     // }

        //     cout << "Id: " << v_productos[i].id << ". Descripcion: " << v_productos[i].descripcion << ". Stock: " << v_productos[i].stock << ". Stock minimo: " << v_productos[i].stock_min << endl;

        //     // cout << "Id: " << v_productos[i].id << ". Proveedor: " << prov << endl;
        //     // << ". Descripcion: " << v_productos[i].descripcion << ". Stock: " << v_productos[i].stock << ". Stock minimo: " << v_productos[i].stock_min << endl;
        // }
        Listar(opt);
        int id;
        cout << "Selecciona un id: ";
        cin >> id;
        cin.ignore();

        Producto producto;
        producto.id = id;
        productoController.Delete(producto);

        break;
    }
    case 2:
    {
        // vector<Proveedor> v_proveedores = proveedorController.GetAll();

        // for (Proveedor proveedor : v_proveedores)
        // {
        //     cout << "Id: " << proveedor.id << ". Nombre: " << proveedor.nombre << ". Telef: " << proveedor.telefono << endl;
        // }
        Listar(opt);

        int id;
        cout << "Selecciona un id: ";
        cin >> id;
        cin.ignore();

        Proveedor proveedor;
        proveedor.id = id;
        proveedorController.Delete(proveedor);

        break;
    }
    case 3:
    {
        // vector<Compra> v_compra = compraController.GetAll();
        // vector<Producto> v_productos = productoController.GetAll();
        // vector<Factura> v_factura = facturaController.GetAll();
        // vector<Cliente> v_cliente = clienteController.GetAll();

        // for (int i = 0; i < v_compra.size(); i++)
        // {
        //     // char *desc;
        //     // char *client;
        //     // for (int j = 0; j < v_productos.size(); j++)
        //     // {
        //     //     if (v_productos[j].id == v_compra[i].id_producto)
        //     //     {
        //     //         strcpy(desc, v_productos[j].descripcion);
        //     //     }
        //     // }
        //     // for (int k = 0; k < v_factura.size(); k++)
        //     // {
        //     //     for (int l = 0; l < v_cliente.size(); l++)
        //     //     {
        //     //         if (v_cliente[l].id == v_factura[k].id_cliente)
        //     //         {
        //     //             strcpy(client, v_cliente[l].nombre);
        //     //         }
        //     //     }
        //     // }
        //     // cout << "Id: " << v_compra[i].id << ". Producto: " << desc << ". Cliente: " << client << ". Cantidad: " << v_compra[i].cantidad << endl;
        //     cout << "Id: " << v_compra[i].id << ". Cantidad: " << v_compra[i].cantidad << endl;
        // }
        Listar(opt);

        int id;
        cout << "Selecciona un id: ";
        cin >> id;
        cin.ignore();

        Compra compra;
        compra.id = id;
        compraController.Delete(compra);

        break;
    }
    case 4:
    {
        // vector<Factura> v_factura = facturaController.GetAll();
        // vector<Cliente> v_cliente = clienteController.GetAll();

        // for (int i = 0; i < v_factura.size(); i++)
        // {
        //     // char *client;
        //     // for (int j = 0; j < v_cliente.size(); j++)
        //     // {
        //     //     if (v_cliente[j].id == v_factura[i].id_cliente)
        //     //     {
        //     //         strcpy(client, v_cliente[j].nombre);
        //     //     }
        //     // }
        //     // cout << "Id: " << v_factura[i].id << ". Cliente: " << client << ". Fecha: " << v_factura[i].fecha << endl;
        //     cout << "Id: " << v_factura[i].id << ". Fecha: " << v_factura[i].fecha << endl;
        // }
        Listar(opt);

        int id;
        cout << "Selecciona un id: ";
        cin >> id;
        cin.ignore();

        Factura factura;
        factura.id = id;
        facturaController.Delete(factura);

        break;
    }
    case 5:
    {
        // vector<Cliente> v_cliente = clienteController.GetAll();
        // for (Cliente cliente : v_cliente)
        // {
        //     cout << "Id: " << cliente.id << ". Nombre: " << cliente.nombre << ". Direccion: " << cliente.direccion << ". Telef: " << cliente.telefono << endl;
        // }
        Listar(opt);

        int id;
        cout << "Selecciona un id: ";
        cin >> id;
        cin.ignore();

        Cliente cliente;
        cliente.id = id;
        clienteController.Delete(cliente);

        break;
    }
    default:
    {
        system("cls");
        cout << "Intente de nuevo." << endl;
        system("pause");
        system("cls");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }
    }
}

void Listar(int item)
{
    switch (item)
    {
    case 1:
    {
        vector<Producto> v_productos = productoController.GetAll();
        // vector<Proveedor> v_proveedores = proveedorController.GetAll();

        for (int i = 0; i < v_productos.size(); i++)
        {
            // char *prov;
            // for (int j = 0; j < v_proveedores.size(); j++)
            // {
            //     if (v_proveedores[j].id == v_productos[i].id_proveedor)
            //     {
            //         strcpy(prov, (char *)v_proveedores[j].nombre);
            //     }
            // }

            cout << "Id: " << v_productos[i].id << ". Descripcion: " << v_productos[i].descripcion << ". Stock: " << v_productos[i].stock << ". Stock minimo: " << v_productos[i].stock_min << ". Falta para reponer stock minimo: " << (v_productos[i].stock_min - v_productos[i].stock) << endl;

            // cout << "Id: " << v_productos[i].id << ". Proveedor: " << prov << endl;
            // << ". Descripcion: " << v_productos[i].descripcion << ". Stock: " << v_productos[i].stock << ". Stock minimo: " << v_productos[i].stock_min << endl;
        }
        break;
    }
    case 2:
    {
        vector<Proveedor> v_proveedores = proveedorController.GetAll();

        for (Proveedor proveedor : v_proveedores)
        {
            cout << "Id: " << proveedor.id << ". Nombre: " << proveedor.nombre << ". Telef: " << proveedor.telefono << endl;
        }

        break;
    }
    case 3:
    {
        vector<Compra> v_compra = compraController.GetAll();
        // vector<Producto> v_productos = productoController.GetAll();
        // vector<Factura> v_factura = facturaController.GetAll();
        // vector<Cliente> v_cliente = clienteController.GetAll();

        for (int i = 0; i < v_compra.size(); i++)
        {
            // char *desc;
            // char *client;
            // for (int j = 0; j < v_productos.size(); j++)
            // {
            //     if (v_productos[j].id == v_compra[i].id_producto)
            //     {
            //         strcpy(desc, v_productos[j].descripcion);
            //     }
            // }
            // for (int k = 0; k < v_factura.size(); k++)
            // {
            //     for (int l = 0; l < v_cliente.size(); l++)
            //     {
            //         if (v_cliente[l].id == v_factura[k].id_cliente)
            //         {
            //             strcpy(client, v_cliente[l].nombre);
            //         }
            //     }
            // }
            // cout << "Id: " << v_compra[i].id << ". Producto: " << desc << ". Cliente: " << client << ". Cantidad: " << v_compra[i].cantidad << endl;
            cout << "Id: " << v_compra[i].id << ". Cantidad: " << v_compra[i].cantidad << endl;
        }

        break;
    }
    case 4:
    {
        vector<Factura> v_factura = facturaController.GetAll();
        // vector<Cliente> v_cliente = clienteController.GetAll();

        for (int i = 0; i < v_factura.size(); i++)
        {
            // char *client;
            // for (int j = 0; j < v_cliente.size(); j++)
            // {
            //     if (v_cliente[j].id == v_factura[i].id_cliente)
            //     {
            //         strcpy(client, v_cliente[j].nombre);
            //     }
            // }
            // cout << "Id: " << v_factura[i].id << ". Cliente: " << client << ". Fecha: " << v_factura[i].fecha << endl;
            cout << "Id: " << v_factura[i].id << ". Fecha: " << v_factura[i].fecha << endl;
        }

        break;
    }
    case 5:
    {
        vector<Cliente> v_cliente = clienteController.GetAll();
        for (Cliente cliente : v_cliente)
        {
            cout << "Id: " << cliente.id << ". Nombre: " << cliente.nombre << ". Direccion: " << cliente.direccion << ". Telef: " << cliente.telefono << endl;
        }

        break;
    }
    default:
    {
        system("cls");
        cout << "Intente de nuevo." << endl;
        system("pause");
        system("cls");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }
    }
}