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
    short totalMsgLength = 0;   //longitud total del msj que se esta leyendo
    short identificador = 0;
    short flags = 0;

    /* buffer donde se guarda lo leido */
    char buffer[maxMsgLength];

    /* leo primeros dos bytes; descarto */
    file.read(buffer, 2);
    /* read other two bytes, which are total msg length */
    file.read(buffer, 2);
    totalMsgLength |= buffer[0];
    totalMsgLength = totalMsgLength << 1;
    totalMsgLength |= buffer[1];

    short msgLength = totalMsgLength - headerLength;

    std::cout<<"msg read: "<<buffer<<std::endl;
    std::cout<<"Total msg length "<<totalMsgLength<<std::endl;
    std::cout<<"msg length "<<msgLength<<std::endl;

    /* next two bytes are the identificador */
    file.read(buffer, 2);
    identificador |= buffer[0];
    identificador = identificador << 1;
    identificador |= buffer[1];

    std::cout<<"identificador: "<<identificador<<std::endl;

    /* next two bytes correspond to: flags(3 bits); offset(13 bits) */
    file.read(buffer, 2);
    /* we're interested in the 3rd bit of the flags part */
    flags |= buffer[3];
    std::cout<<"flags: "<<flags<<std::endl;
    
}

Sniffer::~Sniffer(){
    file.close();
}