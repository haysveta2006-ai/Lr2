#define _CRT_SECURE_NO_WARNINGS
#include "Person.h"
#include <cstring>
#include <iostream>

char* Person::copyString(const char* s) {
    if (!s) s = "";
    std::size_t len = std::strlen(s);
    char* p = new char[len + 1];
    std::strcpy(p, s);
    return p;
}

Person::Person()
    : surname(copyString("")), name(copyString("")) {
    std::cout << "Person(): default constructor\n";
}

Person::Person(const char* s, const char* n)
    : surname(copyString(s)), name(copyString(n)) {
    std::cout << "Person(const char*, const char*): parameterized constructor\n";
}

Person::Person(const Person& other)
    : surname(copyString(other.surname)), name(copyString(other.name)) {
    std::cout << "Person(const Person&): copy constructor\n";
}

Person::~Person() {
    std::cout << "~Person(): destructor for "
        << (surname ? surname : "") << " "
        << (name ? name : "") << "\n";
    delete[] surname;
    delete[] name;
}

Person& Person::operator=(const Person& other) {
    std::cout << "Person::operator=\n";
    if (this != &other) {
        char* ns = copyString(other.surname);
        char* nn = copyString(other.name);
        delete[] surname;
        delete[] name;
        surname = ns;
        name = nn;
    }
    return *this;
}

const char* Person::getSurname() const { return surname ? surname : ""; }
const char* Person::getName() const { return name ? name : ""; }

void Person::setSurname(const char* s) {
    char* tmp = copyString(s);
    delete[] surname;
    surname = tmp;
}

void Person::setName(const char* s) {
    char* tmp = copyString(s);
    delete[] name;
    name = tmp;
}

void Person::print(std::ostream& os) const {
    os << getSurname() << " " << getName();
}