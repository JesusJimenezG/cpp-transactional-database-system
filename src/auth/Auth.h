#pragma once
#include <string>

class Auth
{
private:
    bool IsAuthenticated;
    std::string Username;
    std::string Password;
    const char *ADMIN_USER = (char *)"ADMIN";
    const char *ALMACEN_USER = (char *)"ALMACEN";
    const char *VENDEDOR_USER = (char *)"VENDEDOR";

public:
    Auth() { IsAuthenticated = false; };
    void Login(std::string username, std::string password)
    {
        IsAuthenticated = true;
        Username = username;
        Password = password;
    };
    void Logout()
    {
        IsAuthenticated = false;
        Username = "";
        Password = "";
    };
    std::string username() { return Username; }
    bool isAuthenticated() { return IsAuthenticated; }
    const char *Admin() { return ADMIN_USER; }
    const char *Almacen() { return ALMACEN_USER; }
    const char *Vendedor() { return VENDEDOR_USER; }

    // Mala practica de encapsulacion
    enum credentials
    {
        ADMIN = 23646,
        ALMACEN = 25622,
        VENDEDOR = 83637
    };
};
