#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include "ProductCategory.h"
#include "Exceptions.h"
class Product {
private:
    int id_{0};
    std::string name_;
    int storageGB_{0};
    int ramGB_{0};
    std::string color_;
    double purchasePrice_{0.0};
    int stock_{0};
    std::unique_ptr<char[]> sku_;
    std::size_t skuLen_{0};
    static std::unordered_map<ProductCategory, std::string> categoryNames_;

protected:
    Product(ProductCategory category,
            std::string name,
            int storageGB,
            int ramGB,
            std::string color,
            double purchasePrice,
            int stock,
            const std::string& sku);

    ProductCategory category_{ProductCategory::Phone};

public:
    Product(const Product& other);
    Product& operator=(const Product& other);
    virtual ~Product();

    Product(Product&&) noexcept = default;
    Product& operator=(Product&&) noexcept = default;

    int id() const { return id_; }
    ProductCategory category() const { return category_; }
    const std::string& name() const { return name_; }
    int storageGB() const { return storageGB_; }
    int ramGB() const { return ramGB_; }
    const std::string& color() const { return color_; }
    double purchasePrice() const { return purchasePrice_; }
    int stock() const { return stock_; }
    std::string sku() const;

    void setId(int id) { id_ = id; }

    Product& operator+=(int qty);
    Product& operator-=(int qty);

    virtual void print(std::ostream& os) const;
    virtual void read(std::istream& is);

    static std::string categoryToString(ProductCategory c);

    std::string basicLine() const;

    std::string lineWithPrice(double salePrice) const;
};

std::ostream& operator<<(std::ostream& os, const Product& p);
std::istream& operator>>(std::istream& is, Product& p);

bool operator<(const Product& a, const Product& b);
