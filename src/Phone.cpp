#include "Phone.h"
#include <sstream>

Phone::Phone(std::string name, int storageGB, int ramGB, std::string color,
             double purchasePrice, int stock, std::string sku,
             bool has5G, int cameraMP)
    : Product(ProductCategory::Phone, std::move(name), storageGB, ramGB, std::move(color),
              purchasePrice, stock, std::move(sku)),
      has5G_(has5G),
      cameraMP_(cameraMP) {}

Phone::Phone(const Phone& other) : Product(other), has5G_(other.has5G_), cameraMP_(other.cameraMP_) {}

Phone& Phone::operator=(const Phone& other) {
    if (this == &other) return *this;
    Product::operator=(other);
    has5G_ = other.has5G_;
    cameraMP_ = other.cameraMP_;
    return *this;
}

void Phone::print(std::ostream& os) const {
    os << basicLine() << " | (5G: " << (has5G_ ? "da" : "nu") << ", Camera: " << cameraMP_ << "MP)";
}

void Phone::read(std::istream& is) {
    Product::read(is);
    is >> has5G_ >> cameraMP_;
}

