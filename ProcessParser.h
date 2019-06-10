#ifndef CPPND_SYSTEM_MONITOR_PROCESS_PARSER_H
#define CPPND_SYSTEM_MONITOR_PROCESS_PARSER_H

#include <algorithm>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
#include <iterator>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <dirent.h>
#include <time.h>
#include <unistd.h>
#include "constants.h"

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

    static std::string getOSName();

    static std::string PrintCpuStats(std::vector<std::string> values1, std::vector<std::string> values2);

    static bool isPidExisting(std::string pid);
};

float get_sys_active_cpu_time(std::vector<std::string> values)
{
    return (stof(values[S_USER]) +
            stof(values[S_NICE]) +
            stof(values[S_SYSTEM]) +
            stof(values[S_IRQ]) +
            stof(values[S_SOFTIRQ]) +
            stof(values[S_STEAL]) +
            stof(values[S_GUEST]) +
            stof(values[S_GUEST_NICE]));
}

float get_sys_idle_cpu_time(std::vector<std::string>values)
{
    return (stof(values[S_IDLE]) + stof(values[S_IOWAIT]));
}

#endif //CPPND_SYSTEM_MONITOR_PROCESS_PARSER_H