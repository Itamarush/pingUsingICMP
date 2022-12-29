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

#define ICMP_HDRLEN 8
#define IP4_HDRLEN 20
#define DESTINATION_IP "8.8.8.8"
#define SOURCE_IP "10.0.2.15" //127.0.0.1

// Checksum algo
unsigned short calculate_checksum(unsigned short *paddress, int len);

int main()
{
    struct icmp icmphdr; // ICMP-header
    char data[IP_MAXPACKET] = "This is the ping.\n";

    int datalen = strlen(data) + 1;

//########## Setting the parametes of the icmp struct ##########//

    icmphdr.icmp_type = ICMP_ECHO;
    icmphdr.icmp_code = 8;
    icmphdr.icmp_id = 18;
    icmphdr.icmp_seq = 0;
    icmphdr.icmp_cksum = 0;

    char packet[IP_MAXPACKET];

    // Next, ICMP header
    memcpy((packet), &icmphdr, ICMP_HDRLEN);

    // After ICMP header, add the ICMP data.
    memcpy(packet + ICMP_HDRLEN, data, datalen);

        // Calculate the ICMP header checksume
    icmphdr.icmp_cksum = calculate_checksum((unsigned short *)(packet), ICMP_HDRLEN + datalen);
    memcpy((packet), &icmphdr, ICMP_HDRLEN);

    struct sockaddr_in dest_in;
    memset(&dest_in, 0, sizeof(struct sockaddr_in));
    dest_in.sin_family = AF_INET;

    // The port is irrelant for Networking and therefore was zeroed.
    // dest_in.sin_addr.s_addr = iphdr.ip_dst.s_addr;
    dest_in.sin_addr.s_addr = inet_addr(DESTINATION_IP);
    // inet_pton(AF_INET, DESTINATION_IP, &(dest_in.sin_addr.s_addr));

    // Create raw socket for IP-RAW (make IP-header by yourself)
    int sock = -1;
    if ((sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
    {
        fprintf(stderr, "socket() failed with error: %d", errno);
        fprintf(stderr, "To create a raw socket, the process needs to be run by Admin/root user.\n\n");
        return -1;
    }

    struct timeval start, end;
    gettimeofday(&start, 0);





}