#include "FileAnalyzer.h"

FileAnalyzer::FileAnalyzer(char *filepath, OutputMonitor &outputMonitor1,
                           ThreatDetectorMonitor &threatDetectorMonitor1,
                           AssemblerMonitor &assemblerMonitor1)
        : unSniffer(Sniffer(filepath, outputMonitor1)),
          threatDetectorMonitor(threatDetectorMonitor1),
          assemblerMonitor(assemblerMonitor1){}

void FileAnalyzer::run(){
    while (!unSniffer.isEOF()) {
        IPPacket currentPacket = unSniffer.parseFile();
        if (currentPacket.isOneFragmetPacket()){
            threatDetectorMonitor.addIPPacket(currentPacket);
            threatDetectorMonitor.checkForNewThreats();
            threatDetectorMonitor.removeIPPacket(currentPacket);
        }else{
            assemblerMonitor.addPacket(currentPacket);
            if (assemblerMonitor.fragmentsCompleteWholeMessage(&currentPacket)){
                IPPacket wholePacket =
                        assemblerMonitor.getWholePacketFor(currentPacket);
                threatDetectorMonitor.addIPPacket(wholePacket);
                threatDetectorMonitor.checkForNewThreats();
                threatDetectorMonitor.removeIPPacket(currentPacket);
            }
        }
    }
}

FileAnalyzer::~FileAnalyzer() {}
