# Lucrare 4: Effective C++ (Items 4, 5, 6)

## Cerințe
Implementarea unui proiect C++ care acoperă principalele probleme descrise în următoarele item-uri din cartea **Effective C++** de Scott Meyers:
* **Item 4:** *Make sure that objects are initialized before they're used.*
* **Item 5:** *Know what functions C++ silently writes and calls.*
* **Item 6:** *Explicitly disallow the use of compiler-generated functions you do not want.*

## Structura Proiectului
```
Lucrare-04/
├── CMakeLists.txt                  # Configurare CMake
├── inc/
│   ├── Item4_Initialization.h      # Declarații pentru Item 4
│   ├── Item5_SilentlyGenerated.h   # Declarații pentru Item 5
│   └── Item6_DisallowFunctions.h   # Declarații pentru Item 6
└── src/
    ├── Item4_Initialization.cpp    # Implementare Item 4
    ├── Item5_SilentlyGenerated.cpp # Implementare Item 5
    ├── Item6_DisallowFunctions.cpp # Implementare Item 6
    └── main.cpp                    # Punctul de intrare și rularea demonstrațiilor
```

## Concepte Abordate în Detaliu

### Item 4: Asigurarea inițializării obiectelor înainte de utilizare
1. **Tipuri primitive (built-in):** În C++, citirea variabilelor primitive neinițializate duce la comportament nedefinit (valori reziduale din memorie).
2. **Lista de inițializare a membrilor vs. Atribuire în constructor:**
   * Atribuirea în corpul constructorului (`theName = name;`) realizează mai întâi o construcție implicită (default constructor), urmată de un apel la `operator=`.
   * Folosirea listei de inițializare a constructorului (`: theName(name)`) apelează direct constructorul de copiere, eliminând pașii redundanți.
   * **Obligativitate:** Membrii declarați `const` sau referințele `Type&` **nu pot** fi atribuite ulterior în corpul constructorului; ele pot fi inițializate *exclusiv* prin lista de inițializare.
3. **Ordinea de inițializare a membrilor:**
   * Membrii sunt inițializați în ordinea în care sunt **declarați în clasă**, nu în ordinea în care apar în lista constructorului.
4. **Static Initialization Order Fiasco:**
   * Ordinea de inițializare a obiectelor statice non-locale definite în unități de translație diferite nu este specificată de standardul C++.
   * **Soluția Scott Meyers:** Utilizarea unui obiect static local într-o funcție ("Construct on first use" idiom / Meyers' Singleton):
     ```cpp
     FileSystem& FileSystem::instance() {
         static FileSystem s_instance;
         return s_instance;
     }
     ```

### Item 5: Ce funcții generează și apelează C++ în mod silențios
Compilatorul C++ generează automat următoarele funcții inline publice dacă acestea nu sunt declarate explicit de programator:
1. Default constructor
2. Copy constructor
3. Copy assignment operator (`operator=`)
4. Destructor
* **Refuzul compilatorului de a genera `operator=`:**
  Dacă o clasă conține un membru referință (`&`) sau un membru constant (`const`), compilatorul refuză generarea operatorului de atribuire deoarece referințele nu pot fi re-legate, iar constantele nu pot fi modificate. Proiectul demonstrează acest lucru prin trăsături de tip la compilare (`std::is_copy_assignable`).

### Item 6: Interzicerea explicită a funcțiilor generate nedorite
Pentru clase care reprezintă resurse unice (conexiuni, fișiere, mutex-uri):
1. **Metoda clasică Scott Meyers (C++98/03):**
   * Declararea constructorului de copiere și a `operator=` ca fiind `private` și **fără implementare**.
   * Crearea unei clase de bază `Uncopyable` din care clasa derivă privat. Orice tentativă de copiere este oprită direct la compilare.
2. **Metoda modernă C++ (C++11+):**
   * Folosirea specificatorului `= delete;`:
     ```cpp
     ModernUniqueDevice(const ModernUniqueDevice&) = delete;
     ModernUniqueDevice& operator=(const ModernUniqueDevice&) = delete;
     ```

## Compilare și Rulare
```bash
cmake -B build
cmake --build build
./build/lucrare4_effective_cpp
```
