Förutsättningar
För att bygga och köra servern behöver du följande:

GCC (GNU Compiler Collection) eller en annan C-kompilator
Linux/Unix-baserat operativsystem alternativt subsystem (WSL) för Windows

Bygginstruktioner
Följ dessa steg för att kompilera och köra servern:

Öppna en terminal.
Navigera till mappen där källkoden finns.
Kör följande kommando för att kompilera koden:
gcc web_server.c -o webb

Detta kommando skapar en exekverbar fil med namnet webb.

Körinstruktioner
Efter att du har kompilerat servern kan du köra den med följande kommando:

bash
./webb
Servern startar och lyssnar på port 8080. Du kan nu öppna en webbläsare och navigera till http://localhost:8080

Filstruktur
Servern förväntar sig att filerna den ska skicka finns i /usr/bin/DVGB02/webb

Anpassningar
Du kan ändra servermapp samt port genom att ändra värdena i koden, fullPath och PORT,
samt max antal anslutningar med nConenction.