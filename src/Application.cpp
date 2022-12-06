#include <iostream>
#include <cstring>
#include <limits>
#include "auth/Auth.h"
#include "model/Entities.h"
#include "controller/Controller.h"
#include "controller/Admin.cpp"

using namespace std;
void Application();
void Login();
void Logout();
void MenuPrincipal();
void AdminMenu();
void AlmacenMenu();
void VendedorMenu();

Auth auth;

void Application()
{
    system("cls");

    while (!auth.isAuthenticated())
    {
        Login();
        while (auth.isAuthenticated())
        {

            if (auth.username() == auth.Admin())
            {
                AdminMenu();
            }
            if (auth.username() == auth.Almacen())
            {
                AlmacenMenu();
            }
            if (auth.username() == auth.Vendedor())
            {
                VendedorMenu();
            }
        }
        system("cls");
    }
}

void Login()
{
    while (!auth.isAuthenticated())
    {
        cout << "********************************" << endl;
        cout << "*            LOGIN             *" << endl;
        cout << "********************************" << endl;
        cout << "Por favor ingrese su rol: " << endl;
        cout << "1. Admin" << endl;
        cout << "2. Almacen" << endl;
        cout << "3. Vendedor" << endl;
        cout << "4. Salir" << endl;

        cout << "********************************" << endl;
        int opt;
        cin >> opt;
        cin.ignore();

        string username;
        string password;

        switch (opt)
        {
        case 1:
            username = auth.Admin();
            password = to_string(auth.ADMIN);
            opt = -1;

            break;
        case 2:
            username = auth.Almacen();
            password = to_string(auth.ALMACEN);
            opt = -1;

            break;
        case 3:
            username = auth.Vendedor();
            password = to_string(auth.VENDEDOR);
            opt = -1;

            break;
        case 4:
        {
            Logout();
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
        if (opt == -1)
        {
            auth.Login(username, password);
            // break;
        }
    }
}
void Logout()
{
    system("cls");
    cout << "Hasta pronto." << endl;
    exit(0);
}

void MenuPrincipal()
{
    system("cls");

    cout << "********************************" << endl;
    cout << "*             MENU             *" << endl;
    cout << "********************************" << endl;
    cout << "Seleccione una opcion: " << endl;
}
void AdminMenu()
{
    MenuPrincipal();

    cout << "1. Ingresar registro." << endl;
    cout << "2. Modificar registro." << endl;
    cout << "3. Eliminar registro." << endl;
    cout << "4. Salir." << endl;

    int opt;
    cin >> opt;

    switch (opt)
    {
    case 1:
    {
        IngresarRegistro();
        break;
    }
    case 2:
    {
        ModificarRegistro();
        break;
    }
    case 3:
    {
        EliminarRegistro();
        break;
    }
    case 4:
    {
        auth.Logout();
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
void AlmacenMenu()
{
    MenuPrincipal();

    cout << "1. Ingresar Producto." << endl;
    cout << "2. Modificar Producto." << endl;
    cout << "3. Salir." << endl;

    int opt;
    cin >> opt;

    switch (opt)
    {
    case 1:
    {
        Producto producto;
        IngresarProducto(producto);
        break;
    }
    case 2:
    {
        Listar(1);
        int id;
        cin >> id;
        cin.ignore();
        ModificarProducto(id);

        break;
    }
    case 3:
    {
        auth.Logout();
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
void VendedorMenu()
{
    MenuPrincipal();

    cout << "1. Apertura de Caja." << endl;
    cout << "2. Salir." << endl;

    int opt;
    cin >> opt;

    switch (opt)
    {
    case 1:
    {
        bool caja_abierta = true;
        while (caja_abierta)
        {
            system("cls");

            cout << "1. Ingresar compra." << endl;
            cout << "2. Listar factura." << endl;
            cout << "3. Cerrar caja." << endl;

            int caja_opt;
            cin >> caja_opt;
            cin.ignore();

            switch (caja_opt)
            {
            case 1:
            {
                Compra compra;
                IngresarCompra(compra);
                break;
            }
            case 2:
            {
                Listar(4);
                system("pause");
                // int id;
                // cin >> id;
                // cin.ignore();
                // ModificarProducto(id);
                break;
            }
            case 3:
            {
                Listar(1);
                Listar(2);
                system("pause");
                caja_abierta = false;
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
        break;
    }
    case 2:
    {
        auth.Logout();
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
