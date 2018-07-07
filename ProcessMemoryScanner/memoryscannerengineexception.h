#ifndef MEMORYSCANNERENGINEEXCEPTION_H
#define MEMORYSCANNERENGINEEXCEPTION_H

#include <iostream>
#include <exception>
#include <string>

class MemoryScannerEngineException : public std::exception
{
public:
    MemoryScannerEngineException(std::string exceptionMessage);
    std::string what();

private:
    std::string message;
};

#endif // MEMORYSCANNERENGINEEXCEPTION_H
