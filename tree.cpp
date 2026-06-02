#include "tree.h"

Tree::Tree() {}

void Tree::addBook(const BookNode& book) {
    root.getBooks().push_back(book);
}

void Tree::listar() {
    std::cout << "\n=====================================\n";
    std::cout << "        LISTADO DE LIBROS\n";
    std::cout << "=====================================\n";
    for (const auto& book : root.getBooks()) {
        std::cout << "ID: " << book.getId().getInfo() << "\n";
    }
    std::cout << "-------------------------------------\n";
    std::cout << "Total de libros: " << root.getBooks().size() << "\n";
    std::cout << "=====================================\n\n";
}

void Tree::borrar_ratings(double r) {
    std::cout << "\n=====================================\n";
    std::cout << "      ELIMINAR POR RATING\n";
    std::cout << "=====================================\n";
    for (auto it = root.getBooks().begin(); it != root.getBooks().end(); ) {
        if (it->getAvgRating().getInfo() <= r) {
            it = root.getBooks().erase(it);
        } 
        else {
            ++it;
        }
    }
    std::cout << "-------------------------------------\n";
    std::cout << "Libros con rating mayor a " << r << ": " << root.getBooks().size() << "\n";
    std::cout << "=====================================\n\n";
}

void Tree::precursores() {
    std::cout << "\n=====================================\n";
    std::cout << "     LIBROS PRECURSORES\n";
    std::cout << "=====================================\n";
    bool condition = true;
    int bookYear = 0;
    int count = 0;
    for (const auto& book : root.getBooks()) {
        condition = true;
        bookYear = book.getYear().getInfo();

        if (bookYear == 0 || book.getSimilars().getSimilars().empty()) {
            continue;
        }

        for (const auto& similar : book.getSimilars().getSimilars()) {
            if (similar.getYear().getInfo() <= bookYear) {
                condition = false;
                break;
            }
        }
        if (condition) {
            std::cout << "ID: " << book.getId().getInfo() << "\n";
            count++;
        }
    }
    std::cout << "-------------------------------------\n";
    std::cout << "Total de libros precursores: " << count << "\n";
    std::cout << "=====================================\n\n";
}

int Tree::contarLibros() {
    return root.getBooks().size();
}