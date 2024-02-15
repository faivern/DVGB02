#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#define PORT 8080 // HTTP PORT för webserver
#define BUFFER_SIZE 1024 // 1 byte

/*Filsystemet*/
// Funktionen sendFile skickar fil till klienten
void sendFile(int clientSocket, char *filePath) {
    char buffer[BUFFER_SIZE]; // Temporärt lagra dara i buffert som kommer bli läst av requested fil och skickas över i socket
    int file = open(filePath, O_RDONLY); // Öppna fil i läsbartläge

    // Om filen inte finns, skicka 404 genom klientsocketen
    if (file < 0) {
        char *header = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>404 Not Found</h1>";
        send(clientSocket, header, strlen(header), 0);
    } 
    // Annars skicka filen, 200 OK
    else {
        sprintf(buffer, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
        send(clientSocket, buffer, strlen(buffer), 0);
        
        // Läser fil och skicka över i BUFFER_SIZE-chunks tills filen är tom, -1
        int bytesRead;
        while ((bytesRead = read(file, buffer, BUFFER_SIZE)) > 0) {
            send(clientSocket, buffer, bytesRead, 0);
        }
        close(file);
    }
}
/*HTTP Serverprocess*/
int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    //Skapar TCP-socket och konfigurerar serveraddress
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; 
    serverAddr.sin_port = htons(PORT);

    // Bindar serverSocketen till konfigurerad serveraddress och lyssnar efter inkommande anslutningar
    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 3);
    printf("Listening on port %d\n", PORT);

    // Mainloop för att acceptera och bearbeta förfrågningar
    while(1) {
        // Acceptera anslutning och läs förfrågning från klient
        clientSocket = accept(serverSocket, NULL, NULL);
        read(clientSocket, buffer, BUFFER_SIZE);

        // Tolkar/parsar HTTP-förfrågan för att hämta sökväg och metod
        char *method = strtok(buffer, " ");
        char *path = strtok(NULL, " ");
        char fullPath[256] = "/usr/bin/DVGB02/sample_website"; // sökväg till server filer
        strcat(fullPath, path); 
        
        // Om GET-request, skicka efterfrågade filen
        if (strcmp(method, "GET") == 0) {
            sendFile(clientSocket, fullPath);
        }
       close(clientSocket);
    }
    return 0;
}