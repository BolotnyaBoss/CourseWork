#ifndef INCORECTDATAEXCEPTION_H
#define INCORECTDATAEXCEPTION_H
#include <exception>

class IncorectDataException : public std::exception{
public:
    IncorectDataException() = default;

    const char * what() const noexcept{
        return "Incorect input data!";
    }
};
#endif // INCORECTDATAEXCEPTION_H
