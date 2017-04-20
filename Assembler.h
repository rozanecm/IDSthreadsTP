#ifndef PROYECTO_ASSEMBLER_H
#define PROYECTO_ASSEMBLER_H


#include <vector>
#include "IPPacket.h"

class Assembler {
private:
    std::vector<IPPacket> packetFragments;

public:
    Assembler();

    void addPacket(IPPacket packet);

    IPPacket getWholePacketFor(IPPacket packet);

    bool fragmentsCompleteWholeMessage(IPPacket *packet);
};


#endif //PROYECTO_ASSEMBLER_H
