#include "tree.h"

Tree::Tree() {}

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

void Tree::precursores() {
    bool condition = true;
    int bookYear = 0;
    int count = 0;
    for (const auto& book : root.getBooks()) {
        condition = true;
        bookYear = book.getYear().getInfo();
        for (const auto& similar : book.getSimilars().getSimilars()) {
            if (similar.getYear().getInfo() < bookYear) {
                condition = false;
                break;
            }
        }
        if (condition) {
            std::cout << "ID: " << book.getId().getInfo() << "\n";
            count++;
        }
    }
    std::cout << "Total de libros precursores: " << count << "\n";
}

int Tree::contarLibros() {
    return root.getBooks().size();
}