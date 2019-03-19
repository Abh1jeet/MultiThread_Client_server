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
#include<time.h>
#define PORT 8080 




int main(int argc, char *argv[])
{
    int sockfd;
    int len, port;
    struct sockaddr_in address;
    int result;
    char ch;
    int task1=1,task2=2,task3=3,task4=4,task5=5,task6=6,task7=7,task8=8,task9=9;
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


    char message[50];
    float x;
    int intInput;
    int LENGTH=512;
	char sdbuf[LENGTH]; 
    char fs_name[20]; 
    while(1)
    {int task;
    
    //receive task from server
    
    int return_status = read(sockfd, &task, sizeof(task));
    if (return_status > 0) {
    task=ntohl(task);
    }
    //printf("%d\n",task);

        fflush(stdout);
    
       // bzero(message,50); 
    if(task==task1)
    {
        //take input string from user

        
        fflush(stdout);  
        bzero(message,50);         
        scanf(" %[^\n]%*c", message);
        
        //client to server
        //writing string to server
        write(sockfd, &message, strlen(message));


    }
    else if(task ==task2)
    {
        //take string from server
         fflush(stdout);  
        bzero(message,50); 
        read(sockfd, message, 50);
       // printf("string passed by server%s\n",message);


    }
    else if(task==task3)
    {
        //write string to server

        write(sockfd, &message, strlen(message));
       // printf("string passed to server%s\n",message);
         bzero(message,50); 
        
    }
    else if(task==task4)
    {
        //read float from server
        float y;
        recv(sockfd, &y, sizeof(float),0);
        x=y;
    }
    else if(task==task5)
    {
        //print float to user
        printf("time taken=%f \n",x);
    }
    else if(task==task6)
    {
        break;
    }

    else if(task==task7)
    {
        //scan integer from user
    scanf("%d",&intInput);
    //sending integer input to server
    int y= htonl(intInput);
    write(sockfd, &y, sizeof(y));
    fflush(stdin);
    }
    else if(task==task8)
    {    
              //to read and send data to file
		FILE *fs = fopen(message, "r");
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
		printf("File %s from Client was Sent!\n", message);
               
   //***********************************************************************************

    }
    else if(task==task9)
    {
        //print string
        printf("%s\n",message);
        
    }

    }



        

}

