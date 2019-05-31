#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include "constants.h"
#include "util.h"
#include "ProcessParser.h"

std::string
ProcessParser::getCmd(std::string pid) {
    return std::string();
}

std::vector<std::string>
ProcessParser::getPidList() {
    return std::vector<std::string>();
}

std::string
ProcessParser::getVmSize(const std::string &pid) {
    std::string line;
    std::string name = "VmData";
    std::string value;
    float result = 0.0f;
    std::ifstream stream = Util::getStream(Path::basePath() + pid + Path::statusPath());
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(), name) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            result = stof(values[1])/1024.0f;
            break;
        }
    }
    return std::to_string(result);
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