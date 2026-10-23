#include "Poet.h"
#include <sstream>

using namespace std;

Poet::Poet() : Base() {
    birthYear = 0;
    deathYear = 0;
    cout << "Вызван конструктор по умолчанию для класса Poet" << endl;
}

Poet::Poet(string newName, int newBirth, int newDeath, const string* newWorks, int newCount)
    : Base(newName, newWorks, newCount) {
    birthYear = newBirth;
    deathYear = newDeath;
    cout << "Вызван конструктор с параметрами для класса Poet" << endl;
}

Poet::Poet(const Poet& other) : Base(other) {
    birthYear = other.birthYear;
    deathYear = other.deathYear;
    cout << "Вызван конструктор копирования для класса Poet" << endl;
}

Poet::~Poet() {
    cout << "Вызван деструктор для класса Poet" << endl;
}

Poet& Poet::operator=(const Poet& other) {
    if (this != &other) {
        Base::operator=(other);
        birthYear = other.birthYear;
        deathYear = other.deathYear;
    }
    return *this;
}

int Poet::getBirthYear() const {
    return birthYear;
}

int Poet::getDeathYear() const {
    return deathYear;
}

void Poet::setBirthYear(int year) {
    birthYear = year;
}

void Poet::setDeathYear(int year) {
    deathYear = year;
}

string Poet::getType() const {
    return "POET";
}

void Poet::print(ostream& out) const {
    out << "Тип: Поэт" << endl;
    out << "ФИО: " << getName() << endl;
    out << "Годы жизни: " << birthYear << " - " << deathYear << endl;
    printWorks(out);
}

/*
Формат файла:
  ФИО
  год рождения и смерти через пробел
  кол-во произведений
  произведения с новой строки
*/

void Poet::save(ostream& out) const {
    out << getName() << endl;
    out << birthYear << " " << deathYear << endl;
    saveWorks(out);
}

void Poet::load(istream& in) {
    string line;

    if (!readFileLine(in, line) || line == "") {
        in.setstate(ios::failbit);
        return;
    }
    setName(line);

    if (!readFileLine(in, line)) {
        in.setstate(ios::failbit);
        return;
    }
    istringstream iss(line);
    iss >> birthYear >> deathYear;
    if (iss.fail() || birthYear < 1 || deathYear < birthYear) {
        in.setstate(ios::failbit);
        return;
    }

    loadWorks(in);
}
