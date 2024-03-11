//Mikel Echarri 
//This code can only be run on Linux
//You first start the server.cpp, then the client.cpp, all the commands will be inputted via the client terminal

using namespace std;
#include <iostream>
#include <string>

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
//port
#define PORT 8081


bool isInt(const string& str)
{
    bool result = true;
    try
    {
        // Convert string to int
        int n = stoi(str);
    }
    catch (const invalid_argument& e)
    {
        result = false;
    }
    catch (const out_of_range& e)
    {
        result = false;
    }
    return result;
}


int main ( int argument, char const *argv[] )
{
    //items for connnection
    int obj_socket = 0, reader;
    //create address
    struct sockaddr_in serv_addr;
    //buffer for messaging
    char buffer[1024] = {0};
    //try socket creation
    if (( obj_socket = socket (AF_INET, SOCK_STREAM, 0 )) < 0)
    {
    printf ( "Socket creation error !" );
    return -1;
    }
    //types of sockets
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    // Converting IPv4 and IPv6 addresses from text to binary form
    if(inet_pton ( AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
    printf ( "\nInvalid address ! This IP Address is not supported !\n" );
    return -1;
    }
    //try connection over socket
    if ( connect( obj_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr )) < 0)
    {
    printf ( "Connection Failed : Can't establish a connection over this socket !" );
    return -1;
    }
    //startup
    printf ( "\nDigital Sum Client Started\n" );
    printf ( "\nServer Ip >> 127.0.0.1\n" );
    printf ( "\nServer Port >> 8081\n" );
    printf ( "\nEnter a number >> " );
    //digit
    std::string strtmp;
    //take in digit
    cin >> strtmp;

    if (isInt(strtmp))
    {
        
    }
    else
    {
        cout << "That isn't a number...\n";
        return 0;
    }
    //for the loop
    bool end = false;
    //string to char
    const char* numberr = strtmp.c_str();
    //send digit
    send ( obj_socket , numberr , strlen(numberr) , 0 );
    //wait for server response
    /*int waiting = 0;
    while(waiting==0) {
        //read for any messages 
        reader = read(obj_socket, buffer, 1024);
        //waiting for 1
        waiting = atoi(buffer);

    }*/
    //clear buffer
    memset(buffer, 0, sizeof(buffer));
    while(end==false) {
        //server is waiting create 1 string
        std::string strtmp = "1";
        //string to char
        const char* wait = strtmp.c_str();
        //send ok to server to continue
        //send ( obj_socket , wait , strlen(wait) , 0 );
        //reset buffer
        //memset(buffer, 0, sizeof(buffer));
        //read server info
        reader = read ( obj_socket, buffer, 1024 );
        
        //printf ( "%s\n",buffer );
        std::string trtmp;
        int ia = atoi(buffer);
        memset(buffer, 0, sizeof(buffer));
        //take in digit
        printf ( "\nEnter another number >> " );
        cin >> trtmp;

        if (isInt(trtmp))
        {
        
        }
        else
        {
            cout << "That isn't a number...\n";
            return 0;
        }

        const char* numberr = trtmp.c_str();
        //send digit
        send ( obj_socket , numberr , strlen(numberr) , 0 );

        reader = read ( obj_socket, buffer, 1024 );
        printf ( "%s\n",buffer );
        
        return 0;
        //check for error
        /*if (strcmp(buffer, "wrong") == 0) {
            printf("\nServer returned 'Not A Number error', Exiting Client Application\n");
            end = true;
            //end
            return 0; 
        }*/
        //print result
        //printf("Recieved digit sum result: ");
        
        //convert char to int
        
        //check if single digit
        /*if(ia<10) {
            printf("\nServer returned a single digit result, Exiting Client Application\n");
            end = true;
            //end
            return 0;
        }
        //continue summing
        else {
            printf("Sending %s to Digit Sum Server\n",buffer);
        }
        return 0;*/
    }
    //end
    
}