#include <fstream>
#include "IPPacket.h"

#ifndef PROYECTO_SNIFFER_H
#define PROYECTO_SNIFFER_H

#endif //PROYECTO_SNIFFER_H
class Sniffer{
private:
    std::ifstream file;

    unsigned short getTotalMsgLength(unsigned char *header);

    unsigned short getIdentificador(unsigned char *buffer);

    unsigned short getFlags(unsigned char *buffer);

    unsigned short getOffset(unsigned char *buffer);

    unsigned int getDireccionOrigen(unsigned char *buffer);

    unsigned int getDireccionDestino(unsigned char *buffer);

public:
    explicit Sniffer(char *filePath);

    explicit Sniffer(Sniffer&& other);

    IPPacket parseFile();

    bool isEOF();

    ~Sniffer();
};
