#include <iostream>
#include "Item10_AssignmentReturnThis.h"
#include "Item11_SelfAssignment.h"
#include "Item12_CopyAllParts.h"

int main() {
    std::cout << "======================================================================\n";
    std::cout << "  PAOO - Lucrarea 5: Effective C++ (Scott Meyers)                     \n";
    std::cout << "  Item 10, Item 11 si Item 12                                         \n";
    std::cout << "======================================================================\n";

    // Item 10: Have assignment operators return a reference to *this
    Item10::runDemo();

    // Item 11: Handle assignment to self in operator=
    Item11::runDemo();

    // Item 12: Copy all parts of an object
    Item12::runDemo();

    std::cout << "\n======================================================================\n";
    std::cout << "  Toate testele pentru Lucrarea 5 au rulat cu succes!                 \n";
    std::cout << "======================================================================\n";

    return 0;
}
