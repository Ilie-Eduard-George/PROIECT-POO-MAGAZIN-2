#pragma once
#include <memory>
#include "ProductCategory.h"
#include "IPriceStrategy.h"
class PricingEngine {
private:
    std::shared_ptr<IPriceStrategy> normal_;
    std::shared_ptr<IPriceStrategy> discounted_;
    ProductCategory discountedCategory_{ProductCategory::Phone};

public:
    PricingEngine(std::shared_ptr<IPriceStrategy> normal,
                  std::shared_ptr<IPriceStrategy> discounted);

    void setDiscountedCategory(ProductCategory c) { discountedCategory_ = c; }
    ProductCategory discountedCategory() const { return discountedCategory_; }

    double salePriceFor(const Product& p) const;
};
