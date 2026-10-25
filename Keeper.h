#ifndef KEEPER_H
#define KEEPER_H

#include <string>
#include "Base.h"

// контейнер
class Keeper {
private:
    Base** data;
    int size;
    int capacity;

    Keeper(const Keeper& other);
    Keeper& operator=(const Keeper& other);

    void clear();  // удаление всех объектов

public:
    Keeper();
    Keeper(int newCapacity);
    ~Keeper();

    // get
    int getSize() const;
    int getCapacity() const;
    Base* get(int index) const;

    // работа с объектами
    void add(Base* obj);
    void remove(int index);
    void printAll() const;

    // работа с файлом
    void saveToFile(std::string filename) const;
    void loadFromFile(std::string filename);
};

#endif
