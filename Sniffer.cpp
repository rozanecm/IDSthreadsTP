#include <iostream>
#include "Sniffer.h"
#include "Lock.h"
//#include "IPPacket.h"
#include <string>

Sniffer::Sniffer(char *filePath){
    file.open(filePath, std::ifstream::binary);

    /* check if file was opened correctly */
    if (!file.is_open()){
        Lock l(m);
        std::cout<<"Error opnening file\n";
    }

    file.seekg(0);
}

Sniffer::Sniffer(Sniffer &&other) {
    this->file = std::move(other.file);
}

IPPacket Sniffer::parseFile() {
#define maxMsgLength 65535
#define headerLength 20
#define maxReadDataLength maxMsgLength - headerLength
    unsigned short totalPacketLength;          //longitud total
                                                // del msj que se esta leyendo
    unsigned short msgLength;
    unsigned short identificador;
    unsigned short flags;
    unsigned short offset;
    unsigned int direccionOrigen;
    unsigned int direccionDestino;


    /* buffer donde se guarda el header leido */
    unsigned char buffer[headerLength];

    /* leo primeros header */
    file.read((char *) buffer, headerLength);
    /* get total msg length */
    totalPacketLength = getTotalMsgLength(buffer);

    msgLength = totalPacketLength - headerLength;

    /* next two bytes are the identificador */
    identificador = getIdentificador(buffer);

    /* next two bytes correspond to: flags(3 bits); offset(13 bits) */
    /* we're interested in the 3rd bit of the flags part */
    flags = getFlags(buffer);
    offset = getOffset(buffer);

    /* ignore next four bytes */

    /* next 4 bytes are direccoin origen*/
    direccionOrigen = getDireccionOrigen(buffer);

    /* next 4 bytes are direccoin origen*/
    direccionDestino = getDireccionDestino(buffer);

    /* buffer donde se guarda el msj leido */
    char msgBuffer[maxReadDataLength] = "a";
    /* leo msj */
    if (msgLength > maxReadDataLength){
        Lock l(m);
        std::cout<<"Error reading file\n";
    }
    file.read(msgBuffer, msgLength);
    std::string readMsg(msgBuffer, msgLength);

    return IPPacket(totalPacketLength, msgLength, identificador, flags, offset,
                    direccionOrigen, direccionDestino, readMsg);
}

Sniffer::~Sniffer(){
    file.close();
}

unsigned short Sniffer::getTotalMsgLength(unsigned char *header) {
    unsigned short totalMsgLength = 0;
    totalMsgLength |= header[2];
    totalMsgLength = totalMsgLength << 8;
    totalMsgLength |= header[3];
    return totalMsgLength;
}

unsigned short Sniffer::getIdentificador(unsigned char *buffer) {
    unsigned short identificador = 0;
    identificador |= buffer[4];
    identificador = identificador << 8;
    identificador |= buffer[5];
    return identificador;
}

unsigned short Sniffer::getFlags(unsigned char *buffer) {
    unsigned short flags = 0;
    flags |= buffer[6];
    flags = flags >> 5;
    return flags;
}

unsigned short Sniffer::getOffset(unsigned char *buffer) {
    unsigned short offset = 0;
    offset |= buffer[6];
    offset = offset << 8;
    offset |= buffer[7];
    offset = offset << 3;
    offset = offset >> 3;
    return offset;
}

unsigned int Sniffer::getDireccionOrigen(unsigned char *buffer) {
    unsigned int direccionOrigen = 0;
    direccionOrigen |= buffer[12];
    direccionOrigen = direccionOrigen << 8;
    direccionOrigen |= buffer[13];
    direccionOrigen = direccionOrigen << 8;
    direccionOrigen |= buffer[14];
    direccionOrigen = direccionOrigen << 8;
    direccionOrigen |= buffer[15];
    return direccionOrigen;
}

unsigned int Sniffer::getDireccionDestino(unsigned char *buffer) {
    unsigned int direccionDestino = 0;
    direccionDestino |= buffer[16];
    direccionDestino = direccionDestino << 8;
    direccionDestino |= buffer[17];
    direccionDestino = direccionDestino << 8;
    direccionDestino |= buffer[18];
    direccionDestino = direccionDestino << 8;
    direccionDestino |= buffer[19];
    return direccionDestino;
}

bool Sniffer::isEOF(){
    return file.peek() == EOF;
}
