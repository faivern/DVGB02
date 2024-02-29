#include "Sim_Engine.h"
#include "checkSum.h"
#define payloadSize 20

// Räknar ut checksumman för ett packet
int calcChecksum(struct pkt packet) {
     int checksum = packet.seqnum + packet.acknum;
for (int i = 0; i < payloadSize; i++) {
    checksum += packet.payload[i];
  }
  return checksum;
}