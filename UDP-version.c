#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 17 // QOTD is on port 17
#define BUFSIZE 100 // Maximum buffer size
#define QUOTE "This is the quote of the day."

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in server, client;
    char buf[BUFSIZE];

    // Create a socket using UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket error");
        return 1;
    }

    // Set up the server address structure
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket to the specified port
    if (bind(sockfd, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("bind error");
        return 1;
    }

    // Receive a message from the client
    int len = sizeof(client);
    if (recvfrom(sockfd, buf, BUFSIZE, 0, (struct sockaddr *) &client, &len) < 0) {
        perror("recvfrom error");
        return 1;
    }

    // Send the quote of the day to the client
    if (sendto(sockfd, QUOTE, strlen(QUOTE), 0, (struct sockaddr *) &client, len) < 0) {
        perror("sendto error");
        return 1;
    }

    return 0;
}
