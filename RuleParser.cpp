#include <fstream>
#include "RuleParser.h"
#include <string>
#include <vector>

void RuleParser::parseRulesFromFile(char *filePath, std::vector<Rule> &rules) {
    std::ifstream rulesFile;
    rulesFile.open(filePath);
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

        std::string aux;
        rulesFile>>aux;
        while (aux != ";"){
            if (keyword != "always") {
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
