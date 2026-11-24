#include "SIGN.h"
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

bool SIGN::validDate(int d, int m, int y) {
    if (y < 1900 || y > 2100) return false;
    if (m < 1 || m > 12) return false;

    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    bool leap = (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
    if (leap) days[1] = 29;

    return d >= 1 && d <= days[m - 1];
}

SIGN::SIGN()
    : Person(), zodiac(copyString("")), birthDate{ 1, 1, 2000 } {
    std::cout << "SIGN(): default constructor\n";
}

SIGN::SIGN(const char* s, const char* n, const char* z, int d, int m, int y)
    : Person(s, n), zodiac(copyString(z)), birthDate{ d, m, y } {
    if (!validDate(d, m, y)) {
        delete[] zodiac;
        zodiac = nullptr;
        throw std::invalid_argument("Invalid birth date");
    }
    std::cout << "SIGN(...): parameterized constructor\n";
}

SIGN::SIGN(const SIGN& other)
    : Person(other),
    zodiac(copyString(other.zodiac)),
    birthDate{ other.birthDate[0], other.birthDate[1], other.birthDate[2] } {
    std::cout << "SIGN(const SIGN&): copy constructor\n";
}

SIGN::~SIGN() {
    std::cout << "~SIGN(): destructor for " << getSurname() << " " << getName() << "\n";
    delete[] zodiac;
}

SIGN& SIGN::operator=(const SIGN& other) {
    std::cout << "SIGN::operator=\n";
    if (this != &other) {
        Person::operator=(other);
        char* z = copyString(other.zodiac);
        delete[] zodiac;
        zodiac = z;
        for (int i = 0; i < 3; ++i)
            birthDate[i] = other.birthDate[i];
    }
    return *this;
}

const char* SIGN::getZodiac() const { return zodiac ? zodiac : ""; }

void SIGN::getBirthDate(int& d, int& m, int& y) const {
    d = birthDate[0]; m = birthDate[1]; y = birthDate[2];
}

void SIGN::setZodiac(const char* z) {
    char* tmp = copyString(z);
    delete[] zodiac;
    zodiac = tmp;
}

void SIGN::setBirthDate(int d, int m, int y) {
    if (!validDate(d, m, y))
        throw std::invalid_argument("Invalid birth date");
    birthDate[0] = d; birthDate[1] = m; birthDate[2] = y;
}

bool SIGN::operator<(const SIGN& other) const {
    if (birthDate[2] != other.birthDate[2]) return birthDate[2] < other.birthDate[2];
    if (birthDate[1] != other.birthDate[1]) return birthDate[1] < other.birthDate[1];
    return birthDate[0] < other.birthDate[0];
}

bool SIGN::surnameEquals(const char* s) const {
    return s && std::strcmp(getSurname(), s) == 0;
}

void SIGN::print(std::ostream& os) const {
    Person::print(os);
    os << ", zodiac: " << getZodiac() << ", birth date: "
        << birthDate[0] << "." << birthDate[1] << "." << birthDate[2];
}

std::ostream& operator<<(std::ostream& os, const SIGN& s) {
    s.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, SIGN& s) {
    std::string sur, nm, z;
    int d, m, y;
    if (!(is >> sur >> nm >> z >> d >> m >> y)) {
        throw std::runtime_error("SIGN input error. Format: Surname Name Zodiac DD MM YYYY");
    }
    s.setSurname(sur.c_str());
    s.setName(nm.c_str());
    s.setZodiac(z.c_str());
    s.setBirthDate(d, m, y);
    return is;
}