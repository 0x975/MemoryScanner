#include "memoryinteractionstratege.h"

MemoryInteractionStratege::MemoryInteractionStratege()
{

}

MemoryInteractionStratege::~MemoryInteractionStratege()
{

}

uint8_t* MemoryInteractionStratege::calculateAddres(uint8_t *region, uint8_t* offset)
{
    uintptr_t ipt1 =  reinterpret_cast<uintptr_t>(region);
    uintptr_t ipt2 =  reinterpret_cast<uintptr_t>(offset);
    uintptr_t ipt3 =  ipt1 + ipt2;

    return reinterpret_cast<uint8_t*>(ipt3);
}


