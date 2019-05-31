#include <iostream>
#include "constants.h"
#include "util.h"
#include "ProcessParser.h"

std::string pid = "1";

std::cout << ProcessParser::getVmSize(pid) << std::endl;