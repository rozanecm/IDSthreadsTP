#include "FileAnalyzer.h"

FileAnalyzer::FileAnalyzer(char *filepath,
                           ThreatDetectorMonitor &threatDetectorMonitor1,
                           AssemblerMonitor assemblerMonitor1)
        : unSniffer(Sniffer(filepath)),
          threatDetectorMonitor(threatDetectorMonitor1),
          assemblerMonitor(assemblerMonitor1){}

void FileAnalyzer::run() {
    while (!unSniffer.isEOF()) {
        IPPacket currentPacket = unSniffer.parseFile();
        if (currentPacket.isOneFragmetPacket()){
            threatDetectorMonitor.addIPPacket(currentPacket);
            threatDetectorMonitor.checkForNewThreats();
            threatDetectorMonitor.removeIPPacket(currentPacket);
        }else{
            assemblerMonitor.addPacket(currentPacket);
            if (assemblerMonitor.fragmentsCompleteWholeMessage(&currentPacket)){
                threatDetectorMonitor.addIPPacket(
                        assemblerMonitor.getWholePacketFor(currentPacket));
                threatDetectorMonitor.checkForNewThreats();
                threatDetectorMonitor.removeIPPacket(currentPacket);
            }
        }
    }
}
