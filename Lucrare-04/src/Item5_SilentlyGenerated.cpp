#include "Item5_SilentlyGenerated.h"
#include <type_traits>

namespace Item5 {

    void runDemo() {
        std::cout << "\n--- DEMONSTRATIE ITEM 5: Ce functii scrie si apeleaza C++ in mod silentios ---\n";

        std::cout << "\n1. Pentru clasa 'Empty', compilatorul declara si apeleaza silentios:\n";
        Empty e1;          // Apel default constructor generat automat
        Empty e2(e1);      // Apel copy constructor generat automat
        e1 = e2;           // Apel copy assignment operator generat automat
        // ~Empty()        // Apel destructor la iesirea din bloc
        std::cout << "  - Default constructor: apelat pentru Empty e1;\n";
        std::cout << "  - Copy constructor: apelat pentru Empty e2(e1);\n";
        std::cout << "  - Copy assignment operator: apelat pentru e1 = e2;\n";
        std::cout << "  - Destructor: apelat automat la final.\n";

        std::cout << "\n2. Copiere membru cu membru generata automat pentru SimpleObject:\n";
        SimpleObject obj1(1, "Senzor_Temperatura");
        SimpleObject obj2 = obj1; // Copy ctor
        SimpleObject obj3(2, "Senzor_Presiune");
        obj3 = obj1;              // Copy assignment operator
        std::cout << "    obj1: id=" << obj1.id << ", name=" << obj1.name << "\n";
        std::cout << "    obj2: id=" << obj2.id << ", name=" << obj2.name << " (dupa copy ctor)\n";
        std::cout << "    obj3: id=" << obj3.id << ", name=" << obj3.name << " (dupa operator=)\n";

        std::cout << "\n3. Cand REFUZA compilatorul sa genereze automat functiile implicite?\n";
        std::cout << "  Daca o clasa contine un membru referinta ('&') sau un membru constant ('const'),\n";
        std::cout << "  compilatorul REFUZA sa genereze 'operator='.\n";

        std::string s1 = "Linia_A";
        std::string s2 = "Linia_B";
        NamedRef<int> r1(s1, 100);
        NamedRef<int> r2(s2, 200);

        r1.print();
        r2.print();

        std::cout << "\n  Verificare la compilare (std::is_copy_assignable):\n";
        std::cout << "  - Este SimpleObject copy-assignable? " 
                  << (std::is_copy_assignable<SimpleObject>::value ? "DA (compilatorul a generat operator=)" : "NU") << "\n";
        std::cout << "  - Este NamedRef<int> copy-assignable? " 
                  << (std::is_copy_assignable<NamedRef<int>>::value ? "DA" : "NU (Compilatorul a refuzat generarea lui operator=)") << "\n";
        std::cout << "  -> Incercarea de a face 'r1 = r2;' ar produce direct eroare la compilare!\n";
    }

} // namespace Item5
