#ifndef MEMORYINTERACTIONSTRATEGE_H
#define MEMORYINTERACTIONSTRATEGE_H

#include <iostream>
#include <fstream>
#include <vector>

typedef unsigned char byte;
typedef uint8_t* addres;

enum region_type
{
    heap,
    stack,
    thread_stack,
    vdso,
    binary
};

struct memory_region
{
    uint8_t *start_addres;
    uint8_t *end_addres;
    size_t size;

    region_type type;
};

class MemoryInteractionStratege
{
public:
    MemoryInteractionStratege();
    virtual ~MemoryInteractionStratege();

    virtual std::vector<memory_region> readMemoryLayout(unsigned int pid) = 0;
    virtual unsigned int readMemoryRegion(unsigned int pid, std::vector<byte> &buffer, memory_region) = 0;
    virtual unsigned int readMemory(unsigned int pid, void *buffer, size_t b_size, uint8_t *p_addres) = 0;
    virtual unsigned int writeMemory(unsigned int pid, void *buffer, size_t b_size, uint8_t *p_addres) = 0;
    virtual int openProcessForInteraction(unsigned int pid) = 0;

    uint8_t* calculateAddres(uint8_t *region, uint8_t* offset);
};

#endif // MEMORYINTERACTIONSTRATEGE_H
