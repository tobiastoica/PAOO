#include <iostream>
#include "Item4_Initialization.h"
#include "Item5_SilentlyGenerated.h"
#include "Item6_DisallowFunctions.h"

int main() {
    std::cout << "======================================================================\n";
    std::cout << "  PAOO - Lucrarea 4: Effective C++ (Scott Meyers)                     \n";
    std::cout << "  Item 4, Item 5 si Item 6                                            \n";
    std::cout << "======================================================================\n";

    // Item 4: Make sure that objects are initialized before they're used
    Item4::runDemo();

    // Item 5: Know what functions C++ silently writes and calls
    Item5::runDemo();

    // Item 6: Explicitly disallow the use of compiler-generated functions you do not want
    Item6::runDemo();

    std::cout << "\n======================================================================\n";
    std::cout << "  Toate testele pentru Lucrarea 4 au rulat cu succes!                 \n";
    std::cout << "======================================================================\n";

    return 0;
}
