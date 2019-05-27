#include <string>
#include <vector>
#include "ProcessParser.h"

std::string
ProcessParser::getCmd(string pid) {
    return std::string();
}

std::vector<std::string>
ProcessParser::getPidList() {
    return std::vector<std::string>();
}

std::string
ProcessParser::getVmSize(std::string pid) {
    return std::string();
}

std::string
ProcessParser::getCpuPercent(std::string pid) {
    return std::string();
}

long int
ProcessParser::getSysUpTime() {
    return 123L;
}

std::string
ProcessParser::getProcUpTime(std::string pid) {
    return std::string();
}

std::string
ProcessParser::getProcUser(std::string pid) {
    return std::string();
}

std::vector<std::string>
ProcessParser::getSysCpuPercent(std::string coreNumber) {
    return std::vector<std::string>();
}

float
ProcessParser::getSysRamPercent() {
    return 12.3F;
}

std::string
ProcessParser::getSysKernelVersion() {
    return std::string();
}

int
ProcessParser::getTotalThreads() {
    return 123;
}

int
ProcessParser::getTotalNumberOfProcesses() {
    return 123;
}

int
ProcessParser::getNumberOfRunningProcesses() {
    return 123;
}

std::string
ProcessParser::getOSName() {
    return std::string();
}

std::string
ProcessParser::PrintCpuStats(std::vector<std::string> values1, std::vector<std::string> values2) {
    return std::string();
}

bool
ProcessParser::isPidExisting(std::string pid) {
    return true;
}