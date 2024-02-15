#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


//https://www.geeksforgeeks.org/stop-and-wait-arq/

/*

Sender:
Rule 1) Send one data packet at a time. 
Rule 2) Send the next packet only after receiving acknowledgement for the previous. 
 

Receiver:
Rule 1) Send acknowledgement after receiving and consuming a data packet. 
Rule 2) After consuming packet acknowledgement need to be sent (Flow Control) 

*/

int main(){




    return 0;
}