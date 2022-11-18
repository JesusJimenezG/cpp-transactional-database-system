cmake_minimum_required(VERSION 3.22.1)

project(TransactionalSystemDatabase
        VERSION 0.0.1
        DESCRIPTION "Sistema transaccional y de control de ventas"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)