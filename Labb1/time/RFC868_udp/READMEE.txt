Förutsättningar
För att bygga och köra dessa program behöver du:

GCC eller en annan C-kompilator
En Unix-baserad miljö

Bygginstruktioner
Server
För att kompilera serverprogrammet, använd följande kommando:

bash
gcc server.c -o timeserver
Detta skapar en exekverbar fil timeserver.

Klient
För att kompilera klientprogrammet, använd följande kommando:

bash
gcc client.c -o timeclient
Detta skapar en exekverbar fil timeclient.

Körinstruktioner
Server
Kör servern med standardporten (37) eller specificera en port som (8037):

bash
./timeserver [port]
Om ingen port specificeras kommer servern att lyssna på port 37.

Klient
Kör klienten med serverns IP-adress (127.0.0.1) och port som argument:

bash
./time_client <server_IP> [port]
Om ingen port anges kommer klienten att försöka ansluta till servern på port 37.

Exempel
För att köra servern på port 8037:

bash
./timeserver 8037
För att ansluta klienten till servern som körs på 127.0.0.1 och port 8037:

bash
./timeclient 127.0.0.1 8037