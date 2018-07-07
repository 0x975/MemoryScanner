#ifndef LINUXMEMORYINTERACTION_H
#define LINUXMEMORYINTERACTION_H

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include "memoryinteractionstratege.h"

class LinuxMemoryInteraction : public MemoryInteractionStratege
{
public:
    LinuxMemoryInteraction();
    ~LinuxMemoryInteraction();

    std::vector<memory_region> readMemoryLayout(unsigned int pid) override;
    unsigned int readMemoryRegion(unsigned int pid, std::vector<byte> &buffer, memory_region region) override;
    unsigned int readMemory(unsigned int pid, void *buffer, size_t b_size, uint8_t *p_addres);
    unsigned int writeMemory(unsigned int pid, void *buffer, size_t b_size, uint8_t *p_addres);
    int openProcessForInteraction(unsigned int pid);

private:
    std::vector<std::string> readProcessMapsLines(unsigned int pid);

};

#endif // LINUXMEMORYINTERACTION_H
