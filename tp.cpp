#include <iostream>
#include "Sniffer.h"

int main(int argc, char *argv[]) {
    /* chequeo cant. de parametros: debe haber al menos 3
     * (nombre del programa, reglas, y al menos una captura
     * */
//    if (argc < 3){
//        return 1;
//    }
//    std::cout <<argv[1]<< std::endl;
    Sniffer unSniffer(argv[1]);
    unSniffer.parseFile();
    return 0;
}