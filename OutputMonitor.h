#ifndef PROYECTO_OUTPUTMONITOR_H
#define PROYECTO_OUTPUTMONITOR_H


#include <mutex>
#include <string>

class OutputMonitor {
private:
    std::mutex m;

public:
    void cout(std::string outMsg);
};


#endif //PROYECTO_OUTPUTMONITOR_H
