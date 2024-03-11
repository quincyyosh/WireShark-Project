package com.journaldev.socket;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class client
{
    public static void main(String[] args) throws UnknownHostException, IOException, ClassNotFoundException, InterruptedException
    {
        Socket socket = null;
        ObjectOutputStream oos = null;
        ObjectInputStream ois = null;
        //for loop to loop code four times
        for(int i=1; i<5;i++)
        {
            socket = new Socket("127.0.0.1", 12345);
            oos = new ObjectOutputStream(socket.getOutputStream());
            System.out.println("Sending request to Socket Server");
            //since we start at 1, we only want 3 messages so the 4th time through
             //the communication between the server and client will end
            if(i==4)
            {
            	oos.writeObject("exit");
            }
            else
            {             
            	oos.writeObject(""+i);
        	}
            ois = new ObjectInputStream(socket.getInputStream());
            String message = (String) ois.readObject();
            //prints out 
            System.out.println("Message: " + message);
            ois.close();
            oos.close();
            Thread.sleep(100);
        }
    }
}