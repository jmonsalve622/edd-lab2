#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "nodes.h"

class Tree {
    private:
        // El nodo raíz del árbol, que contiene la lista de libros
        RootNode root;
    public:
        // Constructor por defecto
        Tree();

        // Método para agregar un libro al árbol
        void addBook(const BookNode& book);

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