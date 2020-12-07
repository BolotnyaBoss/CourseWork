#ifndef SAVEFILEEXCEPTION_H
#define SAVEFILEEXCEPTION_H
#include <exception>

class SaveFileException : public std::exception{
public:
    SaveFileException() = default;

    const char * what() const noexcept{
        return "Cannot save to file!";
    }
};
#endif // SAVEFILEEXCEPTION_H
