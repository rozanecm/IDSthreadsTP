//#include <iostream>
//#include <vector>
#include "Sniffer.h"
//#include "IPPacket.h"
#include "ThreatDetector.h"
#include "Assembler.h"

int main(int argc, char *argv[]) {
    /* chequeo cant. de parametros: debe haber al menos 3
     * (nombre del programa, reglas, y al menos una captura
     * */
    if (argc < 3){
        return 1;
    }
    ThreatDetector threatDetector(argv[1]);
    Assembler assembler = Assembler();
    for (int i = 2; i < argc; i++){
        Sniffer unSniffer(argv[i]);
        while (!unSniffer.isEOF()) {
            IPPacket currentPacket = unSniffer.parseFile();
            if (currentPacket.isOneFragmetPacket()){
                threatDetector.addIPPacket(currentPacket);
                threatDetector.checkForNewThreats();
                threatDetector.removeIPPacket(currentPacket);
            }else{
                assembler.addPacket(currentPacket);
                if (assembler.fragmentsCompleteWholeMessage(&currentPacket)){
                    threatDetector.addIPPacket(
                            assembler.getWholePacketFor(currentPacket));
                    threatDetector.checkForNewThreats();
                    threatDetector.removeIPPacket(currentPacket);
                }
            }
        }
    }
    return 0;
}
