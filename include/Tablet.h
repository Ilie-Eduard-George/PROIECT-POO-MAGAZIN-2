#pragma once
#include "Product.h"

class Tablet : public Product {
private:
    bool hasStylus_{false};
    double screenInches_{0.0};

public:
    Tablet(std::string name, int storageGB, int ramGB, std::string color,
           double purchasePrice, int stock, std::string sku,
           bool hasStylus, double screenInches);

    Tablet(const Tablet& other);
    Tablet& operator=(const Tablet& other);
    ~Tablet() override = default;

    bool hasStylus() const { return hasStylus_; }
    double screenInches() const { return screenInches_; }

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

};
