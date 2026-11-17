#ifndef SIGN_H
#define SIGN_H

#include "Person.h"

class SIGN : public Person {
private:
    char* zodiac;
    int birthDate[3];

    static bool validDate(int d, int m, int y);

public:
    SIGN();
    SIGN(const char* surname, const char* name, const char* zodiac,
        int d, int m, int y);
    SIGN(const SIGN& other);
    virtual ~SIGN();

    SIGN& operator=(const SIGN& other);

    const char* getZodiac() const;
    void getBirthDate(int& d, int& m, int& y) const;
    void setZodiac(const char* z);
    void setBirthDate(int d, int m, int y);

    bool operator<(const SIGN& other) const;
    bool surnameEquals(const char* s) const;

    virtual void print(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const SIGN& s);
    friend std::istream& operator>>(std::istream& is, SIGN& s);
};

#endif