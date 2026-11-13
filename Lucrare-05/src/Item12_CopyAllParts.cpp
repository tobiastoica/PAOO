#include "Item12_CopyAllParts.h"

namespace Item12 {

    // --- Customer ---
    Customer::Customer(const std::string& name, const std::string& email)
        : m_name(name), m_email(email) {}

    Customer::Customer(const Customer& rhs)
        : m_name(rhs.m_name), m_email(rhs.m_email) {
        std::cout << "      [Customer::Copy Constructor] Copiere date clasa de baza ('" 
                  << m_name << "', '" << m_email << "')\n";
    }

    Customer& Customer::operator=(const Customer& rhs) {
        std::cout << "      [Customer::operator=] Atribuire membrii clasa de baza\n";
        if (this != &rhs) {
            m_name = rhs.m_name;
            m_email = rhs.m_email;
        }
        return *this;
    }

    void Customer::print() const {
        std::cout << "Nume: '" << m_name << "', Email: '" << m_email << "'";
    }

    // --- BuggyPriorityCustomer (Gresit: Omite copierea clasei de baza) ---
    BuggyPriorityCustomer::BuggyPriorityCustomer(const std::string& name, const std::string& email, int priority)
        : Customer(name, email), m_priority(priority) {}

    // GRESIT: Omite apelul lui Customer(rhs)!
    // Compilatorul apeleaza automat constructorul implicit Customer(), pierzand numele si emailul!
    BuggyPriorityCustomer::BuggyPriorityCustomer(const BuggyPriorityCustomer& rhs)
        : Customer(), // Apel implicit default constructor baza!
          m_priority(rhs.m_priority) {
        std::cout << "    [BuggyPriorityCustomer::Copy Ctor] ATENTIE: S-a omis copierea partii de baza Customer!\n";
    }

    // GRESIT: Omite apelul lui Customer::operator=(rhs)!
    BuggyPriorityCustomer& BuggyPriorityCustomer::operator=(const BuggyPriorityCustomer& rhs) {
        std::cout << "    [BuggyPriorityCustomer::operator=] ATENTIE: S-a omis apelul Customer::operator=!\n";
        if (this != &rhs) {
            m_priority = rhs.m_priority;
            // EROARE: membrii mosteniti (m_name, m_email) NU sunt actualizati!
        }
        return *this;
    }

    void BuggyPriorityCustomer::print() const {
        std::cout << "    [BuggyPriorityCustomer] ";
        Customer::print();
        std::cout << ", Prioritate: " << m_priority << "\n";
    }

    // --- CorrectPriorityCustomer (Corect: Copiaza toate partile obiectului) ---
    CorrectPriorityCustomer::CorrectPriorityCustomer(const std::string& name, const std::string& email, int priority)
        : Customer(name, email), m_priority(priority) {}

    // CORECT: Apeleaza explicit copy constructor-ul din Customer
    CorrectPriorityCustomer::CorrectPriorityCustomer(const CorrectPriorityCustomer& rhs)
        : Customer(rhs), // Transmite felia de baza catre constructorul de copiere parinte
          m_priority(rhs.m_priority) {
        std::cout << "    [CorrectPriorityCustomer::Copy Ctor] Copiat cu succes baza + membrii proprii!\n";
    }

    // CORECT: Apeleaza explicit Customer::operator=(rhs)
    CorrectPriorityCustomer& CorrectPriorityCustomer::operator=(const CorrectPriorityCustomer& rhs) {
        std::cout << "    [CorrectPriorityCustomer::operator=] Atribuire completa baza + membrii proprii!\n";
        if (this != &rhs) {
            Customer::operator=(rhs); // Invocam operatorul clasei de baza
            m_priority = rhs.m_priority;
        }
        return *this;
    }

    void CorrectPriorityCustomer::print() const {
        std::cout << "    [CorrectPriorityCustomer] ";
        Customer::print();
        std::cout << ", Prioritate: " << m_priority << "\n";
    }

    void runDemo() {
        std::cout << "\n--- DEMONSTRATIE ITEM 12: Copierea tuturor partilor unui obiect ---\n";

        std::cout << "\n1. Problema copierii partiale in clase derivate (BuggyPriorityCustomer):\n";
        BuggyPriorityCustomer buggyOriginal("Stefan cel Mare", "stefan@moldova.ro", 10);
        std::cout << "Obiect original:\n";
        buggyOriginal.print();

        std::cout << "\nCreem o copie: BuggyPriorityCustomer buggyCopy = buggyOriginal;\n";
        BuggyPriorityCustomer buggyCopy = buggyOriginal;
        std::cout << "Obiectul copiat gresit:\n";
        buggyCopy.print();
        std::cout << "OBSERVATIE: Numele a redevenit 'Anonim' si emailul 'none@mail.com' deoarece\n"
                  << "            a fost apelat default constructor-ul din Customer in loc de copy constructor!\n";

        std::cout << "\n2. Implementarea CORECTA conform Item 12 (CorrectPriorityCustomer):\n";
        CorrectPriorityCustomer correctOriginal("Mircea cel Batran", "mircea@tara-romaneasca.ro", 9);
        std::cout << "Obiect original:\n";
        correctOriginal.print();

        std::cout << "\nCreem o copie: CorrectPriorityCustomer correctCopy = correctOriginal;\n";
        CorrectPriorityCustomer correctCopy = correctOriginal;
        std::cout << "Obiectul copiat corect:\n";
        correctCopy.print();

        std::cout << "\nTestare operator= corect in clasa derivata:\n";
        CorrectPriorityCustomer anotherCustomer("Vlad Tepes", "vlad@valahia.ro", 1);
        std::cout << "Inainte de atribuire:\n";
        anotherCustomer.print();
        anotherCustomer = correctOriginal;
        std::cout << "Dupa 'anotherCustomer = correctOriginal':\n";
        anotherCustomer.print();
    }

} // namespace Item12
