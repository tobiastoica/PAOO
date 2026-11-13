#ifndef ITEM12_COPY_ALL_PARTS_H
#define ITEM12_COPY_ALL_PARTS_H

#include <iostream>
#include <string>

namespace Item12 {

    /**
     * @brief Clasa de baza Customer
     */
    class Customer {
    private:
        std::string m_name;
        std::string m_email;

    public:
        Customer(const std::string& name = "Anonim", const std::string& email = "none@mail.com");
        Customer(const Customer& rhs);
        Customer& operator=(const Customer& rhs);
        virtual ~Customer() = default;

        const std::string& getName() const { return m_name; }
        const std::string& getEmail() const { return m_email; }
        virtual void print() const;
    };

    /**
     * @brief Clasa derivata INCORRECTA:
     * Uita sa apeleze copy constructor-ul si operator= din clasa de baza!
     * Efect: Partea mostenita din Customer NU este copiata, ci ramane cu valorile default!
     */
    class BuggyPriorityCustomer : public Customer {
    private:
        int m_priority;

    public:
        BuggyPriorityCustomer(const std::string& name, const std::string& email, int priority);

        // EROARE COMUNA: Omite apelul lui Customer(rhs) in lista de initializare!
        BuggyPriorityCustomer(const BuggyPriorityCustomer& rhs);

        // EROARE COMUNA: Omite apelul Customer::operator=(rhs)!
        BuggyPriorityCustomer& operator=(const BuggyPriorityCustomer& rhs);

        void print() const override;
    };

    /**
     * @brief Clasa derivata CORECTA:
     * Conform Item 12: Copiaza explicit toate partile obiectului,
     * incluzand invocarea constructorului de copiere si a operatorului de atribuire din clasa de baza!
     */
    class CorrectPriorityCustomer : public Customer {
    private:
        int m_priority;

    public:
        CorrectPriorityCustomer(const std::string& name, const std::string& email, int priority);

        // CORECT: Apeleaza Customer(rhs) in lista de initializare!
        CorrectPriorityCustomer(const CorrectPriorityCustomer& rhs);

        // CORECT: Apeleaza Customer::operator=(rhs)!
        CorrectPriorityCustomer& operator=(const CorrectPriorityCustomer& rhs);

        void print() const override;
    };

    void runDemo();

} // namespace Item12

#endif // ITEM12_COPY_ALL_PARTS_H
