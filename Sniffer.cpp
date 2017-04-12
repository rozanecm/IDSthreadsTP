#include "Sniffer.h"

Sniffer::Sniffer(char *filePath){
    file.open(filePath);
    file.close();
}