#pragma once
#include <memory>
#include <string>
#include "Product.h"
#include "Phone.h"
#include "Tablet.h"
#include "Laptop.h"

class ProductFactory {
private:
    static int nextId_;

public:
    static std::shared_ptr<Product> createPhone(
        const std::string& name, int storageGB, int ramGB, const std::string& color,
        double purchasePrice, int stock, const std::string& sku,
        bool has5G, int cameraMP);

    static std::shared_ptr<Product> createTablet(
        const std::string& name, int storageGB, int ramGB, const std::string& color,
        double purchasePrice, int stock, const std::string& sku,
        bool hasStylus, double screenInches);

    static std::shared_ptr<Product> createLaptop(
        const std::string& name, int storageGB, int ramGB, const std::string& color,
        double purchasePrice, int stock, const std::string& sku,
        bool dedicatedGPU, int refreshHz);

    static int allocateId();
};
