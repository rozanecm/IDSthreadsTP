#include "FileAnalyzer.h"

FileAnalyzer::FileAnalyzer(char *filepath,
                           ThreatDetectorMonitor &threatDetectorMonitor1,
                           AssemblerMonitor assemblerMonitor1)
        : unSniffer(Sniffer(filepath)),
          threatDetectorMonitor(threatDetectorMonitor1),
          assemblerMonitor(assemblerMonitor1){}
