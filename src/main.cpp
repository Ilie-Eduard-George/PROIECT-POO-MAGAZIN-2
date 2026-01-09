#include <iostream>
#include <vector>
#include "Utils.h"
#include "Spec.h"
#include "Product.h"
#include "CatalogItem.h"
#include "StocProdus.h"
#include "Inventory.h"
#include "Store.h"

int main() {
    using namespace std;

    // creez cateva Spec/Product/CatalogItem
    Spec s1("Snapdragon 8", 8, 128);
    Spec s2("Exynos 2200", 12, 256);
    Spec s3("Apple M1", 8, 256);
    Spec s4("Intel i7", 16, 512);

    Product p_s24("Telefon", "Samsung", "s24", s1);
    Product p_s23("Telefon", "Samsung", "s23", s2);
    Product p_ipad("Tableta", "Apple", "iPadAir", s3);
    Product p_xps("Laptop", "Dell", "XPS15", s4);

    vector<CatalogItem> catalog;
    catalog.emplace_back(p_s24, 1200, "negru");
    catalog.emplace_back(p_s23, 900, "alb");
    catalog.emplace_back(p_ipad, 2000, "gri");
    catalog.emplace_back(p_xps, 6000, "gri");

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

            StocProdus toAdd(chosen.getProduct(), qty, chosen.getPret(), chosen.getCuloare());
            bool ok = magazin.buyFromCatalog(toAdd);
            if (!ok) cout << "Cumparare esuata. Buget insuficient sau parametri invalidi.\n";
        }
        else if (opt == 2) {
            cout << "\n" << magazin << "\n";
            cout << "Potential profit: " << magazin.getInventory().calcTotalPotentialProfit() << " lei\n";
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

