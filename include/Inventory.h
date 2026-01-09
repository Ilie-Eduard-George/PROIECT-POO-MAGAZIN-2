#pragma once
#include "StocProdus.h"
#include <vector>
#include <map>
#include <optional>

class Inventory {
private:
    std::vector<StocProdus> items;
    std::map<std::string,int> indexByModel;
public:
    Inventory() = default;

    void addItem(const StocProdus& s);
    bool removeItemAt(size_t idx);

    size_t size() const;
    const StocProdus& at(size_t idx) const;
    StocProdus& at(size_t idx);

    double calcTotalPotentialProfit() const;
    std::vector<const StocProdus*> findByBrand(const std::string& brand) const;
    void sortByPotentialProfitDesc();
    std::optional<size_t> findIndexByModel(const std::string& model) const;

    friend std::ostream& operator<<(std::ostream& os, const Inventory& inv);
};

