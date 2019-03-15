/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> 
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

    //receiving menu from server
     char buffer[1024] = {0}; 
     read(sockfd, buffer, 1024); //reading from the server
     printf("menu sent by server %s\n",buffer);
    
    //receiving input from user
    int option;
    printf("choose service\n");    
    scanf("%d",&option);
    //sending input to server
    int convertedOption= htonl(option);
    write(sockfd, &convertedOption, sizeof(convertedOption));
    fflush(stdin);
    if(option==1)
    {      
       char str[20]; 
   scanf("%s",str);
   printf("%s",str);
    //send file path to server
   write(sockfd, &str, strlen(str));
   // send(sockfd, &str, strlen(str), 0);
    }


    
}

