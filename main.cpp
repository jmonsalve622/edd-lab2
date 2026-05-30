// Compilar con: g++ -std=c++17 main.cpp tinyxml2.cpp nodes.cpp tree.cpp -o test 

#include <iostream>
#include <filesystem>
#include "tinyxml2.h"
#include "nodes.h"
#include "tree.h"

BookNode xmlToBookNode(const tinyxml2::XMLDocument* doc) {
    const tinyxml2::XMLElement* bookElement = doc->FirstChildElement("GoodreadsResponse")->FirstChildElement("book");
    int id = bookElement->FirstChildElement("id")->IntText();
    int isbn = bookElement->FirstChildElement("isbn")->IntText();
    int year = bookElement->FirstChildElement("publication_year")->IntText();
    std::string language = bookElement->FirstChildElement("language_code")->GetText();
    std::string description = bookElement->FirstChildElement("description")->GetText();
    double avg_rating = bookElement->FirstChildElement("average_rating")->DoubleText();
    int num_pages = bookElement->FirstChildElement("num_pages")->IntText();
    
    BookNode bookNode(id, isbn, year, language, description, avg_rating, num_pages);

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
    }
    return 0;
}
