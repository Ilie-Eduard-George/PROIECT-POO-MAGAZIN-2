#include "Utils.h"
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

