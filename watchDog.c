#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <mqueue.h>
#include <signal.h>

int main()
{   
    printf("im the Watchdog");
    int server_sock = socket(AF_INET, SOCK_STREAM, 0); 
    char buffer[1];
    struct timeval currentFirstTime ,lastFirstTime;
    
    if (server_sock < 0)
    {
        printf("Could not create socket\n");
        exit(1);
    }
        printf("Created socket succesfully\n");
    

    struct sockaddr_in serverAddress; // new struct decleration of sockaddr_in type
    struct sockaddr_in * pserver_addr = &serverAddress; // Pointer Decleration
    memset(&serverAddress,0, sizeof(serverAddress)); // zerod the last 8 bits so it will match the suckaddr struct

    serverAddress.sin_family = AF_INET; // value = AF_INET. match to the sa_family of suckaddr struct
    serverAddress.sin_port = htons(3008); // switch from host byte order to network(Big endian) byte order.
    int convert = inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
	if (convert <= 0)
	{
		printf("inet_pton() failed\n");
		exit(1);
	}

    int bindNum = bind(server_sock, (struct sockaddr *)&serverAddress , sizeof(serverAddress));
    if (bindNum == -1)
    {
        printf("Could not bind\n");
        perror("Error binding socket");
        exit(1);
    }
    else if (bindNum == 0)
    {
        printf("Binding succesfully to port number: %d\n", 20000);
    }

    if (listen(server_sock, 400) == -1)
	{
	printf("listen() failed with error code\n");
    exit(1);
    }
    printf("Listening...\n");

    
    //### struct for the client address, size and the accept function which makes the first connection with the sender ###//

    struct sockaddr_in clientAddress;  
    socklen_t clientAddressLen = sizeof(clientAddress);

    memset(&clientAddress, 0, sizeof(clientAddress));
    clientAddressLen = sizeof(clientAddress);
    int clientSocket = accept(server_sock, (struct sockaddr *)&clientAddress, &clientAddressLen);
        if (clientSocket == -1)
    	{
           printf("listen failed with error code\n");
           return -1;
    	}
    	    printf("A new client connection accepted\n");

    int i = 0;
    int recieve2;
    int stay = 1;
    while(stay == 1)
    {
        printf("a");
        int recieve1 = recv(clientSocket, buffer, sizeof(buffer), 0);
        printf("b");
        if (buffer[0] == '1')
        {
            printf("here!");        
            // gettimeofday(&currentFirstTime, NULL);
        }

        while (i != 10)
        {
            i++;
            sleep(1); 
            recv(clientSocket, buffer, sizeof(buffer), MSG_DONTWAIT);
            if (i == 10)
            {
                "break";
                stay = 0;
                kill(0, SIGKILL);

            }
        }
    }
}