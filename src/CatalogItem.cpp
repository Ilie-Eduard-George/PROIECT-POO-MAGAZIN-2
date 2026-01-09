#include "CatalogItem.h"
using namespace std;

CatalogItem::CatalogItem(const Product& product, int pret, const string& culoare)
    : product(product), pret(pret), culoare(culoare) {}

const Product& CatalogItem::getProduct() const { return product; }
int CatalogItem::getPret() const { return pret; }
const string& CatalogItem::getCuloare() const { return culoare; }

ostream& operator<<(ostream& os, const CatalogItem& c) {
    os << c.product << " " << c.culoare << ", pret: " << c.pret << " lei";
    return os;
}

