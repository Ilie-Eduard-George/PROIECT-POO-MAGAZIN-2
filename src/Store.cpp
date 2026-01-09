#include "Store.h"
using namespace std;

Store::Store(int initialBudget) : inventory(), buget(initialBudget) {
    if (initialBudget < 0) buget = 0;
}

int Store::getBuget() const { return buget; }
const Inventory& Store::getInventory() const { return inventory; }
Inventory& Store::getInventory() { return inventory; }

bool Store::buyFromCatalog(const StocProdus& item) {
    if (item.getQuantity() <= 0) return false;
    long long cost = static_cast<long long>(item.getPretCumpararePerBuc()) * item.getQuantity();
    if (cost > buget) return false;
    inventory.addItem(item);
    buget -= static_cast<int>(cost);
    return true;
}

int Store::sellItem(size_t idx, int qty) {
    if (idx >= inventory.size()) return -1;
    StocProdus& it = inventory.at(idx);
    if (qty <= 0 || qty > it.getQuantity()) return -1;
    int suma = it.pretRevanzarePerBuc() * qty;
    if (!it.removeQuantity(qty)) return -1;
    buget += suma;
    if (it.getQuantity() == 0) inventory.removeItemAt(idx);
    return suma;
}

int Store::sellAll() {
    int total = 0;
    for (size_t i = 0; i < inventory.size(); ++i) {
        const StocProdus& it = inventory.at(i);
        total += it.pretRevanzarePerBuc() * it.getQuantity();
    }
    while (inventory.size() > 0) inventory.removeItemAt(0);
    buget += total;
    return total;
}

ostream& operator<<(ostream& os, const Store& s) {
    os << "Magazin - buget: " << s.buget << " lei\n";
    os << s.inventory;
    return os;
}

