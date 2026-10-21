#include "Exceptions.h"

using namespace std;

IndexException::IndexException(string newMessage) {
    message = newMessage;
}

const char* IndexException::what() const noexcept {
    return message.c_str();
}

FileException::FileException(string newMessage) {
    message = newMessage;
}

const char* FileException::what() const noexcept {
    return message.c_str();
}
