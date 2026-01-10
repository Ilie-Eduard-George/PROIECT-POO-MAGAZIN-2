#include "Store.h"
#include "PriceStrategies.h"
#include "Phone.h"
#include "Tablet.h"
#include "Laptop.h"
#include "ProductFactory.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

std::string SaleTransaction::description() const {
    return "Vanzare produs id=" + std::to_string(productId_) + " x" + std::to_string(qty_);
}

std::string PurchaseTransaction::description() const {
    return "Aprovizionare produs id=" + std::to_string(productId_) + " x" + std::to_string(qty_);
}

Store::Store(PricingEngine pricing, MarketSimulator market)
    : pricing_(std::move(pricing)), market_(std::move(market)) {}

void Store::indexCatalog() {
    byId_.clear();
    for (const auto& p : catalog_) {
        byId_[p->id()] = p;
    }
}

void Store::seedInitialCatalog() {
    catalog_.clear();

    catalog_.push_back(ProductFactory::createPhone("Samsung Galaxy S23", 256, 8, "Negru", 3500, 0, "SKU-PH-001", true, 50));
    catalog_.push_back(ProductFactory::createPhone("iPhone 14", 128, 6, "Alb", 4000, 0, "SKU-PH-002", true, 12));
    catalog_.push_back(ProductFactory::createPhone("Xiaomi Redmi Note 12", 128, 6, "Albastru", 1100, 0, "SKU-PH-003", true, 108));

    catalog_.push_back(ProductFactory::createLaptop("Dell XPS 13", 512, 16, "Argintiu", 5200, 0, "SKU-LP-001", false, 60));
    catalog_.push_back(ProductFactory::createLaptop("Lenovo Legion 5", 1024, 16, "Negru", 4800, 0, "SKU-LP-002", true, 144));
    catalog_.push_back(ProductFactory::createLaptop("MacBook Air M2", 256, 8, "Gri", 5400, 0, "SKU-LP-003", false, 60));

    catalog_.push_back(ProductFactory::createTablet("iPad 10", 64, 4, "Argintiu", 1800, 0, "SKU-TB-001", false, 10.9));
    catalog_.push_back(ProductFactory::createTablet("Samsung Tab S8", 128, 8, "Negru", 2600, 0, "SKU-TB-002", true, 11.0));
    catalog_.push_back(ProductFactory::createTablet("Lenovo Tab M10", 64, 4, "Gri", 900, 0, "SKU-TB-003", false, 10.1));

    budget_ = 20000.0;

    indexCatalog();
}

void Store::tickMarketAndAnnounce() {
    const std::string ev = market_.tick();
    if (!ev.empty()) {
        pricing_.setDiscountedCategory(market_.currentDiscount());

        const auto cat = pricing_.discountedCategory();
        std::string msg = " ===Eveniment De Piata===\nPreturile la " + Product::categoryToString(cat) +
                          " s-au ieftinit\n"
                          "Pret de vanzare este acum 80% din pretul de cumparare.\n";

        std::cout << "\n" << msg << "\n";
        eventHistory_.add(msg);
    }
}

void Store::printCatalogForRestock() const {
    std::cout << "\n=== CATALOG APROVIZIONARE ===\n";
    for (const auto& p : catalog_) {
        const double buy = p->purchasePrice(); // fara adaos
        std::cout << p->lineWithPrice(buy) << "\n";
    }
}

void Store::printCatalogWithSalePrices() const {
    std::cout << "\n=== CATALOG ===\n";
    for (const auto& p : catalog_) {
        const double sp = pricing_.salePriceFor(*p);
        std::cout << p->lineWithPrice(sp) << "\n";
    }
    std::cout << "\n===Categorie cu reducere activa: " << Product::categoryToString(pricing_.discountedCategory()) << "=== \n";
    std::cout << "\n";
}

const Product& Store::getProduct(int productId) const {
    auto it = byId_.find(productId);
    if (it == byId_.end()) throw NotFoundError("Produs inexistent (id=" + std::to_string(productId) + ")");
    return *(it->second);
}

Product& Store::getProductMut(int productId) {
    auto it = byId_.find(productId);
    if (it == byId_.end()) throw NotFoundError("Produs inexistent (id=" + std::to_string(productId) + ")");
    return *(it->second);
}

