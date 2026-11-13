# Lucrare 5: Effective C++ (Items 10, 11, 12)

## Cerințe
Implementarea unui proiect C++ care acoperă principalele probleme descrise în următoarele item-uri din cartea **Effective C++** de Scott Meyers:
* **Item 10:** *Have assignment operators return a reference to `*this`.*
* **Item 11:** *Handle assignment to self in `operator=`.*
* **Item 12:** *Copy all parts of an object.*

## Structura Proiectului
```
Lucrare-05/
├── CMakeLists.txt                      # Configurare CMake
├── inc/
│   ├── Item10_AssignmentReturnThis.h   # Declarații Item 10
│   ├── Item11_SelfAssignment.h         # Declarații Item 11
│   └── Item12_CopyAllParts.h           # Declarații Item 12
└── src/
    ├── Item10_AssignmentReturnThis.cpp # Implementare Item 10
    ├── Item11_SelfAssignment.cpp       # Implementare Item 11
    ├── Item12_CopyAllParts.cpp         # Implementare Item 12
    └── main.cpp                        # Punctul de intrare și demonstrații
```

## Concepte Abordate în Detaliu

### Item 10: Operatorii de atribuire trebuie să returneze o referință la `*this`
* **Convenția standard C++:** Toți operatorii de atribuire (`=`, `+=`, `-=`, `*=`, `/=` etc.) trebuie să returneze o referință la obiectul din partea stângă:
  ```cpp
  Widget& operator=(const Widget& rhs) {
      ...
      return *this;
  }
  ```
* **Motive:**
  * Permite înlănțuirea atribuirilor (ex: `x = y = z = 42;`), fiind evaluate conform asociativității de la dreapta la stânga: `x = (y = (z = 42))`.
  * Permite compunerea expresiilor de atribuire: `(a += 5) *= 2;`.
  * Evită copieri inutile pe care le-ar produce returnarea prin valoare (`Widget`).

### Item 11: Tratarea auto-atribuirii (assignment to self) în `operator=`
* **Pericolul auto-atribuirii:** Când un obiect este atribuit lui însuși (`w = w;` sau prin aliasuri de pointeri/referințe `*px = *py;`):
  * Dacă eliberează resursa alocată pe heap (`delete pb;`) înainte de a aloca și copia noua resursă (`new Bitmap(*rhs.pb)`), își distruge propria sursă de date! Obiectul va citi memorie deja dealocată, ducând la corupere de date sau crash.
* **Soluții demonstrate:**
  1. **Testul de identitate (Identity test):**
     ```cpp
     if (this == &rhs) return *this;
     ```
  2. **Secvențiere sigură la excepții (Exception-safe ordering):**
     Reținerea vechiului pointer, alocarea noii resurse și doar după succesul alocării se apelează `delete` pe vechea resursă.
  3. **Idiomul Copy-and-Swap:**
     Primirea parametrului prin valoare (`operator=(Widget rhs)`) și interschimbarea stării prin `swap(*this, rhs);`. Asigură automat siguranță deplină la auto-atribuire și la excepții.

### Item 12: Copierea tuturor părților unui obiect
* **Problema:** Compilatorul nu avertizează programatorul dacă într-o funcție de copiere personalizată a omis copierea unui membru de date.
* **Cazul cel mai frecvent întâlnit - Moștenirea:**
  Când o clasă derivată (`PriorityCustomer`) își suprascrie copy constructor-ul sau `operator=`:
  * Dacă omite apelul constructorului de copiere din clasa de bază în lista de inițializare (`: Customer(rhs)`), compilatorul va apela constructorul **implicit** `Customer()`, resetând datele moștenite la valorile default!
  * Dacă omite apelul `Customer::operator=(rhs);` în cadrul propriului `operator=`, componentele din clasa de bază nu vor fi actualizate la atribuire.
* **Regula:**
  * În constructorul de copiere al clasei derivate, apelați întotdeauna constructorul de copiere al clasei de bază:
    ```cpp
    Derived::Derived(const Derived& rhs) : Base(rhs), m_derivedData(rhs.m_derivedData) {}
    ```
  * În operatorul de atribuire al clasei derivate, apelați întotdeauna operatorul de atribuire al clasei de bază:
    ```cpp
    Derived& Derived::operator=(const Derived& rhs) {
        Base::operator=(rhs);
        m_derivedData = rhs.m_derivedData;
        return *this;
    }
    ```

## Compilare și Rulare
```bash
cmake -B build
cmake --build build
./build/lucrare5_effective_cpp
```
