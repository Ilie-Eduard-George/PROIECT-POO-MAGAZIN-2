#pragma once
#include <string>
#include "ProductCategory.h"

class MarketSimulator {
private:
    std::size_t step_{0};
    std::size_t triggerEvery_{5};
    ProductCategory currentDiscount_{ProductCategory::Phone};

public:
    explicit MarketSimulator(std::size_t triggerEvery = 5);
    std::string tick();

    ProductCategory currentDiscount() const { return currentDiscount_; }
};
