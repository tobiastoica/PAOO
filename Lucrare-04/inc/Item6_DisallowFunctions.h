#ifndef ITEM6_DISALLOW_FUNCTIONS_H
#define ITEM6_DISALLOW_FUNCTIONS_H

#include <string>
#include <iostream>

namespace Item6 {

    /**
     * @brief Abordarea clasica Effective C++ (Scott Meyers - C++98/03):
     * Clasa de baza Uncopyable declara copy constructor-ul si copy assignment operator
     * in sectiunea 'private', fara implementare (fara corp de functie).
     */
    class Uncopyable {
    protected:
        Uncopyable() {}   // Permite derivatilor sa se construiasca
        ~Uncopyable() {}  // si sa se distruga
    private:
        Uncopyable(const Uncopyable&);            // Declarat private, neimplementat
        Uncopyable& operator=(const Uncopyable&); // Declarat private, neimplementat
    };

    /**
     * @brief Clasa HomeForSale: Mosteneste privat clasa Uncopyable.
     * Orice incercare de copiere va esua la compilare!
     */
    class HomeForSale : private Uncopyable {
    private:
        std::string m_address;
        double m_price;
    public:
        HomeForSale(const std::string& address, double price);
        void print() const;
    };

    /**
     * @brief Abordarea moderna (C++11 si ulterioare):
     * Utilizarea specificatorului '= delete;'
     */
    class ModernUniqueDevice {
    private:
        int m_deviceId;
        std::string m_hardwarePort;

    public:
        ModernUniqueDevice(int id, const std::string& port);

        // Dezactivare explicita a operatiilor de copiere prin '= delete'
        ModernUniqueDevice(const ModernUniqueDevice&) = delete;
        ModernUniqueDevice& operator=(const ModernUniqueDevice&) = delete;

        // Mutarea poate ramane permisa daca este de dorit
        ModernUniqueDevice(ModernUniqueDevice&&) noexcept = default;
        ModernUniqueDevice& operator=(ModernUniqueDevice&&) noexcept = default;

        void print() const;
    };

    void runDemo();

} // namespace Item6

#endif // ITEM6_DISALLOW_FUNCTIONS_H
