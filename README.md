# Proiectarea Aplicațiilor Orientate pe Obiecte (PAOO)

Acest repository conține rezolvarea și testarea lucrărilor practice și temelor de laborator pentru disciplina **Proiectarea Aplicațiilor Orientate pe Obiecte (PAOO)** din cadrul Universității Politehnica Timișoara (UPT).

**Student:** Stoica Tobias  
**GitHub:** [tobiastoica/PAOO](https://github.com/tobiastoica/PAOO)

---

## 🛠️ Mediu de Lucru și Tehnologii

* **Sistem de Operare:** Linux (Ubuntu 22.04 LTS via WSL2 / Mașină Virtuală)
* **Compilator:** GCC / G++ (suport C++11, C++14, C++17, C++20)
* **Build System:** CMake (versiunea >= 3.2)
* **Controlul Versiunilor:** Git & GitHub
* **IDE / Editor:** Visual Studio Code

---

## 📁 Structura Repository-ului

| Director | Denumire Lucrare | Descriere / Concepte Cheie |
| :--- | :--- | :--- |
| [`Lucrare-01/`](Lucrare-01/) | **Lucrare 1: Mediu de lucru și Git** | Descrierea mediului de lucru (Linux, GCC, CMake, Git), configurare repository și verificare compilare. |
| [`Lucrare-02/`](Lucrare-02/) | **Lucrare 2: Utilizare CMake** | Structură multi-proiect cu CMake: exportarea unei biblioteci statice (`.a`) cu fișier header (`.h`) și consumarea acesteia într-o aplicație executabilă. |
| [`Lucrare-03/`](Lucrare-03/) | **Lucrare 3: Concepte OOP Fundamentale** | Încapsulare, lista de inițializare a membrilor, managementul memoriei heap în destructor (RAII), copy constructor (deep copy) și move constructor (move semantics). |
| [`Lucrare-04/`](Lucrare-04/) | **Lucrare 4: Effective C++ (Items 4, 5, 6)** | Scott Meyers Effective C++: Inițializarea corectă a obiectelor (Item 4), Funcțiile generate automat de compilator (Item 5), Interzicerea copierii (Item 6). |
| [`Lucrare-05/`](Lucrare-05/) | **Lucrare 5: Effective C++ (Items 10, 11, 12)** | Scott Meyers Effective C++: Returnarea referinței la `*this` în operatorii de atribuire (Item 10), Gestionarea auto-atribuirii (Item 11), Copierea completă a părților unui obiect (Item 12). |

---

## 🚀 Instrucțiuni Generale de Compilare și Rulare

Pentru a construi oricare dintre proiecte, deschideți un terminal Linux / WSL în folderul lucrării dorite și rulați:

```bash
# 1. Configurare proiect prin CMake
cmake -B build

# 2. Compilare executabile
cmake --build build

# 3. Rulare
./build/<nume_executabil>
```
