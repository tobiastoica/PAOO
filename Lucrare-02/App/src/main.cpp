#include <iostream>
#include "MathUtils.h"

int main() {
    std::cout << "========================================================\n";
    std::cout << "  PAOO - Lucrare 2: Utilizare CMake                     \n";
    std::cout << "  Consumare biblioteca statica 'MathLib' in aplicatie  \n";
    std::cout << "========================================================\n";

    std::cout << "Versiune biblioteca utilizata: " << MathUtils::getLibraryVersion() << "\n\n";

    // 1. Vector2D operations
    std::cout << "--- 1. Operatii Vector2D ---\n";
    MathUtils::Vector2D v1(3.0, 4.0);
    MathUtils::Vector2D v2(1.0, 2.0);

    v1.print("Vector v1:");
    v2.print("Vector v2:");

    std::cout << "Magnitudine v1: " << v1.magnitude() << "\n";
    
    MathUtils::Vector2D v1_norm = v1.normalized();
    v1_norm.print("v1 normalizat:");
    std::cout << "Magnitudine v1 normalizat: " << v1_norm.magnitude() << "\n";

    MathUtils::Vector2D v_sum = MathUtils::add(v1, v2);
    v_sum.print("v1 + v2:");

    std::cout << "Produs scalar (dot product) v1 . v2: " 
              << MathUtils::dotProduct(v1, v2) << "\n";
    std::cout << "Distanta intre v1 si v2: " 
              << MathUtils::distance(v1, v2) << "\n\n";

    // 2. Scalar utilities
    std::cout << "--- 2. Functii Utilitare Scalare ---\n";
    std::cout << "Factorial de 6 (6!): " << MathUtils::factorial(6) << "\n";
    std::cout << "CMMDC (gcd) intre 48 si 18: " << MathUtils::gcd(48, 18) << "\n";
    std::cout << "Clamp valoare 15.5 in intervalul [0.0, 10.0]: " 
              << MathUtils::clamp(15.5, 0.0, 10.0) << "\n";
    std::cout << "Interpolare liniara (lerp) de la 10.0 la 20.0 cu t = 0.25: " 
              << MathUtils::lerp(10.0, 20.0, 0.25) << "\n";

    std::cout << "========================================================\n";
    std::cout << "Executie finalizata cu succes!\n";
    return 0;
}
