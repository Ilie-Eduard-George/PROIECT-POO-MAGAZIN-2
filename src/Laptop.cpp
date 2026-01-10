#include "Laptop.h"

Laptop::Laptop(std::string name, int storageGB, int ramGB, std::string color,
               double purchasePrice, int stock, std::string sku,
               bool dedicatedGPU, int refreshHz)
    : Product(ProductCategory::Laptop, std::move(name), storageGB, ramGB, std::move(color),
              purchasePrice, stock, std::move(sku)),
      dedicatedGPU_(dedicatedGPU),
      refreshHz_(refreshHz) {}

Laptop::Laptop(const Laptop& other)
    : Product(other), dedicatedGPU_(other.dedicatedGPU_), refreshHz_(other.refreshHz_) {}

Laptop& Laptop::operator=(const Laptop& other) {
    if (this == &other) return *this;
    Product::operator=(other);
    dedicatedGPU_ = other.dedicatedGPU_;
    refreshHz_ = other.refreshHz_;
    return *this;
}

void Laptop::print(std::ostream& os) const {
    os << basicLine()
       << " | (GPU dedicat: " << (dedicatedGPU_ ? "da" : "nu")
       << ", Refresh: " << refreshHz_ << "Hz)";
}

void Laptop::read(std::istream& is) {
    Product::read(is);
    is >> dedicatedGPU_ >> refreshHz_;
}