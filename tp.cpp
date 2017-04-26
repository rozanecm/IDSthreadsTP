#include "ThreatDetector.h"
#include "Assembler.h"
#include "ThreatDetectorMonitor.h"
#include "AssemblerMonitor.h"
#include "Thread.h"
#include "FileAnalyzer.h"
#include <string>
#include <vector>

#define RETURNERROR 1
#define EXPECTEDRETURN 0

void setOfRules(char *rulesPath, std::vector<Rule> &rules);

int main(int argc, char *argv[]) {
    /* chequeo cant. de parametros: debe haber al menos 3
     * (nombre del programa, reglas, y al menos una captura
     * */
    if (argc < 3){
        return RETURNERROR;
    }
    std::vector<Rule> rules;
    setOfRules(argv[1], rules);
    ThreatDetector threatDetector(&rules);
    ThreatDetectorMonitor threatDetectorMonitor(threatDetector);

    Assembler assembler = Assembler();
    AssemblerMonitor assemblerMonitor(assembler);

    std::vector<Thread*> threads;

    for (int i = 2; i < argc; i++){
        threads.push_back(new FileAnalyzer(argv[i], threatDetectorMonitor,
                                           assemblerMonitor));
    }

    for (unsigned int i = 0; i < threads.size(); i++){
        threads.at(i)->start();
    }

    for (unsigned int i = 0; i < threads.size(); i++){
        threads.at(i)->join();
        delete threads.at(i);
    }
    return EXPECTEDRETURN;
}

void setOfRules(char *rulesPath, std::vector<Rule> &rules) {
    std::ifstream rulesFile;
    rulesFile.open(rulesPath);
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
