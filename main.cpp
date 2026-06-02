// Compilar con: g++ -std=c++17 main.cpp tinyxml2.cpp nodes.cpp tree.cpp -o test

#include <iostream>
#include <filesystem>
#include "tinyxml2.h"
#include "nodes.h"
#include "tree.h"

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

int main(int argc, char** argv) {
    // Se recorre la carpeta con los archivos XML, se parsean y se agregan al árbol
    Tree tree;
    std::filesystem::path folder = "./books_xml";

    for (const auto& input : std::filesystem::directory_iterator(folder)) {
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLError resultado = doc.LoadFile(input.path().c_str());
        if (resultado != tinyxml2::XML_SUCCESS) {
            std::cerr << "Error al cargar el XML: " << doc.ErrorStr() << "\n";
            return 1;
        }
        BookNode bookNode = xmlToBookNode(&doc);
        tree.addBook(bookNode);
    }

    // Se listan los libros, se muestran los precursores y se borran los libros con rating menor o igual a 4.5 y se vuelve a listar para mostrar el resultado final
    tree.listar();
    tree.precursores();
    tree.borrar_ratings(4.5);
    tree.listar();
    
    return 0;
}