double Store::salePriceFor(int productId) const {
    const Product& p = getProduct(productId);
    return pricing_.salePriceFor(p);
}

void Store::restock(int productId, int qty) {
    Product& p = getProductMut(productId);
    p += qty;
    const double total = p.purchasePrice() * qty;
    if (total > budget_) {
        throw StoreError("Buget insuficient pentru aprovizionare");
    }
    budget_ -= total;
    std::cout << "Buget ramas: " << std::fixed << std::setprecision(2) << budget_ << " lei\n";
    std::cout << "Total de plata aprovizionare: " << std::fixed << std::setprecision(2) << total << " lei\n";
}

SaleTransaction Store::sell(int productId, int qty) {
    Product& p = getProductMut(productId);

    const double unitSale = pricing_.salePriceFor(p);
    const double unitCost = p.purchasePrice();

    if (p.category() == pricing_.discountedCategory()) {
        std::cout << "\n=== Categoria selectata este redusa, pretul de vanzare este 80% din pretul de cumparare ===\n";
    }

    p -= qty;

    SaleTransaction t(productId, qty, unitSale);
    const double total = t.total();
    budget_ += total;
    std::cout << "Buget curent: " << std::fixed << std::setprecision(2) << budget_ << " lei\n";
    const double profit = (unitSale - unitCost) * qty;

    revenueHistory_.add(total);

    std::cout << "TOTAL DE INCASAT: " << std::fixed << std::setprecision(2) << total << " lei\n";
    std::cout << "PROFIT: " << std::fixed << std::setprecision(2) << profit << " lei\n";

    return t;
}

double Store::sellAllInventory(double& outProfit) {
    double revenue = 0.0;
    outProfit = 0.0;

    for ( auto& sp : catalog_) {
        Product& p = *sp;
        if (p.stock() <= 0) continue;

        const int qty = p.stock();
        const double unitSale = pricing_.salePriceFor(p);
        const double unitCost = p.purchasePrice();

        revenue += unitSale * qty;
        outProfit += (unitSale - unitCost) * qty;

        p -= qty;
    }
    budget_ += revenue;
    revenueHistory_.add(revenue);
    return revenue;
}

int Store::performanceScore(const Product& p) {
    if (auto lp = dynamic_cast<const Laptop*>(&p)) {
        return (lp->ramGB() * 2) + (lp->dedicatedGPU() ? 50 : 10) + lp->refreshHz() / 10;
    }
    if (auto ph = dynamic_cast<const Phone*>(&p)) {
        return ph->ramGB() + (ph->has5G() ? 10 : 0) + ph->cameraMP() / 10;
    }
    if (auto tb = dynamic_cast<const Tablet*>(&p)) {
        return tb->ramGB() + (tb->hasStylus() ? 15 : 0) + static_cast<int>(tb->screenInches());
    }
    return 0;
}

double Store::insuranceCost(const Product& p) {
    if (auto lp = dynamic_cast<const Laptop*>(&p)) {
        return lp->purchasePrice() * (lp->dedicatedGPU() ? 0.1 : 0.05);
    }
    if (auto ph = dynamic_cast<const Phone*>(&p)) {
        return ph->purchasePrice() * (ph->has5G() ? 0.1 : 0.05);
    }
    if (auto tb = dynamic_cast<const Tablet*>(&p)) {
        return tb->purchasePrice() * (tb->hasStylus() ? 0.1 : 0.05);
    }
    return p.purchasePrice() * 0.05;
}

bool Store::isHighDemand(const Product& p) {
    if (auto ph = dynamic_cast<const Phone*>(&p)) return ph->has5G();
    if (auto tb = dynamic_cast<const Tablet*>(&p)) return tb->hasStylus();
    if (auto lp = dynamic_cast<const Laptop*>(&p)) return lp->dedicatedGPU();
    return false;
}
bool Store::isInventoryEmpty() const {
    for (const auto& sp : catalog_) {
        if (sp && sp->stock() > 0) return false;
    }
    return true;
}
void Store::sortCatalogByCurrentSalePrice() {
    std::sort(catalog_.begin(), catalog_.end(), [this](const auto& a, const auto& b) {
        return pricing_.salePriceFor(*a) < pricing_.salePriceFor(*b);
    });

}
