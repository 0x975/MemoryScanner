#ifndef READPROCESSSTRATEGY_H
#define READPROCESSSTRATEGY_H

#include "processdescriptor.h"
#include <vector>
#include <string>
#include <list>

class ReadProcessStrategy
{
public:
    ReadProcessStrategy();
    virtual std::vector<ProcessDescriptor> readAllRunningProcesses() = 0;
    virtual void readAllRunningProcesses(std::vector<ProcessDescriptor> &pds) = 0;

private:

};

#endif // READPROCESSSTRATEGY_H
