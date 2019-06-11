#ifndef CPPND_SYSTEM_MONITOR_PROCESS_H
#define CPPND_SYSTEM_MONITOR_PROCESS_H

#include "ProcessParser.h"
#include <string>

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
private:
    std::string pid;
    std::string user;
    std::string cmd;
    std::string cpu;
    std::string mem;
    std::string upTime;

public:
    explicit Process(const std::string &pid) {
        this->pid = pid;
        this->user = ProcessParser::getProcUser(pid);
        this->mem = ProcessParser::getVmSize(pid);
        this->cmd = ProcessParser::getCmd(pid);
        this->upTime = ProcessParser::getProcUpTime(pid);
        this->cpu = ProcessParser::getCpuPercent(pid);
    }

    void setPid(std::string pid);

    std::string getPid() const;

    std::string getUser() const;

    std::string getCmd() const;

    std::string getCpu() const;

    std::string getMem() const;

    std::string getUpTime() const;

    std::string getProcess();
};

#endif