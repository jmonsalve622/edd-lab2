// Compilar con: g++ -std=c++17 main.cpp tinyxml2.cpp nodes.cpp tree.cpp -o test

#include <iostream>
#include <filesystem>
#include "tinyxml2.h"
#include "nodes.h"
#include "tree.h"

BookNode xmlToBookNode(const tinyxml2::XMLDocument* doc) {

    //valores por defecto en caso de que un libro tenga algun valor null
    int id = 0;
    std::string title = "";
    int isbn = 0;
    int year = 0;
    std::string language = "";
    std::string description = "";
    double avg_rating = 0.0;
    int num_pages = 0;

    const tinyxml2::XMLElement* rootElement = doc->FirstChildElement("GoodreadsResponse");
    const tinyxml2::XMLElement* bookElement = nullptr;
    
    if (rootElement) {
        bookElement = rootElement->FirstChildElement("book");
    }

    //extraemos los datos reales del libro, en caso de que un libro no tenga algun valor, quedara con el valor predeterminado
    if (bookElement) {
        const tinyxml2::XMLElement* elem;

        elem = bookElement->FirstChildElement("id");
        if (elem) elem->QueryIntText(&id);
        elem = bookElement->FirstChildElement("isbn");
        if (elem) elem->QueryIntText(&isbn);
        elem = bookElement->FirstChildElement("publication_year");
        if (elem) elem->QueryIntText(&year);
        elem = bookElement->FirstChildElement("average_rating");
        if (elem) elem->QueryDoubleText(&avg_rating);
        elem = bookElement->FirstChildElement("num_pages");
        if (elem) elem->QueryIntText(&num_pages);
        
        elem = bookElement->FirstChildElement("title");
        if (elem && elem->GetText()) title = elem->GetText();
        elem = bookElement->FirstChildElement("language_code");
        if (elem && elem->GetText()) language = elem->GetText();
        elem = bookElement->FirstChildElement("description");
        if (elem && elem->GetText()) description = elem->GetText();
    }

    BookNode bookNode(id, title, isbn, year, language, description, avg_rating, num_pages);

    // Falta agregar los libros similares al bookNode

    return bookNode;
}

int main() {
    Tree tree;
    std::filesystem::path folder = "./books_xml";

    for (const auto& input : std::filesystem::directory_iterator(folder)) {
        std::cout << "=== " << input.path().filename() << " ===\n";
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLError resultado = doc.LoadFile(input.path().c_str());
        if (resultado != tinyxml2::XML_SUCCESS) {
            std::cerr << "Error al cargar el XML: " << doc.ErrorStr() << "\n";
        return 1;
        }
        std::cout << "Archivo cargado correctamente\n";
        BookNode bookNode = xmlToBookNode(&doc);
        bookNode.print();
        tree.addBook(bookNode);
    }

    //imprime la cantidad de libros leidos
    std::cout << "Total de libros leidos: " << tree.contarLibros() << "\n";

    return 0;
}
