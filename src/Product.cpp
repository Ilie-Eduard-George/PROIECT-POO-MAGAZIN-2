#include "Product.h"
#include <cstring>
#include <sstream>
#include <iomanip>

std::unordered_map<ProductCategory, std::string> Product::categoryNames_ = {
    {ProductCategory::Phone, "Telefoane"},
    {ProductCategory::Laptop, "Laptopuri"},
    {ProductCategory::Tablet, "Tablete"}
};

static std::unique_ptr<char[]> makeSkuBuffer(const std::string& sku, std::size_t& outLen) {
    outLen = sku.size();
    auto buf = std::make_unique<char[]>(outLen + 1);
    std::memcpy(buf.get(), sku.c_str(), outLen + 1);
    return buf;
}

Product::Product(ProductCategory category,
                 std::string name,
                 int storageGB,
                 int ramGB,
                 std::string color,
                 double purchasePrice,
                 int stock,
                 const std::string& sku)
    : name_(std::move(name)),
      storageGB_(storageGB),
      ramGB_(ramGB),
      color_(std::move(color)),
      purchasePrice_(purchasePrice),
      stock_(stock),
      sku_(makeSkuBuffer(sku, skuLen_)),
      category_(category) {}

Product::Product(const Product& other)
    : id_(other.id_),
      name_(other.name_),
      storageGB_(other.storageGB_),
      ramGB_(other.ramGB_),
      color_(other.color_),
      purchasePrice_(other.purchasePrice_),
      stock_(other.stock_),
      sku_(other.sku_ ? makeSkuBuffer(other.sku(), skuLen_) : nullptr),
      skuLen_(other.skuLen_),
      category_(other.category_) {}

Product& Product::operator=(const Product& other) {
    if (this == &other) return *this;
    id_ = other.id_;
    name_ = other.name_;
    storageGB_ = other.storageGB_;
    ramGB_ = other.ramGB_;
    color_ = other.color_;
    purchasePrice_ = other.purchasePrice_;
    stock_ = other.stock_;
    category_ = other.category_;

    if (other.sku_) {
        sku_ = makeSkuBuffer(other.sku(), skuLen_);
    } else {
        sku_.reset();
        skuLen_ = 0;
    }
    return *this;
}

Product::~Product() = default;

std::string Product::sku() const {
    if (!sku_) return "";
    return std::string(sku_.get());
}

Product& Product::operator+=(int qty) {
    if (qty <= 0) throw InputError("Cantitatea trebuie sa fie > 0");
    stock_ += qty;
    return *this;
}

Product& Product::operator-=(int qty) {
    if (qty <= 0) throw InputError("Cantitatea trebuie sa fie > 0");
    if (qty > stock_) throw OutOfStockError("Stoc insuficient pentru produsul selectat");
    stock_ -= qty;
    return *this;
}

void Product::print(std::ostream& os) const {
    os << basicLine();
}

void Product::read(std::istream& is) {
    // Exemplu simplu de citire; folosit dacă vrei să extinzi meniul cu "adaugă produs"
    is >> id_ >> name_ >> storageGB_ >> ramGB_ >> color_ >> purchasePrice_ >> stock_;
    std::string skuIn;
    is >> skuIn;
    sku_ = makeSkuBuffer(skuIn, skuLen_);
}

std::string Product::categoryToString(ProductCategory c) {
    auto it = categoryNames_.find(c);
    if (it == categoryNames_.end()) return "Necunoscut";
    return it->second;
}

std::string Product::basicLine() const {
    std::ostringstream ss;
    ss << "[" << id_ << "] "
       << name_ << " | "
       << storageGB_ << "GB | "
       << ramGB_ << "GB RAM | "
       << color_ << " | "
       << "Stoc: " << stock_;
    return ss.str();
}

std::string Product::lineWithPrice(double salePrice) const {
    std::ostringstream ss;
    ss << basicLine()
       << " | Pret: " << std::fixed << std::setprecision(2) << salePrice << " lei";
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Product& p) {
    p.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Product& p) {
    p.read(is);
    return is;
}

bool operator<(const Product& a, const Product& b) {
    if (a.name() != b.name()) return a.name() < b.name();
    return a.id() < b.id();
}
