#pragma once
#include "Product.h"
#include <string>
#include <ostream>

class CatalogItem {
private:
    Product product;
    int pret;
    std::string culoare;
public:
    explicit CatalogItem(const Product& product, int pret, const std::string& culoare);
    CatalogItem(const CatalogItem& other) = default;
    CatalogItem& operator=(const CatalogItem& other) = default;
    ~CatalogItem() = default;

    [[nodiscard]] const Product& getProduct() const;
    [[nodiscard]] int getPret() const;
    [[nodiscard]] const std::string& getCuloare() const;

    friend std::ostream& operator<<(std::ostream& os, const CatalogItem& c);
};

