#ifndef PROYECTO_IPPACKET_H
#define PROYECTO_IPPACKET_H

#include <vector>
#include <string>

class IPPacket {
private:
    IPPacket(unsigned short identificador, unsigned int origen,
                 unsigned int destino, std::string msg);

    unsigned short totalPacketLength;
    unsigned short msgLength;
    unsigned short identificador;
    unsigned short flags;
    unsigned short offset;
    unsigned int direccionOrigen;
    unsigned int direccionDestino;
    std::string msg;

    static bool packetOrderCriteria(IPPacket a, IPPacket b);

    bool isFirstOfFragments();

    bool isLastOfFragments();

public:
    IPPacket(unsigned short totalPacketLength, unsigned short msgLength,
                 unsigned short identificador, unsigned short flags,
                 unsigned short offset, unsigned int direccionOrigen,
                 unsigned int direccionDestino, std::string msg);

    bool isSource(unsigned int src);

    bool isDestination(unsigned int dst);

    bool isWordPresent(std::string);

    unsigned int getSrc();

    unsigned int getDest();

    std::string getMsg();

    bool isOneFragmetPacket();

//    bool isTerminatingPacket();

    static void orderVectorOfPacketsByOffset(std::vector<IPPacket>
                                             *packetsVector);

    bool isFragmentOf(IPPacket *packet);

    static bool fragmentsCompleteWholeMessage(std::vector<IPPacket> *fragments);

    static IPPacket getMessageFromFragments(const std::vector<IPPacket>
                                     *orderedFragments);

    bool operator == (const IPPacket &packet) const;
};


#endif //PROYECTO_IPPACKET_H
