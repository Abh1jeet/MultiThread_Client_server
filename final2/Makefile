all: EchoServer.exe EchoClient.exe

EchoServer.exe: EchoServer.c
	gcc EchoServer.c -lpthread -o EchoServer.exe

EchoClient.exe: EchoClient.c
	gcc -o EchoClient.exe EchoClient.c

clean:
	rm *.exe all

