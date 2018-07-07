#include "processdescriptor.h"

ProcessDescriptor::ProcessDescriptor()
{
    p_valid = false;
}

ProcessDescriptor::ProcessDescriptor(unsigned int pid, std::string name, std::string user)
{
    p_valid = true;

    p_pid   = pid;
    p_name  = name;
    p_uname = user;
}

int ProcessDescriptor::pid()
{
    return p_pid;
}

int ProcessDescriptor::ppid()
{
    return p_ppid;
}

int ProcessDescriptor::priority()
{
    return p_priority;
}

int ProcessDescriptor::threads()
{
    return p_threads;
}

std::string ProcessDescriptor::name()
{
    return p_name;
}

std::string ProcessDescriptor::user()
{
    return p_uname;
}

bool ProcessDescriptor::is_valid()
{
    return p_valid;
}
