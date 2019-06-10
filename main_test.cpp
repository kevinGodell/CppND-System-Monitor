#include <iostream>
#include "constants.h"
#include "Util.h"
#include "ProcessParser.h"

int main() {

    //std::string pid = "1";

    //std::cout << "Enter pid: ";

    //std::cin >> pid;

    std::cout << "getSysUpTime " << ProcessParser::getSysUpTime() << std::endl;

    //-----------------

    std::cout << "getNumberOfCores " << ProcessParser::getNumberOfCores() << std::endl;

    //-----------------

    std::vector<std::string> pidList = ProcessParser::getPidList();

    std::cout << "getPidList size " << pidList.size() << std::endl;

    std::cout << "//////////////////////////////////////////////////////////////////////" << std::endl;

    for (const std::string & pid : pidList) {

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

        result = ProcessParser::getProcUser(pid);

        std::cout << "getProcUser " << result << std::endl;

        //-----------------

        result = ProcessParser::getCmd(pid);

        std::cout << "getCmd " << result << std::endl;

        //-----------------

        std::cout << "//////////////////////////////////////////////////////////////////////" << std::endl;
    }

    return 0;
}



