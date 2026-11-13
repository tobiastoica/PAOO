#include "Item10_AssignmentReturnThis.h"

namespace Item10 {

    ChainedValue::ChainedValue(int val, const std::string& name)
        : m_val(val), m_name(name) {}

    // Conform Item 10: returneaza intotdeauna o referinta la *this
    ChainedValue& ChainedValue::operator=(const ChainedValue& rhs) {
        std::cout << "    [ChainedValue::operator=] Atribuire '" << rhs.m_name 
                  << "' (val=" << rhs.m_val << ") in '" << m_name << "'\n";
        m_val = rhs.m_val;
        // Mentinem numele original al obiectului curent sau il actualizam conform specificatiei
        return *this; // Intoarcem referinta la obiectul curent stang
    }

    ChainedValue& ChainedValue::operator+=(const ChainedValue& rhs) {
        m_val += rhs.m_val;
        return *this;
    }

    ChainedValue& ChainedValue::operator+=(int delta) {
        m_val += delta;
        return *this;
    }

    ChainedValue& ChainedValue::operator*=(int factor) {
        m_val *= factor;
        return *this;
    }

    void ChainedValue::print() const {
        std::cout << "    [ChainedValue] Obiect '" << m_name << "' are valoarea: " << m_val << "\n";
    }

    void runDemo() {
        std::cout << "\n--- DEMONSTRATIE ITEM 10: Operatorii de atribuire returneaza referinta la *this ---\n";

        std::cout << "\n1. Atribuire inlantuita (Chained Assignment): x = y = z = 42\n";
        ChainedValue x(1, "x");
        ChainedValue y(2, "y");
        ChainedValue z(42, "z");

        std::cout << "Stare initiala:\n";
        x.print();
        y.print();
        z.print();

        std::cout << "\nExecutam: x = y = z;\n";
        // Asociativitate de la dreapta la stanga: x = (y = z)
        x = y = z;

        std::cout << "\nStare dupa atribuire inlantuita:\n";
        x.print();
        y.print();
        z.print();

        std::cout << "\n2. Operatori compusi inlantuiti: (a += 5) *= 2\n";
        ChainedValue a(10, "a");
        a.print();
        (a += 5) *= 2; // Datorita returnarii Type&, putem aplica un nou operator pe rezultatul returnat!
        std::cout << "Dupa (a += 5) *= 2:\n";
        a.print();
    }

} // namespace Item10
