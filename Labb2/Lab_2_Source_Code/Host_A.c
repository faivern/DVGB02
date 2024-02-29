#include "Sim_Engine.h"
#include <string.h>
#include "checkSum.h"
#define payloadSize 20
#define Timer 10
#define A 0

typedef enum{ WAIT_LAYER5, WAIT_ACK } A_state; // Två möjliga tillstånd för A
A_state state; // Nuvarande tillstånd
struct pkt last_packet; // Lagrar det senaste paketet som skickades, om det sker en retransmission
int A_seqNum; // Växlar mellan 0 och 1 för att identifiera packet

/* Called from layer 5, passed the data to be sent to other side */
void A_output( struct msg message) {
 printf("A - HERE\n");
    if(state == WAIT_LAYER5){
      // Gör ett packet från meddelandet
      struct pkt packet;
      packet.seqnum = A_seqNum;
      packet.acknum = 0;
      memcpy(packet.payload, message.data, payloadSize);

      // Räkna ut checksum
      packet.checksum = calcChecksum(packet);

      // Skicka packet till layer 3
      tolayer3(A, packet);

      // Starta timer
      starttimer(A, Timer);

      // Spara det senaste skickade packetet för retransmission
      last_packet = packet;

      // Ändra tillstånd
      state = WAIT_ACK;
    }
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) {
    // om gilitgt ack är mottaget, stoppa timer och informera applikationslagret
    if(state == WAIT_ACK && packet.checksum == calcChecksum(packet) && packet.acknum == A_seqNum){
        stoptimer(A);
        state = WAIT_LAYER5;
        A_seqNum = 1 - A_seqNum;
    }
}

/* Called when A's timer goes off */
void A_timerinterrupt() {
  // timern gick ut, ACK var inte alltså inte mottaget, retransmitta
  if(state == WAIT_ACK){
    tolayer3(A, last_packet);
    starttimer(A, Timer);
  }
}  

/* The following routine will be called once (only) before any other */
/* Host A routines are called. You can use it to do any initialization */
void A_init() {
state = WAIT_LAYER5;
A_seqNum = 0;
}