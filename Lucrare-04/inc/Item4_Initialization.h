#ifndef ITEM4_INITIALIZATION_H
#define ITEM4_INITIALIZATION_H

#include <string>
#include <iostream>

namespace Item4 {

    // 1. Diferenta dintre initializare prin lista vs atribuire in corpul constructorului
    class BadEntry {
    private:
        std::string theName;
        std::string theAddress;
        int theNumTimesConsulted;
    public:
        // Antipattern: Atribuire in corpul constructorului (theName este mai intai
        // initializat prin constructorul sau implicit, apoi suprascris prin operator=)
        BadEntry(const std::string& name, const std::string& address);
        void print() const;
    };

    class GoodEntry {
    private:
        std::string theName;
        std::string theAddress;
        int theNumTimesConsulted;
    public:
        // Corect: Lista de initializare a membrilor (initializare directa o singura data)
        GoodEntry(const std::string& name, const std::string& address);
        void print() const;
    };

    // 2. Membri 'const' si membri referinta '&' -> Obligativitatea listei de initializare
    class ConstAndRefHolder {
    private:
        const int m_constantId;
        const std::string& m_externalRef;
        int m_value;

    public:
        // Fara lista de initializare, acest cod nici macar NU ar compila in C++!
        ConstAndRefHolder(int id, const std::string& extRef, int val);
        void print() const;
    };

    // 3. Ordinea de initializare a membrilor (declarare vs lista)
    class InitializationOrderDemo {
    private:
        // Membrii sunt initializati INTOTDEAUNA in ordinea in care sunt declarati in clasa,
        // indiferent de ordinea scrisa in lista de initializare a constructorului!
        int m_first;
        int m_second;

    public:
        InitializationOrderDemo(int val);
        void print() const;
    };

    // 4. Problema ordinii de initializare a obiectelor statice non-locale
    // si Solutia lui Scott Meyers: Singleton cu obiect static local ("Construct on first use")
    class FileSystem {
    private:
        FileSystem() {
            std::cout << "    [FileSystem] Sub-sistem initializat garantat la primul apel!\n";
        }
    public:
        static FileSystem& instance() {
            // Obiect static local: initializarea sa este garantata la prima executie a functiei
            static FileSystem s_instance;
            return s_instance;
        }
        size_t numDisks() const { return 3; }
    };

    class Directory {
    public:
        Directory();
        void printInfo() const;
    };

    void runDemo();

} // namespace Item4

#endif // ITEM4_INITIALIZATION_H
