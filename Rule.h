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

    bool direccionDestinoSospechosa(const IPPacket &packet);

    bool direccionOrigenSospechosa(const IPPacket &packet);

public:
    Rule(unsigned short ruleNumber, unsigned int src,
         unsigned int dst, unsigned int threshold,
         std::string keyword, const std::vector<std::string> &forbiddenWords);

    bool analyzePacket(const IPPacket &packet);

    bool areAllTheWordsPresent(const IPPacket &packet);

    bool isAnyOfTheWordsPresent(const IPPacket &packet);

    bool hasBeenViolated();

    void printViolationMsg(const IPPacket &packet);
};


#endif //PROYECTO_RULE_H
