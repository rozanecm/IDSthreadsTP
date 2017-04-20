#include "Rule.h"
#include <string>
#include <vector>

Rule::Rule(unsigned short ruleNumber, unsigned int src,
           unsigned int dst, unsigned int threshold,
           std::string keyword, std::vector<std::string> forbiddenWords) {
    this->ruleNumber = ruleNumber;
    this->src = src;
    this->dst = dst;
    this->threshold = threshold;
    this->keyword = keyword;
    this->forbiddenWords = forbiddenWords;
    this->numberOfTimesTheRuleWasApplied = 0;
}

bool Rule::direccionDestinoSospechosa(IPPacket &packet) {
    return (this->dst == 0 || packet.isDestination(this->dst));
}

bool Rule::direccionOrigenSospechosa(IPPacket &packet) {
    return (this->src == 0 || packet.isSource(this->src));
}

bool Rule::analyzePacket(IPPacket &packet){
    /* wanted to implemet with switch, but since it's not supported in c++
     * I go with an if. Not so nice tough
     * */
    if (direccionOrigenSospechosa(packet) &&
            direccionDestinoSospechosa(packet)){
        if (this->keyword == "always"){
            this->numberOfTimesTheRuleWasApplied++;
            return true;
        }else if (this->keyword == "all"){
            if (areAllTheWordsPresent(packet)) {
                this->numberOfTimesTheRuleWasApplied++;
                return true;
            }
        }else {
            /* caso any */
            if (isAnyOfTheWordsPresent(packet)) {
                this->numberOfTimesTheRuleWasApplied++;
                return true;
            }
        }
    }
    return false;
}

bool Rule::areAllTheWordsPresent(IPPacket &packet) {
    for (unsigned int i = 0; i < this->forbiddenWords.size(); i++){
        if (!packet.isWordPresent(this->forbiddenWords.at(i))){
            return false;
        }
    }
    return true;
}

bool Rule::isAnyOfTheWordsPresent(IPPacket &packet) {
    for (unsigned int i = 0; i < this->forbiddenWords.size(); i++){
        if (packet.isWordPresent(this->forbiddenWords.at(i))){
            return true;
        }
    }
    return false;
}

bool Rule::hasBeenViolated() {
    return this->threshold <= this->numberOfTimesTheRuleWasApplied;
}

void Rule::printViolationMsg(IPPacket &packet) {
    std::cout << "Rule " << ruleNumber << ": ALERT! " << packet.getSrc()
              << " -> " << std::hex << packet.getDest() << ":";
    for (unsigned int i = 0; i < packet.getMsg().length(); i++){
        std::cout<<" "<< std::hex<< (int) packet.getMsg()[i];
    }
    std::cout<<std::endl;
}
