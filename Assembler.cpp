#include <algorithm>
#include "Assembler.h"
#include <vector>

void Assembler::addPacket(IPPacket packet) {
    this->packetFragments.push_back(packet);
    IPPacket::orderVectorOfPacketsByOffset(&this->packetFragments);
}

Assembler::Assembler() {
}

IPPacket Assembler::getWholePacketFor(IPPacket packet) {
    std::vector<IPPacket> orderedFragments;
    for (unsigned int i = 0; i < packetFragments.size(); i++){
        IPPacket currentPacket = packetFragments.at(i);
        if (currentPacket.isFragmentOf(&packet)){
            orderedFragments.push_back(currentPacket);
        }
    }
        return IPPacket::getMessageFromFragments(&orderedFragments);
}

bool Assembler::fragmentsCompleteWholeMessage(IPPacket *packet) {
    std::vector<IPPacket> orderedFragments;
    for (unsigned int i = 0; i < packetFragments.size(); i++){
        IPPacket currentPacket = packetFragments.at(i);
        if (currentPacket.isFragmentOf(packet)){
            orderedFragments.push_back(currentPacket);
        }
    }
    return IPPacket::fragmentsCompleteWholeMessage(&orderedFragments);
}
