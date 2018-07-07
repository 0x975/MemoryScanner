#include "memoryscannerengineexception.h"

MemoryScannerEngineException::MemoryScannerEngineException(std::string exceptionMessage)
{
    message = exceptionMessage;
}

std::string MemoryScannerEngineException::what()
{
    return message;
}
