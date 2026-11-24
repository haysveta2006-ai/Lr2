#include "SIGNArray.h"
#include <stdexcept>
#include <iostream>

SIGNArray::SIGNArray()
    : data(nullptr), size(0), capacity(0) {
    std::cout << "SIGNArray(): default constructor\n";
}

SIGNArray::SIGNArray(const SIGNArray& other)
    : data(nullptr), size(0), capacity(0) {
    std::cout << "SIGNArray(const SIGNArray&): copy constructor\n";
    if (other.size > 0) {
        capacity = other.size;
        data = new SIGN[capacity];
        size = other.size;
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }
}

SIGNArray::~SIGNArray() {
    std::cout << "~SIGNArray(): destructor\n";
    delete[] data;
}

SIGNArray& SIGNArray::operator=(const SIGNArray& other) {
    std::cout << "SIGNArray::operator=\n";
    if (this != &other) {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
        if (other.size > 0) {
            capacity = other.size;
            data = new SIGN[capacity];
            size = other.size;
            for (int i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
    }
    return *this;
}

void SIGNArray::reserve(int newCapacity) {
    if (newCapacity <= capacity) return;
    SIGN* newData = new SIGN[newCapacity];
    for (int i = 0; i < size; ++i)
        newData[i] = data[i];
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

int SIGNArray::getSize() const { return size; }

void SIGNArray::add(const SIGN& s) {
    if (size == capacity) reserve(capacity == 0 ? 4 : capacity * 2);
    data[size] = s;
    ++size;
}

void SIGNArray::insertAt(int index, const SIGN& s) {
    if (index < 0 || index > size) throw std::out_of_range("insertAt: index out of bounds");
    if (size == capacity) reserve(capacity == 0 ? 4 : capacity * 2);
    for (int i = size; i > index; --i)
        data[i] = data[i - 1];
    data[index] = s;
    ++size;
}

void SIGNArray::removeAt(int index) {
    if (index < 0 || index >= size) throw std::out_of_range("removeAt: index out of bounds");
    for (int i = index; i < size - 1; ++i)
        data[i] = data[i + 1];
    --size;
}

SIGN& SIGNArray::at(int index) {
    if (index < 0 || index >= size) throw std::out_of_range("at: index out of bounds");
    return data[index];
}

const SIGN& SIGNArray::at(int index) const {
    if (index < 0 || index >= size) throw std::out_of_range("at const: index out of bounds");
    return data[index];
}

void SIGNArray::editAt(int index, const SIGN& s) {
    if (index < 0 || index >= size) throw std::out_of_range("editAt: index out of bounds");
    data[index] = s;
}

void SIGNArray::sortByBirthDate() {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1 - i; ++j) {
            if (data[j + 1] < data[j]) {
                SIGN tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
        }
    }
}

int SIGNArray::findBySurname(const char* surname) const {
    for (int i = 0; i < size; ++i) {
        if (data[i].surnameEquals(surname)) return i;
    }
    return -1;
}

void SIGNArray::printAll(std::ostream& os) const {
    if (size == 0) {
        os << "List is empty.\n";
        return;
    }
    for (int i = 0; i < size; ++i) {
        os << i << ": " << data[i] << "\n";
    }
}