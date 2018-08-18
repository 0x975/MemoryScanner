#include "memoryscannerengine.h"


template <typename Type>
MemoryScannerEngine<Type>::MemoryScannerEngine(MemoryInteractionStratege *stratege)
{
    memoryInteraction = stratege;
    scannCounter = 0;
}

template <typename Type>
void MemoryScannerEngine<Type>::setMemoryInteractionStratege(MemoryInteractionStratege *stratege)
{
    memoryInteraction = stratege;
}

template <typename Type>
MemoryInteractionStratege* MemoryScannerEngine<Type>::getMemoryInteractionStratege()
{
    return memoryInteraction;
}

template <typename Type>
void MemoryScannerEngine<Type>::refreshScanner()
{
    prevMatches.clear();
    scannCounter = 0;
}

template <typename Type>
int MemoryScannerEngine<Type>::getScanningCount()
{
    return scannCounter;
}

template <typename Type>
std::vector<memoryMatch<Type>> MemoryScannerEngine<Type>::executeScanning(unsigned int pid, Type value, CompareType compareType)
{
    std::vector<memoryMatch<Type>> matches;
    if(scannCounter == 0) {
        matches = makeFirstScan(pid, value, compareType);
    }
    else {
        matches = makeNextScan(pid, value, compareType);
    }
    return matches;
}

template <typename Type>
std::vector<memoryMatch<Type>> MemoryScannerEngine<Type>::executeScanning(unsigned int pid, CompareType compareType)
{
    if(scannCounter == 0) {
        throw MemoryScannerEngineException("can not make scann without initial value");
    }
    return makeNextScan(pid, compareType);
}

template <typename Type>
std::vector<memoryMatch<Type>> MemoryScannerEngine<Type>::makeFirstScan(unsigned int pid, Type value,  CompareType compareType)
{
    std::vector<memoryMatch<Type>> matches;
    if(checkFirstScannConditions(compareType) == false) {
        throw MemoryScannerEngineException("wrong compare type for first scan");
    }

    std::vector<byte> memory_block;
    std::vector<memory_region> mem_layout;
    mem_layout = memoryInteraction->readMemoryLayout(pid);

    memoryMatch<Type> memMatch;
    for(memory_region m_region : mem_layout) {
        memory_block.resize(m_region.size);
        memoryInteraction->readMemoryRegion(pid, memory_block, m_region);

        Type *vPtr;
        vPtr = (Type*)&memory_block[0];
        Type curValue;
        for(int i = 0; i < memory_block.size() / sizeof(Type); i++) {
            //if(!vPtr) return matches;
            curValue = *vPtr;
            if(compareMethod(compareType, curValue, value)) {
                uint8_t *offset = reinterpret_cast<uint8_t*>(i*sizeof(Type));
                memMatch.addres = memoryInteraction->calculateAddres(m_region.start_addres, offset);
                memMatch.offset = offset;
                memMatch.value = value;
                memMatch.type = m_region.type;

                matches.push_back(memMatch);
            }
            vPtr++;
        }
    }

    prevMatches = matches;
    scannCounter++;
    return matches;
}

template <typename Type>
std::vector<memoryMatch<Type>> MemoryScannerEngine<Type>::makeNextScan(unsigned int pid, Type value, CompareType compareType)
{
    std::vector<memoryMatch<Type>> matches;

    memoryMatch<Type> memMatch;
    for(int i = 0; i < prevMatches.size(); i++) {

        memoryInteraction->readMemory(pid, &memMatch.value, sizeof(memMatch.value), prevMatches[i].addres);
        if(compareMethod(compareType, memMatch.value, value)) {
            memMatch.addres = prevMatches[i].addres;
            memMatch.offset = prevMatches[i].offset;
            memMatch.type = prevMatches[i].type;

            matches.push_back(memMatch);
        }
    }

    prevMatches = matches;
    scannCounter++;
    return matches;
}

template <typename Type>
std::vector<memoryMatch<Type>> MemoryScannerEngine<Type>::makeNextScan(unsigned int pid, CompareType compareType)
{
    std::vector<memoryMatch<Type>> matches;
    if(checkNextScannCondition(compareType) == false) {
        throw MemoryScannerEngineException("unavailable compare type for scann without value");
    }

    memoryMatch<Type> memMatch;
    for(int i = 0; i < prevMatches.size(); i++) {
        memoryInteraction->readMemory(pid, &memMatch.value, sizeof(memMatch.value), prevMatches[i].addres);
        if(compareMethod(compareType, memMatch.value, prevMatches[i].value)) {
            memMatch.addres = prevMatches[i].addres;
            memMatch.offset = prevMatches[i].offset;
            memMatch.type = prevMatches[i].type;

            matches.push_back(memMatch);
        }
    }

    prevMatches = matches;
    scannCounter++;
    return matches;
}

template <typename Type>
void  MemoryScannerEngine<Type>::changeMemoryValue(unsigned int pid, Type value, uint8_t* addres)
{
    int bytes = memoryInteraction->writeMemory(pid, &value, sizeof(value), addres);
    if(bytes != sizeof(value)) {
        throw MemoryScannerEngineException("something wrong with change value process");
    }
}

template <typename Type>
bool MemoryScannerEngine<Type>::compareMethod(CompareType compareType, Type first_value, Type second_value)
{
    if(compareType == Equal)        return first_value == second_value;
    if(compareType == Less)         return first_value < second_value;
    if(compareType == Greater)      return first_value > second_value;

    if(compareType == Increased)    return first_value > second_value;
    if(compareType == Decreased)    return first_value < second_value;

    if(compareType == Changed)      return first_value != second_value;
    if(compareType == Unchanged)    return first_value == second_value;
}

template <typename Type>
bool MemoryScannerEngine<Type>::checkFirstScannConditions(CompareType compareType) {
    if(compareType == Increased) return false;
    if(compareType == Decreased) return false;
    if(compareType == Unknown)   return false;
    if(compareType == Unchanged) return false;
    if(compareType == Changed)   return false;
    return true;
}

template <typename Type>
bool MemoryScannerEngine<Type>::checkNextScannCondition(CompareType compareType)
{
    if(compareType == Equal)    return false;
    if(compareType == Less)     return false;
    if(compareType == Greater)  return false;
    return true;
}

template class MemoryScannerEngine<char>;
template class MemoryScannerEngine<short>;
template class MemoryScannerEngine<int>;
template class MemoryScannerEngine<long>;
template class MemoryScannerEngine<float>;
template class MemoryScannerEngine<double>;
