// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include<pthread.h>
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
#define PORT 8080 

void * socketThread(void *arg)
{   pthread_mutex_lock(&lock);
  int new_socket = *((int *)arg);
  char *hello = "Hello from server 1.echo 2.RTT 3.upload";
  int valread; 
  char buffer[1024] = {0}; 
  
  //server receive
  valread = read( new_socket , buffer, 1024); 
  printf("%s\n",buffer );
  
  //server send
  send(new_socket , hello , strlen(hello) , 0 ); 
  printf("Hello message sent\n"); 
    pthread_mutex_unlock(&lock);
sleep(1);
  close(new_socket);

  pthread_exit(NULL);
}




int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char *hello = "Hello from server"; 
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	//listening
    if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 

    //accepting
    //accepting is a block calll
pthread_t tid[60];
int i=0;
while(1)
    {
        //Accept call creates a new socket for the incoming connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) 
	    { 
		    perror("accept"); 
		    exit(EXIT_FAILURE); 
	    }
        //for each client request creates a thread and assign the client request to it to process
       //so the main thread can entertain next request
        if( pthread_create(&tid[i], NULL, socketThread, &new_socket) != 0 )
           printf("Failed to create thread\n");

       i++; 
    }





	 
    
	
	return 0; 
} 