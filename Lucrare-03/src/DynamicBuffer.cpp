#include "DynamicBuffer.h"
#include <cstring>
#include <stdexcept>
#include <utility>

char* DynamicBuffer::allocateAndCopyString(const char* src) {
    if (!src) return nullptr;
    size_t len = std::strlen(src) + 1;
    char* dest = new char[len];
    std::memcpy(dest, src, len);
    return dest;
}

// 1. Constructor implicit
DynamicBuffer::DynamicBuffer()
    : m_tag(allocateAndCopyString("Default")),
      m_data(new int[5]{0}),
      m_size(0),
      m_capacity(5) {
    std::cout << "  [DynamicBuffer::Constructor Implicit] Creat '" << m_tag 
              << "' la adresa heap m_data=" << static_cast<void*>(m_data) << "\n";
}

// 2. Constructor parametrizat utilizand lista de initializare a membrilor
DynamicBuffer::DynamicBuffer(const char* tag, size_t capacity)
    : m_tag(allocateAndCopyString(tag ? tag : "Unnamed")),
      m_data(capacity > 0 ? new int[capacity]{0} : nullptr),
      m_size(0),
      m_capacity(capacity) {
    std::cout << "  [DynamicBuffer::Constructor Parametrizat] Creat '" << m_tag 
              << "' (cap=" << m_capacity << ") la adresa heap m_data=" 
              << static_cast<void*>(m_data) << "\n";
}

// 3. Destructor - eliberarea resurselor de pe heap (RAII)
DynamicBuffer::~DynamicBuffer() {
    std::cout << "  [DynamicBuffer::Destructor] Eliberare memorie pentru '" 
              << (m_tag ? m_tag : "nullptr") 
              << "' (heap m_data=" << static_cast<void*>(m_data) << ")\n";

    delete[] m_data;
    m_data = nullptr;

    delete[] m_tag;
    m_tag = nullptr;

    m_size = 0;
    m_capacity = 0;
}

// 4. Suprascrierea Copy Constructor-ului (DEEP COPY)
DynamicBuffer::DynamicBuffer(const DynamicBuffer& other)
    : m_tag(nullptr),
      m_data(nullptr),
      m_size(other.m_size),
      m_capacity(other.m_capacity) {
    
    // Alocam memorie noua pe heap pentru eticheta si copiem continutul
    if (other.m_tag) {
        size_t len = std::strlen(other.m_tag) + 10;
        m_tag = new char[len];
        std::snprintf(m_tag, len, "%s_copy", other.m_tag);
    }

    // Alocam un buffer complet nou pe heap (DEEP COPY)
    if (m_capacity > 0) {
        m_data = new int[m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }

    std::cout << "  [DynamicBuffer::Copy Constructor (DEEP COPY)] Copiat din '" 
              << (other.m_tag ? other.m_tag : "nullptr") << "' (src heap=" << static_cast<void*>(other.m_data) 
              << ") -> Nou obiect '" << m_tag << "' (nou heap=" << static_cast<void*>(m_data) << ")\n";
}

// Copy Assignment Operator
DynamicBuffer& DynamicBuffer::operator=(const DynamicBuffer& other) {
    std::cout << "  [DynamicBuffer::Copy Assignment Operator] Atribuire din '" 
              << other.m_tag << "' in '" << m_tag << "'\n";
    if (this == &other) {
        return *this; // Protectie auto-atribuire
    }

    // Eliberam vechea memorie
    delete[] m_data;
    delete[] m_tag;

    // Alocam si copiem
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_tag = allocateAndCopyString(other.m_tag);
    m_data = m_capacity > 0 ? new int[m_capacity] : nullptr;
    for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
    }
    return *this;
}

// 5. Move Constructor (Move Semantics - transferul proprietatii resurselor)
DynamicBuffer::DynamicBuffer(DynamicBuffer&& other) noexcept
    : m_tag(other.m_tag),
      m_data(other.m_data),
      m_size(other.m_size),
      m_capacity(other.m_capacity) {
    
    std::cout << "  [DynamicBuffer::Move Constructor] Mutat resurse de la obiectul sursa '" 
              << (other.m_tag ? other.m_tag : "nullptr") 
              << "' (heap=" << static_cast<void*>(m_data) 
              << ") catre noul obiect. Sursa este golita (nullptr).\n";

    // "Furam" pointerii si resetam starea obiectului sursa
    // Astfel destructorul obiectului sursa nu va elibera memoria acum detinuta de this!
    other.m_tag = nullptr;
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

// Move Assignment Operator
DynamicBuffer& DynamicBuffer::operator=(DynamicBuffer&& other) noexcept {
    std::cout << "  [DynamicBuffer::Move Assignment] Transfer de resurse prin mutare\n";
    if (this == &other) {
        return *this;
    }

    delete[] m_data;
    delete[] m_tag;

    m_tag = other.m_tag;
    m_data = other.m_data;
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    other.m_tag = nullptr;
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;

    return *this;
}

// Metode pentru incapsulare
void DynamicBuffer::push_back(int value) {
    if (m_size >= m_capacity) {
        // Redimensionare simpla a bufferului daca e plin
        size_t newCap = (m_capacity == 0) ? 2 : m_capacity * 2;
        int* newData = new int[newCap];
        for (size_t i = 0; i < m_size; ++i) {
            newData[i] = m_data[i];
        }
        delete[] m_data;
        m_data = newData;
        m_capacity = newCap;
    }
    m_data[m_size++] = value;
}

int DynamicBuffer::get(size_t index) const {
    if (index >= m_size) {
        throw std::out_of_range("Index in afara limitelor in DynamicBuffer!");
    }
    return m_data[index];
}

void DynamicBuffer::set(size_t index, int value) {
    if (index >= m_size) {
        throw std::out_of_range("Index in afara limitelor in DynamicBuffer!");
    }
    m_data[index] = value;
}

size_t DynamicBuffer::size() const { return m_size; }
size_t DynamicBuffer::capacity() const { return m_capacity; }
const char* DynamicBuffer::tag() const { return m_tag ? m_tag : ""; }
const int* DynamicBuffer::dataPointer() const { return m_data; }

void DynamicBuffer::print() const {
    std::cout << "    [Buffer '" << (m_tag ? m_tag : "nullptr") << "' la " 
              << static_cast<const void*>(m_data) << ", size=" << m_size 
              << ", cap=" << m_capacity << "]: [ ";
    for (size_t i = 0; i < m_size; ++i) {
        std::cout << m_data[i] << " ";
    }
    std::cout << "]\n";
}
