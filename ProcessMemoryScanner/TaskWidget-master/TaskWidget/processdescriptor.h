#ifndef PROCESSDESCRIPTOR_H
#define PROCESSDESCRIPTOR_H

#include <iostream>
#include <string>

class ProcessDescriptor
{
public:
    ProcessDescriptor();
    ProcessDescriptor(unsigned int pid, std::string name, std::string user);

    int pid();
    int ppid();
    int priority();
    int threads();
    std::string name();
    std::string user();  
    bool is_valid();

private:
    bool p_valid;

    unsigned int p_pid;
    unsigned int p_ppid;
    unsigned int p_priority;
    unsigned int p_threads;
    std::string p_name;
    std::string p_uname;
};

#endif // PROCESSDESCRIPTOR_H
