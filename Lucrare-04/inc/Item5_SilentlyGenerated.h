#ifndef ITEM5_SILENTLY_GENERATED_H
#define ITEM5_SILENTLY_GENERATED_H

#include <string>
#include <iostream>

namespace Item5 {

    /**
     * @brief Clasa Empty: Compilatorul genereaza in mod silentios:
     * - Default constructor: Empty()
     * - Copy constructor: Empty(const Empty&)
     * - Destructor: ~Empty()
     * - Copy assignment operator: Empty& operator=(const Empty&)
     */
    class Empty {
        // Niciun membru sau functie declarata explicit
    };

    /**
     * @brief Clasa SimpleObject: Demonstreaza apelul silentios al functiilor generate
     */
    class SimpleObject {
    public:
        int id;
        std::string name;
        SimpleObject(int i, const std::string& n) : id(i), name(n) {}
        // Copy constructor si copy assignment sunt generate automat de compilator
    };

    /**
     * @brief Clasa RefAndConstHolder:
     * Contine o referinta '&' si un membru 'const'.
     * In acest caz, compilatorul C++ REFUZA sa genereze automat 'operator='
     * deoarece referintele nu pot fi re-legate la alt obiect si variabilele const nu pot fi modificate!
     */
    template <typename T>
    class NamedRef {
    private:
        std::string& nameValue; // Referinta la string (nu poate fi re-legata!)
        const T objectValue;    // Membru const (nu poate fi modificat!)

    public:
        NamedRef(std::string& name, const T& value)
            : nameValue(name), objectValue(value) {}

        void print() const {
            std::cout << "    [NamedRef] nameValue='" << nameValue 
                      << "', objectValue=" << objectValue << "\n";
        }

        // Daca un utilizator ar apela: obj1 = obj2;
        // Compilatorul va refuza sa compileze codul deoarece operator= este implicit sters!
    };

    void runDemo();

} // namespace Item5

#endif // ITEM5_SILENTLY_GENERATED_H
