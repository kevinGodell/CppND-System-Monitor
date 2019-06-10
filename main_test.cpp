#include <iostream>
#include "constants.h"
#include "Util.h"
#include "ProcessParser.h"

int main() {

    std::string pid = "1";

    std::cout << "Enter pid: ";

    std::cin >> pid;

    //-----------------

    std::string result = ProcessParser::getVmSize(pid);

    std::cout << "getVmSize " << result << std::endl;

    //-----------------

    result = ProcessParser::getProcUpTime(pid);

    std::cout << "getProcUpTime " << result << std::endl;

    //-----------------

    result = ProcessParser::getCpuPercent(pid);

    std::cout << "getCpuPercent " << result << std::endl;

    //-----------------

    std::cout << "getSysUpTime " << ProcessParser::getSysUpTime() << std::endl;

    //-----------------

    result = ProcessParser::getProcUser(pid);

    std::cout << "getProcUser " << result << std::endl;

    //-----------------

    std::vector<std::string> list = ProcessParser::getPidList();

    std::cout << "getPidList size " << list.size() << std::endl;

    //-----------------

    return 0;
}



