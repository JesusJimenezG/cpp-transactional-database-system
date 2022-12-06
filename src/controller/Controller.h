#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

using namespace std;

template <typename T>
class Controller
{
private:
    // T &buffer;
    T buffer;
    const char *file_name;

public:
    Controller(const char *file_name) : file_name(this->file_name = file_name){};

    // Controller(T& buffer)
    // Controller(T &buffer)
    //     : buffer(buffer) {}
    bool Write(T model);
    bool Search(T &model);
    bool Read(T &model);
    vector<T> GetAll();
    bool Modify(T mod);
    bool Delete(T modelo);
};

template <typename T>
bool Controller<T>::Write(T model)
{
    fstream file;
    filesystem::path cwd = filesystem::current_path() / file_name;
    file.open(cwd.c_str(), ios::out | ios::binary | ios::app);

    if (file.fail() || file.bad())
    {
        // cerr << "Error: " << strerror(errno) << endl;
        return false;
    }
    file.write((char *)&model, sizeof(model));
    file.close();
    // cout << "Successfully wrote" << endl;
    return true;
}

template <typename T>
bool Controller<T>::Search(T &model)
{
    fstream file;
    filesystem::path cwd = filesystem::current_path() / file_name;
    file.open(cwd.c_str(), ios::in);

    if (file.fail() || file.bad())
    {
        // cerr << "Error: " << strerror(errno) << endl;
        return false;
    }

    bool found = false;
    while (!found)
    {
        // cout << "Before read: model id: " << model.id << " buffer id: " << buffer.id << endl;

        file.read((char *)&buffer, sizeof(buffer));
        if (file.eof())
            return false;

        // cout << "After read: model id: " << model.id << " buffer id: " << buffer.id << endl;
        if (model.id == buffer.id)
            found = true;
    }

    file.close();
    return true;
}

template <typename T>
bool Controller<T>::Read(T &model)
{
    fstream file;
    filesystem::path cwd = filesystem::current_path() / file_name;
    file.open(cwd.c_str(), ios::in);

    if (file.fail() || file.bad())
    {
        // cerr << "Error: " << strerror(errno) << endl;
        return false;
    }

    bool found = false;
    while (!found)
    {
        // cout << "Before read: model id: " << model.id << " buffer id: " << buffer.id << endl;

        file.read((char *)&buffer, sizeof(buffer));
        if (file.eof())
            return false;

        // cout << "After read: model id: " << model.id << " buffer id: " << buffer.id << endl;
        if (model.id == buffer.id)
        {
            model = buffer;
            found = true;
        }
    }

    file.close();
    return true;
}

template <typename T>
vector<T> Controller<T>::GetAll()
{
    vector<T> v_models;
    fstream file;
    filesystem::path cwd = filesystem::current_path() / file_name;
    file.open(cwd.c_str(), ios::in);

    // if (file.fail() || file.bad())
    //     return vector;

    while (true)
    {
        file.read((char *)&buffer, sizeof(buffer));
        v_models.push_back(buffer);

        if (file.eof())
            break;
    }

    file.close();
    return v_models;
}

template <class T>
bool Controller<T>::Modify(T modelo)
{
    filesystem::path cwd = filesystem::current_path() / file_name;
    fstream file;

    T aux = modelo;
    int enc = Read(aux);
    if (enc >= 0)
    {
        file.open(cwd.c_str(), ios::binary | ios::in | ios::out);
        if (file.fail() || file.bad())
            return false;
        file.seekg(enc * sizeof(modelo), ios::beg);
        file.write((char *)&modelo, sizeof(modelo));
        file.close();
    }
    else
        return false;
    return true;
}

template <class T>
bool Controller<T>::Delete(T modelo)
{
    filesystem::path cwd = filesystem::current_path() / file_name;
    filesystem::path cwd_temp = filesystem::current_path() / "db//temp.dat";

    fstream file;
    ofstream fileCopy;
    fileCopy.open(cwd_temp.c_str(), ios::binary);

    file.open(cwd.c_str(), ios::binary | ios::in);
    if (file.fail() || file.bad())
        return false;
    while (true)
    {
        file.read((char *)&buffer, sizeof(buffer));
        if (file.eof())
            break;
        if (buffer.id != modelo.id)
        {
            fileCopy.write((char *)&buffer, sizeof(buffer));
        }
    }
    fileCopy.close();
    file.close();

    remove(cwd);
    rename(cwd_temp, cwd);
    return true;
}