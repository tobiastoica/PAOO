#include <iostream>

int main() {
    std::cout << "========================================================\n";
    std::cout << "  PAOO - Proiectarea Aplicatiilor Orientate pe Obiecte  \n";
    std::cout << "  Lucrare 1: Descrierea Mediului de Lucru               \n";
    std::cout << "========================================================\n";
    std::cout << "Sistem de operare / Platforma: Linux (WSL / Native)\n";

#if defined(__GNUC__)
    std::cout << "Compilator detectat: GCC / G++ "
              << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << "\n";
#elif defined(_MSC_VER)
    std::cout << "Compilator detectat: MSVC " << _MSC_VER << "\n";
#elif defined(__clang__)
    std::cout << "Compilator detectat: Clang " << __clang_version__ << "\n";
#else
    std::cout << "Compilator detectat: Alt compilator\n";
#endif

    std::cout << "Valoare standard C++ (__cplusplus): " << __cplusplus << " (";
    if (__cplusplus == 201103L) std::cout << "C++11";
    else if (__cplusplus == 201402L) std::cout << "C++14";
    else if (__cplusplus == 201703L) std::cout << "C++17";
    else if (__cplusplus == 202002L) std::cout << "C++20";
    else std::cout << "Alta versiune";
    std::cout << ")\n";

    std::cout << "Status mediu de lucru: CONFIGURAT CU SUCCES!\n";
    std::cout << "========================================================\n";

    return 0;
}
