cmake_minimum_required(VERSION 3.22.1)

project(TransactionalSystemDatabase
        VERSION 0.0.1
        DESCRIPTION "Sistema transaccional y de control de ventas"
        LANGUAGES CXX)

add_executable(TransactionalSystemDatabase main.cpp)
target_compile_features(TransactionalSystemDatabase PRIVATE cxx_std_20)