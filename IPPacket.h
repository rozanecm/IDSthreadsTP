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
             unsigned int direccionDestino, const std::string &msg);

    /* check if given int is equal to packet's source */
    bool isSource(unsigned int src) const;

    /* check if given int is equal to packet's source */
    bool isDestination(unsigned int dst) const;

    /* check if passed string is contained in packet's message */
    bool isWordPresent(std::string) const;

    unsigned int getSrc() const;

    unsigned int getDest() const;

    std::string getMsg() const;

    /* checks is packet is complete by itself or if
     * it is part of a bigger packet
     * */
    bool isOneFragmetPacket();

    static void orderVectorOfPacketsByOffset(std::vector<IPPacket>
                                             *packetsVector);

    /* checks if passed packet and current packet are part of the same packet */
    bool isFragmentOf(IPPacket *packet);

    /* checks if passed fragments complete whole message or
     * if there are still packets missing
     * */
    static bool fragmentsCompleteWholeMessage(std::vector<IPPacket> *fragments);

    /* get message contained in passed packets.
     * Passed packets MUST be able to complete whole message.
     * To check that, use fragmentsCompleteWholeMessage
     * */
    static IPPacket getMessageFromFragments(const std::vector<IPPacket>
                                     *orderedFragments);

    bool operator == (const IPPacket &packet) const;
};


#endif //PROYECTO_IPPACKET_H
