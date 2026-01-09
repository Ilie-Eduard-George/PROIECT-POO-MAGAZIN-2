#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <limits>

using namespace std;

void clearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int profitCuloare(const string& culoare) {
    if (culoare == "negru") return 200;
    if (culoare == "alb") return 150;
    if (culoare == "rosu") return -100;
    if (culoare == "albastru") return 150;
    if (culoare == "verde") return 75;
    if (culoare == "galben") return -150;
    if (culoare == "mov") return -100;
    if (culoare == "gri") return 250;
    if (culoare == "portocaliu") return 75;
    return 0;
}

class Spec {
private:
    string Cpu;
    int Ram;
    int Stocare;

public:
    explicit Spec(string  cpu = "", int ram = 0, int stocare = 0)
        : Cpu(std::move(cpu)), Ram(ram), Stocare(stocare) {}

    [[nodiscard]] string getCpu() const { return Cpu; }
    [[nodiscard]] int getRam() const { return Ram; }
    [[nodiscard]] int getStocare() const { return Stocare; }

    friend ostream& operator<<(ostream& os, const Spec& s) {
        os << "CPU: " << s.Cpu << ", RAM: " << s.Ram << "GB, Storage: " << s.Stocare << "GB";
        return os;
    }
};

class Product {
private:
    string categorie;
    string brand;
    string model;
    Spec spec;

public:
    explicit Product(string  categorie = "", string  brand = "",
                     string  model = "", Spec  spec = Spec())
        : categorie(std::move(categorie)), brand(std::move(brand)), model(std::move(model)), spec(std::move(spec)) {}

    [[nodiscard]] string getCategorie() const { return categorie; }
    [[nodiscard]] string getBrand() const { return brand; }
    [[nodiscard]] string getModel() const { return model; }
    [[nodiscard]] const Spec& getSpec() const { return spec; }

    friend ostream& operator<<(ostream& os, const Product& p) {
        os << p.categorie << " " << p.brand << " " << p.model << " - " << p.spec;
        return os;
    }
};

class CatalogItem {
private:
    Product product;
    int pret;
    string culoare;

public:
    explicit CatalogItem(Product  product, int pret, string  culoare)
        : product(std::move(product)), pret(pret), culoare(std::move(culoare)) {}

    [[nodiscard]] const Product& getProduct() const { return product; }
    [[nodiscard]] int getPret() const { return pret; }
    [[nodiscard]] string getCuloare() const { return culoare; }

    friend ostream& operator<<(ostream& os, const CatalogItem& c) {
        os << c.product << " " << c.culoare << ", pret: " << c.pret << " lei";
        return os;
    }
};

class StocProdus {
private:
    Product product;
    int quantity;
    int pretCumpararePerBuc;
    string culoare;

    [[nodiscard]] int profitPerBuc() const {
        return profitCuloare(culoare);
    }

public:
    explicit StocProdus(Product  product, int quantity, int pretCumpararePerBuc, string  culoare)
        : product(std::move(product)), quantity(quantity),
          pretCumpararePerBuc(pretCumpararePerBuc), culoare(std::move(culoare)) {}

    StocProdus(const StocProdus&) = default;

    StocProdus& operator=(const StocProdus& other) {
        if (this != &other) {
            product = other.product;
            quantity = other.quantity;
            pretCumpararePerBuc = other.pretCumpararePerBuc;
            culoare = other.culoare;
        }
        return *this;
    }

    ~StocProdus() = default;

    [[nodiscard]] const Product& getProduct() const { return product; }
    [[nodiscard]] int getQuantity() const { return quantity; }
    [[nodiscard]] int getPretCumpararePerBuc() const { return pretCumpararePerBuc; }
    [[nodiscard]] string getCuloare() const { return culoare; }

    void addQuantity(int q) { if (q > 0) quantity += q; }

    bool removeQuantity(int q) {
        if (q <= 0 || q > quantity) return false;
        quantity -= q;
        return true;
    }

    [[nodiscard]] int pretRevanzarePerBuc() const {
        int adaosProcentual = pretCumpararePerBuc / 10;
        return pretCumpararePerBuc + adaosProcentual + profitCuloare(culoare);
    }

    friend ostream& operator<<(ostream& os, const StocProdus& s) {
        os << s.product << " " << s.culoare
           << ", cantitate: " << s.quantity
           << ", pret cumparare/buc: " << s.pretCumpararePerBuc
           << ", pret revanzare/buc: " << s.pretRevanzarePerBuc() << " lei";
        return os;
    }
};

