#include "Item4_Initialization.h"

namespace Item4 {

    // BadEntry: Atribuire in corpul constructorului
    BadEntry::BadEntry(const std::string& name, const std::string& address) {
        theName = name;       // theName a fost deja initializat default, acum este apelat operator=
        theAddress = address; // theAddress a fost deja initializat default, acum este apelat operator=
        theNumTimesConsulted = 0;
    }

    void BadEntry::print() const {
        std::cout << "    [BadEntry] " << theName << ", Adresa: " << theAddress 
                  << ", Consultari: " << theNumTimesConsulted << "\n";
    }

    // GoodEntry: Lista de initializare a membrilor (Member Initialization List)
    GoodEntry::GoodEntry(const std::string& name, const std::string& address)
        : theName(name), theAddress(address), theNumTimesConsulted(0) {
        // Initializare directa a obiectelor prin copy constructor, fara constructii redundante
    }

    void GoodEntry::print() const {
        std::cout << "    [GoodEntry] " << theName << ", Adresa: " << theAddress 
                  << ", Consultari: " << theNumTimesConsulted << "\n";
    }

    // ConstAndRefHolder: Membrii const si referintele & cer obligatoriu lista de initializare
    ConstAndRefHolder::ConstAndRefHolder(int id, const std::string& extRef, int val)
        : m_constantId(id), m_externalRef(extRef), m_value(val) {
        // O referinta sau o variabila const nu pot fi atribuite ulterior in corpul constructorului!
    }

    void ConstAndRefHolder::print() const {
        std::cout << "    [ConstAndRefHolder] ID (const): " << m_constantId 
                  << ", Referinta externa: '" << m_externalRef 
                  << "', Valoare: " << m_value << "\n";
    }

    // InitializationOrderDemo: Ordinea de initializare
    // Observatie: desi in lista am putea scrie m_second(val), m_first(m_second),
    // m_first va fi initializat PRIMUL deoarece este declarat primul in clasa!
    InitializationOrderDemo::InitializationOrderDemo(int val)
        : m_first(val), m_second(m_first * 2) {
    }

    void InitializationOrderDemo::print() const {
        std::cout << "    [InitializationOrderDemo] m_first: " << m_first 
                  << ", m_second (depinde de m_first): " << m_second << "\n";
    }

    // Directory
    Directory::Directory() {
        size_t disks = FileSystem::instance().numDisks();
        std::cout << "    [Directory] Initializat folosind FileSystem (numDisks=" << disks << ")\n";
    }

    void Directory::printInfo() const {
        std::cout << "    [Directory] Director functional bazat pe Meyers' Singleton.\n";
    }

    void runDemo() {
        std::cout << "\n--- DEMONSTRATIE ITEM 4: Initializarea corecta a obiectelor inainte de utilizare ---\n";
        
        std::cout << "\n1. Comparatie intre atribuire in corpul constructorului si lista de initializare:\n";
        BadEntry bad("Ionescu Andrei", "Str. Observatorului 10");
        bad.print();

        GoodEntry good("Popescu Maria", "Bd. Vasile Parvan 2");
        good.print();

        std::cout << "\n2. Initializarea membrilor 'const' si referinte '&' (obligatorie prin lista):\n";
        std::string externalLabel = "Sursa_Configurare_Globala";
        ConstAndRefHolder holder(101, externalLabel, 42);
        holder.print();

        std::cout << "\n3. Respectarea ordinii de declarare a membrilor:\n";
        InitializationOrderDemo orderDemo(15);
        orderDemo.print();

        std::cout << "\n4. Evitarea 'Static Initialization Order Fiasco' (Scott Meyers Singleton):\n";
        Directory dir;
        dir.printInfo();
    }

} // namespace Item4
