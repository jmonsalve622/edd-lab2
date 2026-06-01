#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "nodes.h"

class Tree {
    private:
        RootNode root;
    public:
        Tree();

        void addBook(const BookNode& book);
        void listar();
        void borrar_ratings(double r);
        void precursores();
        int contarLibros(); 
};


#endif