package Networking;

/**
 * Created by anas on 10/24/15.
 */
import java.io.InputStream;
import java.io.OutputStream;
import java.io.IOException;
import java.net.Socket;

public class WorkerRunnable implements Runnable {

    Socket clientSocket = null;
    String serverText = null;

    public WorkerRunnable(Socket clientSocket, String serverText) {
        this.clientSocket = clientSocket;
        this.serverText = serverText;
    }

    public void run() {
        try {
            InputStream input = clientSocket.getInputStream();
            OutputStream output = clientSocket.getOutputStream();
            int client = input.read();
            output.write(client * 5);
            long time = System.currentTimeMillis();
            /*output.write(("HTTP/1.1 200 OK\n\nWorkerRunnable: " +
                    this.serverText + " - " + time + " ").getBytes());*/
            output.flush();
            output.close();
            input.close();
            System.out.println("Request processed: " + time);
        } catch(IOException e) {
            e.printStackTrace();
        }
    }
}
