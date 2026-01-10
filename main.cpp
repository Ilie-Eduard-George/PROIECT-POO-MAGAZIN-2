#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include "Store.h"
#include "PriceStrategies.h"
#include "Exceptions.h"

static int readInt(const std::string& prompt) {
    std::cout << prompt;
    int x;
    if (!(std::cin >> x)) {
        throw InputError("Valoare intreaga invalida");
    }
    return x;
}

static int readPositiveInt(const std::string& prompt) {
    int x = readInt(prompt);
    if (x <= 0) throw InputError("Numarul trebuie sa fie > 0");
    return x;
}

static void printMenu() {
    std::cout << "\n==============================\n";
    std::cout << " MAGAZIN: telefoane/tablete/laptopuri\n";
    std::cout << "==============================\n";
    std::cout << "1) Afiseaza catalog\n";
    std::cout << "2) Aprovizionare\n";
    std::cout << "3) Vinde un produs\n";
    std::cout << "4) Vinde tot inventarul\n";
    std::cout << "5) Afiseaza buget\n";
    std::cout << "6) Sorteaza catalog dupa pretul de vanzare\n";
    std::cout << "0) Iesire\n";
}
static bool checkGameOver(const Store& store) {
    if (store.budget() <= 0.0 && store.isInventoryEmpty()) {
        std::cout << "\nGAME OVER: Bugetul este 0 si inventarul este gol.\n";
        return true;
    }
    return false;
}


int main() {
    try {
        PricingEngine pricing(std::make_shared<Markup15Strategy>(),
                              std::make_shared<Discount80Strategy>());

        MarketSimulator market(5);
        Store store(pricing, market);
        store.seedInitialCatalog();

        while (true) {
            printMenu();
            int opt = -1;

            try {
                opt = readInt("Alege optiunea: ");
            } catch (const StoreError& e) {
                std::cout << e.what() << "\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (opt == 0) {
                std::cout << "La revedere!\n";
                break;
            }

            try {
                switch (opt) {
                    case 1: {
                        store.printCatalogWithSalePrices();
                        store.tickMarketAndAnnounce();
                        if (checkGameOver(store)) return 0;
                        break;
                    }

                    case 2: {
                        store.printCatalogForRestock();
                        int id = readInt("Introdu ID produs pentru aprovizionare: ");
                        int qty = readPositiveInt("Introdu numarul de bucati: ");
                        store.restock(id, qty);
                        store.tickMarketAndAnnounce();
                        if (checkGameOver(store)) return 0;
                        break;
                    }
                    case 3: {
                        store.printCatalogWithSalePrices();
                        int id = readInt("Alege ID produs de vandut: ");
                        const Product& p = store.getProduct(id);
                        std::cout << "Selectat: " << p.name()
                                  << " | " << p.storageGB() << "GB"
                                  << " | " << p.ramGB() << "GB RAM"
                                  << " | " << p.color() << "\n";
                        std::cout <<" ";
                        std::cout << "Informatii in plus: scor performanta  " << Store::performanceScore(p)
                                  << " | cost asigurare: " << Store::insuranceCost(p)
                                  << " | cerere mare: " << (Store::isHighDemand(p) ? "da" : "nu") << "\n";

                        std::cout << "Introdu numarul de bucati: ";
                        int qty;
                        if (!(std::cin >> qty)) throw InputError("Cantitate invalida");
                        if (qty <= 0) throw InputError("Cantitatea trebuie sa fie > 0");

                        store.sell(id, qty);
                        store.tickMarketAndAnnounce();
                        if (checkGameOver(store)) return 0;
                        break;
                    }

                    case 4: {
                        double profit = 0.0;
                        const double revenue = store.sellAllInventory(profit);
                        std::cout << "\nInventar vandut complet\n";
                        std::cout << "Valoare totala incasata: " << revenue << " lei\n";
                        std::cout << "Profit total: " << profit << " lei\n";
                        store.tickMarketAndAnnounce();
                        if (checkGameOver(store)) return 0;
                        break;
                    }
                    case 5: {
                        std::cout << "Buget curent: " << store.budget() << " lei\n";
                        store.tickMarketAndAnnounce();
                        if (checkGameOver(store)) return 0;
                        break;
                    }
                    case 6: {
                        store.sortCatalogByCurrentSalePrice();
                        std::cout << "Catalog sortat dupa pretul de vanzare curent.\n";
                        store.printCatalogWithSalePrices();
                        store.tickMarketAndAnnounce();
                        if (checkGameOver(store)) return 0;
                        break;
                    }
                    default:
                        std::cout << "Optiune invalida.\n";
                        if (checkGameOver(store)) return 0;
                        break;
                }
            } catch (const StoreError& e) {
                std::cout << "\n" << e.what() << "\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } catch (const std::exception& e) {
                std::cout << "\nEroare neasteptata: " << e.what() << "\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

    } catch (const std::exception& e) {
        std::cout << "Fatal: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
