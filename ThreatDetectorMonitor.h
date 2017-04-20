#ifndef PROYECTO_THREATDETECTORMONITOR_H
#define PROYECTO_THREATDETECTORMONITOR_H


#include <mutex>
#include "IPPacket.h"
#include "Rule.h"
#include "ThreatDetector.h"

class ThreatDetectorMonitor {
private:
    std::mutex m;

    ThreatDetector &threatDetector;

public:
    ThreatDetectorMonitor(ThreatDetector threatDetector1);

    void addIPPacket(IPPacket packet);

    void checkForNewThreats();

    void removeIPPacket(IPPacket packet);
};


#endif //PROYECTO_THREATDETECTORMONITOR_H
