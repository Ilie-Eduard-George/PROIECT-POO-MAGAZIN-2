#pragma once
#include "Product.h"

class Phone : public Product {
private:
    bool has5G_{false};
    int cameraMP_{0};

public:
    Phone(std::string name, int storageGB, int ramGB, std::string color,
          double purchasePrice, int stock, std::string sku,
          bool has5G, int cameraMP);

    Phone(const Phone& other);
    Phone& operator=(const Phone& other);
    ~Phone() override = default;

    bool has5G() const { return has5G_; }
    int cameraMP() const { return cameraMP_; }

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

};
