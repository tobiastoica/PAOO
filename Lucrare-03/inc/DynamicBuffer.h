#ifndef DYNAMIC_BUFFER_H
#define DYNAMIC_BUFFER_H

#include <cstddef>
#include <iostream>

/**
 * @brief Clasa DynamicBuffer demonstreaza conceptele esentiale de OOP:
 * 1. Incapsulare (membri privati, validare invarianti)
 * 2. Initializarea membrilor prin lista de initializare in constructor
 * 3. Eliberarea resurselor alocate pe heap in cadrul destructorului (RAII)
 * 4. Suprascrierea Copy Constructor-ului pentru realizarea de Deep Copy
 * 5. Implementarea Move Constructor-ului pentru transferul eficient al resurselor (Move Semantics)
 */
class DynamicBuffer {
private:
    char* m_tag;         // Sir de caractere alocat pe heap pentru eticheta
    int* m_data;         // Buffer de intregi alocat dinamic pe heap
    size_t m_size;       // Numarul curent de elemente stocate
    size_t m_capacity;   // Capacitatea maxima alocata

    // Functie auxiliara privata pentru copiere sir de caractere pe heap
    static char* allocateAndCopyString(const char* src);

public:
    // 1. Constructor implicit (Default Constructor)
    DynamicBuffer();

    // 2. Constructor parametrizat cu lista de initializare a membrilor
    explicit DynamicBuffer(const char* tag, size_t capacity = 5);

    // 3. Destructor (elibereaza memoria de pe heap - RAII)
    ~DynamicBuffer();

    // 4. Copy Constructor (Deep Copy)
    DynamicBuffer(const DynamicBuffer& other);

    // Copy Assignment Operator (pentru completitudine conform Rule of 5)
    DynamicBuffer& operator=(const DynamicBuffer& other);

    // 5. Move Constructor (Move Semantics - C++11)
    DynamicBuffer(DynamicBuffer&& other) noexcept;

    // Move Assignment Operator (Rule of 5)
    DynamicBuffer& operator=(DynamicBuffer&& other) noexcept;

    // Metode publice pentru incapsulare (Getters, Mutators)
    void push_back(int value);
    int get(size_t index) const;
    void set(size_t index, int value);
    size_t size() const;
    size_t capacity() const;
    const char* tag() const;
    const int* dataPointer() const;

    void print() const;
};

#endif // DYNAMIC_BUFFER_H
