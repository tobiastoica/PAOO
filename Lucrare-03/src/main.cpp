#include <iostream>
#include <vector>
#include <utility>
#include "DynamicBuffer.h"
#include "ShallowBufferDemo.h"

void printHeader(const std::string& title) {
    std::cout << "\n======================================================================\n";
    std::cout << "  " << title << "\n";
    std::cout << "======================================================================\n";
}

int main() {
    printHeader("PAOO - Lucrare 3 + Tema: Concepte OOP Fundamentale");

    // -------------------------------------------------------------------------
    // SUBPUNCTUL 1 & 2: Incapsulare si Protectia Invariantilor
    // -------------------------------------------------------------------------
    printHeader("1. & 2. Incapsulare si Integritatea Datelor");
    std::cout << "Se creeaza un obiect 'BufferA' cu membri privati:\n";
    DynamicBuffer bufA("BufferA", 4);
    bufA.push_back(10);
    bufA.push_back(20);
    bufA.push_back(30);
    bufA.print();

    std::cout << "Accesare securizata prin getter: bufA.get(1) = " << bufA.get(1) << "\n";
    std::cout << "Modificare securizata prin setter: bufA.set(1, 25);\n";
    bufA.set(1, 25);
    bufA.print();

    std::cout << "Incercare de acces la un index invalid (bufA.get(99)):\n";
    try {
        bufA.get(99);
    } catch (const std::exception& e) {
        std::cout << "  [Exceptie prinsa conform incapsularii]: " << e.what() << "\n";
    }

    // -------------------------------------------------------------------------
    // SUBPUNCTUL 3: Initializarea Membrilor din Constructor (Member Initializer List)
    // -------------------------------------------------------------------------
    printHeader("3. Initializarea Membrilor din Constructor");
    std::cout << "Clasa DynamicBuffer utilizeaza LISTA DE INITIALIZARE A MEMBRILOR:\n";
    std::cout << "  DynamicBuffer(const char* tag, size_t capacity)\n";
    std::cout << "    : m_tag(allocateAndCopyString(tag)),\n";
    std::cout << "      m_data(new int[capacity]{0}),\n";
    std::cout << "      m_size(0),\n";
    std::cout << "      m_capacity(capacity) { ... }\n\n";
    std::cout << "Beneficii majore ale listei de initializare fata de atribuire in corpul constructorului:\n";
    std::cout << "  - Eficienta: membrii sunt initializati direct o singura data (evita apelul constructorului implicit urmat de operator=).\n";
    std::cout << "  - Necesitate obligatorie: membrii 'const' si membrii referinta '&' pot fi initializati DOAR prin lista!\n";
    DynamicBuffer bufInit("InitDemo", 3);
    bufInit.push_back(100);
    bufInit.print();

    // -------------------------------------------------------------------------
    // SUBPUNCTUL 4: Eliberarea Heap-ului in Cadrul Destructorului (RAII)
    // -------------------------------------------------------------------------
    printHeader("4. Eliberarea Heap-ului in Cadrul Destructorului (RAII)");
    std::cout << "Intram intr-un bloc delimitat de scope local...\n";
    {
        std::cout << "Creem 'ScopedBuffer' in interiorul scope-ului:\n";
        DynamicBuffer scopedBuf("ScopedBuffer", 2);
        scopedBuf.push_back(7);
        scopedBuf.push_back(14);
        scopedBuf.print();
        std::cout << "Iesim din blocul delimitat de scope local...\n";
    }
    std::cout << "Destructorul a fost apelat AUTOMAT la iesirea din scope, eliberand memoria heap!\n";

    // -------------------------------------------------------------------------
    // SUBPUNCTUL 5: Suprascrierea Copy Constructor-ului (Deep Copy vs Shallow Copy)
    // -------------------------------------------------------------------------
    printHeader("5. Suprascrierea Copy Constructor-ului (Deep Copy)");
    std::cout << "A. DEEP COPY realizat prin Copy Constructor-ul suprascris in DynamicBuffer:\n";
    DynamicBuffer bufOriginal("OriginalBuffer", 3);
    bufOriginal.push_back(111);
    bufOriginal.push_back(222);
    bufOriginal.print();

    std::cout << "\nCopiem 'bufOriginal' in 'bufDeepCopy' folosind Copy Constructor:\n";
    DynamicBuffer bufDeepCopy = bufOriginal;
    bufDeepCopy.print();

    std::cout << "\nVerificare adrese heap:\n";
    std::cout << "  Adresa heap bufOriginal.m_data: " << static_cast<const void*>(bufOriginal.dataPointer()) << "\n";
    std::cout << "  Adresa heap bufDeepCopy.m_data: " << static_cast<const void*>(bufDeepCopy.dataPointer()) << "\n";

    std::cout << "\nDemonstram INDEPENDENTA obiectelor (modificam doar copia):\n";
    bufDeepCopy.set(0, 999);
    std::cout << "Dupa bufDeepCopy.set(0, 999):\n";
    std::cout << "  bufOriginal (neschimbat): "; bufOriginal.print();
    std::cout << "  bufDeepCopy (modificat):   "; bufDeepCopy.print();

    std::cout << "\nB. Ce s-ar fi intamplat daca NU suprascriam Copy Constructor-ul? (Shallow Copy):\n";
    ShallowBuffer::demonstrateShallowCopyRisks();

    // -------------------------------------------------------------------------
    // SUBPUNCTUL 6: Crearea unui Move Constructor (Move Semantics)
    // -------------------------------------------------------------------------
    printHeader("6. Crearea unui Move Constructor (Move Semantics)");
    std::cout << "Creem un obiect 'SourceBuffer' plin cu date:\n";
    DynamicBuffer sourceBuf("SourceBuffer", 10);
    for (int i = 1; i <= 5; ++i) {
        sourceBuf.push_back(i * 10);
    }
    sourceBuf.print();
    const void* sourceOriginalHeapAddr = static_cast<const void*>(sourceBuf.dataPointer());
    std::cout << "Adresa heap initiala a bufferului sursa: " << sourceOriginalHeapAddr << "\n\n";

    std::cout << "Apelam Move Constructor folosind std::move(sourceBuf):\n";
    DynamicBuffer targetBuf = std::move(sourceBuf);

    std::cout << "\nStarea dupa mutare:\n";
    std::cout << "  Obiect tinta (targetBuf) detine datele:\n";
    targetBuf.print();
    std::cout << "  Adresa heap targetBuf: " << static_cast<const void*>(targetBuf.dataPointer()) << "\n";
    std::cout << "  A fost preluat EXACT pointerul initial (" << sourceOriginalHeapAddr 
              << ") FARA nicio alocare/copiere suplimentara!\n";
    std::cout << "  Obiect sursa (sourceBuf) are acum pointer=" 
              << static_cast<const void*>(sourceBuf.dataPointer()) 
              << " si size=" << sourceBuf.size() << " (stare sigura, neutra)\n";

    printHeader("FINAL DE PROGRAM: Toti destructorii obiectelor ramase sunt apelati acum");
    return 0;
}
