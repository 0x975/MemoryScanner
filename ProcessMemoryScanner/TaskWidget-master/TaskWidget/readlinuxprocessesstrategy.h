#ifndef READLINUXPROCESSESSTRATEGY_H
#define READLINUXPROCESSESSTRATEGY_H

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <pwd.h>

#include <iostream>
#include <fstream>
#include <regex>

#include "readprocessstrategy.h"

struct LinuxProcessDescriptor
{
    short signed int    pid;         // The process ID.
    std::string         pname;       // The filename of the executable, in parentheses.
    std::string         uname;       // The username of the executable.
    unsigned char       state;       // The state of the executable process.
    short signed int    ppid;        // The PID of the parent of this process.
    short signed int    pgrp;        // The process group ID of the process.
    short signed int    session;     // The session ID of the process.
    short signed int    tty_nr;      // The controlling terminal of the process.
    short signed int    tpgid;       // The ID of the foreground process group of the controlling terminal of the process.
    short unsigned int  flags;       // The kernel flags word of the process.
    long unsigned int   minflt;      // The number of minor faults the process has made which have not required loading a memory page from disk.
    long unsigned int   cminflt;     // The number of minor faults that the process's waited-for children have made.
    long unsigned int   majflt;      // The number of major faults the process has made which have required loading a memory page from disk.
    long unsigned int   cmajflt;     // The number of major faults that the process's waited-for children have made.
    long unsigned int   utime;       // Amount of time that this process has been scheduled in user mode, measured in clock ticks
    long unsigned int   stime;       // Amount of time that this process has been scheduled in kernel mode, measured in clock ticks
    long signed int     cutime;      // Amount of time that this process's waited-for children have been scheduled in user mode, measured in clock ticks
    long signed int     cstime;      // Amount of time that this process's waited-for children have been scheduled in kernel mode, measured in clock ticks
    long signed int     priority;    // Process priority
    long signed int     nice;        // The nice value, a value in the range 19 (low priority) to -20 (high priority).
    long signed int     num_threads; // Number of threads in this process.
    long signed int     itrealvalue; // The time in jiffies before the next SIGALRM is sent to the process due to an interval timer.
    unsigned long long  starttime;   // The time the process started after system boot.
    long unsigned int   vsize;       // Virtual memory size in bytes.
    long signed int     rss;         // Resident Set Size: number of pages the process has in real memory.
    long unsigned int   rsslim;      // Current soft limit in bytes on the rss of the process; see the description of RLIMIT_RSS in getrlimit().
    long unsigned int   startcode;   // The address above which program text can run.
    long unsigned int   endcode;     // The address below which program text can run.
    long unsigned int   startstack;  // The address of the start (i.e., bottom) of the stack.
    long unsigned int   kstkesp;     // The current value of ESP (stack pointer), as found in the kernel stack page for the process.
    long unsigned int   kstkeip;     // The current EIP (instruction pointer).
    long unsigned int   signal;
    long unsigned int   blocked;
    long unsigned int   sigignore;
    long unsigned int   sigcatch;
    long unsigned int   wchan;
    long unsigned int   nswap;
    long unsigned int   cnswap;
    short signed int    exit_signal;
    short signed int    processor;
    short unsigned int  rt_priority;
    short unsigned int  policy;
    unsigned long long  delayacct_blkio_ticks;
    long unsigned int   guest_time;
    long signed int     cguest_time;
    long unsigned int   start_data;
    long unsigned int   end_data;
    long unsigned int   start_brk;
    long unsigned int   arg_start;
    long unsigned int   arg_end;
    long unsigned int   env_start;
    long unsigned int   env_end;
    short signed int    exit_code;
};

class ReadLinuxProcessesStrategy : public ReadProcessStrategy
{
public:
    ReadLinuxProcessesStrategy();

    std::vector<ProcessDescriptor> readAllRunningProcesses() override;
    void readAllRunningProcesses(std::vector<ProcessDescriptor> &pds) override;

    LinuxProcessDescriptor readProcessStatus(int pid);
    long int readProcessUid(short signed int pid);
    std::string getUsername(long int uid);
    ProcessDescriptor adaptProcessDescriptor(LinuxProcessDescriptor pd);

private:
    int readEntireDirectory(std::string path, std::vector<std::string> &objects);
    std::string processNameExtract(std::string initialName);
    bool is_pid(std::string dirName);
};

#endif // READLINUXPROCESSESSTRATEGY_H
