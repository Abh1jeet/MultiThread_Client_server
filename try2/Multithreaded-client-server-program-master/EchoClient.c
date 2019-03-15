/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#define PORT 8080 

int main(int argc, char *argv[])
{
    int sockfd;
    int len, port;
    struct sockaddr_in address;
    int result;
    char ch;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORT); 

    len = sizeof(address);

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("oops: client3");
        exit(1);
    }
    printf("Enter a character to send to server\n");
    
    while(1){
        
        printf("\nEnter character: ");
        scanf(" %c", &ch);

        write(sockfd, &ch, 1); //writing to the server
        if(ch == 'q' || ch == 'Q'){ /* This if clause was nessecary so that we could */
            close(sockfd);          /* easily close the server-to-client connection without errors */
            exit(0);
      }
        read(sockfd, &ch, 1); //reading from the server
        printf("char from server = %c\n", ch);
    }
}

