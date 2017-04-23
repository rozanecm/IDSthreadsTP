#ifndef PROYECTO_FILEANALYZER_H
#define PROYECTO_FILEANALYZER_H


class FileAnalyzer : public Thread{
    Sniffer unSniffer;

    ThreatDetectorMonitor &threatDetectorMonitor;

    AssemblerMonitor &assemblerMonitor;
};


#endif //PROYECTO_FILEANALYZER_H
