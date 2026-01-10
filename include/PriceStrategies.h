#pragma once
#include "IPriceStrategy.h"

class Markup15Strategy final : public IPriceStrategy {
public:
    double computeSalePrice(const Product& p) const override {
        return p.purchasePrice() * 1.2;
    }
};

class Discount80Strategy final : public IPriceStrategy {
public:
    double computeSalePrice(const Product& p) const override {
        return p.purchasePrice() * 0.80;
    }
};
