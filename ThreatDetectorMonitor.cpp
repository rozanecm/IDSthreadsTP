#include "ThreatDetectorMonitor.h"
#include "Lock.h"

ThreatDetectorMonitor::ThreatDetectorMonitor(ThreatDetector threatDetector1) :
        threatDetector(threatDetector1){}

void ThreatDetectorMonitor::addIPPacket(IPPacket packet) {
    Lock l(m);
    threatDetector.addIPPacket(packet);
}

void ThreatDetectorMonitor::checkForNewThreats() {
    Lock l(m);
    threatDetector.checkForNewThreats();
}

void ThreatDetectorMonitor::removeIPPacket(IPPacket packet) {
    Lock l(m);
    threatDetector.removeIPPacket(packet);
}
