#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include "Product.h"
#include "PricingEngine.h"
#include "MarketSimulator.h"
#include "History.h"
class Transaction {
public:
    virtual ~Transaction() = default;
    virtual double total() const = 0;
    virtual std::string description() const = 0;
};

class SaleTransaction final : public Transaction {
private:
    int productId_{0};
    int qty_{0};
    double unitPrice_{0.0};

public:
    SaleTransaction(int productId, int qty, double unitPrice)
        : productId_(productId), qty_(qty), unitPrice_(unitPrice) {}

    double total() const override { return unitPrice_ * qty_; }
    std::string description() const override;
};

class PurchaseTransaction final : public Transaction {
private:
    int productId_{0};
    int qty_{0};
    double unitCost_{0.0};

public:
    PurchaseTransaction(int productId, int qty, double unitCost)
        : productId_(productId), qty_(qty), unitCost_(unitCost) {}

    double total() const override { return unitCost_ * qty_; }
    std::string description() const override;
};

class Store {
private:
    std::vector<std::shared_ptr<Product>> catalog_;
    std::unordered_map<int, std::shared_ptr<Product>> byId_;
    double budget_{0.0};
    PricingEngine pricing_;
    MarketSimulator market_;

    History<double> revenueHistory_;
    History<std::string> eventHistory_;

    void indexCatalog();

public:
    Store(PricingEngine pricing, MarketSimulator market);
    double budget() const { return budget_; }

    void seedInitialCatalog();
    void tickMarketAndAnnounce();

    void printCatalogWithSalePrices() const;
    void printCatalogForRestock() const;

    void restock(int productId, int qty);
    SaleTransaction sell(int productId, int qty);

    double sellAllInventory(double& outProfit);

    const Product& getProduct(int productId) const;
    Product& getProductMut(int productId);

    double salePriceFor(int productId) const;

    static int performanceScore(const Product& p);
    static double insuranceCost(const Product& p);
    static bool isHighDemand(const Product& p);

    void sortCatalogByCurrentSalePrice();
    bool isInventoryEmpty() const;
    ProductCategory discountedCategory() const { return pricing_.discountedCategory(); }
};
