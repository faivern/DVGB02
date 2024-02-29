#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define DEFAULT_SERVER_PORT 37 // Server porten
#define SERVER_IP "127.0.0.1" // Körs lokalt
#define UNIX_EPOCH 2208988800U // Sekunder 1900-01-01 och 1970-01-01

int main(int argc, char *argv[]) {
    int sockfd, serverPort = DEFAULT_SERVER_PORT;
    char *serverIP = SERVER_IP;
    struct sockaddr_in serverAddr;
    uint32_t timeValue;

     // Om IP-adress används som argument, används den istället för standardadressen
    if (argc > 1) {
        serverIP = argv[1]; 
    }
    // Om port används som argument, används den istället för standardporten
    if (argc > 2) {
        serverPort = atoi(argv[2]); 
    }

    // Skapar UDP-socket och nollställer serverAddr för att undvika skräp i minnet
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 
    memset(&serverAddr, 0, sizeof(serverAddr)); 
    
    // Konfigurerar klientens addresstruktur
    serverAddr.sin_family = AF_INET; // IPv4
    serverAddr.sin_port = htons(serverPort); // Konverterar port till nätverksbyteordning
    inet_pton(AF_INET, serverIP, &serverAddr.sin_addr); // Konverterar IP-adress till binärt format för att kunna användas i adressstrukturen 
  
    // Klienten skickar tomt paket som request för att signalera att servern ska svara med tiden
    sendto(sockfd, NULL, 0, 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    recvfrom(sockfd, &timeValue, sizeof(timeValue), 0, NULL, NULL); 

    // Konverterar tiden från nätverksbyteordning och skriver ut
    timeValue = ntohl(timeValue); 
    time_t time = (time_t)(timeValue - UNIX_EPOCH); 
    printf("Server time: %s", ctime(&time));

    close(sockfd); 
    return 0;
}