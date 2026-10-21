#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <string>

// макс. кол-во произведений у одного автора
const int MAX_WORKS = 100;

// общий класс авторов
class Base {
private:
    std::string name;     // ФИО
    std::string* works;   // названия произведений
    int worksCount;       // кол-во произвдений

protected:
    // общая работа со списком произведений
    void printWorks(std::ostream& out) const;
    void saveWorks(std::ostream& out) const;
    void loadWorks(std::istream& in);

public:
    Base();                                                                // по умолчанию
    Base(std::string newName, const std::string* newWorks, int newCount);  // с параметрами
    Base(const Base& other);                                               // копирования
    virtual ~Base();                                                       // деструктор
    Base& operator=(const Base& other);                                    // присваивание

    // get
    std::string getName() const;
    int getWorksCount() const;
    std::string getWork(int index) const;

    // set
    void setName(std::string newName);
    void setWorks(const std::string* newWorks, int newCount);

    // виртуальные функции
    virtual std::string getType() const = 0;            // тег: POET, NOVELIST, SCIFI
    virtual void print(std::ostream& out) const = 0;   // вывод на экран
    virtual void save(std::ostream& out) const = 0;    // запись в файл
    virtual void load(std::istream& in) = 0;           // чтение из файла
};

// операторы вывода и ввода
std::ostream& operator<<(std::ostream& out, const Base& obj);
std::istream& operator>>(std::istream& in, Base& obj);

// функции для чтения из файла
bool readFileLine(std::istream& in, std::string& line);  // читает одну строку
int readFileInt(std::istream& in);                       // читает строку как число
#endif
