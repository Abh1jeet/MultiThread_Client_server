/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>
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
   char fs_name[20]; 
   scanf("%s",fs_name);
   printf("%s",fs_name);
    //**********************send file path to server****************************
        int LENGTH=512;
        //char* fs_name = "hello.txt";
		char sdbuf[LENGTH]; 
		printf("Client Sending %s to the Server.....\n ", fs_name);
		FILE *fs = fopen(fs_name, "r");
		if(fs == NULL)
		{
			printf("ERROR: File %s not found.\n", fs_name);
			exit(1);
		}

		bzero(sdbuf, LENGTH); 
		int fs_block_sz; 
		while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs)) > 0)
		{
		    if(send(sockfd, sdbuf, fs_block_sz, 0) < 0)
		    {
		        break;
		    }
		    bzero(sdbuf, LENGTH);
		}
		printf("Ok File %s from Client was Sent!\n", fs_name);
   //***********************************************************************************

   
   //write(sockfd, &str, strlen(str));
   
   
   
   
   
   
   
   // send(sockfd, &str, strlen(str), 0);









    }


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

