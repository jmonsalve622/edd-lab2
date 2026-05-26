#include "tree.h"

Tree::Tree() {
    // Implementar el constructor para inicializar el árbol
}

void Tree::addBook(const BookNode& book) {
    root.getBooks().push_back(book);
}

void Tree::listar() {
    for (const auto& book : root.getBooks()) {
        std::cout << "ID: " << book.getId().getInfo() << "\n";
    }
}

void Tree::borrar_ratings(double r) {
    for (auto it = root.getBooks().begin(); it != root.getBooks().end(); ) {
        if (it->getAvgRating().getInfo() <= r) {
            it = root.getBooks().erase(it);
        } 
        else {
            ++it;
        }
    }
}

void Tree::precursores(int id) {
    // Implementar la función para listar los precursores de un libro dado su id
}