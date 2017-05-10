#include <iostream>
#include "OutputMonitor.h"
#include "Lock.h"
#include <string>

void OutputMonitor::cout(std::string outMsg) {
    Lock l(m);
    std::cout<<outMsg;
}
