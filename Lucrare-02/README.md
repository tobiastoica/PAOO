# Lucrare 2: Utilizare CMake

## Cerințe
Conform fișei de laborator:
* Două proiecte C++ împreună cu fișierele `CMakeLists.txt` aferente.
* Primul proiect exportă o **bibliotecă statică** (`.a`) împreună cu un fișier header (`.h`).
* Al doilea proiect face uz de biblioteca statică creată de primul proiect.

## Structura Proiectului
Structura respectă recomandările din laborator:
```
Lucrare-02/
├── CMakeLists.txt              # Proiectul rădăcină (soluția CMake)
├── MathLib/                    # Proiectul 1: Biblioteca statică
│   ├── CMakeLists.txt          # Configurare add_library(MathLib STATIC ...)
│   ├── inc/
│   │   └── MathUtils.h         # Fișierul header exportat cu declarațiile
│   └── src/
│       └── MathUtils.cpp       # Implementarea funcțiilor matematice
└── App/                        # Proiectul 2: Aplicația consumatoare
    ├── CMakeLists.txt          # Configurare add_executable și target_link_libraries
    └── src/
        └── main.cpp            # Punctul de intrare (utilizează MathLib)
```

## Concepte Cheie CMake Utilizate
1. `add_subdirectory(...)`: legarea ierarhică a sub-proiectelor.
2. `add_library(${PROJECT_NAME} STATIC ${myfiles})`: compilarea bibliotecii statice `libMathLib.a`.
3. `target_include_directories(...)` cu `PUBLIC` și generatoarele de expresie `$<BUILD_INTERFACE:...>`: expunerea automată a căii către directoarele `inc/` pentru proiectele dependente.
4. `target_link_libraries(App PRIVATE MathLib)`: link-editarea bibliotecii statice în executabil.

## Compilare și Rulare (Linux / WSL)
Din directorul `Lucrare-02/`:

```bash
# 1. Generare fișiere de build
cmake -B build

# 2. Compilare soluție completă
cmake --build build

# 3. Rulare aplicație
./build/App/App
```

### Ieșire Așteptată la Execuție
```text
========================================================
  PAOO - Lucrare 2: Utilizare CMake                     
  Consumare biblioteca statica 'MathLib' in aplicatie  
========================================================
Versiune biblioteca utilizata: MathLib v1.0.0 (Static Library - PAOO)

--- 1. Operatii Vector2D ---
Vector v1: (3, 4)
Vector v2: (1, 2)
Magnitudine v1: 5
v1 normalizat: (0.6, 0.8)
Magnitudine v1 normalizat: 1
v1 + v2: (4, 6)
Produs scalar (dot product) v1 . v2: 11
Distanta intre v1 si v2: 2.82843

--- 2. Functii Utilitare Scalare ---
Factorial de 6 (6!): 720
CMMDC (gcd) intre 48 si 18: 6
Clamp valoare 15.5 in intervalul [0.0, 10.0]: 10
Interpolare liniara (lerp) de la 10.0 la 20.0 cu t = 0.25: 12.5
========================================================
Executie finalizata cu succes!
```
