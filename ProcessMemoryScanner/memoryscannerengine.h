#ifndef MEMORYSCANNERENGINE_H
#define MEMORYSCANNERENGINE_H

#include <iostream>
#include <vector>
#include <string>

#include "memoryinteractionstratege.h"
#include "memoryscannerengineexception.h"

enum DataType {
    Char,
    Short,
    Int,
    Long,

    Float,
    Dobule,
    LongDouble,

    NoType
};

enum CompareType {
    Equal,
    Less,
    Greater,

    Increased,
    Decreased,

    Unchanged,
    Changed,

    Unknown
};

struct DataValue
{
    char char_val;
    short short_val;
    int int_val;
    long long_val;
    float float_val;
    double double_val;
};

template <typename Type>
struct memoryMatch
{
    uint8_t *addres;
    uint8_t *offset;

    Type value;
    region_type type;    
};

template <typename Type>
class MemoryScannerEngine
{
public:
    MemoryScannerEngine(MemoryInteractionStratege *stratege);

    void setMemoryInteractionStratege(MemoryInteractionStratege *stratege);
    MemoryInteractionStratege* getMemoryInteractionStratege();

    std::vector<memoryMatch<Type>> executeScanning(unsigned int pid, Type value, CompareType compareType);
    std::vector<memoryMatch<Type>> executeScanning(unsigned int pid, CompareType compareType);

    std::vector<memoryMatch<Type>> makeFirstScan(unsigned int pid, Type value,  CompareType compareType);
    std::vector<memoryMatch<Type>> makeNextScan(unsigned int pid, Type value, CompareType compareType);
    std::vector<memoryMatch<Type>> makeNextScan(unsigned int pid, CompareType compareType);

    void changeMemoryValue(unsigned int pid, Type value, uint8_t* addres);

    bool compareMethod(CompareType compareType, Type first_value, Type second_value);
    bool checkFirstScannConditions(CompareType compareType);
    bool checkNextScannCondition(CompareType compareType);
    void refreshScanner();
    int getScanningCount();

private:
    MemoryInteractionStratege *memoryInteraction;
    std::vector<memoryMatch<Type>> prevMatches;
    int scannCounter;
};

#endif // MEMORYSCANNERENGINE_H
