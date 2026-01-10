#include "ProductFactory.h"

int ProductFactory::nextId_ = 1;

int ProductFactory::allocateId() {
    return nextId_++;
}

std::shared_ptr<Product> ProductFactory::createPhone(
    const std::string& name, int storageGB, int ramGB, const std::string& color,
    double purchasePrice, int stock, const std::string& sku,
    bool has5G, int cameraMP) {

    auto p = std::make_shared<Phone>(name, storageGB, ramGB, color, purchasePrice, stock, sku, has5G, cameraMP);
    p->setId(allocateId());
    return p;
}

std::shared_ptr<Product> ProductFactory::createTablet(
    const std::string& name, int storageGB, int ramGB, const std::string& color,
    double purchasePrice, int stock, const std::string& sku,
    bool hasStylus, double screenInches) {

    auto p = std::make_shared<Tablet>(name, storageGB, ramGB, color, purchasePrice, stock, sku, hasStylus, screenInches);
    p->setId(allocateId());
    return p;
}

std::shared_ptr<Product> ProductFactory::createLaptop(
    const std::string& name, int storageGB, int ramGB, const std::string& color,
    double purchasePrice, int stock, const std::string& sku,
    bool dedicatedGPU, int refreshHz) {

    auto p = std::make_shared<Laptop>(name, storageGB, ramGB, color, purchasePrice, stock, sku, dedicatedGPU, refreshHz);
    p->setId(allocateId());
    return p;
}
