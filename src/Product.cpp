#include "Product.h"
using namespace std;

Product::Product(const string& categorie, const string& brand, const string& model, const Spec& spec)
    : categorie(categorie), brand(brand), model(model), spec(spec) {}

const string& Product::getCategorie() const { return categorie; }
const string& Product::getBrand() const { return brand; }
const string& Product::getModel() const { return model; }
const Spec& Product::getSpec() const { return spec; }

ostream& operator<<(ostream& os, const Product& p) {
    os << p.categorie << " " << p.brand << " " << p.model << " - " << p.spec;
    return os;
}


