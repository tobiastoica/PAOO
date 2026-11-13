# Lucrare 3 + Temă: Concepte OOP Fundamentale în C++

## Cerințe Laborator
Aplicație scrisă în C++ care abordează următoarele subiecte:
1. **Build folosind CMake** respectând structura discutată la laborator.
2. **Încapsulare** (membri privați, acces prin metode, validare stare și invarianți).
3. **Inițializarea membrilor din constructor** (folosirea listei de inițializare a membrilor și avantajele acesteia).
4. **Eliberarea heap-ului în cadrul destructorului** (idiomul RAII - Resource Acquisition Is Initialization).
5. **Suprascrierea Copy Constructor-ului** (Deep Copy) și ilustrarea riscurilor majore ale lipsei acesteia (Shallow Copy: pointer aliasing și double free).
6. **Crearea unui Move Constructor** (Move Semantics din C++11, transferul resurselor fără copiere costisitoare).

## Structura Proiectului
```
Lucrare-03/
├── CMakeLists.txt              # Script de configurare CMake
├── inc/
│   ├── DynamicBuffer.h         # Declarația clasei DynamicBuffer (Rule of 5)
│   └── ShallowBufferDemo.h     # Declarația clasei pentru demonstrarea pericolelor Shallow Copy
└── src/
    ├── DynamicBuffer.cpp       # Implementare: constructori, destructor, deep copy, move semantics
    ├── ShallowBufferDemo.cpp   # Demonstrarea riscurilor de aliasing și double free
    └── main.cpp                # Punctul de intrare: teste reprezentative și explicative
```

## Explicații Teoretice și Practice

### 1. Încapsulare
Membrii `m_data`, `m_tag`, `m_size`, `m_capacity` sunt `private`. Modificarea și citirea lor se face exclusiv prin metode ce validează limitele (`push_back`, `set`, `get`), aruncând `std::out_of_range` în caz de acces ilegal.

### 2. Inițializarea Membrilor din Constructor (Member Initializer List)
Constructorul folosește sintaxa:
```cpp
DynamicBuffer::DynamicBuffer(const char* tag, size_t capacity)
    : m_tag(allocateAndCopyString(tag)),
      m_data(capacity > 0 ? new int[capacity]{0} : nullptr),
      m_size(0),
      m_capacity(capacity) {}
```
Avantaje:
* Inițializează membrii direct la crearea lor, evitând inițializarea implicită urmată de o reatribuire în corpul constructorului.
* Este obligatorie pentru tipuri `const` și referințe `&`.

### 3. Eliberarea Heap-ului în Destructor (RAII)
Memoria alocată dinamic pe heap prin `new[]` este eliberată garantat în destructor prin `delete[]`:
```cpp
DynamicBuffer::~DynamicBuffer() {
    delete[] m_data;
    delete[] m_tag;
}
```

### 4. Suprascrierea Copy Constructor-ului (Deep Copy vs Shallow Copy)
* **Copy Constructor generat implicit (Shallow Copy):** Copiază pointerii bit cu bit. Rezultatul este că două obiecte diferite indică spre aceeași zonă de memorie pe heap.
  * **Problema 1 (Aliasing):** Modificarea stării unui obiect modifică neintenționat și starea celuilalt.
  * **Problema 2 (Double Free Crash):** Când ambele obiecte ies din scope, ambii destructori încearcă să apeleze `delete[]` pe aceeași adresă de memorie, cauzând `SIGABRT (double free or corruption)`.
* **Copy Constructor suprascris (Deep Copy):** Alocă un bloc nou de memorie pe heap și copiază fiecare element în noul spațiu, asigurând independența deplină a obiectelor.

### 5. Move Constructor (Move Semantics)
Move constructor-ul permite transferul dreptului de proprietate asupra resurselor alocate pe heap fără a le copia:
```cpp
DynamicBuffer::DynamicBuffer(DynamicBuffer&& other) noexcept
    : m_tag(other.m_tag),
      m_data(other.m_data),
      m_size(other.m_size),
      m_capacity(other.m_capacity) {
    other.m_data = nullptr;
    other.m_tag = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}
```
Obiectul sursă `other` este lăsat într-o stare vidă dar validă, astfel încât destructorul său să nu elibereze memoria preluată de noul obiect.

## Compilare și Rulare
```bash
cmake -B build
cmake --build build
./build/lucrare3_oop_fundamentals
```
