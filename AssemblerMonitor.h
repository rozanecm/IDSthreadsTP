#ifndef PROYECTO_ASSEMBLERMONITOR_H
#define PROYECTO_ASSEMBLERMONITOR_H


#include <mutex>
#include "Assembler.h"

class AssemblerMonitor {
private:
    std::mutex m;

    Assembler &assembler;

public:
    AssemblerMonitor (Assembler &assembler1);

    void addPacket(IPPacket packet);

    IPPacket getWholePacketFor(IPPacket packet);

    bool fragmentsCompleteWholeMessage(IPPacket *packet);
};


#endif //PROYECTO_ASSEMBLERMONITOR_H
