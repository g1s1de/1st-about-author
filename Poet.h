#ifndef POET_H
#define POET_H

#include "Base.h"

// Поэт: ФИО, годы жизни, произведения
class Poet : public Base {
private:
    int birthYear;
    int deathYear;

public:
    Poet();
    Poet(std::string newName, int newBirth, int newDeath, const std::string* newWorks, int newCount);
    Poet(const Poet& other);
    ~Poet();
    Poet& operator=(const Poet& other);

    // get
    int getBirthYear() const;
    int getDeathYear() const;

    // set
    void setBirthYear(int year);
    void setDeathYear(int year);

    // виртуальные функции базового класса
    std::string getType() const;
    void print(std::ostream& out) const;
    void save(std::ostream& out) const;
    void load(std::istream& in);
};

#endif
