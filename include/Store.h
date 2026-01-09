#pragma once
#include "Inventory.h"
#include "StocProdus.h"
#include <stdexcept>

class Store {
private:
    Inventory inventory;
    int buget;
public:
    explicit Store(int initialBudget);

    int getBuget() const;
    const Inventory& getInventory() const;
    Inventory& getInventory();

    bool buyFromCatalog(const StocProdus& item);
    int sellItem(size_t idx, int qty);
    int sellAll();

    friend std::ostream& operator<<(std::ostream& os, const Store& s);
};

