#ifndef SHALLOW_BUFFER_DEMO_H
#define SHALLOW_BUFFER_DEMO_H

#include <iostream>

/**
 * @brief Clasa de demonstratie pentru Shallow Copy (Copiere Superficiala).
 * Nu suprascrie Copy Constructor-ul (foloseste cel generat implicit de compilator).
 * Este folosita pentru a arata clar de ce este necesara suprascrierea Copy Constructor-ului.
 */
class ShallowBuffer {
private:
    char* m_tag;
    int* m_data;
    size_t m_size;

public:
    ShallowBuffer(const char* tag, int value);
    
    // Destructor standard care elibereaza heap-ul
    // Daca nu se controleaza copierea, va cauza DOUBLE FREE!
    ~ShallowBuffer();

    // Getter pentru adresa pointerului de pe heap
    const int* getDataAddress() const { return m_data; }
    int getValue() const { return m_data ? *m_data : 0; }
    void setValue(int val) { if (m_data) *m_data = val; }
    const char* getTag() const { return m_tag; }

    // Functie statica pentru a rula demonstratia riscurilor Shallow Copy
    static void demonstrateShallowCopyRisks();
};

#endif // SHALLOW_BUFFER_DEMO_H
