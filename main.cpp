// Compilar con: g++ -std=c++17 main.cpp tinyxml2.cpp nodes.cpp tree.cpp -o test 

#include <iostream>
#include <filesystem>
#include "tinyxml2.h"
#include "nodes.h"
#include "tree.h"

BookNode xmlToBookNode(const tinyxml2::XMLElement* bookElement) {
    int id = bookElement->IntAttribute("id");
    int isbn = bookElement->IntAttribute("isbn");
    int year = bookElement->IntAttribute("year");
    std::string language = bookElement->Attribute("language");
    std::string description = bookElement->Attribute("description");
    double avg_rating = bookElement->DoubleAttribute("avg_rating");
    int num_pages = bookElement->IntAttribute("num_pages");

    // Falta implementar la lectura de similars, pero por ahora se devuelve un BookNode sin similars

    return BookNode(InfoNode<int>(id), InfoNode<int>(isbn), InfoNode<int>(year),
                    InfoNode<std::string>(language), InfoNode<std::string>(description),
                    InfoNode<double>(avg_rating), InfoNode<int>(num_pages));
}

int main() {
    std::filesystem::path folder = "./books_xml";

    for (const auto& input : std::filesystem::directory_iterator(folder)) {
        std::cout << "=== " << input.path().filename() << " ===\n";
    }
    
    return 0;
}
