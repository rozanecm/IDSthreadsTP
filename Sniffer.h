#include <fstream>
#include <mutex>
#include "IPPacket.h"
#include "OutputMonitor.h"

#ifndef PROYECTO_SNIFFER_H
#define PROYECTO_SNIFFER_H

#endif //PROYECTO_SNIFFER_H
class Sniffer{
private:
    std::mutex m;

    std::ifstream file;

    unsigned short getTotalMsgLength(unsigned char *header);

    unsigned short getIdentificador(unsigned char *buffer);

    unsigned short getFlags(unsigned char *buffer);

    unsigned short getOffset(unsigned char *buffer);

    unsigned int getDireccionOrigen(unsigned char *buffer);

    unsigned int getDireccionDestino(unsigned char *buffer);

    OutputMonitor &outputMonitor;
public:
    explicit Sniffer(char *filePath, OutputMonitor &outputMonitor1);

    explicit Sniffer(Sniffer&& other);

    IPPacket parseFile();

    bool isEOF();

    ~Sniffer();
};
