#include <fstream>

#ifndef PROYECTO_SNIFFER_H
#define PROYECTO_SNIFFER_H

#endif //PROYECTO_SNIFFER_H
class Sniffer{
private:
    std::ifstream file;
public:
    Sniffer(char *filePath);
    void parseFile();
    ~Sniffer();

    short getTotalMsgLength(char header[]);
};