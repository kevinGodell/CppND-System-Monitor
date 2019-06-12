#ifndef CPPND_SYSTEM_MONITOR_PROCESS_CONTAINER_H
#define CPPND_SYSTEM_MONITOR_PROCESS_CONTAINER_H

#include "Process.h"
#include <string>
#include <vector>

class ProcessContainer {

private:
    std::vector<Process> _list;
public:
    ProcessContainer() {
        this->refreshList();
    }

    void refreshList();

    std::string printList();

    std::vector<std::vector<std::string>> getList();
};

#endif