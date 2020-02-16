cmake_minimum_required (VERSION 2.8)
project (Projet_RDV_Salhi_Abdelaziz)

set(CMAKE_C_STANDARD 11)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB SOURCES
        "${SRC_DIR}/*.h"
        "${SRC_DIR}/*.cpp"
        )

add_executable(Projet_RDV_Salhi_Abdelaziz
        src/main.cpp)