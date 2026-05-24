#include "nodes.h"

template <typename T>
InfoNode<T>::InfoNode(const T& i) : info(i) {}

template <typename T>
const T& InfoNode<T>::getInfo() const {
    return info;
}

template class InfoNode<std::string>;
template class InfoNode<int>;
template class InfoNode<double>;

const InfoNode<std::string>& SimilarBookNode::getTitle() const {
    return title;
}

const InfoNode<int>& SimilarBookNode::getIsbn() const {
    return isbn;
}

const InfoNode<int>& SimilarBookNode::getYear() const {
    return year;
}

const std::vector<SimilarBookNode>& SimilarsBooksNode::getSimilars() const {
    return similars;
}

std::vector<SimilarBookNode>& SimilarsBooksNode::getSimilars() {
    return similars;
}

const InfoNode<int>& BookNode::getId() const {
    return id;
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

std::vector<BookNode>& RootNode::getBooks() {
    return books;
}

