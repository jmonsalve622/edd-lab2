#include <iostream>
#include <filesystem>
#include "tree.h"
#include "tinyxml2.h"
#include "nodes.h"

// Función para convertir un XMLDocument a un BookNode
BookNode xmlToBookNode(const tinyxml2::XMLDocument* doc) {
    // Valores por defecto en caso de que un libro tenga algun valor null
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
    const tinyxml2::XMLElement* similarsElement = nullptr;
    
    if (rootElement) {
        bookElement = rootElement->FirstChildElement("book");
        if (bookElement) {
            similarsElement = bookElement->FirstChildElement("similar_books"); 
        }
    }

    // Extraemos los datos reales del libro, en caso de que un libro no tenga algun valor, quedara con el valor predeterminado
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

    // Se crea el nodo del libro con los datos extraidos del XML, sin incluir los libros similares, que se agregaran posteriormente
    BookNode bookNode(id, title, isbn, year, language, description, avg_rating, num_pages);

    // Se agregan los libros similares al libro principal, en caso de que existan
    if (similarsElement) {
        const tinyxml2::XMLElement* similarBookElement = similarsElement->FirstChildElement("book");
        while (similarBookElement) {
            int similarYear = 0;
            std::string similarTitle = "";
            int similarIsbn = 0;

            const tinyxml2::XMLElement* elem;

            elem = similarBookElement->FirstChildElement("publication_year");
            if (elem) elem->QueryIntText(&similarYear);
            elem = similarBookElement->FirstChildElement("isbn");
            if (elem) elem->QueryIntText(&similarIsbn);
            elem = similarBookElement->FirstChildElement("title");
            if (elem && elem->GetText()) similarTitle = elem->GetText();

            bookNode.getSimilars().addSimilar(SimilarBookNode(similarTitle, similarIsbn, similarYear));

            similarBookElement = similarBookElement->NextSiblingElement("book");
        }
    }
    return bookNode;
}

// Constructor que recibe la ruta de la carpeta donde se encuentran los archivos XML
Tree::Tree(std::string folderPath) {
    std::filesystem::path folder = folderPath;

    for (const auto& input : std::filesystem::directory_iterator(folder)) {
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLError resultado = doc.LoadFile(input.path().c_str());
        if (resultado != tinyxml2::XML_SUCCESS) {
            std::cerr << "Error al cargar el XML: " << doc.ErrorStr() << "\n";
        }
        BookNode bookNode = xmlToBookNode(&doc);
        root.getBooks().push_back(bookNode);
    }
}

// Método para listar los libros en el árbol
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

// Método para eliminar los libros con rating menor o igual a r
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

// Método para mostrar los libros precursores
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

// Método para contar la cantidad de libros en el árbol
int Tree::contarLibros() {
    return root.getBooks().size();
}