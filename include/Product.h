#pragma once
#include "Spec.h"
#include <string>
#include <ostream>

class Product {
private:
    std::string categorie;
    std::string brand;
    std::string model;
    Spec spec;
public:
    explicit Product(const std::string& categorie = "", const std::string& brand = "",
                     const std::string& model = "", const Spec& spec = Spec());
    Product(const Product& other) = default;
    Product& operator=(const Product& other) = default;
    ~Product() = default;

    [[nodiscard]] const std::string& getCategorie() const;
    [[nodiscard]] const std::string& getBrand() const;
    [[nodiscard]] const std::string& getModel() const;
    [[nodiscard]] const Spec& getSpec() const;

    friend std::ostream& operator<<(std::ostream& os, const Product& p);
};
