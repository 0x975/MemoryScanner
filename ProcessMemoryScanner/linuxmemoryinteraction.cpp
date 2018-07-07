#include "linuxmemoryinteraction.h"

LinuxMemoryInteraction::LinuxMemoryInteraction()
{

}

LinuxMemoryInteraction::~LinuxMemoryInteraction()
{

}

std::vector<memory_region> LinuxMemoryInteraction::readMemoryLayout(unsigned int pid)
{
    char fileName[64];
    sprintf(fileName, "/proc/%d/maps", pid);
    FILE *fmaps = fopen(fileName, "r");

    std::vector<memory_region> memory_layout;

    memory_region mem_region;
    uint8_t* addr, *endaddr;
    long long offset, inode;
    char permissions[8], device[8], pathname[100];

    if(fmaps) {
        while(true) {
            int r_ret = fscanf(fmaps, "%p-%p %s %llx %s %llx%[^\n]",
                               &addr, &endaddr, permissions, &offset, device, &inode, pathname);

            if(r_ret == 0 || r_ret == EOF) {
                break;
            }

            bool read = permissions[0] == 'r';
            bool write = permissions[1] == 'w';

            if(read && write) {
                mem_region.start_addres = addr;
                mem_region.end_addres = endaddr;
                mem_region.size = endaddr - addr;


                if(strstr(pathname, "[heap]")) {
                    mem_region.type = heap;
                }
                else if(strstr(pathname, "[stack]")) {
                    mem_region.type = stack;
                }
                else {

                }

                memory_layout.push_back(mem_region);
            }
        }
    }
    return memory_layout;
}

unsigned int LinuxMemoryInteraction::readMemoryRegion(unsigned int pid, std::vector<byte> &buffer, memory_region region)
{
    int fd = openProcessForInteraction(pid);
    unsigned int bytes = pread(fd, &buffer[0], region.size, reinterpret_cast<off_t>(region.start_addres));
    close(fd);
    return bytes;
}

unsigned int LinuxMemoryInteraction::readMemory(unsigned int pid, void *buffer, size_t b_size, uint8_t *p_addres)
{
    int fd = openProcessForInteraction(pid);
    unsigned int bytes= pread(fd, buffer, b_size, reinterpret_cast<off_t>(p_addres));
    close(fd);
    return bytes;
}

unsigned int LinuxMemoryInteraction::writeMemory(unsigned int pid, void *buffer, size_t b_size, uint8_t *p_addres)
{
    int fd = openProcessForInteraction(pid);
    unsigned int bytes = pwrite(fd, buffer, b_size, reinterpret_cast<off_t>(p_addres));
    close(fd);
    return bytes;
}

int LinuxMemoryInteraction::openProcessForInteraction(unsigned int pid)
{
    char fileName[64];
    sprintf(fileName, "/proc/%d/mem", pid);
    return open(fileName, O_RDWR);
}

std::vector<std::string> LinuxMemoryInteraction::readProcessMapsLines(unsigned int pid)
{
    std::string processPath("/proc/");
    processPath += std::to_string(pid) += "/maps";

    std::vector<std::string> mapsBuffer;
    std::string map;

    std::ifstream mapsFile(processPath);
    if(!mapsFile.is_open()) {
        return mapsBuffer;
    }

    while(std::getline(mapsFile, map)) {
        mapsBuffer.push_back(map);
    }
    return mapsBuffer;
}
