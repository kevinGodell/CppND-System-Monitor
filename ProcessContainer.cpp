#include "ProcessContainer.h"
#include "ProcessParser.h"
#include "Process.h"
#include <string>
#include <vector>

void ProcessContainer::refreshList() {
    std::vector<std::string> pidList = ProcessParser::getPidList();
    this->_list.clear();
    for (const auto &i : pidList) {
        Process proc(i);
        this->_list.push_back(proc);
    }
}

std::string ProcessContainer::printList() {
    std::string result = "";
    for (auto &i : this->_list) {
        result += i.getProcess();
    }
    return result;
}

std::vector<std::vector<std::string> > ProcessContainer::getList() {
    std::vector<std::vector<std::string>> values;
    std::vector<std::string> stringifiedList;
    for (auto &i : ProcessContainer::_list) {
        stringifiedList.push_back(i.getProcess());
    }
    int lastIndex = 0;
    for (int i = 0; i < stringifiedList.size(); i++) {
        if (i % 10 == 0 && i > 0) {
            std::vector<std::string> sub(&stringifiedList[i - 10], &stringifiedList[i]);
            values.push_back(sub);
            lastIndex = i;
        }
        if (i == (ProcessContainer::_list.size() - 1) && (i - lastIndex) < 10) {
            std::vector<std::string> sub(&stringifiedList[lastIndex], &stringifiedList[i + 1]);
            values.push_back(sub);
        }
    }
    return values;
}
