#include <iostream>
#include <string>
#include <cstdlib>
#include "Exceptions.h"
#include "Keeper.h"
#include "Poet.h"
#include "Novelist.h"
#include "SciFiWriter.h"

using namespace std;

// ввод

// читаем целое число
int inputInt(string text) {
    int number;
    while (true) {
        cout << text;
        cin >> number;
        if (cin.fail()) {
            if (cin.eof()) {
                cout << endl << "Ввод закончен. Выход из программы." << endl;
                exit(0);
            }
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Ошибка: нужно ввести целое число!" << endl;
        } else {
            cin.ignore(1000, '\n');
            return number;
        }
    }
}

// читаем строку
string inputText(string text) {
    string line;
    while (true) {
        cout << text;
        if (!getline(cin, line)) {
            cout << endl << "Ввод закончен. Выход из программы." << endl;
            exit(0);
        }
        if (line.find_first_not_of(" \t") == string::npos) {  // в строке нет ничего, кроме пробелов
            cout << "Ошибка: строка не может быть пустой!" << endl;
        } else {
            return line;
        }
    }
}

// читаем ответ "да / нет" (1 / 0)
bool inputYesNo(string text) {
    int answer = inputInt(text);
    while (answer != 0 && answer != 1) {
        cout << "Ошибка: нужно ввести 1 (да) или 0 (нет)!" << endl;
        answer = inputInt(text);
    }
    return answer == 1;
}

// читаем годы жизни
void inputYears(int& birth, int& death) {
    birth = inputInt("Год рождения: ");
    death = inputInt("Год смерти: ");
    while (birth < 1 || death < birth) {
        if (birth < 1) {
            cout << "Ошибка: год рождения должен быть положительным!" << endl;
        } else {
            cout << "Ошибка: год смерти не может быть меньше года рождения!" << endl;
        }
        birth = inputInt("Год рождения: ");
        death = inputInt("Год смерти: ");
    }
}

// читаем список произведений
string* inputWorks(int& count) {
    count = inputInt("Количество произведений: ");
    while (count < 1 || count > MAX_WORKS) {
        cout << "Ошибка: количество произведений должно быть от 1 до " << MAX_WORKS << "!" << endl;
        count = inputInt("Количество произведений: ");
    }
    string* works = new string[count];
    for (int i = 0; i < count; i++) {
        cout << "Произведение " << (i + 1) << endl;
        works[i] = inputText("  Название: ");
    }
    return works;
}

// создание объектов из введённых данных

Poet* inputPoet() {
    string name = inputText("ФИО: ");
    int birth, death;
    inputYears(birth, death);
    int count;
    string* works = inputWorks(count);

    Poet* poet = new Poet(name, birth, death, works, count);
    delete[] works;
    return poet;
}

Novelist* inputNovelist() {
    string name = inputText("ФИО: ");
    int birth, death;
    inputYears(birth, death);
    int count;
    string* works = inputWorks(count);
    string biography = inputText("Краткая биография (одной строкой): ");

    Novelist* novelist = new Novelist(name, birth, death, works, count, biography);
    delete[] works;
    return novelist;
}

SciFiWriter* inputSciFi() {
    string name = inputText("ФИО: ");
    int count;
    string* works = inputWorks(count);
    bool hasFilms = inputYesNo("Сняты ли фильмы по книгам? (1 - да, 0 - нет): ");

    SciFiWriter* writer = new SciFiWriter(name, works, count, hasFilms);
    delete[] works;
    return writer;
}

// пункты меню

void printMenu() {
    cout << endl;
    cout << "-----Хранилище печатных изданий-----" << endl;
    cout << "1. Добавить объект" << endl;
    cout << "2. Удалить объект по индексу" << endl;
    cout << "3. Вывести все объекты" << endl;
    cout << "4. Изменить объект" << endl;
    cout << "5. Сохранить в файл" << endl;
    cout << "6. Загрузить из файла" << endl;
    cout << "0. Выход" << endl;
}

void addObject(Keeper& keeper) {
    cout << "Тип объекта: 1 - Поэт, 2 - Романист, 3 - Фантаст" << endl;
    int type = inputInt("Выберите тип: ");

    if (type == 1) {
        keeper.add(inputPoet());
    } else if (type == 2) {
        keeper.add(inputNovelist());
    } else if (type == 3) {
        keeper.add(inputSciFi());
    } else {
        cout << "Ошибка: такого типа нет (нужно 1, 2 или 3)!" << endl;
        return;
    }
    cout << "Объект добавлен. Его индекс: " << keeper.getSize() - 1 << endl;
}

