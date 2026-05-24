#include <vector>
#include <iostream>
#include "nodes.h"

class Tree {
    private:
        RootNode root;
    public:
        Tree();

        void listar();
        void borrar_ratings(double r);
        void precursores(int id);
};