#include <iostream>
#include "Sniffer.h"

Sniffer::Sniffer(char *filePath){
    file.open(filePath);
    if(!file.is_open()){
        std::cout<<"Error opnening file";
    }
    
    file.close();
}