#ifndef PROYECTO_RULEPARSER_H
#define PROYECTO_RULEPARSER_H


#include <vector>
#include "Rule.h"

class RuleParser {
public:
    void parseRulesFromFile(char *filePath, std::vector <Rule> &rules);
};


#endif //PROYECTO_RULEPARSER_H
