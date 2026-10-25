#include "Keeper.h"
#include "Exceptions.h"
#include "Poet.h"
#include "Novelist.h"
#include "SciFiWriter.h"
#include <fstream>

using namespace std;

Keeper::Keeper() {
    capacity = 2;
    size = 0;
    data = new Base*[capacity];
    cout << "Вызван конструктор по умолчанию для класса Keeper" << endl;
}

Keeper::Keeper(int newCapacity) {
    if (newCapacity < 1) {
        newCapacity = 1;
    }
    capacity = newCapacity;
    size = 0;
    data = new Base*[capacity];
    cout << "Вызван конструктор с параметрами для класса Keeper" << endl;
}

Keeper::~Keeper() {
    clear();
    delete[] data;
    cout << "Вызван деструктор для класса Keeper" << endl;
}

// удаление всех объектов (массив data остаётся)
void Keeper::clear() {
    for (int i = 0; i < size; i++) {
        delete data[i];
    }
    size = 0;
}

int Keeper::getSize() const {
    return size;
}

int Keeper::getCapacity() const {
    return capacity;
}

Base* Keeper::get(int index) const {
    if (index < 0 || index >= size) {
        throw IndexException("неверный индекс " + to_string(index) + " (объектов в хранилище: " + to_string(size) + ")");
    }
    return data[index];
}

// добавление
void Keeper::add(Base* obj) {
    if (size == capacity) {
        Base** newData = new Base*[capacity * 2];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data; // удаление старого массива
        data = newData;
        capacity = capacity * 2;
    }
    data[size] = obj;
    size++;
}

// удаление объекта и сдвиг остальных на 1 влево
void Keeper::remove(int index) {
    if (index < 0 || index >= size) {
        throw IndexException("неверный индекс " + to_string(index) + " (объектов в хранилище: " + to_string(size) + ")");
    }
    delete data[index];
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

void Keeper::printAll() const {
    if (size == 0) {
        cout << "Хранилище пусто." << endl;
        return;
    }
    cout << "Объектов в хранилище: " << size << " (вместимость массива: " << capacity << ")" << endl;
    for (int i = 0; i < size; i++) {
        cout << "----- Объект " << i << " -----" << endl;
        cout << *data[i];
    }
}

void Keeper::saveToFile(string filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw FileException("не удалось открыть файл \"" + filename + "\" для записи");
    }
    for (int i = 0; i < size; i++) {
        file << data[i]->getType() << endl;
        data[i]->save(file);
    }
    file.close();
    if (file.fail()) {
        throw FileException("ошибка при записи в файл \"" + filename + "\"");
    }
}

void Keeper::loadFromFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        // старые данные остаются нетронутыми
        throw FileException("не удалось открыть файл \"" + filename + "\" для чтения");
    }

    clear();  // удаление старых объектов

    string tag;
    while (readFileLine(file, tag)) {
        if (tag == "") {
            continue;  // пропускаем пустые строки
        }

        Base* obj = nullptr;
        if (tag == "POET") {
            obj = new Poet();
        } else if (tag == "NOVELIST") {
            obj = new Novelist();
        } else if (tag == "SCIFI") {
            obj = new SciFiWriter();
        } else {
            throw FileException("неизвестный тип объекта \"" + tag + "\" (загружено объектов до ошибки: " +
                                to_string(size) + ")");
        }

        file >> *obj;
        if (file.fail()) {
            delete obj;
            throw FileException("файл повреждён: данные объекта " + tag + " неверные или оборваны (загружено объектов до ошибки: " +
                                to_string(size) + ")");
        }
        add(obj);
    }
}
