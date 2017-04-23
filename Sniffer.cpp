#include <iostream>
#include "Sniffer.h"
//#include "IPPacket.h"
#include <string>

Sniffer::Sniffer(char *filePath){
    file.open(filePath, std::ifstream::binary);
    file.seekg(0);

    //TODO check file opening
    /* check if file was opened correctly */
//    if (!file.is_open()){
//        std::cout<<"Error opnening file\n";
//    }
//    std::cout<<"File successfully opened\n";
}

Sniffer::Sniffer(Sniffer &&other) {
    this->file = std::move(other.file);
}

IPPacket Sniffer::parseFile() {
    const unsigned int maxMsgLength = 65535;
    const unsigned short headerLength = 20;
    const unsigned int maxReadDataLength = maxMsgLength - headerLength;
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

//    std::cout<<"Total msg length "<<totalPacketLength<<std::endl;
//    std::cout<<"msg length "<<msgLength<<std::endl;

    /* next two bytes are the identificador */
    identificador = getIdentificador(buffer);

//    std::cout<<"identificador: "<<identificador<<std::endl;

    /* next two bytes correspond to: flags(3 bits); offset(13 bits) */
    /* we're interested in the 3rd bit of the flags part */
    flags = getFlags(buffer);
//    std::cout<<"flags: "<<flags<<std::endl;
//    std::cout<<"sizeof(short): "<<sizeof(short)<<std::endl;
    offset = getOffset(buffer);
//    std::cout<<"offset: "<<offset<<std::endl;

    /* ignore next four bytes */

    /* next 4 bytes are direccoin origen*/
    direccionOrigen = getDireccionOrigen(buffer);
//    std::cout<<"dir origen: "<<direccionOrigen<<std::endl;

    /* next 4 bytes are direccoin origen*/
    direccionDestino = getDireccionDestino(buffer);
//    std::cout<<"dir origen: "<<direccionDestino<<std::endl;

    /* buffer donde se guarda el msj leido */
    char msgBuffer[maxReadDataLength] = "a";
    /* leo msj */
    file.read(msgBuffer, msgLength);
    std::string readMsg(msgBuffer, msgLength);
//    std::cout<<"Read msg: "<<readMsg<<std::endl;

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
//    offset = offset << (sizeof(short) * 8 - 5);
//    offset = offset >> (sizeof(short) * 8 - 5);
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
