#include <string>

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
private:
    std::string pid;
    std::string user;
    std::string cmd;
    std::string cpu;
    std::string mem;
    std::string upTime;

public:
    Process(std::string pid) {
        this->pid = pid;
        this->user = ProcessParser::getProcUser(pid);
        //TODOs:
        //complete for mem
        //complete for cmd
        //complete for upTime
        //complete for cpu
    }

    void setPid(int pid);

    std::string getPid() const;

    std::string getUser() const;

    std::string getCmd() const;

    int getCpu() const;

    int getMem() const;

    std::string getUpTime() const;

    std::string getProcess();
};

void Process::setPid(int pid) {
    this->pid = pid;
}

std::string Process::getPid() const {
    return this->pid;
}

std::string Process::getProcess() {
    if (!ProcessParser::isPidExisting(this->pid))
        return "";
    this->mem = ProcessParser::getVmSize(this->pid);
    this->upTime = ProcessParser::getProcUpTime(this->pid);
    this->cpu = ProcessParser::getCpuPercent(this->pid);

    return (this->pid + "   " + //TODO: finish the string! this->user + "   "+ mem...cpu...upTime...;
}
