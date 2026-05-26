#include <iostream>
#include <filesystem>
//#include "tinyxml2.h"
//#include "nodes.h"
//#include "tree.h"



int main() {
    std::filesystem::path folder = "./books_xml";

    for (const auto& input : std::filesystem::directory_iterator(folder)) {
        std::cout << "=== " << input.path().filename() << " ===\n";
    }

    return 0;
}
