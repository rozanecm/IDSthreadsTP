#include <iostream>
#include "OutputMonitor.h"
#include "Lock.h"

void OutputMonitor::cout(std::string outMsg) {
    Lock l(m);
    std::cout<<outMsg;
}
