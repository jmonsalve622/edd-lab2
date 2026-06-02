#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <filesystem>
#include "nodes.h"
#include "tinyxml2.h"

// Función para convertir un XMLDocument a un BookNode
BookNode xmlToBookNode(const tinyxml2::XMLDocument* doc);

class Tree {
    private:
        // El nodo raíz del árbol, que contiene la lista de libros
        RootNode root;
    public:
        // Constructor que recibe la ruta de la carpeta donde se encuentran los archivos XML
        Tree(std::string folderPath);   

        // Método para listar los libros en el árbol
        void listar();

        // Método para eliminar los libros con rating menor o igual a r
        void borrar_ratings(double r);

        // Método para mostrar los libros precursores
        void precursores();

        // Método para contar la cantidad de libros en el árbol
        int contarLibros();
};

#endif