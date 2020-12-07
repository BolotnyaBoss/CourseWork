#ifndef OPENFILEEXCEPTION_H
#define OPENFILEEXCEPTION_H
#include <exception>

class OpenFileException : public std::exception{
public:
    OpenFileException() = default;

    const char * what() const noexcept{
        return "Cannot open file!";
    }
};
#endif // OPENFILEEXCEPTION_H
