#ifndef NODES_H
#define NODES_H

#include <vector>
#include <iostream>
#include <string>

template <typename T>
class InfoNode {
    private:
        T info;
    public:
        InfoNode(const T& i);
        const T& getInfo() const;
};

class SimilarBookNode {
    private:
        InfoNode<std::string> title;
        InfoNode<int> isbn;
        InfoNode<int> year;
    public:
        SimilarBookNode(const std::string& t, int i, int y);
        const InfoNode<std::string>& getTitle() const;
        const InfoNode<int>& getIsbn() const;
        const InfoNode<int>& getYear() const;
};

class SimilarsBooksNode {
    private:
        std::vector<SimilarBookNode> similars;
    public:
        SimilarsBooksNode();
        void addSimilar(const SimilarBookNode& similar);
        const std::vector<SimilarBookNode>& getSimilars() const;
        std::vector<SimilarBookNode>& getSimilars();
};

class BookNode {
    private:
        InfoNode<int> id;
        InfoNode<int> isbn;
        InfoNode<int> year;
        InfoNode<std::string> languange;
        InfoNode<std::string> description;
        InfoNode<double> avg_rating;
        InfoNode<int> num_pages;
        SimilarsBooksNode similars;
    public:
        BookNode(int id, int isbn, int year,
                 const std::string& languange, const std::string& description,
                 double avg_rating, int num_pages);
        const InfoNode<int>& getId() const;
        const InfoNode<int>& getIsbn() const;
        const InfoNode<int>& getYear() const;
        const InfoNode<std::string>& getLanguange() const;
        const InfoNode<std::string>& getDescription() const;
        const InfoNode<double>& getAvgRating() const;
        const InfoNode<int>& getNumPages() const;
        const SimilarsBooksNode& getSimilars() const;
        SimilarsBooksNode& getSimilars();
};

class RootNode {
    private:
        std::vector<BookNode> books;
    public:
        RootNode();
        const std::vector<BookNode>& getBooks() const;
        std::vector<BookNode>& getBooks();
};

#endif