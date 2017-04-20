#ifndef PROYECTO_RULE_H
#define PROYECTO_RULE_H

#include <iostream>
#include <vector>
#include "IPPacket.h"
#include <string>

class Rule {
private:
    unsigned short ruleNumber;
    unsigned int src;
    unsigned int dst;
    unsigned int threshold;
    std::string keyword;
    std::vector <std::string> forbiddenWords;

    unsigned int numberOfTimesTheRuleWasApplied;

    bool direccionDestinoSospechosa(IPPacket &packet);

    bool direccionOrigenSospechosa(IPPacket &packet);

public:
    Rule(unsigned short ruleNumber, unsigned int src,
         unsigned int dst, unsigned int threshold,
         std::string keyword, std::vector <std::string> forbiddenWords);

    bool analyzePacket(IPPacket &packet);

    bool areAllTheWordsPresent(IPPacket &packet);

    bool isAnyOfTheWordsPresent(IPPacket &packet);

    bool hasBeenViolated();

    void printViolationMsg(IPPacket &packet);
};


#endif //PROYECTO_RULE_H
