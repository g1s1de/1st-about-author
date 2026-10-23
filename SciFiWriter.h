#ifndef SCIFIWRITER_H
#define SCIFIWRITER_H

#include "Base.h"

// Фантаст: ФИО, произведения, сняты ли фильмы по книгам
class SciFiWriter : public Base {
private:
    bool hasFilms;

public:
    SciFiWriter();
    SciFiWriter(std::string newName, const std::string* newWorks, int newCount, bool newHasFilms);
    SciFiWriter(const SciFiWriter& other);
    ~SciFiWriter();
    SciFiWriter& operator=(const SciFiWriter& other);

    // get
    bool getHasFilms() const;

    // set
    void setHasFilms(bool value);

    // виртуальные функции базового класса
    std::string getType() const;
    void print(std::ostream& out) const;
    void save(std::ostream& out) const;
    void load(std::istream& in);
};

#endif
