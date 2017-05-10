#include "ThreatDetector.h"
#include "Assembler.h"
#include "ThreatDetectorMonitor.h"
#include "AssemblerMonitor.h"
#include "Thread.h"
#include "FileAnalyzer.h"
#include "RuleParser.h"
#include "OutputMonitor.h"
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

    /* create output Monitor to avoid race conditions during outputs */
    OutputMonitor outputMonitor;

    std::vector<Rule> rules;
    RuleParser ruleParser;
    ruleParser.parseRulesFromFile(argv[1], rules);

    ThreatDetector threatDetector(&rules);
    ThreatDetectorMonitor threatDetectorMonitor(threatDetector);

    Assembler assembler = Assembler();
    AssemblerMonitor assemblerMonitor(assembler);

    std::vector<Thread*> threads;

    for (int i = 2; i < argc; i++){
        threads.push_back(
                new FileAnalyzer(argv[i], outputMonitor, threatDetectorMonitor,
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
