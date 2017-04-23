#include "AssemblerMonitor.h"
#include "Lock.h"

AssemblerMonitor::AssemblerMonitor(Assembler &assembler1) :
        assembler(assembler1){}

void AssemblerMonitor::addPacket(IPPacket packet) {
    Lock l(m);
    assembler.addPacket(packet);
}

IPPacket AssemblerMonitor::getWholePacketFor(IPPacket packet) {
    Lock l(m);
    return assembler.getWholePacketFor(packet);
}

bool AssemblerMonitor::fragmentsCompleteWholeMessage(IPPacket *packet) {
    Lock l(m);
    return assembler.fragmentsCompleteWholeMessage(packet);
}
