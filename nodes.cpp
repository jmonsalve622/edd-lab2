#include <iostream>
#include "nodes.h"

// Implementación de InfoNode

template <typename T>
InfoNode<T>::InfoNode(const T& i) : info(i) {}

template <typename T>
const T& InfoNode<T>::getInfo() const {
    return info;
}

template class InfoNode<std::string>;
template class InfoNode<int>;
template class InfoNode<double>;

// Implementación de SimilarBookNode

SimilarBookNode::SimilarBookNode(const std::string& t, int i, int y) : title(t), isbn(i), year(y) {}

const InfoNode<std::string>& SimilarBookNode::getTitle() const {
    return title;
}

const InfoNode<int>& SimilarBookNode::getIsbn() const {
    return isbn;
}

const InfoNode<int>& SimilarBookNode::getYear() const {
    return year;
}

// Implementación de SimilarsBooksNode

SimilarsBooksNode::SimilarsBooksNode() {}

void SimilarsBooksNode::addSimilar(const SimilarBookNode& similar) {
    similars.push_back(similar);
}

const std::vector<SimilarBookNode>& SimilarsBooksNode::getSimilars() const {
    return similars;
}

std::vector<SimilarBookNode>& SimilarsBooksNode::getSimilars() {
    return similars;
}

// Implementación de BookNode

BookNode::BookNode(int id, const std::string& title, int isbn, int year,
                   const std::string& languange, const std::string& description,
                   double avg_rating, int num_pages)
    : id(id), title(title), isbn(isbn), year(year), languange(languange), description(description),
      avg_rating(avg_rating), num_pages(num_pages) {}

const InfoNode<int>& BookNode::getId() const {
    return id;
}

const InfoNode<std::string>& BookNode::getTitle() const {
    return title;
}

const InfoNode<int>& BookNode::getIsbn() const {
    return isbn;
}

const InfoNode<int>& BookNode::getYear() const {
    return year;
}

const InfoNode<std::string>& BookNode::getLanguange() const {
    return languange;
}

const InfoNode<std::string>& BookNode::getDescription() const {
    return description;
}

const InfoNode<double>& BookNode::getAvgRating() const {
    return avg_rating;
}

const InfoNode<int>& BookNode::getNumPages() const {
    return num_pages;
}

const SimilarsBooksNode& BookNode::getSimilars() const {
    return similars;
}

SimilarsBooksNode& BookNode::getSimilars() {
    return similars;
}

const std::vector<BookNode>& RootNode::getBooks() const {
    return books;
}

// Implementación de RootNode

RootNode::RootNode() {}

std::vector<BookNode>& RootNode::getBooks() {
    return books;
}
