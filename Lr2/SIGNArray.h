#ifndef SIGNARRAY_H
#define SIGNARRAY_H

#include "SIGN.h"
#include <iostream>

class SIGNArray {
private:
    SIGN* data;
    int size;
    int capacity;

    void reserve(int newCapacity);

public:
    SIGNArray();
    SIGNArray(const SIGNArray& other);
    ~SIGNArray();

    SIGNArray& operator=(const SIGNArray& other);

    int getSize() const;

    void add(const SIGN& s);
    void insertAt(int index, const SIGN& s);
    void removeAt(int index);
    SIGN& at(int index);
    const SIGN& at(int index) const;
    void editAt(int index, const SIGN& s);

    void sortByBirthDate();
    int findBySurname(const char* surname) const;
    void printAll(std::ostream& os) const;
};

#endif