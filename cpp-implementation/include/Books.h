#ifndef BOOKS_H
#define BOOKS_H

#include "Product.h"
#include <string>

using namespace std;

// The abstract class for books
class Books : public Product {
protected:
    string author;
    string publisher;

public:
    Books(int id, string name, double price, int volume, string author, string publisher, string supplier)
        : Product(id, name, price, volume, supplier), author(author), publisher(publisher) {}

};

// Concrete subclass for fiction books
class Fiction : public Books {
public:
    Fiction(int id, string name, double price, int volume, string author, string publisher, string genre, string supplier);

    double calculateDiscount(int volume, int month) const override;
    string displayProductInfo() const override;

private:
    string genre;
};

// Concrete subclass for non-fiction books
class NonFiction : public Books {
public:
    NonFiction(int id, string name, double price, int volume, string author, string publisher, string field, string supplier);

    double calculateDiscount(int volume, int month) const override;
    string displayProductInfo() const override;

private:
    string field;
};

#endif
