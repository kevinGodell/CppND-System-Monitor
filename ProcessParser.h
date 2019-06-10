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

    static std::string printCpuStats(const std::vector<std::string> &values1, const std::vector<std::string> &values2);

    static bool isPidExisting(std::string pid);
};

float
getSysActiveCpuTime(std::vector<std::string> values) {
    return (std::stof(values[S_USER]) +
            std::stof(values[S_NICE]) +
            std::stof(values[S_SYSTEM]) +
            std::stof(values[S_IRQ]) +
            std::stof(values[S_SOFTIRQ]) +
            std::stof(values[S_STEAL]) +
            std::stof(values[S_GUEST]) +
            std::stof(values[S_GUEST_NICE]));
}

float getSysIdleCpuTime(std::vector<std::string> values) {
    return (std::stof(values[S_IDLE]) + std::stof(values[S_IOWAIT]));
}

#endif //CPPND_SYSTEM_MONITOR_PROCESS_PARSER_H