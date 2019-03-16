#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> 
#include <pthread.h>
#define PORT 8080 
void *thread_connection(void *); // Thread function
int c = 0; // For numbering and keeping track of our clients

int main(int argc, char *argv[])
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    pthread_t tid;
    int port;
     // passing port number as an argument
                          /* Avoid giving special port numbers */      
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_sockfd == -1)
    {
        perror("Could not create server socket");
        exit(2);
    }

    //sigaction(SIGCHLD, &sa, NULL);
    server_address.sin_family = AF_INET; //IPv4 stream socket family
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    printf("I am going to listen on %d \n",server_address.sin_port);
    
    
    server_len = sizeof(server_address);
    /* Binding server to the IP address */
    if (bind(server_sockfd, (struct sockaddr *)&server_address, server_len)== -1)
    {
	perror("Unable to bind");
	exit(2);
    }

/*  Create a connection queue, ignore child exit details and wait for clients.  */

    listen(server_sockfd, 5); // Waits or listens for connection
    printf("server waiting\n");
    client_len = sizeof(client_address);

    /* While loop runs for every client connection ACCEPTED by the server */ 
    while( (client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len)) ) 
    {   
        c++; // For numbering connected clients
        printf("Connection Established with client %d\n",c );

        /* Creating thread for every client connection ACCEPTED */
        if( pthread_create(&tid, NULL, thread_connection, (void*) &client_sockfd) < 0)
        {                                                 /* Passing the thread is the CLIENT SOCKET */  
            perror("Thread not created");                 /* with which server and client can communicate in thread function */
            return 1;
        }
        printf("Thread assigned to client %d \n", c);
    }

    if( client_sockfd < 0)
    {
        perror("accept falied");
        return 1;
    }
    return 0;        
}

void *thread_connection(void *client_sockfd)
{
    char ch;
    /* Converting client_sockfd back to integer type and assigning it to client_sock */
    int client_sock = *(int*)client_sockfd;
    /* Now using client_scok for server-to-client communication */

   //server sending menu
   char *menu = "1.echo 2.RTT 3.upload";
    send(client_sock , menu , strlen(menu) , 0 ); 
    
   //server receiving option from client
   int option;
  // read(client_sock,&option,sizeof(option));
  // printf("%d\n",option);
   
   int recv_option = 0;

   int return_status = read(client_sock, &recv_option, sizeof(recv_option));
    if (return_status > 0) {
   //  fprintf(stdout, "Received int = %d\n", ntohl(recv_option));
    option=ntohl(recv_option);
    }
    else {
    // Handling erros here
        }
fflush(stdin);
   if(option==1)
   {  
       char file[1024] = {0}; 
    // read(client_sock, file, 1024); //reading from the sender
    // printf("filePath received %s \n",file);
//************************************reading entire file**********************
        int LENGTH=512;
        char revbuf[LENGTH]; // Receiver buffer
        char* fr_name = "receive.txt";
		FILE *fr = fopen(fr_name, "a");
		if(fr == NULL)
			printf("File %s Cannot be opened file on server.\n", fr_name);
		else
		{
			bzero(revbuf, LENGTH); 
			int fr_block_sz = 0;
			while((fr_block_sz = recv(client_sock, revbuf, LENGTH, 0)) > 0) 
			{
			    int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
				
				bzero(revbuf, LENGTH);
				if (fr_block_sz == 0 || fr_block_sz != 512) 
				{
					break;
				}
			}
			
			printf("Ok received from client!\n");
			fclose(fr); 
		}



//**********************************************************************************




   }
   else
   {
       printf("pagal hai kya\n");
   }




    while(1)
    {
        read(client_sock, &ch, 1);
        if (ch == 'Q' || ch == 'q') 
        {
            close(client_sock); 
            break;  
        }else {
                ch++;
                write(client_sock, &ch, 1);
            }
    }
    printf("\nYou enetered Q, Connection is now closed with client %d\n", c);
    c--; // keeping track of our client
    
}




        
	    
    


