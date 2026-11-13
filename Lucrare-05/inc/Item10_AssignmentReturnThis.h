#ifndef ITEM10_ASSIGNMENT_RETURN_THIS_H
#define ITEM10_ASSIGNMENT_RETURN_THIS_H

#include <iostream>
#include <string>

namespace Item10 {

    /**
     * @brief Item 10: Operatorii de atribuire trebuie sa returneze o referinta la *this.
     * Aceasta conventie se aplica pentru =, +=, -=, *= etc.
     */
    class ChainedValue {
    private:
        int m_val;
        std::string m_name;

    public:
        ChainedValue(int val = 0, const std::string& name = "anonim");

        // Operator de atribuire standard care returneaza Type& (*this)
        ChainedValue& operator=(const ChainedValue& rhs);

        // Operatori compusi care returneaza Type& (*this)
        ChainedValue& operator+=(const ChainedValue& rhs);
        ChainedValue& operator+=(int delta);
        ChainedValue& operator*=(int factor);

        int getVal() const { return m_val; }
        const std::string& getName() const { return m_name; }

        void print() const;
    };

    void runDemo();

} // namespace Item10

#endif // ITEM10_ASSIGNMENT_RETURN_THIS_H
