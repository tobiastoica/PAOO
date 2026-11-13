# Lucrare 1: Descrierea Mediului de Lucru și Utilizarea Sistemului de Versionare

## Obiective
* Configurarea mediului de lucru pe o platformă Linux (WSL / Mașină Virtuală).
* Verificarea instrumentelor de dezvoltare: `gcc`/`g++`, `cmake`, `git`.
* Configurarea sistemului de versionare Git și a contului GitHub.
* Familiarizarea cu structura de proiecte C++ și ciclul de build.

## Cerințe Laborator
1. **Platformă Linux:** Utilizare Ubuntu 22.04 LTS via WSL2.
2. **Compilator:** `g++` (versiunea 11.4+ cu suport C++14/C++17).
3. **Build System:** `cmake` (versiunea 3.22+).
4. **Versionare:** Git, conectat la depozitul la distanță de pe GitHub.
5. **IDE:** Visual Studio Code.

## Program de Test
Proiectul include un mic program C++ (`src/main.cpp`) care afișează informații despre mediul de execuție:
* Versiunea standardului C++ utilizat (`__cplusplus`).
* Versiunea compilatorului GCC (`__GNUC__`, `__GNUC_MINOR__`).
* Sistemul de operare detectat la compilare.

## Compilare și Rulare
Din directorul `Lucrare-01`:
```bash
cmake -B build
cmake --build build
./build/lucrare1_env_check
```
