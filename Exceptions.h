#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

// исключение для ошибок с индексом (индекс вышел за границы хранилища)
class IndexException : public std::exception {
private:
    std::string message;

public:
    IndexException(std::string newMessage);
    const char* what() const noexcept;
};

// исключение для ошибок при работе с файлом
class FileException : public std::exception {
private:
    std::string message;

public:
    FileException(std::string newMessage);
    const char* what() const noexcept;
};

#endif