class Inventory {
private:
    vector<StocProdus> items;

public:
    Inventory() = default;

    void addItem(const StocProdus& s) {
        for (auto& it : items) {
            if (it.getProduct().getModel() == s.getProduct().getModel()
                && it.getCuloare() == s.getCuloare()) {
                it.addQuantity(s.getQuantity());
                return;
            }
        }
        items.emplace_back(s);
    }

    bool removeItemAt(size_t idx) {
        if (idx >= items.size()) return false;
        items.erase(std::next(items.begin(), static_cast<long long>(idx)));
        return true;
    }

    [[nodiscard]] size_t size() const { return items.size(); }
    [[nodiscard]] const StocProdus& at(size_t idx) const { return items.at(idx); }
    [[nodiscard]] StocProdus& at(size_t idx) { return items.at(idx); }

    friend ostream& operator<<(ostream& os, const Inventory& inv) {
        os << "Inventar: " << inv.items.size() << " produse\n";
        for (size_t i = 0; i < inv.items.size(); ++i) {
            os << i+1 << ") " << inv.items[i] << "\n";
        }
        return os;
    }
};

class Store {
private:
    Inventory inventory;
    int buget;

    [[nodiscard]] bool canAfford(int suma) const { return suma <= buget; }

public:
    explicit Store(int initialBudget) : inventory(), buget(initialBudget) {}

    [[nodiscard]] int getBuget() const { return buget; }

    bool buyFromCatalog(const CatalogItem& catalogItem, int qty) {
        if (qty <= 0) return false;
        int unitPrice = catalogItem.getPret();
        int totalCost = unitPrice * qty;
        if (!canAfford(totalCost)) return false;

        const Product& p = catalogItem.getProduct();
        StocProdus toAdd(p, qty, unitPrice, catalogItem.getCuloare());
        inventory.addItem(toAdd);

        buget -= totalCost;
        return true;
    }

    int sellItem(size_t idx, int qtyToSell) {
        if (idx >= inventory.size()) return -1;
        StocProdus& it = inventory.at(idx);
        if (qtyToSell <= 0 || qtyToSell > it.getQuantity()) return -1;

        int suma = it.pretRevanzarePerBuc() * qtyToSell;
        if (!it.removeQuantity(qtyToSell)) return -1;

        buget += suma;
        if (it.getQuantity() == 0) inventory.removeItemAt(idx);
        return suma;
    }

    int sellAll() {
        int total = 0;
        for (size_t i = 0; i < inventory.size(); ++i) {
            const StocProdus& it = inventory.at(i);
            total += it.pretRevanzarePerBuc() * it.getQuantity();
        }
        while (inventory.size() > 0) inventory.removeItemAt(0);
        buget += total;
        return total;
    }

    [[nodiscard]] const Inventory& getInventory() const { return inventory; }
    [[nodiscard]] Inventory& getInventory() { return inventory; }

    friend ostream& operator<<(ostream& os, const Store& s) {
        os << "Magazin - buget: " << s.buget << " lei\n";
        os << s.inventory;
        return os;
    }
};

vector<string> culori = {
    "negru", "alb", "rosu", "albastru", "verde", "gri", "portocaliu"
};

