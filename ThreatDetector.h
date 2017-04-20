#ifndef PROYECTO_THREATDETECTOR_H
#define PROYECTO_THREATDETECTOR_H


#include <vector>
#include <fstream>
#include "IPPacket.h"
#include "Rule.h"

class ThreatDetector {
    std::ifstream rulesFile;

    std::vector<IPPacket> packetContainer;

    std::vector<Rule> rules;
public:
    explicit ThreatDetector(char *rulesPath);

    void addIPPacket(IPPacket packet);

    void checkForNewThreats();

    void removeIPPacket(IPPacket packet);
};


#endif //PROYECTO_THREATDETECTOR_H
