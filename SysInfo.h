#ifndef CPPND_SYSTEM_MONITOR_SYS_INFO_H
#define CPPND_SYSTEM_MONITOR_SYS_INFO_H

#include "ProcessParser.h"
#include <string>
#include <iostream>
#include <vector>

class SysInfo {
private:
    std::vector<std::string> lastCpuStats;
    std::vector<std::string> currentCpuStats;
    std::vector<std::string> coresStats;
    std::vector<std::vector<std::string>> lastCpuCoresStats;
    std::vector<std::vector<std::string>> currentCpuCoresStats;
    std::string cpuPercent;
    float memPercent;
    std::string osName;
    std::string kernelVer;
    long upTime;
    int totalProc;
    int runningProc;
    int threads;
public:

    SysInfo() {
        /*
        Getting initial info about system
        Initial data for individual cores is set
        System data is set
        */
        this->getOtherCores(ProcessParser::getNumberOfCores());
        this->setLastCpuMeasures();
        this->setAttributes();
        this->osName = ProcessParser::getOsName();
        this->kernelVer = ProcessParser::getSysKernelVersion();
    }

    void setAttributes();

    void setLastCpuMeasures();

    std::string getMemPercent() const;

    long getUpTime() const;

    std::string getThreads() const;

    std::string getTotalProc() const;

    std::string getRunningProc() const;

    std::string getKernelVersion() const;

    std::string getOsName() const;

    std::string getCpuPercent() const;

    void getOtherCores(int _size);

    void setCpuCoresStats();

    std::vector<std::string> getCoresStats() const;
};

#endif