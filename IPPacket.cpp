#include <algorithm>
#include "IPPacket.h"
#include <string>
#include <vector>

IPPacket::IPPacket(unsigned short totalPacketLength, unsigned short msgLength,
                   unsigned short identificador, unsigned short flags,
                   unsigned short offset, unsigned int direccionOrigen,
                   unsigned int direccionDestino, const std::string &msg) :
        totalPacketLength(totalPacketLength), msgLength(msgLength),
        identificador(identificador), flags(flags), offset(offset),
        direccionOrigen(direccionOrigen), direccionDestino(direccionDestino),
        msg(msg){}

bool IPPacket::isSource(unsigned int src) const {
    return this->direccionOrigen == src;
}

bool IPPacket::isDestination(unsigned int dst) const {
    return this->direccionDestino == dst;
}

bool IPPacket::isWordPresent(std::string word) const{
    return (this->msg.find(word) != std::string::npos);
}

std::string IPPacket::getMsg() const {
    return this->msg;
}

unsigned int IPPacket::getSrc() const {
    return this->direccionOrigen;
}

unsigned int IPPacket::getDest() const {
    return this->direccionDestino;
}

bool IPPacket::isOneFragmetPacket() {
    /* si el ultimo bit del flag es 0, y ademas el offset es tambien0,
     * entonces el packet es completo.
     * El tema del flag lo podemos estudiar chequeando paridad
     * */
    return (this->flags % 2 == 0 && this->offset == 0);
}

void IPPacket::orderVectorOfPacketsByOffset(
        std::vector<IPPacket> *packetsVector) {
    std::sort(packetsVector->begin(), packetsVector->end(),
              packetOrderCriteria);
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
                   unsigned int destino, std::string msg) :
        identificador(identificador), direccionOrigen(origen),
        direccionDestino(destino), msg(msg){}


bool IPPacket::operator == (const IPPacket &packet) const {
    return (
            this->identificador == packet.identificador
            && this->direccionOrigen == packet.direccionOrigen
            && this->direccionDestino == packet.direccionDestino
            && this->msg == packet.msg);
}
