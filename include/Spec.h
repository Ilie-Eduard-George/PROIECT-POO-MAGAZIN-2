#pragma once
#include <string>
#include <ostream>

class Spec {
private:
    std::string Cpu;
    int Ram;
    int Stocare;
public:
    explicit Spec(const std::string& cpu = "", int ram = 0, int stocare = 0);
    Spec(const Spec& other) = default;
    Spec& operator=(const Spec& other) = default;
    ~Spec() = default;

    [[nodiscard]] const std::string& getCpu() const;
    [[nodiscard]] int getRam() const;
    [[nodiscard]] int getStocare() const;

    friend std::ostream& operator<<(std::ostream& os, const Spec& s);
};

