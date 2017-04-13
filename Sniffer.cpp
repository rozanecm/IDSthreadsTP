#include <iostream>
#include "Sniffer.h"

Sniffer::Sniffer(char *filePath){
    file.open(filePath, std::ifstream::binary);
    file.seekg(0);

    /* check if file was opened correctly */
    if(!file.is_open()){
        std::cout<<"Error opnening file\n";
    }
    std::cout<<"File successfully opened\n";
}

void Sniffer::parseFile(){
    const int maxMsgLength = 65535;
    const short headerLength = 20;
    const int maxReadDataLength = maxMsgLength - headerLength;
    short totalMsgLength = 0;   //longitud total del msj que se esta leyendo
    short identificador = 0;
    short flags = 0;
    short offset = 0;
    int direccionOrigen = 0;
    int direccionDestino = 0;
    std::string readMsg;

    /* buffer donde se guarda el header leido */
    char buffer[headerLength];

    /* leo primeros header */
    file.read(buffer, headerLength);
    /* read other two bytes, which are total msg length */
    totalMsgLength |= buffer[2];
    totalMsgLength = totalMsgLength << 8;
    totalMsgLength |= buffer[3];

    short msgLength = totalMsgLength - headerLength;

    std::cout<<"msg read: "<<buffer<<std::endl;
    std::cout<<"Total msg length "<<totalMsgLength<<std::endl;
    std::cout<<"msg length "<<msgLength<<std::endl;

    /* next two bytes are the identificador */
    identificador |= buffer[4];
    identificador = identificador << 8;
    identificador |= buffer[5];

    std::cout<<"identificador: "<<identificador<<std::endl;

    /* next two bytes correspond to: flags(3 bits); offset(13 bits) */
    /* we're interested in the 3rd bit of the flags part */
    flags |= buffer[6];
    flags = flags >> 1;
    std::cout<<"flags: "<<flags<<std::endl;
    //TODO quedara verificar si es par o impar (si es impar el ultimo bit es 1)
//    std::cout<<"sizeof(short): "<<sizeof(short)<<std::endl;
    offset |= buffer[6];
    offset = offset << 8;
    offset |= buffer[7];
    offset = offset << (sizeof(short) * 8 - 5);
    offset = offset >> (sizeof(short) * 8 - 5);
    std::cout<<"offset: "<<offset<<std::endl;

    /* ignore next four bytes */

    /* next 4 bytes are direccoin origen*/
    direccionOrigen |= buffer[12];
    direccionOrigen = direccionOrigen << 8;
    direccionOrigen |= buffer[13];
    direccionOrigen = direccionOrigen << 8;
    direccionOrigen |= buffer[14];
    direccionOrigen = direccionOrigen << 8;
    direccionOrigen |= buffer[15];
    std::cout<<"dir origen: "<<direccionOrigen<<std::endl;

    /* next 4 bytes are direccoin origen*/
    direccionDestino |= buffer[16];
    direccionDestino = direccionDestino << 8;
    direccionDestino |= buffer[17];
    direccionDestino = direccionDestino << 8;
    direccionDestino |= buffer[18];
    direccionDestino = direccionDestino << 8;
    direccionDestino |= buffer[19];
    std::cout<<"dir origen: "<<direccionDestino<<std::endl;

    /* buffer donde se guarda el msj leido */
    char msgBuffer[maxReadDataLength];
    /* leo msj */
    file.read(msgBuffer, msgLength);
    msgBuffer[msgLength] = '\0';
    readMsg = msgBuffer;

    std::cout<<"Read msg: "<<readMsg<<std::endl;
}

Sniffer::~Sniffer(){
    file.close();
}