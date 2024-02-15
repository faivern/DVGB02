#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define PORT 37 // Server porten

int main() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    unsigned int alen = sizeof(clientAddr); // Storlek av clientAddr i bytes (för recvfrom) 
    time_t currentTime; 

    // Skapar UDP-socket och nollställer serverAddr för att undvika skräp i minnet
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    memset(&serverAddr, 0, sizeof(serverAddr));

    // Konfigurerar serveraddress
    serverAddr.sin_family = AF_INET; // IPv4
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // lyssna på alla tillgängliga nätverksgränssnitt
    serverAddr.sin_port = htons(PORT); // Konverterar port till nätverksbyteordning

    // Bindar serversocketen till den konfigurerade serveraddressen
    bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    printf("Server is running on port: %d\n", PORT);

    // Mainloop för att acceptera och bearbeta förfrågningar
    while(1) {
        recvfrom(sockfd, NULL, 0, 0, (struct sockaddr *)&clientAddr, &alen) // Väntar på request från klienten
        currentTime = time(NULL); // Hämtar nuvarande tid
        unsigned int timeToSend = htonl((unsigned int)currentTime + 2208988800U); //RFC 868 är antalet sekunder sedan 00:00 1 januari 1900 GMT
        sendto(sockfd, &timeToSend, sizeof(timeToSend), 0, (struct sockaddr *)&clientAddr, alen) // Skickar tiden till klienten
    }
    close(sockfd);
    return 0;
}