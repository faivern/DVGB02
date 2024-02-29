#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define DEFAULT_PORT 37 // Server porten
#define UNIX_EPOCH 2208988800U // Sekunder 1900-01-01 och 1970-01-01

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    unsigned int alen = sizeof(clientAddr); // Storlek av clientAddr i bytes (för recvfrom) 
    time_t currentTime; 
    int serverPort = DEFAULT_PORT;
    
    // Om port används som argument, används den istället för standardporten
    if (argc > 1) {
        serverPort = atoi(argv[1]);
    }

    // Skapar UDP-socket och nollställer serverAddr för att undvika skräp i minnet
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    memset(&serverAddr, 0, sizeof(serverAddr));

    // Konfigurerar serveraddress
    serverAddr.sin_family = AF_INET; // IPv4
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // lyssna på alla tillgängliga nätverksgränssnitt
    serverAddr.sin_port = htons(serverPort); // Konverterar port till nätverksbyteordning

    // Bindar serversocketen till den konfigurerade serveraddressen
    bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    printf("Server is running on port: %d\n", serverPort);

    // Mainloop för att acceptera och bearbeta förfrågningar
    while(1) {
        recvfrom(sockfd, NULL, 0, 0, (struct sockaddr *)&clientAddr, &alen); // Väntar på request från klienten

        // Skriver ut klientens IP, port och tid vid anslutning
        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);
        printf("Connection from (%s:%d): ", clientIP, ntohs(clientAddr.sin_port));

        // Hämtar och konverterar tiden från nätverksbyteordning och skickar tillbaka till klienten
        currentTime = time(NULL); 
        printf("%s", ctime(&currentTime)); 
        unsigned int timeToSend = htonl((unsigned int)currentTime + UNIX_EPOCH);
        sendto(sockfd, &timeToSend, sizeof(timeToSend), 0, (struct sockaddr *)&clientAddr, alen);
    }
    close(sockfd);
    return 0;
}