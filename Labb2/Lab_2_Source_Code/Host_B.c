#include "Sim_Engine.h"
#include "checkSum.h"
#define B 1
int expectedSeqNum;

/* Called from layer 5, passed the data to be sent to other side */
void B_output( struct msg message) {
  /* DON'T IMPLEMENT */
}

/* Called from layer 3, when a packet arrives for layer 4 */
void B_input(struct pkt packet) {
  struct pkt ackPacket;
  printf("B - HERE\n");

// Verifiera packets checksum, skicka till layer 5 om korrekt
if(packet.checksum == calcChecksum(packet) && packet.seqnum == expectedSeqNum){
  tolayer5(B, packet.payload);

  // Skicka ack för mottaget packet till layer 3 
  ackPacket.seqnum = 0;
  ackPacket.acknum = packet.seqnum;
  ackPacket.checksum = calcChecksum(ackPacket); 
  tolayer3(B, ackPacket);

  expectedSeqNum = 1 - expectedSeqNum; // Växla till nästa förväntade seqNum

// Annars, skicka ack för senaste korrekta packet till layer 3
} else {
  ackPacket.seqnum = 0;
  ackPacket.acknum = 1 - expectedSeqNum; // acka det senaste korrekta packet
  ackPacket.checksum = calcChecksum(ackPacket);

  tolayer3(B, ackPacket);
  }
}

/* Called when B's timer goes off */
void B_timerinterrupt() {
  // Används ej här. Främst sändarsidan.
}  

/* The following routine will be called once (only) before any other */
/* Host B routines are called. You can use it to do any initialization */
void B_init() {
  expectedSeqNum = 0;
}