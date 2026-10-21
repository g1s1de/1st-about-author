#include "Base.h"
#include <sstream>

using namespace std;

//  конструкторы и деструктор

Base::Base() {
    works = nullptr;
    worksCount = 0;
    cout << "Вызван конструктор по умолчанию для класса Base" << endl;
}

Base::Base(string newName, const string* newWorks, int newCount) {
    name = newName;
    works = nullptr;
    worksCount = 0;
    setWorks(newWorks, newCount);
    cout << "Вызван конструктор с параметрами для класса Base" << endl;
}

// глубокое копирование, создание нового массива и копирование в него названия
Base::Base(const Base& other) {
    name = other.name;
    worksCount = other.worksCount;
    if (worksCount > 0) {
        works = new string[worksCount];
        for (int i = 0; i < worksCount; i++) {
            works[i] = other.works[i];
        }
    } else {
        works = nullptr;
    }
    cout << "Вызван конструктор копирования для класса Base" << endl;
}

Base::~Base() {
    delete[] works;
    cout << "Вызван деструктор для класса Base" << endl;
}

Base& Base::operator=(const Base& other) {
    if (this == &other) {
        return *this;
    }
    delete[] works;
    name = other.name;
    worksCount = other.worksCount;
    if (worksCount > 0) {
        works = new string[worksCount];
        for (int i = 0; i < worksCount; i++) {
            works[i] = other.works[i];
        }
    } else {
        works = nullptr;
    }
    return *this;
}

// get 

string Base::getName() const {
    return name;
}

int Base::getWorksCount() const {
    return worksCount;
}

string Base::getWork(int index) const {
    if (index < 0 || index >= worksCount) {
        return "";
    }
    return works[index];
}

// set 

void Base::setName(string newName) {
    name = newName;
}

// замена весь списка произведений новым
void Base::setWorks(const string* newWorks, int newCount) {
    delete[] works;
    works = nullptr;
    worksCount = 0;
    if (newCount > 0 && newWorks != nullptr) {
        works = new string[newCount];
        for (int i = 0; i < newCount; i++) {
            works[i] = newWorks[i];
        }
        worksCount = newCount;
    }
}

// вывод, запись, список произведений

void Base::printWorks(ostream& out) const {
    out << "Произведения (" << worksCount << "):" << endl;
    for (int i = 0; i < worksCount; i++) {
        out << "  " << (i + 1) << ". " << works[i] << endl;
    }
}

void Base::saveWorks(ostream& out) const {
    out << worksCount << endl;
    for (int i = 0; i < worksCount; i++) {
        out << works[i] << endl;
    }
}

// чтение кол-ва произведений и самих произведений
void Base::loadWorks(istream& in) {
    int count = readFileInt(in);
    if (count < 1 || count > MAX_WORKS) {
        in.setstate(ios::failbit);
        return;
    }
    string* temp = new string[count];
    for (int i = 0; i < count; i++) {
        if (!readFileLine(in, temp[i]) || temp[i] == "") {
            in.setstate(ios::failbit);
            delete[] temp;
            return;
        }
    }
    setWorks(temp, count);
    delete[] temp;
}

// операторы << и >>

ostream& operator<<(ostream& out, const Base& obj) {
    obj.print(out);
    return out;
}

istream& operator>>(istream& in, Base& obj) {
    obj.load(in);
    return in;
}

// чтение из файла

bool readFileLine(istream& in, string& line) {
    if (!getline(in, line)) {
        return false;
    }
    if (!line.empty() && line[line.size() - 1] == '\r') {
        line.erase(line.size() - 1);
    }
    return true;
}

int readFileInt(istream& in) {
    string line;
    if (!readFileLine(in, line)) {
        return -1;
    }
    istringstream iss(line);
    int number;
    iss >> number;
    if (iss.fail()) {
        return -1;
    }
    return number;
}
