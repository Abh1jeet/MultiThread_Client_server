package Networking;

/**
 * Created by anas on 10/25/15.
 */
import java.net.*;
import java.io.*;
public class FirstClient {

    public static void main(String[] args) {
        Socket socket = null;
        try {
            socket = new Socket("localhost",9000);
            socket.setSoTimeout(15000);
            InputStream in = socket.getInputStream();
            OutputStream out = socket.getOutputStream();
            out.write(5);
            System.out.println(in.read());

            out.flush();
            out.close();
            in.close();
        } catch(IOException e) {
            System.err.println(e);
        }
    }
}