int main() {
    Spec s1("Snapdragon 8", 8, 128);
    Spec s2("Exynos 2200", 12, 256);
    Spec s3("Apple M1", 8, 256);
    Spec s4("Intel i7", 16, 512);
    Spec s5("Snapdragon 8 Gen2", 12, 256);
    Spec s6("MediaTek 9000", 8, 128);

    Product p_s24("Telefon", "Samsung", "s24", s1);
    Product p_s23("Telefon", "Samsung", "s23", s2);
    Product p_s25("Telefon", "Samsung", "s25", s5);
    Product p_a74("Telefon", "Samsung", "a74", s6);

    Product p_ipad("Tableta", "Apple", "iPadAir", s3);
    Product p_ipadMini("Tableta", "Apple", "iPadMini", s3);
    Product p_tabS9("Tableta", "Samsung", "tabS9", s5);

    Product p_xps("Laptop", "Dell", "XPS15", s4);
    Product p_proBook("Laptop", "HP", "ProBook", s4);
    Product p_ultra("Laptop", "Lenovo", "UltraLight", s4);

    vector<CatalogItem> catalog;
    catalog.emplace_back(p_s24, 1200, "negru");
    catalog.emplace_back(p_s23, 900, "alb");
    catalog.emplace_back(p_s25, 1400, "negru");
    catalog.emplace_back(p_a74, 700, "alb");
    catalog.emplace_back(p_ipad, 2000, "gri");
    catalog.emplace_back(p_ipadMini, 1200, "alb");
    catalog.emplace_back(p_tabS9, 2000, "gri");
    catalog.emplace_back(p_xps, 6000, "gri");
    catalog.emplace_back(p_proBook, 2500, "gri");
    catalog.emplace_back(p_ultra, 2300, "negru");

    Store magazin(20000);

    while (true) {
        cout << "\n=== MENIU MAGAZIN ===\n";
        cout << "Buget curent: " << magazin.getBuget() << " lei\n";
        cout << "1 Cumpara produs din catalog\n";
        cout << "2 Afiseaza inventar\n";
        cout << "3 Vinde un produs individual\n";
        cout << "4 Vinde toate produsele\n";
        cout << "5 Afiseaza catalog furnizori\n";
        cout << "6 Iesire\n";
        cout << "Alege optiunea: ";

        int opt;
        if (!(cin >> opt)) { cout << "Intrare invalida.\n"; clearCin(); continue; }

        if (opt == 1) {
            cout << "\nCatalog furnizori\n";
            for (size_t i = 0; i < catalog.size(); ++i) {
                cout << i+1 << " " << catalog[i] << "\n";
            }
            cout << "Alege index produs din catalog: ";
            int idx;
            if (!(cin >> idx)) { cout << "Intrare invalida.\n"; clearCin(); continue; }
            if (idx < 1 || static_cast<size_t>(idx) > catalog.size()) {
                cout << "Index invalid.\n"; continue;
            }
            const CatalogItem& chosen = catalog[idx-1];

            cout << "Introdu cantitatea pe care vrei sa o cumperi: ";
            int qty;
            if (!(cin >> qty)) { cout << "Intrare invalida.\n"; clearCin(); continue; }
            if (qty <= 0) { cout << "Cantitate invalida.\n"; continue; }

            bool ok = magazin.buyFromCatalog(chosen, qty);
            if (!ok) cout << "Cumparare esuata. Buget insuficient sau parametri invalidi.\n";
        }
        else if (opt == 2) {
            cout << "\n" << magazin << "\n";
        }
        else if (opt == 3) {
            if (magazin.getInventory().size() == 0) {
                cout << "Nu ai produse in inventar.\n"; continue;
            }
            cout << "\nProduse in inventar:\n";
            for (size_t i = 0; i < magazin.getInventory().size(); ++i) {
                cout << i+1 << " " << magazin.getInventory().at(i) << "\n";
            }
            cout << "Alege indexul produsului pe care vrei sa-l vinzi: ";
            int idx;
            if (!(cin >> idx)) { cout << "Intrare invalida.\n"; clearCin(); continue; }
            if (idx < 1 || static_cast<size_t>(idx) > magazin.getInventory().size()) {
                cout << "Index invalid.\n"; continue;
            }
            cout << "Introdu cantitatea de vandut: ";
            int qty;
            if (!(cin >> qty)) { cout << "Intrare invalida.\n"; clearCin(); continue; }
            int suma = magazin.sellItem(static_cast<size_t>(idx-1), qty);
            if (suma < 0) cout << "Vanzare esuata. Cantitate invalida sau eroare.\n";
            else cout << "Vanzare reusita. Ai obtinut " << suma << " lei.\n";
        }
        else if (opt == 4) {
            if (magazin.getInventory().size() == 0) {
                cout << "Nu ai produse in inventar.\n"; continue;
            }
            int total = magazin.sellAll();
            cout << "Ai vandut toate produsele si ai obtinut " << total << " lei.\n";
        }
        else if (opt == 5) {
            cout << "\nCatalog furnizori\n";
            for (size_t i = 0; i < catalog.size(); ++i) {
                cout << i+1 << " " << catalog[i] << "\n";
            }
        }
        else if (opt == 6) {
            cout << "Aplicatia se inchide.\n";
            break;
        }
        else {
            cout << "Optiune invalida.\n";
        }
    }
    return 0;
}

