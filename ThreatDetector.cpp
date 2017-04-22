#include <iostream>
#include "ThreatDetector.h"
#include <string>
#include <vector>

void ThreatDetector::addIPPacket(IPPacket packet) {
        this->packetContainer.push_back(packet);
}

ThreatDetector::ThreatDetector(std::vector<Rule> *rules) {
    this->rules = rules;
}

void ThreatDetector::checkForNewThreats() {
    for (unsigned int i = 0; i < this->rules->size(); i++){
        if (rules->at(i).analyzePacket(this->packetContainer.back())){
            if (rules->at(i).hasBeenViolated()) {
                rules->at(i).printViolationMsg(this->packetContainer.back());
            }
        }
    }
}

void ThreatDetector::removeIPPacket(IPPacket packet) {
    for (unsigned int i = 0; i < packetContainer.size(); i++){
        IPPacket currentPacket = packetContainer.at(i);
        if (currentPacket == packet){
            packetContainer.erase(packetContainer.begin()+i);
        }
    }
}

ThreatDetector::ThreatDetector(const ThreatDetector &threatDetector) {
    this->packetContainer = threatDetector.packetContainer;
    this->rules = threatDetector.rules;
//    ThreatDetector threatDetector1 = threatDetector;
}
//
//ThreatDetector::ThreatDetector(const std::vector<IPPacket> packetContainer,
//                               const std::vector<Rule> &rules) {
//    this->rules = std::move(rules);
//}

ThreatDetector ThreatDetector::operator=(const ThreatDetector &threatDetector) {
    packetContainer = threatDetector.packetContainer;
    rules = threatDetector.rules;
    return ThreatDetector(rules);
}
