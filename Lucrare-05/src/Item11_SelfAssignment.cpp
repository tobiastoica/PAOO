#include "Item11_SelfAssignment.h"
#include <utility>

namespace Item11 {

    // --- UnsafeWidget ---
    UnsafeWidget::UnsafeWidget(const std::string& name, const std::string& text)
        : pb(new Bitmap(text)), m_name(name) {}

    UnsafeWidget::~UnsafeWidget() {
        delete pb;
        pb = nullptr;
    }

    UnsafeWidget::UnsafeWidget(const UnsafeWidget& rhs)
        : pb(rhs.pb ? new Bitmap(*rhs.pb) : nullptr), m_name(rhs.m_name + "_copy") {}

    UnsafeWidget& UnsafeWidget::operator=(const UnsafeWidget& rhs) {
        std::cout << "    [UnsafeWidget::operator=] ATENTIE: Se elibereaza vechea resursa FARA verificare de auto-atribuire!\n";
        // GRESIT: Daca this == &rhs, stergem 'pb' care este si 'rhs.pb'!
        delete pb;
        // In acest punct, rhs.pb este un dangling pointer invalid!
        // Urmatoarea alocare citeste memorie deja eliberata:
        pb = new Bitmap(*rhs.pb);
        return *this;
    }

    void UnsafeWidget::print() const {
        std::cout << "    [UnsafeWidget '" << m_name << "'] Bitmap data: '" 
                  << (pb ? pb->getData() : "nullptr") << "'\n";
    }

    // --- SafeWidgetIdentity ---
    SafeWidgetIdentity::SafeWidgetIdentity(const std::string& name, const std::string& text)
        : pb(new Bitmap(text)), m_name(name) {}

    SafeWidgetIdentity::~SafeWidgetIdentity() {
        delete pb;
        pb = nullptr;
    }

    SafeWidgetIdentity::SafeWidgetIdentity(const SafeWidgetIdentity& rhs)
        : pb(rhs.pb ? new Bitmap(*rhs.pb) : nullptr), m_name(rhs.m_name) {}

    SafeWidgetIdentity& SafeWidgetIdentity::operator=(const SafeWidgetIdentity& rhs) {
        std::cout << "    [SafeWidgetIdentity::operator=] Verificare test de identitate (this == &rhs)...\n";
        if (this == &rhs) {
            std::cout << "    -> Auto-atribuire detectata! Se returneaza imediat *this fara a corupe datele.\n";
            return *this;
        }

        // De asemenea realizat in mod sigur la exceptii:
        Bitmap* pOrig = pb;
        pb = new Bitmap(*rhs.pb);
        delete pOrig;
        m_name = rhs.m_name;
        return *this;
    }

    void SafeWidgetIdentity::print() const {
        std::cout << "    [SafeWidgetIdentity '" << m_name << "'] Bitmap data: '" 
                  << (pb ? pb->getData() : "nullptr") << "'\n";
    }

    // --- SafeWidgetCopyAndSwap ---
    SafeWidgetCopyAndSwap::SafeWidgetCopyAndSwap(const std::string& name, const std::string& text)
        : pb(new Bitmap(text)), m_name(name) {}

    SafeWidgetCopyAndSwap::~SafeWidgetCopyAndSwap() {
        delete pb;
        pb = nullptr;
    }

    SafeWidgetCopyAndSwap::SafeWidgetCopyAndSwap(const SafeWidgetCopyAndSwap& rhs)
        : pb(rhs.pb ? new Bitmap(*rhs.pb) : nullptr), m_name(rhs.m_name) {}

    void SafeWidgetCopyAndSwap::swap(SafeWidgetCopyAndSwap& other) noexcept {
        using std::swap;
        swap(this->pb, other.pb);
        swap(this->m_name, other.m_name);
    }

    // Copy-and-Swap: parametrul rhs este o copie locala
    SafeWidgetCopyAndSwap& SafeWidgetCopyAndSwap::operator=(SafeWidgetCopyAndSwap rhs) {
        std::cout << "    [SafeWidgetCopyAndSwap::operator=] Utilizare idiom Copy-and-Swap (siguranta la auto-atribuire si exceptii)\n";
        swap(rhs);
        return *this;
    }

    void SafeWidgetCopyAndSwap::print() const {
        std::cout << "    [SafeWidgetCopyAndSwap '" << m_name << "'] Bitmap data: '" 
                  << (pb ? pb->getData() : "nullptr") << "'\n";
    }

    void runDemo() {
        std::cout << "\n--- DEMONSTRATIE ITEM 11: Tratarea corecta a auto-atribuirii in operator= ---\n";

        std::cout << "\n1. Problema: De ce auto-atribuirea este periculoasa?\n";
        std::cout << "  Cand un obiect se atribuie siesi (ex: w = w, sau prin aliasuri *p1 = *p2),\n";
        std::cout << "  daca elibereaza pointerul intern inainte de a-l copia, isi distruge propria sursa!\n";

        std::cout << "\n2. Solutia 1: Testul de identitate (Identity Test) in SafeWidgetIdentity:\n";
        SafeWidgetIdentity safeId("WidgetIdentitate", "Date_Importante_Grafice");
        safeId.print();
        std::cout << "Executam: safeId = safeId (auto-atribuire directa):\n";
        safeId = safeId;
        std::cout << "Stare dupa auto-atribuire:\n";
        safeId.print();

        std::cout << "\n3. Solutia 2 & 3: Secventiere exception-safe si Copy-and-Swap in SafeWidgetCopyAndSwap:\n";
        SafeWidgetCopyAndSwap safeCS("WidgetCopySwap", "Texturi_Rendering_3D");
        safeCS.print();
        std::cout << "Executam: safeCS = safeCS:\n";
        safeCS = safeCS;
        std::cout << "Stare dupa auto-atribuire prin Copy-and-Swap:\n";
        safeCS.print();
    }

} // namespace Item11
