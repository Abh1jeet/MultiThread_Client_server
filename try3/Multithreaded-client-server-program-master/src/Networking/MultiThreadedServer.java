package Networking;

/**
 * Created by anas on 10/24/15.
 */

import java.net.ServerSocket;
import java.net.Socket;
import java.io.IOException;

public class MultiThreadedServer implements Runnable {

    int serverPort            = 8080;
    ServerSocket serverSocket = null;
    boolean isStopped         = false;
    Thread runningThread      = null;

    public MultiThreadedServer(int port){
        this.serverPort = port;
    }

    public void run() {

        this.runningThread = Thread.currentThread();

        openServerSocket();

        while(! isStopped()) {
            Socket clientSocket = null;
            try {
                clientSocket = this.serverSocket.accept();
            } catch (IOException e) {
                if(isStopped()){
                    System.out.println("Server Stopped with if statement");
                    return;
                }
                throw new RuntimeException("Error accepting client connection", e);
            }
            new Thread(
                    new WorkerRunnable(clientSocket, "Multithreaded Server")
            ).start();
           /* try {
                processClientRequest(clientSocket);
            } catch (IOException e) {
                //log exception and go on to next request.
            }*/
        }

        System.out.println("Server stopped, while loop finished");
    }

    /*private void processClientRequest(Socket clientSocket) throws IOException {
        InputStream  input  = clientSocket.getInputStream();
        OutputStream output = clientSocket.getOutputStream();
        long time = System.currentTimeMillis();

        output.write(("HTTP/1.1 200 OK\n\n<html><body>" +
                "SingleThreaded Server: " +
                time +
                "</body></html>").getBytes());
        output.close();
        input.close();
        System.out.println("Request processed: " + time);
    }*/

    private synchronized boolean isStopped() {
        return this.isStopped;
    }

    public synchronized void stop() {
        this.isStopped = true;
        try {
            this.serverSocket.close();
        } catch (IOException e) {
            throw new RuntimeException("Error closing Server", e);
        }
    }

    private void openServerSocket() {
        try{
            this.serverSocket = new ServerSocket(this.serverPort);
        } catch (IOException e) {
            throw new RuntimeException("Cannot open port 8080", e);
        }
    }

    /*public static void main(String[] args) {
        SingleThreadedServer server = new SingleThreadedServer(9000);
        new Thread(server).start();

        try {
            Thread.sleep(10 * 1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Stopping Server from main");
        server.stop();
    }*/

    public static void main(String[] args) {
        MultiThreadedServer server = new MultiThreadedServer(9000);
        new Thread(server).start();

        try {
            Thread.sleep(20 * 1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Stopping Server in main");
        server.stop();
    }

}
