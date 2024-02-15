#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define SERVER_PORT 37 // Server porten
#define SERVER_IP "127.0.0.1" // Körs lokalt

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;
    uint32_t timeValue;

    // Skapar UDP-socket och nollställer serverAddr för att undvika skräp i minnet
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 
    memset(&serverAddr, 0, sizeof(serverAddr)); 
    
    // Konfigurerar klientens addresstruktur
    serverAddr.sin_family = AF_INET; // IPv4
    serverAddr.sin_port = htons(SERVER_PORT); // Konverterar port till nätverksbyteordning
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr); // Konverterar IP-adress till binärt format för att kunna användas i adressstrukturen 
  
    // Klienten skickar tomt paket som request för att signalera att servern ska svara med tiden
    sendto(sockfd, NULL, 0, 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    recvfrom(sockfd, &timeValue, sizeof(timeValue), 0, NULL, NULL); 

    // Konverterar tiden från nätverksbyteordning och skriver ut
    timeValue = ntohl(timeValue); 
    time_t time = (time_t)(timeValue - 2208988800U); 
    printf("Server time: %s", ctime(&time));

    close(sockfd); 
    return 0;
}