void removeObject(Keeper& keeper) {
    if (keeper.getSize() == 0) {
        cout << "Ошибка: хранилище пусто, удалять нечего!" << endl;
        return;
    }
    keeper.printAll();
    int index = inputInt("Индекс объекта для удаления: ");
    try {
        keeper.remove(index);
        cout << "Объект " << index << " удалён." << endl;
    } catch (IndexException& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void editObject(Keeper& keeper) {
    if (keeper.getSize() == 0) {
        cout << "Ошибка: хранилище пусто, изменять нечего!" << endl;
        return;
    }
    keeper.printAll();
    int index = inputInt("Индекс объекта для изменения: ");
    Base* obj = nullptr;
    try {
        obj = keeper.get(index);
    } catch (IndexException& e) {
        cout << "Ошибка: " << e.what() << endl;
        return;
    }

    // узнаём настоящий тип объекта, если тип не подходит, dynamic_cast возвращает nullptr
    Poet* poet = dynamic_cast<Poet*>(obj);
    Novelist* novelist = dynamic_cast<Novelist*>(obj);
    SciFiWriter* writer = dynamic_cast<SciFiWriter*>(obj);

    cout << "Что изменить?" << endl;
    cout << "1. ФИО" << endl;
    cout << "2. Список произведений" << endl;
    if (poet != nullptr) {
        cout << "3. Годы жизни" << endl;
    }
    if (novelist != nullptr) {
        cout << "3. Годы жизни" << endl;
        cout << "4. Краткая биография" << endl;
    }
    if (writer != nullptr) {
        cout << "3. Сняты ли фильмы по книгам" << endl;
    }
    int choice = inputInt("Ваш выбор: ");

    if (choice == 1) {
        obj->setName(inputText("Новое ФИО: "));
    } else if (choice == 2) {
        int count;
        string* works = inputWorks(count);
        obj->setWorks(works, count);
        delete[] works;
    } else if (choice == 3 && poet != nullptr) {
        int birth, death;
        inputYears(birth, death);
        poet->setBirthYear(birth);
        poet->setDeathYear(death);
    } else if (choice == 3 && novelist != nullptr) {
        int birth, death;
        inputYears(birth, death);
        novelist->setBirthYear(birth);
        novelist->setDeathYear(death);
    } else if (choice == 4 && novelist != nullptr) {
        novelist->setBiography(inputText("Новая биография: "));
    } else if (choice == 3 && writer != nullptr) {
        writer->setHasFilms(inputYesNo("Сняты ли фильмы по книгам? (1 - да, 0 - нет): "));
    } else {
        cout << "Ошибка: такого пункта нет!" << endl;
        return;
    }
    cout << "Данные изменены:" << endl;
    cout << *obj;
}

void saveFile(Keeper& keeper) {
    string filename = inputText("Имя файла для сохранения: ");
    try {
        keeper.saveToFile(filename);
        cout << "Сохранено объектов: " << keeper.getSize() << endl;
    } catch (FileException& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void loadFile(Keeper& keeper) {
    string filename = inputText("Имя файла для загрузки: ");
    if (keeper.getSize() > 0) {
        if (!inputYesNo("Текущие данные будут заменены. Продолжить? (1 - да, 0 - нет): ")) {
            cout << "Загрузка отменена." << endl;
            return;
        }
    }
    try {
        keeper.loadFromFile(filename);
        cout << "Загружено объектов: " << keeper.getSize() << endl;
    } catch (FileException& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

// главная функция

int main() {
    Keeper keeper;
    int choice = -1;

    while (choice != 0) {
        printMenu();
        choice = inputInt("Ваш выбор: ");

        switch (choice) {
            case 1:
                addObject(keeper);
                break;
            case 2:
                removeObject(keeper);
                break;
            case 3:
                keeper.printAll();
                break;
            case 4:
                editObject(keeper);
                break;
            case 5:
                saveFile(keeper);
                break;
            case 6:
                loadFile(keeper);
                break;
            case 0:
                cout << "Завершение работы программы" << endl;
                break;
            default:
                cout << "Ошибка: такого пункта меню нет (введите число от 0 до 6)!" << endl;
                break;
        }
    }
    return 0;
}
