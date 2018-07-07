#include "readlinuxprocessesstrategy.h"

ReadLinuxProcessesStrategy::ReadLinuxProcessesStrategy()
{

}

std::vector<ProcessDescriptor> ReadLinuxProcessesStrategy::readAllRunningProcesses()
{
    std::vector<std::string> procDir;
    std::vector<ProcessDescriptor> pds;
    std::string path = "/proc";
    LinuxProcessDescriptor pd;

    if(readEntireDirectory(path, procDir) != 0) {
        return pds;
    }

    // TO DO - READ PROCESS NAME FROM COMMAND LINE ARGUMENT FILE
    pds.clear();
    for(int i = 0; i < procDir.size(); i++) {
        if(is_pid(procDir[i])) {
            pd = readProcessStatus(std::stoi(procDir[i]));
            pd.pname = processNameExtract(pd.pname);
            pd.uname = getUsername(readProcessUid(pd.pid));

            pds.push_back(adaptProcessDescriptor(pd));
        }
    }
    return pds;
}

void ReadLinuxProcessesStrategy::readAllRunningProcesses(std::vector<ProcessDescriptor> &pds)
{
    std::vector<std::string> procDir;
    std::string path = "/proc";
    LinuxProcessDescriptor pd;

    if(readEntireDirectory(path, procDir) != 0) {
        return ;
    }

    pds.clear();
    for(int i = 0; i < procDir.size(); i++) {
        if(is_pid(procDir[i])) {
            pd = readProcessStatus(std::stoi(procDir[i]));
            pd.pname = processNameExtract(pd.pname);
            pd.uname = getUsername(readProcessUid(pd.pid));

            pds.push_back(adaptProcessDescriptor(pd));
        }
    }
}

ProcessDescriptor ReadLinuxProcessesStrategy::adaptProcessDescriptor(LinuxProcessDescriptor pd)
{
    return ProcessDescriptor(pd.pid, pd.pname, pd.uname);
}

LinuxProcessDescriptor ReadLinuxProcessesStrategy::readProcessStatus(int pid)
{
    LinuxProcessDescriptor pd;
    std::ifstream pState;
    std::string path = "/proc/";
    path += std::to_string(pid) += "/stat";

    pState.open(path);
    pState >> pd.pid         >> pd.pname                 >> pd.state
           >> pd.ppid        >> pd.pgrp                  >> pd.session
           >> pd.tty_nr      >> pd.tpgid                 >> pd.flags
           >> pd.minflt      >> pd.cminflt               >> pd.majflt
           >> pd.cmajflt     >> pd.utime                 >> pd.stime
           >> pd.cutime      >> pd.cstime                >> pd.priority
           >> pd.nice        >> pd.num_threads           >> pd.itrealvalue
           >> pd.starttime   >> pd.vsize                 >> pd.rss
           >> pd.rsslim      >> pd.startcode             >> pd.endcode
           >> pd.startstack  >> pd.kstkesp               >> pd.kstkeip
           >> pd.signal      >> pd.blocked               >> pd.sigignore
           >> pd.sigcatch    >> pd.wchan                 >> pd.nswap
           >> pd.cnswap      >> pd.exit_signal           >> pd.processor
           >> pd.policy      >> pd.delayacct_blkio_ticks >> pd.guest_time
           >> pd.cguest_time >> pd.end_data              >> pd.start_brk
           >> pd.arg_start   >> pd.arg_end               >> pd.env_start
           >> pd.env_end     >> pd.exit_code;
    pState.close();
    return pd;
}

long int ReadLinuxProcessesStrategy::readProcessUid(short signed int pid)
{
    std::string path = "/proc/";
    path += std::to_string(pid) += "/status";
    std::ifstream uidFile(path);

    std::string uid;
    while(uidFile >> uid) {
        if(uid == "Uid:") {
            uidFile >> uid;
            break;
        }
    }

    uidFile.close();
    return std::stoll(uid);
}

std::string ReadLinuxProcessesStrategy::getUsername(long int uid)
{
    struct passwd *pw;
    pw = getpwuid(uid);
    return pw ? std::string(pw->pw_name) : "";
}

int ReadLinuxProcessesStrategy::ReadLinuxProcessesStrategy::readEntireDirectory(std::string path, std::vector<std::string> &objects)
{
    DIR *dir;
    dirent *entry;
    std::string dirName;

    dir = opendir(path.c_str());
    if (dir == NULL) {
        return -1;
    }

    while ((entry = readdir(dir)) != NULL) {
        dirName = entry->d_name;
        dirName = entry->d_name;
        objects.push_back(dirName);
    }
    return 0;
}

std::string ReadLinuxProcessesStrategy::processNameExtract(std::string initialName)
{
    std::smatch match;
    std::regex pname_extractor("[^()]+");
    std::regex_search(initialName, match, pname_extractor);
    std::string ret = match.str();
    return ret;
}

bool ReadLinuxProcessesStrategy::is_pid(std::string dirName)
{
    std::regex pidExtractor("[[:digit:]]+");
    return std::regex_match(dirName, pidExtractor);
}
