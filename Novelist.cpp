#include "Novelist.h"
#include <sstream>

using namespace std;

Novelist::Novelist() : Base() {
    birthYear = 0;
    deathYear = 0;
    biography = "";
    cout << "Вызван конструктор по умолчанию для класса Novelist" << endl;
}

Novelist::Novelist(string newName, int newBirth, int newDeath, const string* newWorks, int newCount,
                   string newBiography)
    : Base(newName, newWorks, newCount) {
    birthYear = newBirth;
    deathYear = newDeath;
    biography = newBiography;
    cout << "Вызван конструктор с параметрами для класса Novelist" << endl;
}

Novelist::Novelist(const Novelist& other) : Base(other) {
    birthYear = other.birthYear;
    deathYear = other.deathYear;
    biography = other.biography;
    cout << "Вызван конструктор копирования для класса Novelist" << endl;
}

Novelist::~Novelist() {
    cout << "Вызван деструктор для класса Novelist" << endl;
}

Novelist& Novelist::operator=(const Novelist& other) {
    if (this != &other) {
        Base::operator=(other);
        birthYear = other.birthYear;
        deathYear = other.deathYear;
        biography = other.biography;
    }
    return *this;
}

int Novelist::getBirthYear() const {
    return birthYear;
}

int Novelist::getDeathYear() const {
    return deathYear;
}

string Novelist::getBiography() const {
    return biography;
}

void Novelist::setBirthYear(int year) {
    birthYear = year;
}

void Novelist::setDeathYear(int year) {
    deathYear = year;
}

void Novelist::setBiography(string newBiography) {
    biography = newBiography;
}

string Novelist::getType() const {
    return "NOVELIST";
}

void Novelist::print(ostream& out) const {
    out << "Тип: Романист" << endl;
    out << "ФИО: " << getName() << endl;
    out << "Годы жизни: " << birthYear << " - " << deathYear << endl;
    printWorks(out);
    out << "Биография: " << biography << endl;
}

/*
формат файла:
  ФИО
  год рождения и смерти через пробел
  кол-во произведений
  произведения с новой строки
  строка биографии
*/

 void Novelist::save(ostream& out) const {
    out << getName() << endl;
    out << birthYear << " " << deathYear << endl;
    saveWorks(out);
    out << biography << endl;
}

void Novelist::load(istream& in) {
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
    if (in.fail()) {
        return;
    }

    if (!readFileLine(in, line) || line == "") {
        in.setstate(ios::failbit);
        return;
    }
    biography = line;
}
