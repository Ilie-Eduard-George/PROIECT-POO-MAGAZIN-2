#include "StocProdus.h"
#include "Utils.h"
using namespace std;

StocProdus::StocProdus(const Product& product, int quantity, int pret, const string& culoare)
    : product(product), quantity(quantity), pretCumpararePerBuc(pret), culoare(culoare) {
    if (quantity < 0) quantity = 0;
    if (pretCumpararePerBuc < 0) pretCumpararePerBuc = 0;
}

StocProdus::StocProdus(const StocProdus& other) = default;
StocProdus& StocProdus::operator=(const StocProdus& other) = default;
StocProdus::~StocProdus() = default;

const Product& StocProdus::getProduct() const { return product; }
int StocProdus::getQuantity() const { return quantity; }
int StocProdus::getPretCumpararePerBuc() const { return pretCumpararePerBuc; }
const string& StocProdus::getCuloare() const { return culoare; }

void StocProdus::addQuantity(int q) { if (q > 0) quantity += q; }

bool StocProdus::removeQuantity(int q) {
    if (q <= 0 || q > quantity) return false;
    quantity -= q;
    return true;
}

int StocProdus::pretRevanzarePerBuc() const {
    int adaosProcentual = pretCumpararePerBuc / 10;
    return pretCumpararePerBuc + adaosProcentual + profitCuloare(culoare);
}

ostream& operator<<(ostream& os, const StocProdus& s) {
    os << s.product << " " << s.culoare
       << ", cantitate: " << s.quantity
       << ", pret cumparare/buc: " << s.pretCumpararePerBuc
       << ", pret revanzare/buc: " << s.pretRevanzarePerBuc() << " lei";
    return os;
}

