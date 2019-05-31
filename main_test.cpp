#include <iostream>
#include "constants.h"
#include "Util.h"
#include "ProcessParser.h"

int main() {
    std::string pid = "1";

    std::string result = ProcessParser::getVmSize(pid);

    std::cout << result << std::endl;

    return 0;
}



