#ifndef ENTITIES_H_
#define ENTITIES_H_
#include <string.h>

struct Producto
{
    int id;
    int id_proveedor;
    int stock;
    float precio;
    char descripcion[45];
    int stock_min;
};

struct Proveedor
{
    int id;
    char nombre[45];
    char telefono[30];
};

struct Compra
{
    int id;
    int id_producto;
    int id_factura;
    int cantidad;
};

struct Factura
{
    int id;
    int id_cliente;
    char fecha[12];
};

struct Cliente
{
    int id;
    char nombre[45];
    char direccion[70];
    char telefono[18];
};

struct FilePaths
{
    char *db_productos = (char *)"db//productos.dat";
    char *db_proveedores = (char *)"db//proveedores.dat";
    char *db_compras = (char *)"db//compras.dat";
    char *db_facturas = (char *)"db//facturas.dat";
    char *db_clientes = (char *)"db//clientes.dat";
};

#endif
