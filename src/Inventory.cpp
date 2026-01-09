#include "Inventory.h"
#include <algorithm>
using namespace std;

void Inventory::addItem(const StocProdus& s) {
    for (auto& it : items) {
        if (it.getProduct().getModel() == s.getProduct().getModel()) {
            it.addQuantity(s.getQuantity());
            indexByModel[it.getProduct().getModel()] = static_cast<int>(&it - &items[0]);
            return;
        }
    }
    items.push_back(s);
    indexByModel[s.getProduct().getModel()] = static_cast<int>(items.size()-1);
}

bool Inventory::removeItemAt(size_t idx) {
    if (idx >= items.size()) return false;
    indexByModel.erase(items[idx].getProduct().getModel());
    items.erase(items.begin() + static_cast<ptrdiff_t>(idx));
    indexByModel.clear();
    for (size_t i = 0; i < items.size(); ++i) indexByModel[items[i].getProduct().getModel()] = static_cast<int>(i);
    return true;
}

size_t Inventory::size() const { return items.size(); }
const StocProdus& Inventory::at(size_t idx) const { return items.at(idx); }
StocProdus& Inventory::at(size_t idx) { return items.at(idx); }

double Inventory::calcTotalPotentialProfit() const {
    double total = 0.0;
    for (const auto& it : items) {
        double profitPer = it.pretRevanzarePerBuc() - it.getPretCumpararePerBuc();
        total += profitPer * it.getQuantity();
    }
    return total;
}

vector<const StocProdus*> Inventory::findByBrand(const string& brand) const {
    vector<const StocProdus*> res;
    for (const auto& it : items) if (it.getProduct().getBrand() == brand) res.push_back(&it);
    return res;
}

void Inventory::sortByPotentialProfitDesc() {
    std::sort(items.begin(), items.end(), [](const StocProdus& a, const StocProdus& b) {
        double pa = (a.pretRevanzarePerBuc() - a.getPretCumpararePerBuc()) * a.getQuantity();
        double pb = (b.pretRevanzarePerBuc() - b.getPretCumpararePerBuc()) * b.getQuantity();
        return pa > pb;
    });
}

optional<size_t> Inventory::findIndexByModel(const string& model) const {
    auto it = indexByModel.find(model);
    if (it == indexByModel.end()) return nullopt;
    return static_cast<size_t>(it->second);
}

ostream& operator<<(ostream& os, const Inventory& inv) {
    os << "Inventar: " << inv.items.size() << " produse\n";
    for (size_t i = 0; i < inv.items.size(); ++i) os << i+1 << ") " << inv.items[i] << "\n";
    return os;
}
