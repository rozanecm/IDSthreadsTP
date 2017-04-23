#ifndef PROYECTO_FILEANALYZER_H
#define PROYECTO_FILEANALYZER_H


#include "Thread.h"
#include "Sniffer.h"
#include "ThreatDetectorMonitor.h"
#include "AssemblerMonitor.h"

class FileAnalyzer : public Thread{
    Sniffer unSniffer;

    ThreatDetectorMonitor &threatDetectorMonitor;

    AssemblerMonitor &assemblerMonitor;

public:
    FileAnalyzer(char* filepath,
                 ThreatDetectorMonitor &threatDetectorMonitor1,
                 AssemblerMonitor assemblerMonitor1);
};


#endif //PROYECTO_FILEANALYZER_H
