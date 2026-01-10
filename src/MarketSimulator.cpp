#include "MarketSimulator.h"

MarketSimulator::MarketSimulator(std::size_t triggerEvery)
    : triggerEvery_(triggerEvery) {}

static ProductCategory nextCategory(ProductCategory c) {
    if (c == ProductCategory::Phone) return ProductCategory::Laptop;
    if (c == ProductCategory::Laptop) return ProductCategory::Tablet;
    return ProductCategory::Phone;
}

std::string MarketSimulator::tick() {
    ++step_;
    if (triggerEvery_ == 0) return "";

    if (step_ % triggerEvery_ == 0) {
        currentDiscount_ = nextCategory(currentDiscount_);
        return "EVENIMENT";
    }
    return "";
}
