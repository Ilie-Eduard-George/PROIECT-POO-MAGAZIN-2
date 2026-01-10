#include "PricingEngine.h"

PricingEngine::PricingEngine(std::shared_ptr<IPriceStrategy> normal,
                             std::shared_ptr<IPriceStrategy> discounted)
    : normal_(std::move(normal)), discounted_(std::move(discounted)) {}

double PricingEngine::salePriceFor(const Product& p) const {
    const bool isDiscounted = (p.category() == discountedCategory_);
    return isDiscounted ? discounted_->computeSalePrice(p)
                        : normal_->computeSalePrice(p);
}
