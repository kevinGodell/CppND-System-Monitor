#ifndef CPPND_SYSTEM_MONITOR_PROCESS_PARSER_H
#define CPPND_SYSTEM_MONITOR_PROCESS_PARSER_H

#include "constants.h"
#include <algorithm>
#include <cerrno>
#include <chrono>
#include <cstring>
#include <dirent.h>
#include <fstream>
#include <iostream>

#include <math.h>
#include <thread>
#include <iterator>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <time.h>
#include <unistd.h>

class ProcessParser {
private:
    std::ifstream stream;
public:
    static std::string getCmd(const std::string &pid);

    static std::vector<std::string> getPidList();

    static std::string getVmSize(const std::string &pid);

    static std::string getCpuPercent(const std::string &pid);

    static long int getSysUpTime();

    static std::string getProcUpTime(const std::string &pid);

    static std::string getProcUser(const std::string &pid);

    static std::vector<std::string> getSysCpuPercent(const std::string &coreNumber = "");

    static float getSysRamPercent();

    static std::string getSysKernelVersion();

    static int getNumberOfCores();

    static int getTotalThreads();

    static int getTotalNumberOfProcesses();

    static int getNumberOfRunningProcesses();

    static std::string getOsName();

    static std::string printCpuStats(const std::vector<std::string> &values1, const std::vector<std::string> &values2);

    static bool isPidExisting(std::string pid);

    static float getSysActiveCpuTime(const std::vector<std::string> &values);

    static float getSysIdleCpuTime(const std::vector<std::string> &values);
};



#endif //CPPND_SYSTEM_MONITOR_PROCESS_PARSER_H