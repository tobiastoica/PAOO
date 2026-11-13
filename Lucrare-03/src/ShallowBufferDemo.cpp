#include "ShallowBufferDemo.h"
#include <cstring>
#include <iostream>

ShallowBuffer::ShallowBuffer(const char* tag, int value)
    : m_tag(nullptr), m_data(new int(value)), m_size(1) {
    if (tag) {
        size_t len = std::strlen(tag) + 1;
        m_tag = new char[len];
        std::memcpy(m_tag, tag, len);
    }
    std::cout << "  [ShallowBuffer::Constructor] Creat '" << (m_tag ? m_tag : "") 
              << "' la adresa heap m_data=" << static_cast<void*>(m_data) 
              << " cu valoare=" << *m_data << "\n";
}

ShallowBuffer::~ShallowBuffer() {
    std::cout << "  [ShallowBuffer::Destructor] Eliberare pointer heap=" 
              << static_cast<void*>(m_data) << " pentru '" << (m_tag ? m_tag : "") << "'\n";
    delete m_data;
    m_data = nullptr;
    delete[] m_tag;
    m_tag = nullptr;
}

void ShallowBuffer::demonstrateShallowCopyRisks() {
    std::cout << "\n  --- DEMONSTRATIE: Ce se intampla daca NU suprascriem Copy Constructor-ul? ---\n";
    std::cout << "  Creem obiectul 'Original' cu valoarea 42...\n";
    ShallowBuffer original("Original", 42);

    std::cout << "\n  Realizam o copiere prin constructorul implicit (SHALLOW COPY): ShallowBuffer copie = original;\n";
    // Copiere implicita membru cu membru generata de compilator
    ShallowBuffer copie = original;

    std::cout << "  Adresa memorie heap original.m_data: " 
              << static_cast<const void*>(original.getDataAddress()) << "\n";
    std::cout << "  Adresa memorie heap copie.m_data:    " 
              << static_cast<const void*>(copie.getDataAddress()) << "\n";

    std::cout << "\n  [Problema 1: Pointer Aliasing / Date partajate accidental]\n";
    std::cout << "  Modificam valoarea in 'copie' la 999: copie.setValue(999);\n";
    copie.setValue(999);
    std::cout << "  Valoare original: " << original.getValue() << " (A fost alterata neintentionat din cauza partajarii pointerului!)\n";
    std::cout << "  Valoare copie:    " << copie.getValue() << "\n";

    std::cout << "\n  [Problema 2: Double Free la distrugerea obiectelor]\n";
    std::cout << "  Ambele obiecte 'original' si 'copie' detin exact aceeasi adresa de memorie pe heap (" 
              << static_cast<const void*>(original.getDataAddress()) << ").\n";
    std::cout << "  Daca ambii destructori ar incerca sa execute 'delete m_data', sistemul de operare\n";
    std::cout << "  ar declansa un semnal SIGABRT cu mesajul: 'free(): double free detected in tcache 2'!\n";
    std::cout << "  -> De aceea este OBLIGATORIU sa suprascriem Copy Constructor-ul (Deep Copy)!\n\n";

    // Pentru a permite aplicatiei sa continue demonstratiile fara a fi oprita de sistemul de operare
    // prin SIGABRT (double free), alocam un pointer separat pentru copie inainte de iesirea din scope:
    copie.m_data = new int(999);
    copie.m_tag = new char[12];
    std::strcpy(copie.m_tag, "Copie_Fix");
}
