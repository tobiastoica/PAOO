#include "Item6_DisallowFunctions.h"
#include <type_traits>

namespace Item6 {

    HomeForSale::HomeForSale(const std::string& address, double price)
        : m_address(address), m_price(price) {}

    void HomeForSale::print() const {
        std::cout << "    [HomeForSale] Adresa: '" << m_address 
                  << "', Pret: " << m_price << " EUR\n";
    }

    ModernUniqueDevice::ModernUniqueDevice(int id, const std::string& port)
        : m_deviceId(id), m_hardwarePort(port) {}

    void ModernUniqueDevice::print() const {
        std::cout << "    [ModernUniqueDevice] ID: " << m_deviceId 
                  << ", Port hardware: " << m_hardwarePort << "\n";
    }

    void runDemo() {
        std::cout << "\n--- DEMONSTRATIE ITEM 6: Dezactivarea explicita a functiilor generate automat ---\n";

        std::cout << "\n1. Modelul clasic Scott Meyers: Mostenire din clasa de baza 'Uncopyable':\n";
        HomeForSale h1("Str. Republicii 14", 150000.0);
        HomeForSale h2("Bd. Revolutiei 4", 220000.0);
        h1.print();
        h2.print();

        std::cout << "  Verificare la compilare pentru HomeForSale (prin Uncopyable):\n";
        std::cout << "  - Este HomeForSale copy-constructible? " 
                  << (std::is_copy_constructible<HomeForSale>::value ? "DA" : "NU (Blocat la compilare de Uncopyable!)") << "\n";
        std::cout << "  - Este HomeForSale copy-assignable?    " 
                  << (std::is_copy_assignable<HomeForSale>::value ? "DA" : "NU (Blocat la compilare de Uncopyable!)") << "\n";

        std::cout << "\n2. Modelul modern C++: Specificatorul '= delete;':\n";
        ModernUniqueDevice dev1(404, "/dev/ttyUSB0");
        dev1.print();

        std::cout << "  Verificare la compilare pentru ModernUniqueDevice (prin '= delete'):\n";
        std::cout << "  - Este ModernUniqueDevice copy-constructible? " 
                  << (std::is_copy_constructible<ModernUniqueDevice>::value ? "DA" : "NU (Blocat de '= delete'!)") << "\n";
        std::cout << "  - Este ModernUniqueDevice copy-assignable?    " 
                  << (std::is_copy_assignable<ModernUniqueDevice>::value ? "DA" : "NU (Blocat de '= delete'!)") << "\n";
        std::cout << "  - Este ModernUniqueDevice move-constructible? " 
                  << (std::is_move_constructible<ModernUniqueDevice>::value ? "DA (Permis prin '= default')" : "NU") << "\n";
    }

} // namespace Item6
