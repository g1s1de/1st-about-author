#include "SciFiWriter.h"

using namespace std;

SciFiWriter::SciFiWriter() : Base() {
    hasFilms = false;
    cout << "Вызван конструктор по умолчанию для класса SciFiWriter" << endl;
}

SciFiWriter::SciFiWriter(string newName, const string* newWorks, int newCount, bool newHasFilms)
    : Base(newName, newWorks, newCount) {
    hasFilms = newHasFilms;
    cout << "Вызван конструктор с параметрами для класса SciFiWriter" << endl;
}

SciFiWriter::SciFiWriter(const SciFiWriter& other) : Base(other) {
    hasFilms = other.hasFilms;
    cout << "Вызван конструктор копирования для класса SciFiWriter" << endl;
}

SciFiWriter::~SciFiWriter() {
    cout << "Вызван деструктор для класса SciFiWriter" << endl;
}

SciFiWriter& SciFiWriter::operator=(const SciFiWriter& other) {
    if (this != &other) {
        Base::operator=(other);
        hasFilms = other.hasFilms;
    }
    return *this;
}

bool SciFiWriter::getHasFilms() const {
    return hasFilms;
}

void SciFiWriter::setHasFilms(bool value) {
    hasFilms = value;
}

string SciFiWriter::getType() const {
    return "SCIFI";
}

void SciFiWriter::print(ostream& out) const {
    out << "Тип: Фантаст" << endl;
    out << "ФИО: " << getName() << endl;
    printWorks(out);
    if (hasFilms) {
        out << "Фильмы по книгам сняты: да" << endl;
    } else {
        out << "Фильмы по книгам сняты: нет" << endl;
    }
}

/*
Формат файла:
  ФИО
  кол-во произведений
  произведения с новой строки
  1 - фильмы сняты, 0 - не сняты
*/

void SciFiWriter::save(ostream& out) const {
    out << getName() << endl;
    saveWorks(out);
    if (hasFilms) {
        out << 1 << endl;
    } else {
        out << 0 << endl;
    }
}

void SciFiWriter::load(istream& in) {
    string line;

    if (!readFileLine(in, line) || line == "") {
        in.setstate(ios::failbit);
        return;
    }
    setName(line);

    loadWorks(in);
    if (in.fail()) {
        return;
    }

    int flag = readFileInt(in);
    if (flag != 0 && flag != 1) {
        in.setstate(ios::failbit);
        return;
    }
    hasFilms = (flag == 1);
}
