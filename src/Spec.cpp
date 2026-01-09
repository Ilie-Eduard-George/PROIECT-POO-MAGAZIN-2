#include "Spec.h"
using namespace std;

Spec::Spec(const string& cpu, int ram, int stocare)
    : Cpu(cpu), Ram(ram), Stocare(stocare) {}

const string& Spec::getCpu() const { return Cpu; }
int Spec::getRam() const { return Ram; }
int Spec::getStocare() const { return Stocare; }

ostream& operator<<(ostream& os, const Spec& s) {
    os << "CPU: " << s.Cpu << ", RAM: " << s.Ram << "GB, Storage: " << s.Stocare << "GB";
    return os;
}

