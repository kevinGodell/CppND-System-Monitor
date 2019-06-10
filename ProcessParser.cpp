#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <iostream>
#include "constants.h"
#include "Util.h"
#include "ProcessParser.h"

std::string
ProcessParser::getCmd(std::string pid) {

    char *cstr = new char[pid.size() + 1];
    pid.copy(cstr, pid.size() + 1);
    cstr[pid.size()] = '\0';

    std::cout << cstr << "\n";

    return std::string();
}

std::vector<std::string>
ProcessParser::getPidList() {
    DIR *dir;
    // Basically, we are scanning /proc dir for all directories with numbers as their names
    // If we get valid check we store dir names in vector as list of machine pids
    std::vector<std::string> container;
    if (!(dir = opendir("/proc")))
        throw std::runtime_error(std::strerror(errno));

    while (dirent *dirp = readdir(dir)) {
        // is this a directory?
        if (dirp->d_type != DT_DIR)
            continue;
        // Is every character of the name a digit?
        if (std::all_of(dirp->d_name, dirp->d_name + std::strlen(dirp->d_name), [](char c) { return std::isdigit(c); })) {
            container.emplace_back(dirp->d_name);
        }
    }
    //Validating process of directory closing
    if (closedir(dir))
        throw std::runtime_error(std::strerror(errno));
    return container;
}

std::string
ProcessParser::getVmSize(const std::string &pid) {
    float result = 0.0f;
    std::string line;
    std::string name = "VmData";
    std::ifstream stream = Util::getStream(Path::basePath() + pid + Path::statusPath());
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(), name) == 0) {
            //std::cout << "Found " << name << std::endl;
            //std::cout << "line " << line << std::endl;
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            //std::cout << "Value " << std::stof(values[1]) << std::endl;
            // conversion kB -> MB
            result = std::stof(values[1]) / float(1024);
            break;
        }
    }
    return std::to_string(result);
}

std::string
ProcessParser::getCpuPercent(const std::string &pid) {
    float result;
    std::string line;
    std::ifstream stream = Util::getStream(Path::basePath() + pid + "/" + Path::statPath());
    std::getline(stream, line);
    std::istringstream buf(line);
    std::istream_iterator<std::string> beg(buf), end;
    std::vector<std::string> values(beg, end);
    // acquiring relevant times for calculation of active occupation of CPU for selected process
    float utime = std::stof(ProcessParser::getProcUpTime(pid));
    float stime = std::stof(values[14]);
    float cutime = std::stof(values[15]);
    float cstime = std::stof(values[16]);
    float starttime = std::stof(values[21]);
    float uptime = ProcessParser::getSysUpTime();
    float freq = sysconf(_SC_CLK_TCK);
    float total_time = utime + stime + cutime + cstime;
    float seconds = uptime - (starttime / freq);
    result = 100.0 * ((total_time / freq) / seconds);
    return std::to_string(result);
}

long int
ProcessParser::getSysUpTime() {
    std::string line;
    std::ifstream stream = Util::getStream((Path::basePath() + Path::upTimePath()));
    std::getline(stream, line);
    std::istringstream buf(line);
    std::istream_iterator<std::string> beg(buf), end;
    std::vector<std::string> values(beg, end);
    return std::stoi(values[0]);
}

std::string
ProcessParser::getProcUpTime(const std::string &pid) {
    float result;
    std::string line;
    std::ifstream stream = Util::getStream((Path::basePath() + pid + "/" + Path::statPath()));
    std::getline(stream, line);
    //std::cout << "line " << line << std::endl;
    //std::cout << "clock tick " << _SC_CLK_TCK << std::endl;
    //std::cout << "frequency " << sysconf(_SC_CLK_TCK) << std::endl;
    std::string str = line;
    std::istringstream buf(str);
    std::istream_iterator<std::string> beg(buf), end;
    std::vector<std::string> values(beg, end);
    result = std::stof(values[13]) / float(sysconf(_SC_CLK_TCK));
    return std::to_string(result);
}

std::string
ProcessParser::getProcUser(const std::string &pid) {
    std::string line;
    std::string name = "Uid:";
    std::string result;
    std::ifstream stream = Util::getStream((Path::basePath() + pid + Path::statusPath()));
    // Getting UID for user
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(), name) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            result = values[1];
            break;
        }
    }
    stream = Util::getStream("/etc/passwd");
    name = ("x:" + result);
    // Searching for name of the user with selected UID
    while (std::getline(stream, line)) {
        if (line.find(name) != std::string::npos) {
            result = line.substr(0, line.find(':'));
            return result;
        }
    }
    return "";
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
ProcessParser::getNumberOfCores() {
    return 123;
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