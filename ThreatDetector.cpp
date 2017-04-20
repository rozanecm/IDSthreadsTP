#include <iostream>
#include "ThreatDetector.h"
#include <string>
#include <vector>

void ThreatDetector::addIPPacket(IPPacket packet) {
        this->packetContainer.push_back(packet);
}

ThreatDetector::ThreatDetector(char *rulesPath) {
    try {
        rulesFile.open(rulesPath);
    }catch (std::ios_base::failure e){
        std::cout<<"Error opnening error file"<<std::endl;
    }
    rulesFile.seekg(0);
    unsigned short numOfRulesProcessed = 0;
    while (!rulesFile.eof()) {
        std::vector<std::string> forbiddenWords;
        unsigned int src, dst, threshold;
        std::string keyword;
        rulesFile>>std::hex>>src>>std::hex>>dst>>std::hex>>threshold>>keyword;
        if (rulesFile.eof()){
            break;
        }
        //TEST OUT
//        std::cout<<src<<" "<<dst<<" "<<threshold<<" "<<keyword<<::std::endl;
        std::string aux;
        rulesFile>>aux;
        while (aux != ";"){
            if (keyword != "always") {
                //TEST OUT
//            std::cout<<aux<<std::endl;
                forbiddenWords.push_back(aux);
                rulesFile >> aux;
            }
        }
        rules.push_back(Rule(numOfRulesProcessed, src, dst,
                             threshold, keyword, forbiddenWords));
        numOfRulesProcessed++;
    }
    rulesFile.close();
}

void ThreatDetector::checkForNewThreats() {
    for (unsigned int i = 0; i < this->rules.size(); i++){
        if (rules.at(i).analyzePacket(this->packetContainer.back())){
            if (rules.at(i).hasBeenViolated()) {
                rules.at(i).printViolationMsg(this->packetContainer.back());
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
