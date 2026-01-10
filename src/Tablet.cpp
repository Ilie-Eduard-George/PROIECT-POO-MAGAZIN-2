#include "Tablet.h"

Tablet::Tablet(std::string name, int storageGB, int ramGB, std::string color,
               double purchasePrice, int stock, std::string sku,
               bool hasStylus, double screenInches)
    : Product(ProductCategory::Tablet, std::move(name), storageGB, ramGB, std::move(color),
              purchasePrice, stock, std::move(sku)),
      hasStylus_(hasStylus),
      screenInches_(screenInches) {}

Tablet::Tablet(const Tablet& other)
    : Product(other), hasStylus_(other.hasStylus_), screenInches_(other.screenInches_) {}

Tablet& Tablet::operator=(const Tablet& other) {
    if (this == &other) return *this;
    Product::operator=(other);
    hasStylus_ = other.hasStylus_;
    screenInches_ = other.screenInches_;
    return *this;
}

void Tablet::print(std::ostream& os) const {
    os << basicLine()
       << " | (Stylus: " << (hasStylus_ ? "da" : "nu")
       << ", Ecran: " << screenInches_ << "\")";
}

void Tablet::read(std::istream& is) {
    Product::read(is);
    is >> hasStylus_ >> screenInches_;
}
