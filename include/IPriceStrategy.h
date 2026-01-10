#pragma once
#include "Product.h"

class IPriceStrategy {
public:
    virtual ~IPriceStrategy() = default;
    virtual double computeSalePrice(const Product& p) const = 0;
};
