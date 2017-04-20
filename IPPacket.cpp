#include <algorithm>
#include "IPPacket.h"
#include <string>
#include <vector>

IPPacket::IPPacket(unsigned short totalPacketLength, unsigned short msgLength,
                   unsigned short identificador, unsigned short flags,
                   unsigned short offset, unsigned int direccionOrigen,
                   unsigned int direccionDestino, std::string msg) {
    this->totalPacketLength = totalPacketLength;
    this->msgLength = msgLength;
    this->identificador = identificador;
    this->flags = flags;
    this->offset = offset;
    this->direccionOrigen = direccionOrigen;
    this->direccionDestino = direccionDestino;
    this->msg = msg;
}

bool IPPacket::isSource(unsigned int src) {
    return this->direccionOrigen == src;
}

bool IPPacket::isDestination(unsigned int dst) {
    return this->direccionDestino == dst;
}

bool IPPacket::isWordPresent(std::string word) {
    return (this->msg.find(word) != std::string::npos);
}

std::string IPPacket::getMsg() {
    return this->msg;
}

unsigned int IPPacket::getSrc() {
    return this->direccionOrigen;
}

unsigned int IPPacket::getDest() {
    return this->direccionDestino;
}

bool IPPacket::isOneFragmetPacket() {
    /* si el ultimo bit del flag es 0, y ademas el offset es tambien0,
     * entonces el packet es completo.
     * El tema del flag lo podemos estudiar chequeando paridad
     * */
    return (this->flags % 2 == 0 && this->offset == 0);
}

//bool IPPacket::isTerminatingPacket() {
//    return (this->flags % 2 == 0 && this->offset > 0);
//}

void IPPacket::orderVectorOfPacketsByOffset(
        std::vector<IPPacket> *packetsVector) {
    std::sort(packetsVector->begin(), packetsVector->end(),
              packetOrderCriteria);
    //todo ver bien funcion de condicion de ordenamiento
}

bool IPPacket::packetOrderCriteria(IPPacket a, IPPacket b){
    return a.offset < b.offset;
}

bool IPPacket::isFragmentOf(IPPacket *packet) {
    return (this->identificador == packet->identificador
            && this->direccionOrigen == packet->direccionOrigen
            && this->direccionDestino == packet->direccionDestino);
}

bool IPPacket::fragmentsCompleteWholeMessage(std::vector<IPPacket> *fragments) {
    if (fragments->front().isFirstOfFragments()
        && fragments->back().isLastOfFragments()){
        for (unsigned int i = 1; i < fragments->size(); i++){
            if (fragments->at(i).offset
                != fragments->at(i-1).msgLength + fragments->at(i-1).offset){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool IPPacket::isFirstOfFragments(){
    return this->offset == 0;
}

bool IPPacket::isLastOfFragments(){
    return this->flags % 2 == 0;
}

IPPacket IPPacket::getMessageFromFragments(
        //todo borrar fragments usados.
        const std::vector<IPPacket> *orderedFragments) {
    unsigned short identificador = orderedFragments->at(0).identificador;
    unsigned int direccionOrigen = orderedFragments->at(0).direccionOrigen;
    unsigned int direccionDestino = orderedFragments->at(0).direccionDestino;
    std::string wholeMsg;
    for (unsigned int i = 0; i < orderedFragments->size(); i++){
        wholeMsg.append(orderedFragments->at(i).msg);
    }
    return IPPacket(identificador, direccionOrigen, direccionDestino, wholeMsg);
}

IPPacket::IPPacket(unsigned short identificador, unsigned int origen,
                   unsigned int destino, std::string msg) {
    this->identificador = identificador;
    this->direccionOrigen = origen;
    this->direccionDestino = destino;
    this->msg = msg;
}


bool IPPacket::operator == (const IPPacket &packet) const {
    return (
//            this->totalPacketLength == packet.totalPacketLength
//            && this->msgLength == packet.msgLength
            this->identificador == packet.identificador
//            && this->flags == packet.flags
//            && this->offset == packet.offset
            && this->direccionOrigen == packet.direccionOrigen
            && this->direccionDestino == packet.direccionDestino
            && this->msg == packet.msg);
}
