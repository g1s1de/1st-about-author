#ifndef NOVELIST_H
#define NOVELIST_H

#include "Base.h"

// романист: ФИО, годы жизни, произведения, биография
class Novelist : public Base {
private:
    int birthYear;
    int deathYear;
    std::string biography;

public:
    Novelist();
    Novelist(std::string newName, int newBirth, int newDeath, const std::string* newWorks, int newCount,
             std::string newBiography);
    Novelist(const Novelist& other);
    ~Novelist();
    Novelist& operator=(const Novelist& other);

    // get
    int getBirthYear() const;
    int getDeathYear() const;
    std::string getBiography() const;

    // set
    void setBirthYear(int year);
    void setDeathYear(int year);
    void setBiography(std::string newBiography);

    // виртуальные функции базового класса
    std::string getType() const;
    void print(std::ostream& out) const;
    void save(std::ostream& out) const;
    void load(std::istream& in);
};

#endif
