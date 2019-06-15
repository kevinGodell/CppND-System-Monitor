#include "ProcessParser.h"
#include "constants.h"
#include "Util.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

bool
ProcessParser::isPidExisting(const std::string &pid) {
    std::string pidPath = Path::basePath() + pid;
    DIR *dir = nullptr;
    dir = opendir(pidPath.c_str());
    if (dir) {
        closedir(dir);
        return true;
    }
    return false;
}

std::string
ProcessParser::getCmd(const std::string &pid) {
    std::string line;
    std::ifstream stream = Util::getStream(Path::basePath() + pid + Path::cmdPath());
    std::getline(stream, line);
    return line;
}

std::vector<std::string>
ProcessParser::getPidList() {
    DIR *dir;
    std::vector<std::string> container;
    if (!(dir = opendir(Path::basePath().c_str()))) throw std::runtime_error(std::strerror(errno));
    while (dirent *dirp = readdir(dir)) {
        if (dirp->d_type != DT_DIR) continue;
        if (std::all_of(dirp->d_name, dirp->d_name + std::strlen(dirp->d_name), [](char c) { return std::isdigit(c); })) {
            container.emplace_back(dirp->d_name);
        }
    }
    if (closedir(dir)) throw std::runtime_error(std::strerror(errno));
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
    result = 100.0f * ((total_time / freq) / seconds);
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
ProcessParser::getSysCpuPercent(const std::string &coreNumber) {
    // It is possible to use this method for selection of data for overall cpu or every core.
    // when nothing is passed "cpu" line is read
    // when, for example "0" is passed  -> "cpu0" -> data for first core is read
    std::string line;
    std::string name = "cpu" + coreNumber;
    std::ifstream stream = Util::getStream(Path::basePath() + Path::statPath());
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(), name) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            // set of cpu data active and idle times;
            return values;
        }
    }
    return std::vector<std::string>();
}

float
ProcessParser::getSysRamPercent() {
    std::string line;
    std::string name1 = "MemAvailable:";
    std::string name2 = "MemFree:";
    std::string name3 = "Buffers:";

    std::string value;
    std::ifstream stream = Util::getStream((Path::basePath() + Path::memInfoPath()));
    float total_mem = 0;
    float free_mem = 0;
    float buffers = 0;
    while (std::getline(stream, line)) {
        if (total_mem != 0 && free_mem != 0)
            break;
        if (line.compare(0, name1.size(), name1) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            total_mem = std::stof(values[1]);
        }
        if (line.compare(0, name2.size(), name2) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            free_mem = std::stof(values[1]);
        }
        if (line.compare(0, name3.size(), name3) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            buffers = std::stof(values[1]);
        }
    }
    //calculating usage:
    return float(100.0 * (1 - (free_mem / (total_mem - buffers))));
}

std::string
ProcessParser::getSysKernelVersion() {
    std::string line;
    std::string name = "Linux version ";
    std::ifstream stream = Util::getStream((Path::basePath() + Path::versionPath()));
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(), name) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            return values[2];
        }
    }
    return "";
}

int
ProcessParser::getNumberOfCores() {
    std::string line;
    std::string name = "cpu cores";
    std::ifstream stream = Util::getStream((Path::basePath() + Path::cpuInfoPath()));
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(), name) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            return std::stoi(values[3]);
        }
    }
    return 0;
}

int
ProcessParser::getTotalThreads() {
    std::string line;
    int result = 0;
    std::string name = "Threads:";
    std::vector<std::string> _list = ProcessParser::getPidList();
    for (const auto &pid : _list) {
        //getting every process and reading their number of their threads
        std::ifstream stream = Util::getStream((Path::basePath() + pid + Path::statusPath()));
        while (std::getline(stream, line)) {
            if (line.compare(0, name.size(), name) == 0) {
                std::istringstream buf(line);
                std::istream_iterator<std::string> beg(buf), end;
                std::vector<std::string> values(beg, end);
                result += stoi(values[1]);
                break;
            }
        }
        //todo return result;
    }
    return result;
}

int
ProcessParser::getTotalNumberOfProcesses() {
    std::string line;
    int result = 0;
    std::string name = "processes";
    std::ifstream stream = Util::getStream((Path::basePath() + Path::statPath()));
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(), name) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            result += std::stoi(values[1]);
            break;
        }
    }
    return result;
}

int
ProcessParser::getNumberOfRunningProcesses() {
    std::string line;
    int result = 0;
    std::string name = "procs_running";
    std::ifstream stream = Util::getStream((Path::basePath() + Path::statPath()));
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(), name) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            result += std::stoi(values[1]);
            break;
        }
    }
    return result;
}

std::string
ProcessParser::getOsName() {
    std::string line;
    std::string name = "PRETTY_NAME=";
    std::ifstream stream = Util::getStream(("/etc/os-release"));
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(), name) == 0) {
            std::size_t found = line.find('=');
            found++;
            std::string result = line.substr(found);
            result.erase(std::remove(result.begin(), result.end(), '"'), result.end());
            return result;
        }
    }
    return "";
}

std::string
ProcessParser::printCpuStats(const std::vector<std::string> &values1, const std::vector<std::string> &values2) {
    /*
Because CPU stats can be calculated only if you take measures in two different time,
this function has two parameters: two vectors of relevant values.
We use a formula to calculate overall activity of processor.
*/
    float activeTime = ProcessParser::getSysActiveCpuTime(values2) - ProcessParser::getSysActiveCpuTime(values1);
    float idleTime = ProcessParser::getSysIdleCpuTime(values2) - ProcessParser::getSysIdleCpuTime(values1);
    float totalTime = activeTime + idleTime;
    float result = 100.0f * (activeTime / totalTime);
    return std::to_string(result);
}

float
ProcessParser::getSysActiveCpuTime(const std::vector<std::string> &values) {
    return (std::stof(values[S_USER]) +
            std::stof(values[S_NICE]) +
            std::stof(values[S_SYSTEM]) +
            std::stof(values[S_IRQ]) +
            std::stof(values[S_SOFTIRQ]) +
            std::stof(values[S_STEAL]) +
            std::stof(values[S_GUEST]) +
            std::stof(values[S_GUEST_NICE]));
}

float
ProcessParser::getSysIdleCpuTime(const std::vector<std::string> &values) {
    return (std::stof(values[S_IDLE]) + std::stof(values[S_IOWAIT]));
}

