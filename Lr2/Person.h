#ifndef PERSON_H
#define PERSON_H

#include <iostream>

class Person {
protected:
    char* surname;
    char* name;
    static char* copyString(const char* s);

public:
    Person();
    Person(const char* surname, const char* name);
    Person(const Person& other);
    virtual ~Person();

    Person& operator=(const Person& other);

    const char* getSurname() const;
    const char* getName() const;
    void setSurname(const char* s);
    void setName(const char* s);

    virtual void print(std::ostream& os) const;
};

#endif
