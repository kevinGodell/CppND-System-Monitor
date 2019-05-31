#ifndef CPPND_SYSTEM_MONITOR_UTIL_H
#define CPPND_SYSTEM_MONITOR_UTIL_H

#include <string>
#include <fstream>

// Classic helper function
class Util {

public:

    static std::string convertToTime(long int input_seconds);

    static std::string getProgressBar(const std::string &percent);

    static std::ifstream getStream(const std::string &path);
};

#endif //CPPND_SYSTEM_MONITOR_UTIL_H