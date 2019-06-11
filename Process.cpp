#include "Process.h"
#include "ProcessParser.h"
#include <string>

void Process::setPid(std::string _pid) {
    this->pid = _pid;
}

std::string Process::getPid() const {
    return this->pid;
}

std::string Process::getProcess() {
    this->mem = ProcessParser::getVmSize(this->pid);
    this->upTime = ProcessParser::getProcUpTime(this->pid);
    this->cpu = ProcessParser::getCpuPercent(this->pid);
    return (this->pid + "   "
            + this->user
            + "   "
            + this->mem.substr(0, 5)
            + "     "
            + this->cpu.substr(0, 5)
            + "     "
            + this->upTime.substr(0, 5)
            + "    "
            + this->cmd.substr(0, 30)
            + "...");
}

std::string Process::getUser() const {
    return this->user;
};

std::string Process::getCmd() const {
    return this->cmd;
};

std::string Process::getCpu() const {
    return this->cpu;
};

std::string Process::getMem() const {
    return this->mem;
};

std::string Process::getUpTime() const {
    return std::string();
};