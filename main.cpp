// Compilar con: g++ -std=c++17 main.cpp tinyxml2.cpp nodes.cpp tree.cpp -o test

#include <iostream>
#include "tinyxml2.h"
#include "nodes.h"
#include "tree.h"

int main(int argc, char** argv) {
    // Se crea el árbol a partir de la carpeta que contiene los archivos XML de los libros
    Tree tree("./books_xml");

    // Se listan los libros, se muestran los precursores y se borran los libros con rating menor o igual a 4.5 y se vuelve a listar para mostrar el resultado final
    tree.listar();
    tree.precursores();
    tree.borrar_ratings(4.5);
    tree.listar();
    
    return 0;
}
