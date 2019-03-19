# MultiThread_Client_server
Server that can handle Multiple Client using threading

• To Implement feature that one server can handle many clients simultaneously we have used concept of multi threading.

• If a server is running and clients wants to connect to server a new thread will be created which will handle all the functionality of that client.

• Server will send menu list to client through which user can select any service.

• Client is implemented in such a way that can if a new feature is to be implemented it can be easily added.

• Client can only perform basic operations like
          Reading from user
          Printing to user
          Writing to server
          Reading from server
• Server program is implemented in such a way that it can guide client program in such a way that given three features can be implemented.

• Thus if a new feature is to be added we don’t have to do anything on Client server will guide client in such a way that any feature can be broken down into these basic features.

# HOW TO RUN ?

To compile program a make file is given through which program can be compiled
After compilation server is started first then client is started.
  
          make
   
          ./EchoServer.exe
  
          ./EchoClient.exe
  
