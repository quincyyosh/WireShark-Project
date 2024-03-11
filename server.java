package com.journaldev.socket;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.lang.ClassNotFoundException;
import java.net.ServerSocket;
import java.net.Socket;


public class server 
{    
    private static ServerSocket server;
    private static int port = 12345;
    
    public static void main(String args[]) throws IOException, ClassNotFoundException
    {
        //creates server
        server = new ServerSocket(port);
        while(true)
        {
            //waits for the client to connect to the server
            System.out.println("Waiting for the client request");
            Socket socket = server.accept();
            //if client never connects to the server then the program won't continue
            ObjectInputStream ois = new ObjectInputStream(socket.getInputStream());
            String message = (String) ois.readObject();
            //prints out message number starting at 1 and increasing one, for each message
            System.out.println("Message Received: " + message);
            ObjectOutputStream oos = new ObjectOutputStream(socket.getOutputStream());
            //message should match number from client
            oos.writeObject("Client "+message);
            ois.close();
            oos.close();
            socket.close();
            //after 3 steps of messages, code ends
            if(message.equalsIgnoreCase("exit")) break;
        }
        //shutsdown the socket and ends the code
        System.out.println("Shutting down Socket server!!");
        server.close();
    }
}