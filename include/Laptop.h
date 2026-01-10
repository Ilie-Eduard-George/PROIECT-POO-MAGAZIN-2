#pragma once
#include "Product.h"

class Laptop : public Product {
private:
    bool dedicatedGPU_{false};
    int refreshHz_{0};

public:
    Laptop(std::string name, int storageGB, int ramGB, std::string color,
           double purchasePrice, int stock, std::string sku,
           bool dedicatedGPU, int refreshHz);

    Laptop(const Laptop& other);
    Laptop& operator=(const Laptop& other);
    ~Laptop() override = default;

    bool dedicatedGPU() const { return dedicatedGPU_; }
    int refreshHz() const { return refreshHz_; }

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

};
