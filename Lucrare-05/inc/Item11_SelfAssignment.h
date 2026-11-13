#ifndef ITEM11_SELF_ASSIGNMENT_H
#define ITEM11_SELF_ASSIGNMENT_H

#include <iostream>
#include <string>

namespace Item11 {

    // Resursa gestionata dinamic (simulare Bitmap din cartea lui Scott Meyers)
    class Bitmap {
    private:
        std::string m_data;
    public:
        Bitmap(const std::string& data = "") : m_data(data) {}
        const std::string& getData() const { return m_data; }
        void setData(const std::string& data) { m_data = data; }
    };

    /**
     * @brief Clasa UnsafeWidget:
     * Implementare gresita a lui operator= care NU trateaza auto-atribuirea (self-assignment).
     * Cand se face 'w = w', obiectul isi sterge propriul pointer INAINTE de a incerca sa-l copieze!
     */
    class UnsafeWidget {
    private:
        Bitmap* pb;
        std::string m_name;
    public:
        UnsafeWidget(const std::string& name, const std::string& text);
        ~UnsafeWidget();
        UnsafeWidget(const UnsafeWidget& rhs);

        // Operator nesigur: stergere inainte de alocare
        UnsafeWidget& operator=(const UnsafeWidget& rhs);

        void print() const;
    };

    /**
     * @brief Clasa SafeWidgetIdentity:
     * Solutia 1: Testul de identitate (Identity Test)
     * if (this == &rhs) return *this;
     */
    class SafeWidgetIdentity {
    private:
        Bitmap* pb;
        std::string m_name;
    public:
        SafeWidgetIdentity(const std::string& name, const std::string& text);
        ~SafeWidgetIdentity();
        SafeWidgetIdentity(const SafeWidgetIdentity& rhs);

        SafeWidgetIdentity& operator=(const SafeWidgetIdentity& rhs);

        void print() const;
    };

    /**
     * @brief Clasa SafeWidgetCopyAndSwap:
     * Solutia 2 & 3: Secventiere sigura la exceptii si Idiomul Copy-and-Swap
     */
    class SafeWidgetCopyAndSwap {
    private:
        Bitmap* pb;
        std::string m_name;
    public:
        SafeWidgetCopyAndSwap(const std::string& name, const std::string& text);
        ~SafeWidgetCopyAndSwap();
        SafeWidgetCopyAndSwap(const SafeWidgetCopyAndSwap& rhs);

        void swap(SafeWidgetCopyAndSwap& other) noexcept;

        // Copy-and-Swap idiom: parametrul rhs este primit prin valoare (creand o copie)
        SafeWidgetCopyAndSwap& operator=(SafeWidgetCopyAndSwap rhs);

        void print() const;
    };

    void runDemo();

} // namespace Item11

#endif // ITEM11_SELF_ASSIGNMENT_H
