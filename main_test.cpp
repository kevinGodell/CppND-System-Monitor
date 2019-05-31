#include <iostream>
#include "constants.h"
#include "util.h"
#include "ProcessParser.h"

std::string pid = "1";

std::string result = ProcessParser::getVmSize(pid);

std::cout << result << std::endl;


